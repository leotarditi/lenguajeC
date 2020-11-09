> **Malloc Dynamic Memory Allocator :** Una implementación de malloc en C usando explicit free list alcanzando un 86% de eficiencia


---

### DESCRIPCION 

La solución adoptada es utilizar una explicit free list para mantener la lista de punteros a bloques libres. Esto mejora el rendimiento del asignador en cuanto a velocidad en comparación con la implicit free list, ya que el asignador no necesita atravesar los bloques asignados mientras encuentra el tamaño apropiado de memoria libre. Este rendimiento mejoró en gran medida. Para mejorar la asignación de memoria (util), se han realizado algunos cambios en la estrategia de reasignación. Finalmente, para mejorar un poco más el rendimiento, se han realizado algunos cambios en la función de búsqueda de ajuste para evitar recorridos muy largos a veces.

### DISEÑO 

En total, hay 3 características principales que se han agregado al asignador

* Se implementó una explicit free list para mantener la lista de punteros a bloques libres.
* La estructura de datos utilizada de la free list es la lista doblemente enlazada.
* El programador accede únicamente a la memoria asignada, es decir (los bloques asignados). Por lo tanto, los bloques libres pueden almacenar de manera eficiente otra información importante. Dado que el tamaño mínimo de bloque indicado es de 4 palabras, ningún bloque libre puede tener menos de 4 palabras. Con este hecho, podemos almacenar fácilmente 2 punteros en bloques libres (lo que requiere solo 2 palabras). El primer puntero apuntará al bloque libre (en el montón) anterior al bloque libre actual (en el que estoy almacenando punteros) y el segundo apuntará al bloque libre de al lado del bloque libre actual.

#### 1.
Cualquier bloque libre en el heap tendrá el siguiente formato.

```
---------------------------------------------------------------------------------------
| Bloque Libre Anterior ptr (1 word) | Bloque Libre Siguiente ptr(1 word) |  ...      |
---------------------------------------------------------------------------------------
```

Por lo tanto, si tengo un puntero bp a un bloque libre, entonces puedo acceder a los bloques libres siguientes y anteriores usando macros:

```
	#define GET_NEXT_PTR(bp)  (*(char **)(bp + WSIZE))
	#define GET_PREV_PTR(bp)  (*(char **)(bp))
```

Y para establecer el puntero anterior y siguiente utilize: 

```
    	#define SET_NEXT_PTR(bp, qp) (GET_NEXT_PTR(bp) = qp)
    	#define SET_PREV_PTR(bp, qp) (GET_PREV_PTR(bp) = qp)
```

Otras dos funciones:

```
    	void insert_in_free_list(void *bp)
    	void remove_from_free_list(void *bp)
```
Se han implementado utilizando las macros anteriores para mantener la free list.

#### 2.

Se modificó la función de mm_realloc para mejorar el rendimiento de caída.

La función de mm_realloc busca una memoria de nuevo tamaño y copia todo el contenido en ella, incluso cuando no sea necesario.

Para solucionar este problema, hemos agregado una condición en mm_realloc.

Por ejemplo, para el escenario en el que mm_realloc solicita un nuevo tamaño de espacio y el tamaño nuevo es mayor que el tamaño antiguo. Es decir, (el bloque necesita expandirse), entonces, primero debe verificar si el siguiente bloque está libre o no. En caso de que el siguiente bloque esté libre y la suma total de ambos bloques (este bloque y el siguiente bloque) sea mayor que el tamaño anterior, solo podemos cambiar el tamaño del bloque actual, corregir el encabezado, el pie de página y listo. No es necesario copiar contenidos en ningún lugar. El contenido del bloque antiguo todavía está intacto y seguro.

Por Ejemplo,

```
---------------------------------------------------------------------------
| Bloque Actual (oldsize = 8 words)| Bloque siguiente (8 word) (free)     |
---------------------------------------------------------------------------
```
Ahora, si el programador solicita que el bloque actual se extienda a 16 palabras, no es necesario volver a llamar a malloc y copiar el contenido.
Simplemente combina dos bloques mientras se ocupa del espacio adicional restante:
```
---------------------------------------------------------------------------
| Bloque Actual                     (newsize = 16 words)		          |
---------------------------------------------------------------------------
```

#### 3.

Evitar la caída del rendimiento debido a llamadas mm_malloc repetitivas del mismo tamaño.

Si se da cuenta de que muchas veces (digamos > 30 veces) se ha realizado la misma solicitud de tamaño de mm_malloc, en lugar de recorrer la free list completa, cuando sé que tomará mucho tiempo, puedo extender el heap por la cantidad solicitada. Sin embargo, se debe tener cuidado para evitar que muchas llamadas a extend_heap hagan que el programa se quede sin memoria.

##### Puntos extra acerca del programa:

Los encabezados y pies de página se han mantenido como tales en el programa. Tiene la siguiente estructura:
```
      63                     3  2  1  0 
      -----------------------------------
     | s  s  s  s  ... s  s  s  0  0  a/f
      ----------------------------------- 
```
* El esquema de fusion es de fusion inmediata mediante fusion de tag.
* La búsqueda en la free list ejecuta el algoritmo first fit.
