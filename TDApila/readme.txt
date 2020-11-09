Este TDA basicamente tiene la funcion de realizar varias primitivas sobre una estructura denominada pila
cada una de estas primitivas, es una funcion que se le aplica a la pila para poder hacer asi la accion
que el usuario requiera.

Ademas del TDA se implemento una serie de pruebas para revisar si las primitivas creadas funcionan de una
manera correcta o al menos como deberian.
Como programador de este TDA me tome la licencia de realizar pruebas sobre como se redimensiona la pila
utilizando asi el tamaño almancenado en la estructura pila. Esto me permite ver si una de las funciones
creada en mi biblioteca my_pila funciona como deberia.
El resto de las funciones cumplen con la practica de no saber lo que hay dentro de la pila

la linea de compilacion para este TDA es la siguiente:
gcc *.c -o pila_vd -g -std=c99 -Wall -Wconversion -pedantic -Werror -O0

y esto nos generara un archivo llamado pila_vd que podemos ejecutarlo de dos maneras:

1) si solo queremos ver como funciona:
./pila_vd

2) si queremos ver si no estamos perdiendo memoria y demas incovenientes que no podemos ver solo con
la anterior linea de ejecucion podemos utilizar valgrind con la siguiente linea:
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pila_vd