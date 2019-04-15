#define COL PORTK
#define FILA PORTF
const int out[7]={1,2,4,8,16,32,64};
volatile int fila=0,col=0;

void setup()
{
  DDRF=255;
  PORTF=1;  
  DDRK=255;
  PORTK=254;
  // initialize timer1 
  cli();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 34286;            // preload timer 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  sei();             // enable all interrupts
}

ISR(TIMER1_OVF_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  TCNT1 = 34286;            // preload timer
  COL=~(1<<col);
  FILA=(1<<fila);
  if(col<5)col++;
  else{
    col=0;
    if(fila<7)fila++;
    else fila=0;
  }
}

void loop()
{
  // your program here...
}
