#define COL PORTK
#define FILA PORTF

const int out[7]={1,2,4,8,16,32,64};
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

  OCR1A=5;            //3 valor minimo, 5 se ve multiplexado en grabacion de 60fps, 8 valor maximo
  TCCR1B|=(1<<WGM12);
  TCCR1B|=(1<<CS10);
  TCCR1B|=(1<<CS12);
  
  
  TIMSK1|=(1<<OCIE1A);                  //enciendo el timer1
  
  sei();                              //activamos las interrupciones

}

void loop() {
  Blink();
  VerticalClean();
  FillingUp();
  HorizontalClean();
  Full();
}

ISR(TIMER1_COMPA_vect){                 //ISR es la rutina de interrupcion
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

void VerticalClean(){
  int i;
  for(i=0;i<7;i++){
    VerticalEdit(i,0);
    delay(100);
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
  int i;
  for(i=0;i<5;i++){
    HorizontalEdit(i,0);
    delay(100);
  }
}

void Blink(){
  int i;
  for(i=0;i<4;i++){
    Clear();
    delay(100);
    Full();
    delay(100);
  }
}
