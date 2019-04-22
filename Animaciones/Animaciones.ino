#define COL PORTK
#define FILA PORTF

bool hab[7][5]={
{1,1,1,1,1},
{1,1,1,1,1},
{1,1,1,1,1},
{1,1,1,1,1},
{1,1,1,1,1},
{1,1,1,1,1},
{1,1,1,1,1}
};
volatile int fila=0,col=0;

volatile int c_animation=0,animate=0,i=0;

void VerticalEdit(int y,bool value);
void HorizontalEdit(int x,bool value);
void Clear();
void Full();
void VerticalClean();
void HorizontalClean();
void FillingUp();
void Blink();

void setup() {
 
  DDRF=255;
  FILA=1;  
  DDRK=255;
  COL=255;
  Serial.begin(9600);
  cli();                              //deshabilito temporalmente las interrupciones
  TCCR1A=0;                           //limpiamos los registros de control
  TCCR1B=0;                           //del timer 1

  OCR1A=3;            //3 valor minimo, 5 se ve multiplexado en grabacion de 60fps, 8 valor maximo
  TCCR1B|=(1<<WGM12);
  TCCR1B|=(1<<CS10);
  TCCR1B|=(1<<CS12);
  
  
  TIMSK1|=(1<<OCIE1A);                  //enciendo el timer1
  
  sei();                              //activamos las interrupciones

}

void loop() {

}

ISR(TIMER1_COMPA_vect){                 //ISR es la rutina de interrupcion
  switch(animate){
    case 0:
      if(c_animation<512)c_animation++;
      else{
        Blink();
        c_animation=0;
      }
      break;
    case 1:
      if(c_animation<512)c_animation++;
      else{
        VerticalClean();
        c_animation=0;
      }
      break;
    case 2:
      if(c_animation<512)c_animation++;
      else{
        HorizontalClean();
        c_animation=0;
      }
      break;
    default: break;
  }
  if(hab[fila][col])
  COL=~(1<<col);
  else COL=~(0<<col);
  FILA=(1<<fila);
  if(col<5)col++;
  else{
    col=0;
    if(fila<6)fila++;
    else fila=0;
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

void FillingUp(){
  int i,j;
  for(i=7;i>=0;i--){
    for(j=0;j<5;j++){
      hab[i][j]=1;
      delay(50);
    }
  }
}

void Full(){
  int i;
  for(i=0;i<5;i++){
    HorizontalEdit(i,1);
  }
}

void HorizontalClean(){
  if(i<5){
    HorizontalEdit(i,0);
    i++;
  }
  else{
    animate=0;
    i=0;
    Full();
  }
}

void VerticalClean(){
  if(i<7){
    VerticalEdit(i,0);
    i++;
  }
  else{
    animate=2;
    i=0;
    Full(); //Se vuelve a llenar la matriz solo para probar COMENTAR LINEA
  }
}

void Blink(){
  if(i<8){
    if(i%2)
    Clear();
    else Full();
    i++;
  }
  else{
    animate=1;
    i=0;
    Full(); //Se vuelve a llenar la matriz solo para probar COMENTAR LINEA
  }
}
