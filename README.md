# Bitris
Proyecto de instalaciones industriales
Se trata de un juego el cual consta de controlar los leds de una matriz con un boton, la matriz desplazará un bit de izquierda a derecha 
en la fila superior, el jugador tendrá un boton que al presionarlo dejará caer el bit al fondo de la matriz.
El objetivo del juego es que el jugador llene todas las filas de la matriz pero siempre una fila a la vez; si el jugador comienza a apilar
La siguiente fila sin haber completado la que se encuentra, perderá una vida, a medida que vaya llenando las filas el juego se volverá mas
veloz.

## Changelog:

_28-03 Funcionamiento de la matriz (delay)_

_10-04 Control de la matriz (Habilitacion de que leds prender)_

_11-04 Funcionamiento de la matriz (TIMER)_

_12-04 Multiplexado de la matriz (Prescaler a 1024 con OCR1A=3,5,8)_

_12-04 Control de velocidad de niveles y desplazamiento del jugador_

_12-04 Deteccion del boton del jugador y animacion de caida (velocidad constante)_

_13-04 1er ensamble: Multiplexado+Desplazamiento+boton+caida_

_13-04 Se agrega la capacidad de mantener el led prendido en el fondo tras realizar la animacion de caida_

_13-04 Se le agrega control de vida y nivel (La vida es solo visual y no afecta el juego todavia)_

_17/04 Se creó programa con animaciones basicas, horizontales y verticales_

_17/04 El boton da inicio al primer juego, se agregó animación cuando se pierde y reinicio con el boton_

~~**[Arreglar falso inicio]**~~

_22/04 VerticalClean, HorizontalClean, Blink pasadas a TIMER_

_23/04 animacion de FillUp pasada a TIMER_

_23/04 Renovacion de Bitris con animaciones de inicio, perdida y victoria (En timer), Falso inicio arreglado_

_23/04 Definiciones Globales del juego_

---------------**FIN DEL CUERPO PRINCIPAL**----------------

_24/04 Creado programa de Display de vida y nivel con CD4511_

_24/04 Acoplado el control de displays al programa principal_

_30/07 Realizado programa para Arduino UNO_

_30/07 Realizado PCB de placa principal_

_13/08 Realizado PCB de placa displays_

_16/08 Adjuntado informe del proyecto_

_19/08 Agregado Diseño 3D del gabinete_

_03/09 Arreglo de diseño de PCB principal_


## Bugs/Trabajo por hacer:

### Software 

* **LED fantasma**

* **Doble pulsacion**

* Agregar sonido

### Hardware 

* Diseñar amplificador (SCH Y PCB)

* Montar placas

## Creadores

Alejo Rodrigo Campos (@ljcmps01):

* -_Primer programa de control Arduino MEGA_-

* -_Primer diseño SCH y PCB_-


Alex Obregon (@alobre4148):

* -_Programa compatible Arduino UNO_ (Programa a utilizar para producto final)-

* -_Diseño PCB final placa principal_-