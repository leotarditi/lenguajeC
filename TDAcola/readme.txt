Este TDA basicamente tiene la funcion de realizar varias primitivas sobre una estructura denominada cola
cada una de estas primitivas, es una funcion que se le aplica a la cola para poder hacer asi la accion
que el usuario requiera.

Ademas del TDA se implemento una serie de pruebas para revisar si las primitivas creadas funcionan de una
manera correcta o al menos como deberian.

la linea de compilacion para este TDA es la siguiente:
gcc *.c -o cola_ne -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

y esto nos generara un archivo llamado cola_ne que podemos ejecutarlo de dos maneras:

1) si solo queremos ver como funciona:
./cola_ne

2) si queremos ver si no estamos perdiendo memoria y demas incovenientes que no podemos ver solo con
la anterior linea de ejecucion podemos utilizar valgrind con la siguiente linea:
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./cola_ne

El resultado esperado de las pruebas corrido con valgrind es el siguiente:

==3072== Memcheck, a memory error detector
==3072== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==3072== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==3072== Command: ./cola_ne
==3072== 
Encolo el elemento 1
Encolo el elemento 2
Encolo el elemento 3
Encolo el elemento 4
La cola tiene 4 elementos
Desencolo un elemento
¿La cola está vacía?: NO
El primer elemento de la cola es: 2




Prueba de cola vacia: APROBADA
Prueba de encolar una letra: APROBADA
Prueba de cola no vacia: APROBADA
Prueba de cantidad con un elemento apilado: APROBADA
El primer elemento de la cola es el esperado: APROBADA
Prueba desencola un elemento: APROBADA
Prueba cola vacia: APROBADA
cola sin elementos: APROBADA
El primer elemento es NULL: APROBADA
Prueba de desencolar cola vacia: APROBADA

El primer elemento es el esperado: APROBADA
Prueba cola no vacia: APROBADA
Prueba 100 elementos encolados: APROBADA


El primer elemento es NULL: APROBADA
Prueba 1: OK





Prueba cola vacia: APROBADA
Cola sin elementos: APROBADA
El primero es NULL: APROBADA
Prueba de desencolar cola vacia: APROBADA
Prueba 2: OK





Prueba cola vacia: APROBADA
Prueba encola un elemento: APROBADA
Prueba cola con un elemento: APROBADA
Prueba cantidad con un elemento apilado: APROBADA
El primer es el elemento apilado: APROBADA
Prueba encolar un elemento: APROBADA
Prueba encolar un elemento: APROBADA
Prueba cola con elementos: APROBADA
Prueba cantidad de elementos esperados: APROBADA
Prueba desencolar un elemento: APROBADA
Prueba desencolar un elemento: APROBADA
Se desencolar el ultimo elemento de la cola: APROBADA
Prueba cola vacia: APROBADA
Cola sin elementos: APROBADA
el primer elemento es NULL: APROBADA
Prueba desencolar pila vacia: APROBADA
Prueba 3: OK





Prueba encolar 300k: APROBADA
Prueba desencolar 300k: APROBADA
Prueba encolar 200k: APROBADA
Prueba desencolar 200k: APROBADA
Prueba con encolar 100k: APROBADA
Prueba desencolar 100k: APROBADA
prueba 4: OK





Prueba encolar cola NULL: APROBADA
Prueba desencolar cola NULL: APROBADA
Prueba cola vacia: APROBADA
Prueba cantidad en cola NULL: APROBADA
El primer elemento es NULL: APROBADA
prueba 5: OK






Pruebas pasadas 6/6 
==3072== 
==3072== HEAP SUMMARY:
==3072==     in use at exit: 0 bytes in 0 blocks
==3072==   total heap usage: 600,114 allocs, 600,114 frees, 9,602,872 bytes allocated
==3072== 
==3072== All heap blocks were freed -- no leaks are possible
==3072== 
==3072== For counts of detected and suppressed errors, rerun with: -v
==3072== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)