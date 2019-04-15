#include <avr/io.h>
#include <avr/interrupt.h>
#define COL PORTK
#define FILA PORTF

const int nivel[5]={15,12,10,8,6};
volatile int ContadorDeNivel=0;
volatile int fila=0,col=0,altura=7;
volatile bool dir=0;
volatile bool button=0;

void Drop();

void setup() {
  DDRF=255;
  FILA=1;  
  DDRK=255;
  COL=254;
  PORTD=255;
  DDRD=0;
  Serial.begin(9600);
  cli();                              //deshabilito temporalmente las interrupciones
  EIMSK|=(1<<INT0);
  EICRA|=(1<<ISC01);
  TCCR1A=0;                           //limpiamos los registros de control
  TCCR1B=0;                           //del timer 1

//OCR1A=1562;//Este valor es de prueba para arreglar el desplazamiento
  OCR1A=156;
  TCCR1B|=(1<<WGM12);
  TCCR1B|=(1<<CS10);
  TCCR1B|=(1<<CS12);
  
  
  TIMSK1|=(1<<OCIE1A);                  //enciendo el timer1
  
  sei();                              //activamos las interrupciones

}

void loop() {

}

ISR(TIMER1_COMPA_vect){                 //ISR es la rutina de interrupcion
  if (button)
      Drop();
  else{
    if(ContadorDeNivel==nivel[4]){
        FILA=1;
        if(dir){
          Serial.println("izquierda");
        if(col>0)col--;
        else dir=0;
          Serial.println(col);
        }
        else{
          Serial.println("derecha");
          if(col<4)col++;
          else dir=1;  
          Serial.println(col);
        }
        COL=~(1<<col);
        
        ContadorDeNivel=0;
        EIMSK|=(1<<INT0);
    }
    ContadorDeNivel++;
  }
}

ISR(INT0_vect){
  EIMSK&=(0<<INT0);
  button=true;
  Serial.println("Interrupcion");
}

void Drop(){
  int place=col;
  Serial.println("Drop");
  COL=~(1<<place);
  FILA|=(1<<fila);
  if(fila!=altura)
    fila++;
  else{
    fila=0;
    button=false;
        
  }
}
