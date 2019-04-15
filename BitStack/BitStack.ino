/*Tarea:[FUNCIONA]
 * Hacer que se los leds se vayan apilando uno encima del otro
 * Agregar nuevas funciones y variables maybe?
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#define COL PORTK
#define FILA PORTF

//Variables de desplazamiento del jugador
const int nivel[6]={15,12,10,8,6,4};
volatile int ContadorDeNivel=0,nivelSelector=0;
volatile int pos=0;
volatile bool dir=0;
volatile int contShift=31;

//Variables de control de la matriz
bool hab[7][5]={
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0}
};
volatile int fila=0,col=0;

//Variables del boton y animacion de caida
volatile bool boton=0;
void Drop();
volatile int altura=6,caida=0;
volatile int contDrop=100;
volatile int place;

//Variables del juego
int rowCheck();

void setup() {
  DDRF=255;
  FILA=1;  
  DDRK=255;
  COL=254;
  Serial.begin(9600);
  cli();                  //deshabilito temporalmente las interrupciones
  TCCR1A=0;               //limpiamos los registros de control
  TCCR1B=0;               //del timer 1

  OCR1A=5;                //3 valor minimo, 5 se ve multiplexado en grabacion de 60fps, 8 valor maximo
  TCCR1B|=(1<<WGM12);     //Habilito el Comparador
  TCCR1B|=(1<<CS10);      //Ajusto el prescaler a 1024
  TCCR1B|=(1<<CS12);
  
  
  TIMSK1|=(1<<OCIE1A);    //enciendo el timer1

  EIMSK|=(1<<INT0);       //Habilito int0
  EICRA|=(1<<ISC01);  
  
  sei();                  //activamos las interrupciones

}

void loop() {

}

ISR(TIMER1_COMPA_vect){                 //ISR es la rutina de interrupcion
  //Funcion de caida
  if(boton){
  if(contDrop==0){  
    Drop();
    contDrop=100;
  }
  else contDrop--;
  }
  else{
    EIMSK|=(1<<INT0);
    //Desplazamiento del jugador
    if(contShift==0){
      if(rowCheck()==5){
        altura--;
        nivelSelector++;
        Serial.print("Fila: ");
        Serial.println(altura);        
        Serial.print("Nivel: ");
        Serial.println(nivelSelector);
      }
      ContadorDeNivel++;                //Se aumenta el contador de Shifteo
      if(ContadorDeNivel>=nivel[nivelSelector]){    //Si matchea con la velocidad del nivel correspondiente
        hab[0][pos]=0;                  //Luego de hacer la suma o resta correspondiente se muestra la posicion en la matriz
        if(dir){                        //Depende la direccion 
          if(pos>0)pos--;               //Se baja el valor de pos(columna de posicion) del jugador moviendolo a la izquierda
          else dir=0;                   //Cuando llega a 0 se invierte dir
        }
        else{
          if(pos<4)pos++;               //Se aumenta el valor de pos(columna de posicion) del jugador moviendolo a la derecha
          else dir=1;                   //Cuando llega a 4 se invierte dir
        }
        hab[0][pos]=1;                  //Luego de hacer la suma o resta correspondiente se muestra la posicion en la matriz
        ContadorDeNivel=0;              //Y se resetea el contador de Shifteo
      }
      contShift=31;
    }
    else contShift--;
  }
  //Multiplexado de la matriz
  if(hab[fila][col])
  COL=~(1<<col);
  else COL=~(0<<col);
  FILA=(1<<fila);
  if(col<5)col++;
  else{
    col=0;
    if(fila<7)fila++;
    else fila=0;
  }
}
ISR(INT0_vect){
  EIMSK&=(0<<INT0);
  place=pos;
  boton=true;
}

void Drop(){
  hab[caida][place]=0;
  if(caida!=altura)
    caida++;
  else{
    hab[altura][place]=1;
    caida=0;
    boton=false;      
  }
  hab[caida][place]=1;

}

int rowCheck(){
  int i;
  int full=0;
  for(i=0;i<5;i++){
    if(hab[altura][i])full++;
  }
  return full;
}
