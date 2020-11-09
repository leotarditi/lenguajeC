1- INTRODUCCION

Esto es un simulador del juego de tronos. Para ello, se dispondre de una serie de casas y tras pedirle al usuario una cierta cantidad de años a transcurrir,
se le informará el nombre de la casa que ocupa el Trono de Hierro en ese momento.
Las casas se leerán de un archivo de texto y se irán insertando en un ABB cuya clave a utilizar para realizar las comparaciones es el nombre de las mismas ("Stark”, ”Lannister”, ”Martell”, etc.). Además, cada una de ellas contiene una lista con todas las personas que la integran.

La dinámica es la siguiente:

Cada año que transcurre, en una casa pueden morir o nacer integrantes. Esto depende del factor de nacimiento y de envejecimiento de la misma.
Para que muera un integrante debe llegar a la edad de 60 años (esperanza de vida promedio de la época, mueren a la edad de 60 años). Sin embargo, cada casa tiene una genética distinta y, por ende, envejecen de diferentes maneras.

Por ello en cada año las edades cambian de acuerdo a la siguiente regla: edad = edad + factor de envejecimiento.

Algo similar ocurre con los nacimientos, donde se da a luz a un nuevo integrante si ocurre que: cantidad a nacer = cantidad de integrantes/factor de nacimiento.

El orden de chequeo es el siguiente: primero las muertes y luego los nacimientos. No pueden nacer personas en una casa vacı́a.
Cuando una casa se queda sin integrantes pasa a extinguirse, siendo eliminada del árbol y agregada a una cola de casas extintas.
Una vez acabada la simulación, la casa con la mayor cantidad de integrantes será la que ocupe el Trono de Hierro.

2- INTERACCION CON EL USUARIO

El programa debe comunicarse con el usuario (y viceversa) a través de un menú que contiene las siguientes opciones:

S: inicia la simulación. Para ello, antes se le pregunta al usuario la cantidad de años a transcurrir y, una vez finalizados, se le informa la casa que controla el Trono de Hierro.

A: agrega una casa al árbol. Se le pedirá al usuario el nombre del archivo con su extension donde se encuentra la información de la casa a cargar. Si la casa ya existe, se le sumará todos lo integrantes de la nueva casa en la ya exitente.

L: lista las casas por cantidad de integrantes en orden descendente con su respectivos integrantes.

E: muestra las casas extintas en el orden en el que fueron desapareciendo.

Q: finaliza la ejecución del programa.

Si la letra ingresada no corresponde a la del menú, se le volvera a pedir una de las letras especificadas anteriormente.

3- ARCHIVO DE CASAS

El archivo inicial de casas tendrá el siguiente formato:

C;nombre_de_la_casa_1;factor_de_envejecimiento;factor_de_nacimiento
I;nombre_persona_1;edad
I;nombre_persona_2;edad
I;nombre_persona_3;edad
I;nombre_persona_4;edad
...
I;nombre_persona_N;edad
C;nombre_de_la_casa_1;factor_de_envejecimiento;factor_de_nacimiento
I;nombre_persona_1;edad
I;nombre_persona_2;edad
I;nombre_persona_3;edad
I;nombre_persona_4;edad
...
I;nombre_persona_M;edad

4- COMPILACION

La linea de compilacion para este programa es la siguiente:
gcc *.c -o simulacion -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

y esto nos generara un archivo llamado simulacion. que podemos ejecutarlo de dos maneras:

1) si solo queremos ver como funciona:
./simulacion

2) si queremos ver si no estamos perdiendo memoria y demas incovenientes que no podemos ver solo con
la anterior linea de ejecucion podemos utilizar valgrind con la siguiente linea:
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./simulacion


5- RESULTADO ESPERADO

Los resultados esperados con la ejecucion (1) es similar a la que sale con la ejecucion (2) sin ver detalles sobre la perdida de memoria y errores de contexto por eso solo mostrare los que se espera con valgrind:

leotarditi@leotarditi-HP-Laptop-14-bw0xx:~/Facultad/AlgoII/TP2$ valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./simulacion
==2974== Memcheck, a memory error detector
==2974== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2974== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==2974== Command: ./simulacion
==2974== 
Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: S

Cuantos anios desea transcurrir: 5

La casa que esta en el trono es: Casa4 

Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: L

Las casas de este reino son: 
Casa4 
Persona 1 
Persona 2 
Persona 3 
Persona 4 
Persona 5 
Persona 6 
Junior 
Junior 
Junior 
Junior 
Junior 


Casa1 
Persona 1 
Persona 2 
Persona 3 
Persona 5 
Persona 6 
Persona 7 
Persona 8 
Persona 10 
Persona 14 
Persona 15 


Casa3 
Persona 2 
Persona 5 
Persona 6 
Persona 7 
Junior 
Junior 
Junior 
Junior 
Junior 


Casa5 
Persona 12 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 


Casa2 
Persona 1 
Persona 2 
Persona 3 
Persona 9 



Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: E

No hay casas extintas

Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: S

Cuantos anios desea transcurrir: 10

La casa que esta en el trono es: Casa3 

Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: L

Las casas de este reino son: 
Casa3 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 


Casa4 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 


Casa2 
Persona 1 
Persona 3 
Persona 9 



Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: E

Estas casas ya no existen: 
Casa1 
Casa5 

Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: A

Por favor ingrese el nombre del archivo donde se encuentra la nueva casa: casa_existente.txt

Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: L

Las casas de este reino son: 
Casa2 
Persona 1 
Persona 3 
Persona 9 
Persona 1 
Persona 2 
Persona 3 
Persona 4 
Persona 5 
Persona 6 
Persona 7 
Persona 8 
Persona 9 
Persona 10 
Persona 11 
Persona 12 
Persona 13 
Persona 14 
Persona 15 


Casa3 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 


Casa4 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 



Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: S

Cuantos anios desea transcurrir: 20

La casa que esta en el trono es: Casa3 

Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: L

Las casas de este reino son: 
Casa3 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 


Casa4 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 



Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: E

Estas casas ya no existen: 
Casa1 
Casa5 
Casa2 

Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: A

Por favor ingrese el nombre del archivo donde se encuentra la nueva casa: casa_nueva.txt

Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: L

Las casas de este reino son: 
Casa3 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 


Casa4 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 


Casa6 
Persona 4 
Persona 7 
Persona 9 
Persona 11 
Persona 13 
Persona 21 
Persona 6 
Persona 19 



Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: S

Cuantos anios desea transcurrir: L

La casa que esta en el trono es: Casa3 

Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: 
Las casas de este reino son: 
Casa3 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 


Casa4 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 
Junior 


Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: E

Estas casas ya no existen: 
Casa1 
Casa5 
Casa2 
Casa6 

Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas 
por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: Q

==2974== 
==2974== HEAP SUMMARY:
==2974==     in use at exit: 0 bytes in 0 blocks
==2974==   total heap usage: 621 allocs, 621 frees, 34,240 bytes allocated
==2974== 
==2974== All heap blocks were freed -- no leaks are possible
==2974== 
==2974== For counts of detected and suppressed errors, rerun with: -v
==2974== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


6- OBSERVACIONES SOBRE EL CODIGO

1) Opte por cambiar los factores de envejecimiento y nacimiento cuando el usuario desea agregar una casa ya existente.
2) Otra de las cosas que hice fue ponerle a todos los nacidos con el nombre JUNIOR.
3) Estan incluidos en el zip los dos archivos que nombre.
4) Use un static char en el leer linea porque asi fue explicado en clase, ademas opte por ponerle NULL a la linea cuando el fgets devolvia NULL para que no me tirara un error cuando uso accedo a el valor de linea[0].
5) Ademas opte por usar un detructor NULL en el arbol para que no se me borre la casa cuando la encola en las extintas.