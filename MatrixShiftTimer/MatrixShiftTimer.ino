#include <avr/io.h>
#include <avr/interrupt.h>
#define COL PORTK
#define FILA PORTF
const int out[7]={1,2,4,8,16,32,64};
volatile int fila=0,col=0;
void setup() {
  DDRF=255;
  PORTF=1;  
  DDRK=255;
  PORTK=254;
  Serial.begin(9600);
  cli();                              //deshabilito temporalmente las interrupciones
  TCCR1A=0;                           //limpiamos los registros de control
  TCCR1B=0;                           //del timer 1

  OCR1A=1562;
  TCCR1B|=(1<<WGM12);
  TCCR1B|=(1<<CS10);
  TCCR1B|=(1<<CS12);
  
  
  TIMSK1|=(1<<OCIE1A);                  //enciendo el timer1
  
  sei();                              //activamos las interrupciones

}

void loop() {

}

ISR(TIMER1_COMPA_vect){                 //ISR es la rutina de interrupcion
  COL=~(1<<col);
  FILA=(1<<fila);
  if(col<5)col++;
  else{
    col=0;
    if(fila<6)fila++;
    else fila=0;
  }
}
