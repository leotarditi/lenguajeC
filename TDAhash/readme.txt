Este TDA basicamente tiene la funcion de realizar varias primitivas sobre una estructura denominada hash o diccionario
cada una de estas primitivas, es una funcion que se le aplica al hash para  que el usuario pueda usarlos como le parezca necesario.

Ademas del TDA se implemento una serie de pruebas para revisar si las primitivas creadas funcionan de una
manera correcta o al menos como deberian. (sera explicado cada una al final del archivo)

la linea de compilacion para este TDA es la siguiente:
gcc *.c -o hash -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

y esto nos generara un archivo llamado abb que podemos ejecutarlo de dos maneras:

1) si solo queremos ver como funciona:
./hash

2) si queremos ver si no estamos perdiendo memoria y demas incovenientes que no podemos ver solo con
la anterior linea de ejecucion podemos utilizar valgrind con la siguiente linea:
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./hash

El resultado esperado de las pruebas corrido con valgrind es el siguiente:

==3732== Memcheck, a memory error detector
==3732== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==3732== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==3732== Command: ./hash
==3732== 
Agrego autos al garage
Guardando vehiculo patente AC123BD (Auto de Mariano): OK
Guardando vehiculo patente OPQ976 (Auto de Lucas): OK
Guardando vehiculo patente A421ACB (Bici de Manu): OK
Guardando vehiculo patente AA442CD (Auto de Guido): OK
Guardando vehiculo patente AC152AD (Auto de Agustina): OK
Guardando vehiculo patente DZE443 (Auto de Jonathan): OK
Guardando vehiculo patente AA436BA (Auto de Gonzalo): OK
Guardando vehiculo patente QDM443 (Auto de Daniela): OK
Guardando vehiculo patente BD123AC (Auto de Pablo): OK
Guardando vehiculo patente CD442AA (Auto de Micaela): OK
Guardando vehiculo patente PQO697 (Auto de Juan): OK
(Destructor) Libero el vehiculo: Auto de Jonathan
Guardando vehiculo patente DZE443 (Auto de Jonathan otra vez): OK
(Destructor) Libero el vehiculo: Auto de Agustina
Guardando vehiculo patente AC152AD (Auto de Agustina otra vez): OK
Verifico el vehiculo patente QDM443: OK
Verifico el vehiculo patente PQO697: OK
(Destructor) Libero el vehiculo: Auto de Daniela
Retirando vehiculo patente QDM443: OK
(Destructor) Libero el vehiculo: Auto de Juan
Retirando vehiculo patente PQO697: OK
Verifico el vehiculo patente QDM443: OK
Verifico el vehiculo patente PQO697: OK
Patente: AA436BA -- Vehiculo: Auto de Gonzalo
Patente: AC152AD -- Vehiculo: Auto de Agustina otra vez
Patente: A421ACB -- Vehiculo: Bici de Manu
Patente: AA442CD -- Vehiculo: Auto de Guido
Patente: AC123BD -- Vehiculo: Auto de Mariano
Patente: BD123AC -- Vehiculo: Auto de Pablo
Patente: CD442AA -- Vehiculo: Auto de Micaela
Patente: DZE443 -- Vehiculo: Auto de Jonathan otra vez
Patente: OPQ976 -- Vehiculo: Auto de Lucas
Cantidad de autos guardados: 9. Cantidad de autos listados: 9 -- OK
(Destructor) Libero el vehiculo: Auto de Gonzalo
(Destructor) Libero el vehiculo: Auto de Agustina otra vez
(Destructor) Libero el vehiculo: Bici de Manu
(Destructor) Libero el vehiculo: Auto de Guido
(Destructor) Libero el vehiculo: Auto de Mariano
(Destructor) Libero el vehiculo: Auto de Pablo
(Destructor) Libero el vehiculo: Auto de Micaela
(Destructor) Libero el vehiculo: Auto de Jonathan otra vez
(Destructor) Libero el vehiculo: Auto de Lucas




Prueba quitar un elemento en hash vacio: APROBADO 
Prueba obtener elemento en hash vacio: APROBADO 
Prueba si contiene un elemento en hash vacio: APROBADO 
Prueba cantidad en hash vacio: APROBADO 
PRUEBA 1: Aprobaste 4/4



Prueba iterador siguiente con hash vacio: APROBADO 
Prueba iterador tiene siguiente con hash vacio: APROBADO 
PRUEBA 2: Aprobaste 2/2



Prueba insertar clave1: APROBADO 
Prueba cantidad de elementos es 1: APROBADO 
Prueba de obtener el clave1: APROBADO 
Prueba hash contiene clave1: APROBADO 
Prueba quitar clave1: APROBADO 
Prueba cantidad de elementos es 0: APROBADO 
Prueba insertar clave2: APROBADO 
Prueba cantidad de elementos es 1: APROBADO 
Prueba de obtener el clave2: APROBADO 
Prueba hash contiene clave2: APROBADO 
Prueba insertar clave3: APROBADO 
Prueba cantidad de elementos es 2: APROBADO 
Prueba de obtener el clave3: APROBADO 
Prueba hash contiene clave3: APROBADO 
PRUEBA 3: Aprobaste 14/14



Prueba insertar clave1: APROBADO 
Prueba de obtener el clave1 es elemento1a: APROBADO 
Prueba insertar clave2: APROBADO 
Prueba de obtener el clave2 es elemento2a: APROBADO 
Prueba cantidad de elementos es 2: APROBADO 
Prueba insertar clave1 con otro elemento: APROBADO 
Prueba de obtener el clave1 es elemento1b: APROBADO 
Prueba insertar clave2 con otro elmento: APROBADO 
Prueba de obtener el clave2 es elemento2b: APROBADO 
Prueba cantidad de elementos es 2: APROBADO 
PRUEBA 4: Aprobaste 10/10



Prueba insertar clave1: APROBADO 
Prueba de obtener el clave1 es elemento1a: APROBADO 
Prueba insertar clave2: APROBADO 
Prueba de obtener el clave2 es elemento2a: APROBADO 
Prueba cantidad de elementos es 2: APROBADO 
Prueba insertar clave1 con otro elemento: (Destructor) Libero el elemento APROBADO 
Prueba de obtener el clave1 es elemento1b: APROBADO 
Prueba insertar clave2 con otro elmento: (Destructor) Libero el elemento APROBADO 
Prueba de obtener el clave2 es elemento2b: APROBADO 
Prueba cantidad de elementos es 2: APROBADO 
(Destructor) Libero el elemento (Destructor) Libero el elemento 
PRUEBA 5: Aprobaste 10/10



Prueba insertar clave1: APROBADO 
Prueba insertar clave2: APROBADO 
Prueba insertar clave3: APROBADO 
Prueba cantidad de elemento es 3: APROBADO 
Prueba contiene clave3: APROBADO 
Prueba obtener clave3 devuelve elemento3: APROBADO 
Prueba quitar clave3: APROBADO 
Prueba no puede quitar clave3: APROBADO 
Prueba hash no contiene clave3: APROBADO 
Prueba obtener clave3 devuelve NULL: APROBADO 
Prueba cantidad de elemento es 2: APROBADO 
Prueba contiene clave2: APROBADO 
Prueba obtener clave2 devuelve elemento2: APROBADO 
Prueba quitar clave2: APROBADO 
Prueba no puede quitar clave2: APROBADO 
Prueba hash no contiene clave2: APROBADO 
Prueba obtener clave2 devuelve NULL: APROBADO 
Prueba cantidad de elemento es 1: APROBADO 
Prueba contiene clave1: APROBADO 
Prueba obtener clave1 devuelve elemento1: APROBADO 
Prueba quitar clave1: APROBADO 
Prueba no puede quitar clave1: APROBADO 
Prueba hash no contiene clave1: APROBADO 
Prueba obtener clave1 devuelve NULL: APROBADO 
Prueba cantidad de elemento es 0: APROBADO 
PRUEBA 6: Aprobaste 25/25



Prueba hash almacenar muchos elementos: APROBADO 
Prueba hash cantidad de elementos es la correcta: APROBADO 
Prueba hash pertenece y obtener muchos elementos: APROBADO 
Prueba hash quitar muchos elementos: APROBADO 
Prueba hash almacenar muchos elementos: APROBADO 
Prueba hash cantidad de elementos es la correcta: APROBADO 
Prueba destruir hash masivo con Destructor: APROBADO 
PRUEBA 7: Aprobaste 7/7



Prueba insertar clave1: APROBADO 
Prueba insertar clave2: APROBADO 
Prueba insertar clave3: APROBADO 
Prueba cantidad de elemento es 3: APROBADO 
Prueba clave siguiente devuelve clave1: APROBADO 
Prueba iterador tiene siguiente: APROBADO 
Prueba clave siguiente devuelve clave2: APROBADO 
Prueba iterador tiene siguiente: APROBADO 
Prueba clave siguiente devuelve clave3: APROBADO 
Prueba iterador tiene siguiente: APROBADO 
Prueba clave siguiente devuelve NULL: APROBADO 
Prueba iterador no tiene siguiente: APROBADO 
PRUEBA 8: Aprobaste 12/12



Prueba iterador tiene siguiente: APROBADO 
Prueba hash iteracion masivo: APROBADO 
Prueba hash iteracion masivo, recorrido todo el largo: APROBADO 
Prueba hash iteracion masivo, tiene siguiente: APROBADO 
Prueba hash iteración en volumen, se cambiaron todo los elementos: APROBADO 
PRUEBA 9: Aprobaste 5/5



Prueba insertar un elemento en hash NULL: APROBADO 
Prueba quitar un elemento en hash NULL: APROBADO 
Prueba obtener elemento en hash NULL: APROBADO 
Prueba si contiene un elemento en hash NULL: APROBADO 
Prueba cantidad en hash NULL: APROBADO 
PRUEBA 10: Aprobaste 5/5



Has pasado la totalidad de las pruebas 11/11 


==3732== 
==3732== HEAP SUMMARY:
==3732==     in use at exit: 0 bytes in 0 blocks
==3732==   total heap usage: 60,821 allocs, 60,821 frees, 1,448,003 bytes allocated
==3732== 
==3732== All heap blocks were freed -- no leaks are possible
==3732== 
==3732== For counts of detected and suppressed errors, rerun with: -v
==3732== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

la primera de las pruebas que yo la llame mini pruebas es la proporcionada por la catedra.

la prueba 1 se encarga de ver si las diferentes primitivas funcionan como deberian al ser aplicadas en un hash vacio. 

La prueba 2, quiere ver como se comportan las primitivas del iterador del hash cuando el hash pasado esta vacio.

La prueba 3 se encarga de ver si al insertar difenten claves con sus respectivos elementos, las primitivas responden de la manera esperada. Primero inserta una clave y un elemento y luego la borra. Luego inserta dos claves y elementos, probando el insertar y luego deja que la funcion de destruir del hash borre lo insertado.

La prueba 4 lo que intenta ver esta prueba es como se comporta el hash cuando a una a la primitiva de insertar se le pasa una clave igual a una ya ingresada anteriormente, lo que deberia suceder es que el elemento de la clave sea reemplazado por el nuevo elemento a insertar que posee la misma clave.

La prueba 5, esta se encarga de verificar lo mismo que la prueba 4 pero con la diferencia que realiza las acciones con elementos almacenados en memoria dinamica, lo cual llevaria a que cada elemento debe ser destruido por el destructor que posee la estructura hash.

La prueba 6 se encarga de ver si al borrar tres claves y elementos previamentes insertados, el hash se comporta como deberia, por ejemplo si se desea obtener la clave borrada esta ya no se encontrara en el hash, lo mismo con la disminucion de la cantidad alojada en el hash.

La prueba 7, aqui veremos si se comporta de manera adecuada cada una de las primitivas si se inserta y borrar una cantidad masiva de elementos, se podria agrandar esta cantidad de claves y elementos alojados como el creador de las pruebas desee, yo en mi caso utilize 1000. No solamente prueba con elementos sin necesidad de un destructor, hace una prueba con este tipo de elementos y luego realiza las misma pruebas pero con elementos almacenados en memoria dinamica para asi poder probar el destructor del hash tambien.

La prueba 8, esta prueba simplemente se encarga de ver si el iterador del hash funciona como se lo espera.

La prueba 9 llena un hash con una gran cantidad de elementos y luego prueba si el iterador del hash funciona como deberia con esta cantidad masiva.

La prueba 10 se encarga de probar si se devuelven los valores preestrablecidos en el .h cuando se le pasa por parametro a las diferentes primitivas un hash NULL.

OBSERVACIONES:
1) Una de las grandes cosa que opte por hacer fue modificar la lista que realize anteriormente para el TDA lista, ya que las primitivas que me fueron pedidas realizar no me alcanzaban o al menos crei necesario agregarle algunas mas para poder aplicarlas en el hash de manera mas sencilla.
2) Opte por utilizar un hash abierto porque me parecio mas facil de manejar, y a su vez el hash que cuente con un vector de lista para poder alojar alli adentro las claves y elementos que sean necesarias para el usuario.
3) En cuanto a la fucion de rehasheo, elegi aumentar la capacidad del hash al doble por el simple hecho de estar usando un hash abierto y por lo tanto el rehash solamente estaria cumpliendo la funcion de agrandar el hash para que se sigan comportando la mayoria de las primitivas como o(1), pero al no ser cerrado el aumento de la capacidad no es tan importante en para las colisiones, ya que en una hash abierto cuando se producen colisiones tan solo se ingresan elementos en una lista.