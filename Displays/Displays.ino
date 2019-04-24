/*Este programa esta dedicado al control de los displays de nivel y vida
 * Primer version: Control y multiplexado de los displays
 */

volatile bool Multiplex=0;
volatile int nivel=0;
volatile int vida=0;

 void setup() {
  DDRF=255;
  DDRK=255;
  Serial.begin(9600);
  cli();                              //deshabilito temporalmente las interrupciones
  TCCR1A=0;                           //limpiamos los registros de control
  TCCR1B=0;                           //del timer 1

  OCR1A=5;
  TCCR1B|=(1<<WGM12);
  TCCR1B|=(1<<CS10);
  TCCR1B|=(1<<CS12);
  
  
  TIMSK1|=(1<<OCIE1A);                  //enciendo el timer1
  
  sei();                              //activamos las interrupciones
  PORTF=8;
  PORTK=0;
}

void loop() {
  delay(100);
  if(nivel<6)nivel++;
  else{
    nivel=0;
    if(vida<9)vida++;
    else vida=0;
  }
}

ISR(TIMER1_COMPA_vect){                 //ISR es la rutina de interrupcion
  Multiplex=!Multiplex;
  if(Multiplex){
    PORTF=nivel;
    
    PORTF&=~(1<<7);
    PORTF|=(1<<6);
  }
  else{
    PORTF=vida;
    
    PORTF&=~(1<<6);
    PORTF|=(1<<7);
  }
}
