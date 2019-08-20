#include <avr/interrupt.h>
#define COL PORTK
#define PLAYER PORTB

const int nivel[5]={15,12,10,8,6};
volatile int ContadorDeNivel=0;
volatile int pos=0;
volatile bool dir=0;

void setup() {
  DDRB=255;
  PLAYER=128;  
  DDRK=255;
  COL=254;
  Serial.begin(9600);
  cli();                              //deshabilito temporalmente las interrupciones
  TCCR3A=0;                           //limpiamos los registros de control
  TCCR3B=0;                           //del timer 1

//OCR3A=1562;//Este valor es de prueba para arreglar el desplazamiento
  OCR3A=156;
  TCCR3B|=(1<<WGM12);
  TCCR3B|=(1<<CS10);
  TCCR3B|=(1<<CS12);
  
  
  TIMSK3|=(1<<OCIE3A);                  //enciendo el timer1
  
  sei();                              //activamos las interrupciones

}

void loop() {

}

ISR(TIMER3_COMPA_vect){             //Funcion de Shift
  ContadorDeNivel++;                //Se aumenta el contador de Shifteo
  if(ContadorDeNivel==nivel[0]){    //Si matchea con la velocidad del nivel correspondiente
    PLAYER|=128;                        //Se prende la primer fila de la matriz (fila del jugador)
    if(dir){                        //Depende la direccion 
      Serial.println("izquierda");
      if(pos>0)pos--;               //Se baja el valor de pos(columna de posicion) del jugador moviendolo a la izquierda
      else dir=0;                   //Cuando llega a 0 se invierte dir
      Serial.println(pos);
    }
    else{
      Serial.println("derecha");
      if(pos<4)pos++;               //Se aumenta el valor de pos(columna de posicion) del jugador moviendolo a la derecha
      else dir=1;                   //Cuando llega a 4 se invierte dir
      Serial.println(pos);
    }
    COL=~(1<<pos);                  //Luego de hacer la suma o resta correspondiente se muestra la posicion en la matriz
    ContadorDeNivel=0;              //Y se resetea el contador de Shifteo
  }
}
