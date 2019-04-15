/*FUNCIONA!!!!!
 * La idea es utilizar la matriz boolean para realizar el desplazamiento
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#define COL PORTK
#define FILA PORTF

//Variables de desplazamiento del jugador
const int nivel[5]={15,12,10,8,6};
volatile int ContadorDeNivel=0;
volatile int pos=0;
volatile bool dir=0;
volatile int contShift=31;

//Variables de control de la matriz
bool hab[7][5]={
{0,0,0,0,0},
{1,1,1,1,1},
{1,0,0,0,1},
{1,1,1,1,1},
{1,0,0,0,1},
{1,0,0,0,1},
{1,0,0,0,1}
};
volatile int fila=0,col=0;

void setup() {
  DDRF=255;
  FILA=1;  
  DDRK=255;
  COL=254;
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

}

ISR(TIMER1_COMPA_vect){                 //ISR es la rutina de interrupcion

  if(contShift==0){
//    Serial.print("Contador de nivel= ");
//    Serial.println(ContadorDeNivel);
    ContadorDeNivel++;                //Se aumenta el contador de Shifteo
    if(ContadorDeNivel==nivel[4]){    //Si matchea con la velocidad del nivel correspondiente
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
