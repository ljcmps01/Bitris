# Bitris
Proyecto de instalaciones industriales
Se trata de un juego el cual consta de controlar los leds de una matriz con un boton, la matriz desplazará un bit de izquierda a derecha 
en la fila superior, el jugador tendrá un boton que al presionarlo dejará caer el bit al fondo de la matriz.
El objetivo del juego es que el jugador llene todas las filas de la matriz pero siempre una fila a la vez; si el jugador comienza a apilar
La siguiente fila sin haber completado la que se encuentra, perderá una vida, a medida que vaya llenando las filas el juego se volverá mas
veloz.

Changelog:
28-03 Funcionamiento de la matriz (delay)
10-04 Control de la matriz (Habilitacion de que leds prender)
11-04 Funcionamiento de la matriz (TIMER)
12-04 Multiplexado de la matriz (Prescaler a 1024 con OCR1A=3,5,8
12-04 Control de velocidad de niveles y desplazamiento del jugador
12-04 Deteccion del boton del jugador y animacion de caida (velocidad constante)
13-04 1er ensamble: Multiplexado+Desplazamiento+boton+caida
13-04 Se agrega la capacidad de mantener el led prendido en el fondo tras realizar la animacion de caida
13-04 Se le agrega control de vida y nivel (La vida es solo visual y no afecta el juego todavia