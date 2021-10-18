NOMBRE :: GABRIEL SEBASTIÁN ORTIZ ÁNGEL
ROL    :: 202073535-2

Detalles de Compilacion:
Para compilar el programa utilice el comando 'make exec'
en la consola, y para correrlo use './exec'. Además para
testeos con Valgrind se usó 'valgrind --leak-check=yes ./exec'

Comentarios sobre el código:
Se agregó el parametro "coordenadas" al struct para obtener las coordenadas
comodamente, al colocarse en las matrices se colocan del modo (y,x).
Ademas se agregó a Animal.h la función TraductorValores para facilitar la conversion
a int. Por ultimo se agregaron los archivos Mundo.h y Mundo.c, donde se controla
toda la simulación para las matrices, tanto la del Mundo como la auxiliar.