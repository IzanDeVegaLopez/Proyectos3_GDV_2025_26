# Estructura de Datos: SparseSet
- Referencia https://skypjack.github.io/2020-08-02-ecs-baf-part-9/
- Contiene un array disperso, de índices; un array denso, de datos(opcional); y un array de backlinks, denso también, de igual tamaño que el de datos, que contiene los índices que se corresponden en el array disperso
- El tamaño que ocupa el set de datos solo se conoceré en runtime, es decir, guardará objetos de tipo desconocido. Pero en ejecución será capaz de devolver el objeto del tipo que realmente almacena.

## Características
- iteración sobre todos los elementos en O(N) y en memoria contigua
- acceso aleatorio en O(1)
- inserción en O(1)
- borrado en O(1)

## Objetivo
Esta estructura a cambio de algo más de memoria nos permitirá mejorar el rendimiento.

Y nos facilitará la creación de varias características de nuestro motor. Como son las entidades, componentes, grupos y escenas.

Ser capaces de borrar entidades y componentes en tiempo de ejecución de forma sencilla e inmediata.

## Implementación
De forma que almacenaríamos nuestras entidades en una estructura de datos como la siguiente:
|					   |   |   |   |   |   |   |   |   |   |
|----------------------|---|---|---|---|---|---|---|---|---|
| Index Disperse Array (IdxDisperse) | - | 2 | - | 0 | - | 1 | - | - | - |
| Backlink Dense Array (BackDense) | 3 | 5 | 1 | - | - | - | - | - | - |


Cada elemento en la Index Disperse Array sería el indice de ese mismo elemento en la Backlink Dense Array y viceversa.
Es decir si miramos el indice 2 de la backlink array este contendrá el indice de la posición del indice de la Disperse array en el que podemos encontrar ese dos.
Por lo tanto se cumple el siguiente invariante de representación:
```cpp
	IdxDisperse[BackDense[i]] == i
	BackDense[IdxDisperse[i]] == i
```

En aquellos espacios en los que no haya un elemento habrá un valor específico, reservado para representar esto mismo. Indicado en las imagenes con "-"(guión).
### Inserción en O(1)
Insertar en esta estructura es sencillo.  Simplemente añadiremos al final de la lista de backlinks un nuevo elemento. Para insertar le daremos un indice. Este indice hará referencia a la array dispersa. Nos aseguraremos de que no haya nada ya en esa posición y si es así lo añadiremos a la dispersa.
De forma que la array de antes quedaría así, tras añadir algo en la posición 8.
|					   |   |   |   |   |   |   |   |   |   |
|----------------------|---|---|---|---|---|---|---|---|---|
| Index Disperse Array (IdxDisperse) | - | 2 | - | 0 | - | 1 | - | - | 3 |
| Backlink Dense Array (BackDense) | 3 | 5 | 1 | 8 | - | - | - | - | - |
```cpp
	void insertar(int index){
		IdxDisperse[index] = BackDense.size();
		BackDense.push_back(index);
	}
```

### Eliminación en O(1)
La eliminación en esta estructura es también sencilla aunque no lo parezca a simple vista.
Eliminaremos elementos también por indice. Dando una configuración no válida al elemento en la Index Disperse Array. E intercambiando el último elemento de la backlink con aquel que queremos eliminar. Habrá que actualizar el valor del index disperse array de aquel que hemos movido. Y habríamos concluido la eliminación.
Por ejemplo para eliminar el elemento con indice 5 del anterior SparseSet quedaría así:
|					   |   |   |   |   |   |   |   |   |   |
|----------------------|---|---|---|---|---|---|---|---|---|
| Index Disperse Array (IdxDisperse) | - | 2 | - | 0 | - | - | - | - | 1 |
| Backlink Dense Array (BackDense) | 3 | 8 | 1 | - | - | - | - | - | - |
```cpp
	void eliminar(int index){
		//back devuelve el último elemento válido del array
		BackDense[IdxDisperse[index]] = BackDense.back();
		IdxDisperse[BackDense.back()] = IdxDisperse[index];
		BackDense.pop_back();
		IdxDisperse[index] = NON_VALID_VALUE;
	}
```

Al llamar a eliminar con un indice que no tiene elemento asignado la operación fallará y no hará nada. Pero no producira un error.

### Iteración de todos sus elementos en O(N) y en memoria contigua
Para esto simplemente habremos de recorrer el array de backlinks denso desde el primer elemento hasta el último.

### Añadiendo Datos
De momento solo estamos guardando indices en ambos arrays. Sin duda esto nos será útil para las entidades, grupos y escenas. Pero para los componentes queremos poder guardar su información y poder acceder a ella de forma eficiente. Para esto añadiremos un tercer array que almacenará los datos necesarios. Este tercer array será implementado con type-erased(
https://docs.rs/any_vec/latest/any_vec/).

Es decir, no conoceremos en tiempo de compilación el tipo de los elementos guardados en él ni el tamaño. Pero en tiempo de ejecución será capaz de devolver los elementos del tipo concreto, e iterar y tener acceso constante teniendo en cuenta cuanto ocupan en memoria.

Este tercer vector será también denso e imitará el comportamiento del vector denso de Backlinks.
Es decir el elemento i de la lista de backlinks corresponde con la información guardada en el indice i del array de información.

|					   |   |   |   |   |   |   |   |   |   |
|----------------------|---|---|---|---|---|---|---|---|---|
| Index Disperse Array | - | 2 | - | 0 | - | 1 | - | - | - |
| Backlink Dense Array | 3 | 5 | 1 | - | - | - | - | - | - |
| Data Dense Array 	   | Info_3 | Info_5 | Info_1 | - | - | - | - | - | - |

## Uso de SparseSet para Entidades y Componentes
Para hacer que buscar entidades con un mismo componente así como poder recorrer todas las entidades usaremos un SparseSet base para todas las entidades y uno por componente.

El **identificador** de cada <u>entidad</u> será el **indice** que ocupen en el <u>Index Disperse Array</u>

Los <u>componentes</u> que ocupen el **indice i** de su <u>array sparse</u> correspondiente serán componentes asociados a la entidad con **identificador i**

De forma que los sparseSet de entidades y componentes estan entrelazados de forma implicita.

### Añadir Entidades
Para añadir una entidad la añadiremos al SparseSet de entidades.

### Añadir Componentes
Para añadir un componente necesitamos el id de la entidad a la que queremos añadirselo.
De forma que haremos la operación insertar con el indice de dicha entidad en el SparseSet de ese tipo de componente.

### Eliminar Componentes
Para eliminar un componente volvemos a necesitar el id de la entidad a la que queremos quitarselo.
Después simplemente haremos la operación eliminar con el indice de dicha entidad en el SparSet de ese tipo de componente.

### Eliminar una Entidad
Para eliminar una entidad primero usaremos el indice de la entidad para eliminarla en todas los SparseSet de componentes que la contengan.
Después, la eliminaremos de la lista de entidades. 

## Grupos y escenas
Tanto los grupos como escenas serán meramente vectores con los identificadores de los objetos que contienen.

Podemos volver a usar la estructura SparseSet y modelarlos igual que componentes sin información (sin array adicional de datos o cuya suma del espacio en memoria de sus elementos es 0).

No crearemos un capa de abstracción para no separarlos de los compontes pues son lo mismo y deberían ser tratados como tal.

## Ejemplo completo
|					   |   |   |   |   |   |   |   |   |   |
|----------------------|---|---|---|---|---|---|---|---|---|
|**Entity SparseSet**|***|***|***|***|***|***|***|***|***|
| Index Disperse Array | - | 2 | - | 0 | - | 1 | - | - | 3 |
| Backlink Dense Array | 3 | 5 | 1 | 8 | - | - | - | - | - |
|**Component A SparseSet**|***|***|***|***|***|***|***|***|***|
| Index Disperse Array | - | 2 | - | 1 | - | 0 | - | - | - |
| Backlink Dense Array | 5 | 3 | 1 | - | - | - | - | - | - |
| Data Dense Array 	   | Info_5 | Info_3 | Info_1 | - | - | - | - | - | - |
|**Component B SparseSet**|***|***|***|***|***|***|***|***|***|
| Index Disperse Array | - | 0 | - | - | - | - | - | - | 1 |
| Backlink Dense Array | 1 | 8 | - | - | - | - | - | - | - |
| Data Dense Array 	   | Info_1 | Info_8| - | - | - | - | - | - | - |
|**Group A SparseSet (In reality Component C)**|***|***|***|***|***|***|***|***|***|
| Index Disperse Array | - | - | - | 0 | - | 1 | - | - | 2 |
| Backlink Dense Array | 3 | 5 | 8 | - | - | - | - | - | - |
|**Scene A SparseSet (In reality Component D)**|***|***|***|***|***|***|***|***|***|
| Index Disperse Array | - | 2 | - | 1 | - | 0 | - | - | 3 |
| Backlink Dense Array | 5 | 3 | 1 | 8 | - | - | - | - | - |