/*Adiciones:
 * Definiciones Globales para configuracion facil del juego
 */
#define DISPLAY PORTC
#define COL PORTD
#define FILA PORTB

#define VIDAS 9
#define AlturaDeMatriz 5  //Uno menos que el valor real
#define AnchoDeMatriz 3   //Uno menos que el valor real
#define AnimacionVelocidad 500

//Variables del display
volatile bool Multiplex=0;
byte Aux1=0,Aux2=0;

//Variables de desplazamiento del jugador
const int nivel[6]={15,12,10,8,6,4};    //Vector que regula la velocidad del juego
volatile int ContadorDeNivel=0,nivelSelector=0;
volatile int pos=0;                     //Variable que controla la posicion del jugador
volatile bool dir=0;                    //Variable que controla la direccion del jugador
volatile int contShift=31;

//Variables de control de la matriz
bool hab[6][4]={      //Esquema digital de la matriz
{0,0,0,0},          //Controla que leds se prenden
{0,0,0,0},
{0,0,0,0},
{0,0,0,0},
{0,0,0,0},
{0,0,0,0}
};
volatile int fila=0,col=0;  //Variable que controla que posicion de la matriz verificar

//Variables del boton y animacion de caida
volatile bool boton=0;
void Drop();
volatile int altura,caida=0;
volatile int contDrop=100;
volatile int place;

//Variables del juego
int rowCheck();       //Funcion que checkea cuantos espacios libres quedan en una fila
volatile int vida;  //Variable que controla las vidas del jugador
volatile bool game=0,start=0,lost=0,win=0;  //Game habilita el funcionamiento del juego, 
                                      //start le da comienzo
                                      //Lost indica que se perdió

//animaciones
void VerticalEdit(int y,bool value);  //Edita columnas
void HorizontalEdit(int x,bool value);//Edita filas
void Clear();                         //Limpia la matriz completamente
void VerticalClean();                 //Hace un barrido vertical
void HorizontalClean();               //Barrido Horizontal
void FillingUp();                     //Llenado de izquierda a derecha
void Blink();                         //Parpadeos
volatile int c_animation=0,animate=0,i=0,j=0;

void setup() {
  DDRB=63;
  FILA=1;  
  DDRC|=0B0111111;
  COL=80;
  DDRD|=0b11110000;
  Serial.begin(9600);
  cli();                  //deshabilito temporalmente las interrupciones
  TCCR1A=0;               //limpiamos los registros de control
  TCCR1B=0;               //del timer 1

  OCR1A=3;                //3 valor minimo, 5 se ve multiplexado en grabacion de 60fps, 8 valor maximo
  TCCR1B|=(1<<WGM12);     //Habilito el Comparador
  TCCR1B|=(1<<CS10);      //Ajusto el prescaler a 1024
  TCCR1B|=(1<<CS12);
  
  
  TIMSK1|=(1<<OCIE1A);    //enciendo el timer1

  EIMSK|=(1<<INT0);       //Habilito int0
  EICRA|=(1<<ISC01);  
  
  sei();                  //activamos las interrupciones
  PORTD=0;
  PORTD|=(1<<2);
}

void loop() {
}

ISR(TIMER1_COMPA_vect){                 //ISR es la rutina de interrupcion
  if(start){
    switch(animate){
    case 0:
    
      if(c_animation<AnimacionVelocidad)c_animation++;
      else{
        Blink();
        c_animation=0;
      }
      break;
    case 1:
      if(c_animation<AnimacionVelocidad)c_animation++;
      else{
        VerticalClean();
        c_animation=0;
      }
      break;
    case 2:
      if(c_animation<(AnimacionVelocidad/2))c_animation++;
      else{
        HorizontalClean();
        c_animation=0;
      }
      break;
    case 3:
      if(c_animation<(AnimacionVelocidad/100))c_animation++;
      else{
        FillingUp();
        c_animation=0;
      }
      break;
    default: 
      //Funcion de caida
      if(boton){
      if(contDrop==0){  
        Drop();
        contDrop=100;
      }
      else contDrop--;
      }
      else{
        
        //Desplazamiento del jugador
        if(contShift==0){
          rowCheck();
          ContadorDeNivel++;                //Se aumenta el contador de Shifteo
          if(ContadorDeNivel>=nivel[nivelSelector]){    //Si matchea con la velocidad del nivel correspondiente
            hab[0][pos]=0;                  //Luego de hacer la suma o resta correspondiente se muestra la posicion en la matriz
            if(dir){                        //Depende la direccion 
              if(pos>0)pos--;               //Se baja el valor de pos(columna de posicion) del jugador moviendolo a la izquierda
              else dir=0;                   //Cuando llega a 0 se invierte dir
            }
            else{
              if(pos<AnchoDeMatriz)pos++;               //Se aumenta el valor de pos(columna de posicion) del jugador moviendolo a la derecha
              else dir=1;                   //Cuando llega a 4 se invierte dir
            }
            hab[0][pos]=1;                  //Luego de hacer la suma o resta correspondiente se muestra la posicion en la matriz
            ContadorDeNivel=0;              //Y se resetea el contador de Shifteo
          }
          contShift=31;
        }
        else contShift--;
      }
      break;
    }
    }
      if(Multiplex){
        DISPLAY&=~(1<<4);
        DISPLAY&=~15;
        DISPLAY|=nivelSelector;
        Aux1=nivelSelector&0b00000010;
        Aux2=nivelSelector&0b00001000;
        if(Aux1==2){
        DISPLAY|=(1<<PC3);
        }
        else{
        DISPLAY&=~(1<<PC3);
        }
        if(Aux2==8){
        DISPLAY|=(1<<PC1);
        }
        else{
        DISPLAY&=~(1<<PC1);
        }
        DISPLAY|=(1<<5);
        Multiplex=!Multiplex;
      }
      else{
        DISPLAY&=~(1<<5);
        DISPLAY&=~15;
        DISPLAY|=vida;
        Aux1=vida&0b00000010;
        Aux2=vida&0b00001000;
        if(Aux1==2){
        DISPLAY|=(1<<PC3);
        }
        else{
        DISPLAY&=~(1<<PC3);
        }
        if(Aux2==8){
        DISPLAY|=(1<<PC1);
        }
        else{
        DISPLAY&=~(1<<PC1);
        }
        DISPLAY|=(1<<4);
        Multiplex=!Multiplex;
      }
     // Serial.println(PORTC);
    //Multiplexado de la matriz
    if(hab[fila][col]){
      COL|=(15<<4);
      COL&=~(1<<col+4);
      FILA=(1<<fila);
    }
    else{
      COL|=(15<<4);
      FILA=(0<<fila);
    }
    if(col<=AnchoDeMatriz)col++;
    else{
      col=0;
      if(fila<=AlturaDeMatriz)fila++;
      else fila=0;
    }
}


ISR(INT0_vect){
  if(!start){
    win=0;
    pos=0;
    vida=VIDAS;
    fila=0;
    col=0;
    altura=AlturaDeMatriz;
    nivelSelector=0;
    Clear();
    animate=0;
    //Funcion de vacio de la matriz
    start=1;
    Serial.println("Comienza");
  }
  if(game){
  EIMSK&=(0<<INT0);
  place=pos;
  if(hab[altura][place]){
    vida--;
    Serial.print("Te quedan: ");
    Serial.print(vida);
    Serial.println(" vidas");
    if(vida<=0){
      Serial.println("PERDISTE");
      //TIMSK1&=(0<<OCIE1A);//Se podria deshabilitar el TIMER1 para detener el juego pero se espera agregar animaciones mejor
      VerticalEdit(0,0);
      i=altura;
      lost=1;
      animate=1;
    }
  }
  boton=true;
  }
}

void Drop(){
  hab[caida][place]=0;
  if(caida!=altura)
    caida++;
  else{
    hab[altura][place]=1;
    caida=0;
    boton=false;  
    EIMSK|=(1<<INT0);    
  }
  hab[caida][place]=1;
  
}

int rowCheck(){
  int i;
  int full=0;
  for(i=0;i<AnchoDeMatriz+1;i++){
    if(hab[altura][i])full++;
  }
  if(full==AnchoDeMatriz+1){
    altura--;
    if(altura){
      nivelSelector++;
      Serial.print("Fila: ");
      Serial.println(altura);        
      Serial.print("Nivel: ");
      Serial.println(nivelSelector);
    }
    else{
      Clear();
      game=0;
      animate=3;
      win=1;
    }
  }
}

void VerticalEdit(int y,bool value){
  int i;
  for(i=0;i<5;i++){
    hab[y][i]=value;
  }
}

void HorizontalEdit(int x,bool value){
  int i;
  for(i=0;i<7;i++){
    hab[i][x]=value;
  }
}

void Clear(){
  int i;
  for(i=0;i<5;i++){
    HorizontalEdit(i,0);
  }
}

void Full(){  
  int i;
  for(i=0;i<5;i++){
    HorizontalEdit(i,1);
  }
}

void FillingUp(){ //animate=3
  if(i<7){
    if(j<5){
      hab[6-i][j]=1;
      j++;
    }
    else{
      j=0;
      i++;
    }
    
  }
  else{
    i=0;
    animate=0;
  }
}

void HorizontalClean(){//animate=2
  if(i<5){
    HorizontalEdit(i,0);
    i++;
  }
  else{
    animate=4;
    i=0;
    game=1;
//    Full();
  }
}

void VerticalClean(){//animate=1
  if(i<7){
    VerticalEdit(i,0);
    i++;
  }
  else{
    animate=5;
    i=0;
    if(lost){
      start=0;
      game=0;
      boton=false;
      EIMSK|=(1<<INT0);
      }
  }
}

void Blink(){       //animate=0
  if(i<8){
    if(i%2)
    Clear();
    else Full();
    i++;
  }
  else{
    if(!win){
    animate=2;    
    Full(); //Se vuelve a llenar la matriz solo para probar COMENTAR LINEA
    }
    else {
      start=0;
    }
    i=0;
  }
}
