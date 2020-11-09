Este TDA basicamente tiene la funcion de realizar varias primitivas sobre una estructura denominada lista
cada una de estas primitivas, es una funcion que se le aplica a la lista para poder hacer asi la accion
que el usuario requiera.

Ademas del TDA se implemento una serie de pruebas para revisar si las primitivas creadas funcionan de una
manera correcta o al menos como deberian. (sera explicado cada una al final del archivo)

la linea de compilacion para este TDA es la siguiente:
gcc *.c -o lista_se -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

y esto nos generara un archivo llamado lista_se que podemos ejecutarlo de dos maneras:

1) si solo queremos ver como funciona:
./lista_se

2) si queremos ver si no estamos perdiendo memoria y demas incovenientes que no podemos ver solo con
la anterior linea de ejecucion podemos utilizar valgrind con la siguiente linea:
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se

El resultado esperado de las pruebas corrido con valgrind es el siguiente:

==1665== Memcheck, a memory error detector
==1665== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1665== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==1665== Command: ./lista_se
==1665== 
Elementos en la lista: a b c d 
a b c d 
Imprimo la lista usando el iterador interno: a b c d 




Prueba de lista vacia: APROBADA
cola sin elementos: APROBADA
El ultimo elemento es NULL: APROBADA
Prueba de borrar en lista vacia: APROBADA
El ultimo elemento es el esperado: APROBADA
Prueba lista no vacia: APROBADA
Prueba 100 elementos insertados: APROBADA
El ultimo elemento es NULL: APROBADA
Prueba 1: OK





Prueba lista vacia: APROBADA
Lista sin elementos: APROBADA
El ultimo elemento es NULL: APROBADA
Prueba de borrar lista vacia: APROBADA
Prueba de borrar en posicion lista vacia: APROBADA
Prueba 2: OK





Prueba lista vacia: APROBADA
Prueba insertar un elemento: APROBADA
Prueba lista con un elemento: APROBADA
Prueba cantidad con un elemento insertado: APROBADA
El ultimo es el elemento insertado: APROBADA
Prueba insertar un elemento: APROBADA
Prueba insertar un elemento: APROBADA
Prueba insertar en posicion un elemento: APROBADA
Prueba insertar en posicion un elemento: APROBADA
Prueba lista con elementos: APROBADA
Prueba cantidad de elementos esperados: APROBADA
Prueba borrar en posicion un elemento: APROBADA
Prueba borrar en posicion un elemento: APROBADA
Prueba borrar un elemento: APROBADA
Prueba borrar un elemento: APROBADA
Se borra el ultimo elemento de la lista: APROBADA
Prueba lista vacia: APROBADA
Lista sin elementos: APROBADA
El ultimo elemento es NULL: APROBADA
Prueba borrar lista vacia: APROBADA
Prueba de borrar en posicion lista vacia: APROBADA
Prueba 3: OK





Prueba insertar 10k: APROBADA
Prueba borrar 10k: APROBADA
Prueba insertar 7k: APROBADA
Prueba borrar 7k: APROBADA
Prueba insertar 5k: APROBADA
Prueba borrar 5k: APROBADA
prueba 4: OK





Prueba insertar en lista NULL: APROBADA
Prueba insertar en posicion lista NULL: APROBADA
Prueba borrar en lista NULL: APROBADA
Prueba borrar de posicion en lista NULL: APROBADA
Prueba lista vacia: APROBADA
Prueba cantidad en lista NULL: APROBADA
El ultimo elemento de la lista es NULL: APROBADA
prueba 5: OK





Prueba de iterador siguiente: APROBADA
Prueba iterador siguiente esperado: APROBADA
Prueba de iterador siguiente: APROBADA
Prueba iterador siguiente esperado: APROBADA
Prueba de iterador siguiente: APROBADA
Prueba iterador siguiente esperado: APROBADA
Prueba de iterador siguiente: APROBADA
Prueba iterador siguiente esperado: APROBADA
Prueba de iterador siguiente: APROBADA
prueba 6: OK





Prueba de crear iterador con lista NULL: APROBADA
Prueba con iterador NULL tiene siguiente: APROBADA
Prueba con iterador NULL elemento siguiente esperado: APROBADA
prueba 7: OK





Pasaste 8/8 pruebas
==1665== 
==1665== HEAP SUMMARY:
==1665==     in use at exit: 0 bytes in 0 blocks
==1665==   total heap usage: 22,127 allocs, 22,127 frees, 355,104 bytes allocated
==1665== 
==1665== All heap blocks were freed -- no leaks are possible
==1665== 
==1665== For counts of detected and suppressed errors, rerun with: -v
==1665== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

la primera de las pruebas que yo la llame mini pruebas lo que hace simplemente es imprimir por pantalla los valores de cierto elementos que estan en la lista, esa fue proporcionada por la catedra.

la prueba 1 se encarga de llenar una lista con 100 elemento, antes de eso prueba si la lista esta vacia al comienzo, fue creada y demas pruebas que siempre se
hacen antes de insertar o borrar. cuando inserto todos los elementos, pruebo si el ultimo elemento es el almacenado en el ultimo de la lista y luego borro todos
los nodos uno por una y pruebo si luego del borrado los valores son los esperados para una lista vacia.

La prueba 2, en este veo si los retornos estipulados en el contrato de lista.h son devueltos como esperaba con un lista vacia.

La prueba 3 se encarga de llenar una lista con unos pocos elementos pero insertando no solo con el lista_insertar sino que tambien con el insertar_en_posicion
y a su vez verifica que lo insertado este donde corresponde y pueda hacerlo de manera correcta, luego borrar con lista_borrar y lista_borrar_de_posicion
comprobando tambienn que estas funciones devuelvan los valores esperados y cuando termina de borrar todo, hace las correspondientes pruebas de una lista vacia.

La prueba 4, en esta solamente se carga una lista con unas cantidades masivas de elementos y se comprueba si inserto de manera correcta toda esa cantidad de 
elementos, y luego los borrar probando si esta funcion de borrado lo hizo de manera correcta.

La prueba 5 se encarga de comprobar que si la lista pasada por parametro a las funciones implementadas en el lista.c devuelven los valores estipulados en
el contrato de lista.h que en su mayoria son devolver NULL si la funcion devuelve void* o ERROR si la funcion devuelve un entero.

La prueba 6, esta prueba ve simplemente si las funciones de iterador siguiente y tiene iterador siguiende devuleven los valores esperados segun la lista llenada
con valores previamente provistos por quien hizo las pruebas.

La prueba 7 es la encargada de ver que sucede si se crea un iterador con una lista NULL

OBSERVACIONES:
1) al implementar la estructura de lista decidi hacerlo con un nodo final para que la complejidad computacional de funciones con el insertar o la que devuelve
el ultimo elemento de la lista puedan ser O(1).
2) tambien opte por poner un entero que valla acumulando la cantidad de elementos que posee la lista.
3) en cuanto al iterador interno no es posible hacer muchas mas pruebas de las que se hicieron en la minipruebas (o al menos a mi no se me ocurren) ya que es 
una funcion que necesita de otra funcion para su correcto funcionamiento. No creo que sea necesario probar mas esa funcion que con lo que ya se hizo en las
minipruebas.