Este TDA basicamente tiene la funcion de realizar varias primitivas sobre una estructura denominada arbol
cada una de estas primitivas, es una funcion que se le aplica al arbol para poder hacer asi la accion
que el usuario requiera.

Ademas del TDA se implemento una serie de pruebas para revisar si las primitivas creadas funcionan de una
manera correcta o al menos como deberian. (sera explicado cada una al final del archivo)

la linea de compilacion para este TDA es la siguiente:
gcc *.c -o abb -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

y esto nos generara un archivo llamado abb que podemos ejecutarlo de dos maneras:

1) si solo queremos ver como funciona:
./abb

2) si queremos ver si no estamos perdiendo memoria y demas incovenientes que no podemos ver solo con
la anterior linea de ejecucion podemos utilizar valgrind con la siguiente linea:
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb

El resultado esperado de las pruebas corrido con valgrind es el siguiente:

==2171== Memcheck, a memory error detector
==2171== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2171== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==2171== Command: ./abb
==2171== 
El nodo raiz deberia ser 4: SI
Busco el elemento 5: SI
Borro nodo hoja (7): SI
Borro nodo con un hijo (6): SI
Borro nodo con dos hijos (2): SI
Borro la raiz (4): SI
Busco el elemento (3): SI
Recorrido inorden (deberian salir en orden 1 3 5): 1 3 5 


Inserto mas valores y pruebo el iterador interno

Recorrido inorden iterador interno: 0 1 3 4 5 7 9 15 
Recorrido preorden iterador interno: 3 1 0 5 4 15 9 7 
Recorrido postorden iterador interno: 0 1 4 7 9 15 5 3 

Recorrido inorden hasta encontrar el 5: 0 1 3 4 5 
Recorrido preorden hasta encontrar el 5: 3 1 0 5 
Recorrido postorden hasta encontrar el 5: 0 1 4 7 9 15 5 

Recorrido inorden acumulando los valores: 0 1 4 8 13 20 29 44 
Recorrido preorden acumulando los valores: 3 4 4 9 13 28 37 44 
Recorrido postorden acumulando los valores: 0 1 5 12 21 36 41 44 




Prueba de insertar con arbol NULL: APROBADO
Prueba de borrar con arbol NULL: APROBADO
Prueba de buscar en arbol NULL: APROBADO
Prueba la raiz de arbol NULL: APROBADO
Arbol NULL esta vacio: APROBADO
Prueba 1: OK



Prueba de borrar con arbol vacio: APROBADO
Prueba de buscar en arbol vacio: APROBADO
Prueba de raiz con arbol vacio: APROBADO
Prueba si el arbol esta vacio: APROBADO
Prueba 2: OK



Prueba arbol vacio: APROBADO
Prueba insertar un elemento: APROBADO
Prueba insertar un elemento: APROBADO
Prueba insertar un elemento: APROBADO
Prueba insertar un elemento: APROBADO
Prueba insertar un elemento: APROBADO
Prueba insertar un elemento: APROBADO
Prueba insertar un elemento: APROBADO
Prueba arbol con elementos: APROBADO
Imprime el recorrido inorden (5 10 15 25 26 30 35):  5  10  15  25  26  30  35 
Imprime el recorrido postorden (5 15 10 26 35 30 25):  5  15  10  26  35  30  25 
Imprime el recorrido preorden (25 10 5 15 30 26 35):  25  10  5  15  30  26  35 
La Raiz es la esperada (25): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
La Raiz es la esperada (15): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
La Raiz es la esperada (10): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
La Raiz es la esperada (5): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
La Raiz es la esperada (30): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
Prueba 3: OK



Prueba arbol vacio: APROBADO
Prueba insertar un elemento: APROBADO
Prueba insertar un elemento: APROBADO
Prueba insertar un elemento: APROBADO
Prueba insertar un elemento: APROBADO
Prueba insertar un elemento: APROBADO
Prueba insertar un elemento: APROBADO
Prueba insertar un elemento: APROBADO
Prueba arbol con elementos: APROBADO
Imprime el recorrido inorden (b d f h k q x):  b  d  f  h  k  q  x 
Imprime el recorrido postorden (b f d k x q h):  b  f  d  k  x  q  h 
Imprime el recorrido preorden (h d b f q k x):  h  d  b  f  q  k  x 
La Raiz es la esperada (h): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
La Raiz es la esperada (f): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
La Raiz es la esperada (d): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
La Raiz es la esperada (b): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
La Raiz es la esperada (q): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
Prueba 4: OK



Prueba insertar un alumno: APROBADO
Prueba insertar un alumno: APROBADO
Prueba insertar un alumno: APROBADO
Prueba insertar un alumno: APROBADO
Prueba insertar un alumno: APROBADO
Prueba insertar un alumno: APROBADO
Prueba insertar un alumno: APROBADO

Recorrido inorden iterador interno (padrones: 90822 95480 100203 104010 104521 105525 110321):
Padron:90822 Documento:38837892 Nombre:Maria Martinez 
Padron:95480 Documento:34508554 Nombre:Antonella Maresca 
Padron:100203 Documento:95564899 Nombre:Jhon Millan 
Padron:104010 Documento:41780679 Nombre:Santiago Lopez 
Padron:104521 Documento:41526050 Nombre:Leo Tarditi 
Padron:105525 Documento:36275819 Nombre:Hernan Levi 
Padron:110321 Documento:35367341 Nombre:Santiago Henin 

Recorrido preorden iterador interno (padrones: 104010 100203 95480 90822 104521 105525 110321):
Padron:104010 Documento:41780679 Nombre:Santiago Lopez 
Padron:100203 Documento:95564899 Nombre:Jhon Millan 
Padron:95480 Documento:34508554 Nombre:Antonella Maresca 
Padron:90822 Documento:38837892 Nombre:Maria Martinez 
Padron:104521 Documento:41526050 Nombre:Leo Tarditi 
Padron:105525 Documento:36275819 Nombre:Hernan Levi 
Padron:110321 Documento:35367341 Nombre:Santiago Henin 

Recorrido postorden iterador interno (padrones: 90822 95480 100203 110321 105525 104521 104010):
Padron:90822 Documento:38837892 Nombre:Maria Martinez 
Padron:95480 Documento:34508554 Nombre:Antonella Maresca 
Padron:100203 Documento:95564899 Nombre:Jhon Millan 
Padron:110321 Documento:35367341 Nombre:Santiago Henin 
Padron:105525 Documento:36275819 Nombre:Hernan Levi 
Padron:104521 Documento:41526050 Nombre:Leo Tarditi 
Padron:104010 Documento:41780679 Nombre:Santiago Lopez 

Recorrido inorden hasta encontrar el 105525 (padrones: 90822 95480 100203 104010 104521 105525):
Padron:90822 Documento:38837892 Nombre:Maria Martinez 
Padron:95480 Documento:34508554 Nombre:Antonella Maresca 
Padron:100203 Documento:95564899 Nombre:Jhon Millan 
Padron:104010 Documento:41780679 Nombre:Santiago Lopez 
Padron:104521 Documento:41526050 Nombre:Leo Tarditi 
Padron:105525 Documento:36275819 Nombre:Hernan Levi 

Recorrido preorden hasta encontrar el 105525 (padrones: 104010 100203 95480 90822 104521 105525):
Padron:104010 Documento:41780679 Nombre:Santiago Lopez 
Padron:100203 Documento:95564899 Nombre:Jhon Millan 
Padron:95480 Documento:34508554 Nombre:Antonella Maresca 
Padron:90822 Documento:38837892 Nombre:Maria Martinez 
Padron:104521 Documento:41526050 Nombre:Leo Tarditi 
Padron:105525 Documento:36275819 Nombre:Hernan Levi 

Recorrido postorden hasta encontrar el 105525 (padrones: 90822 95480 100203 110321 105525):
Padron:90822 Documento:38837892 Nombre:Maria Martinez 
Padron:95480 Documento:34508554 Nombre:Antonella Maresca 
Padron:100203 Documento:95564899 Nombre:Jhon Millan 
Padron:110321 Documento:35367341 Nombre:Santiago Henin 
Padron:105525 Documento:36275819 Nombre:Hernan Levi 

Prueba nodo raiz es el alumno1 (padron 104510): APROBADO
Prueba borrar el alumno7 (padron 110321): APROBADO
Prueba buscar el alumno3 (padron 104521): APROBADO
Prueba borra el alumno3 (padron 104521): APROBADO
Prueba buscar el alumno2 (padron 100203): APROBADO
Prueba borra el alumno2 (padron 100203): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
Prueba nodo raiz es el alumno4 (padron 95480): APROBADO
Prueba 5: OK



Prueba insertar una palabra (Algebra): APROBADO
Prueba insertar una palabra (Derecho): APROBADO
Prueba insertar una palabra (Fisica): APROBADO
Prueba insertar una palabra (Matematica): APROBADO
Prueba insertar una palabra (Probabilidad): APROBADO
Prueba insertar una palabra (Quimica): APROBADO
La Raiz es la esperada (Algebra): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
La Raiz es el siguiente como en una lista (Derecho): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
La Raiz es el siguiente como en una lista (Fisica): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
La Raiz es el siguiente como en una lista (Matematica): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
La Raiz es el siguiente como en una lista (Probabilidad): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
La Raiz es el siguiente como en una lista (Quimica): APROBADO
Prueba borrar la raiz: APROBADO
Prueba buscar la raiz borrada: APROBADO
Prueba 6: OK



Prueba de arbol vacio: APROBADO
Prueba insertar un elemento: APROBADO
INSERTO 10K ELEMENTOS
Prueba arbol no vacio: APROBADO
Prueba que la raiz es el primer elemento insertado: APROBADO
Prueba borrar la raiz: APROBADO
Prueba de arbol vacio: APROBADO
Prueba insertar un elemento: APROBADO
INSERTO 5K ELEMENTOS
Prueba arbol no vacio: APROBADO
Prueba que la raiz es el primer elemento insertado: APROBADO
Prueba borrar la raiz: APROBADO
Prueba 7: OK



Has pasado la totalidad de las pruebas 8/8 
==2171== 
==2171== HEAP SUMMARY:
==2171==     in use at exit: 0 bytes in 0 blocks
==2171==   total heap usage: 15,070 allocs, 15,070 frees, 362,828 bytes allocated
==2171== 
==2171== All heap blocks were freed -- no leaks are possible
==2171== 
==2171== For counts of detected and suppressed errors, rerun with: -v
==2171== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

la primera de las pruebas que yo la llame mini pruebas lo que hace es corroborar si el nodo raiz es el esperado, si puede borrar de manera correcta una serie de elementos ubicados en distintas posiciones claves del arbol, luego comprueba si los recorridos devuelven lo esperado y por ultimo comprueba si los recorridos internos responden de la manera adecuada, es decir devolviendo y cortando el recorrido como se espera, esa fue proporcionada por la catedra.

la prueba 1 se encarga de ver si teniendo un arbol NULL las diferentes funciones que son llamadas devuelven el valor preestablecido como correcto.

La prueba 2, en este veo si los retornos estipulados en el contrato de abb.h son devueltos como esperaba con un arbol vacio.

La prueba 3 se encarga de llenar un arbol con enteros y ver si se pasan las distintas funciones devuelven los valores esperados, primero se inserta uno por uno elementos de un vector creado, se imprimen por pantalla los distintos recorridos verificando que estos sean los esperados y luego se borran las raices, se comprueba que esta este bien borrando y por ultimo se verifica que la nueva raiz sea la esperada.

La prueba 4 realiza basicamente las mismas pruebas que la prueba 3 pero ahora utilizando letras en vez de enteros.

La prueba 5 se llena un arbol con una estructura denominada alumnos, la funcion principal de esta prueba es ver si el comparador de esta estructura pueden desarrollarse de manera adecuada, tambien en esta prueba se prueba el recorrido interno con cortes y sin ellos.

La prueba 6, esta prueba se encarga de ver como un arbol degenerado se comporta muy parecido a una lista, ya que si se borron elementos de la raiz quien ocupa su lugar en la raiz es el siguiente como sucede en una lista.

La prueba 7 es la encargada de ver que si se le carga al arbol una cantidad masiva de elementos este puede realizar las distintas funciones sin ningun tipo de problema.

OBSERVACIONES:
1) decidi usar una funcion que busque nodos, en vez de buscar elementos por el simple hecho de que si buscaba elementos luego no me iba a servir para el resto de las funcion, mientras que si buscaba nodos esta podria ser reutilizada en varias funciones para poder encontrar el nodo a borrar por ejemplo.