## Indice

- [Estructura de la solución y proyectos (y repositorios de Git)](#estructura-de-la-solución-y-proyectos-(y-repositorios-de-git))
	- [Librerías a usar](#librerías-a-usar)
		- [Ogre3D](#ogre3d)
		- [SDL2](#sdl2)
		- [Fmod](#fmod)
	- [Interfaz de comunicación con el juego desde el motor](#estructura-de-la-soluciòn-y-proyectos-(y-repositorios-de-git))
		- [Flujo de control Motor-Juego](#flujo-de-control-motor-juego)
	- [Uso de métodos del motor desde el juego](#uso-de-métodos-del-motor-desde-el-juego)
- [Estructura de las clases](#estructura-de-las-clases)
	- [Leyenda de los diagramas](#leyenda-de-los-diagramas)
		- [Sintáxis](#sintáxis)
			- [Prefijos](#prefijos)
			- [Sufijos](#sufijos)
			- [Relaciones](#relaciones)
	- [RAII](#raii)
		- [Aplicación de RAII](#aplicación-de-raii)
		- [Finalidad](#finalidad)
	- [Clases Importantes](#clases-importantes)
		- [EntityManager](#entitymanager)
		- [ComponentManager](#componentmanager)
		- [Componentes](#componentes)
		- [LogManager](#logmanager)
	- [Colisiones](#colisiones)
- [Estructura de componentes del motor y juegos](#estructura-de-componentes-del-motor-y-juegos)
	- [Arquitectura Escogida: ECS](#arquitectura-escogida-ecs)
	- [Implementación](#implementación)
		- [Estructura de Datos: SparseSet](#estructura-de-datos-sparseset)
			- [Características](#características)
			- [Objetivo](#objetivo)
			- [Implementación](#implementación-1)
				- [Inserción en O(1)](#inserción-en-o(1))
				- [Eliminación en O(1)](#eliminación-en-o(1))
				- [Iteración de todos sus elementos en O(N) y en memoría contigua](#iteración-de-todos-sus-elementos-en-o(n)-y-en-memoria-contigua)
				- [Añadiendo datos](#añadiendo-datos)
		- [Uso de SparseSet para Entidades y Componentes](#uso-de-sparseset-para-entidades-y-componentes)
			- [Añadir Entidades](#añadir-entidades)
			- [Añadir Componentes](#añadir-componentes)
			- [Eliminar Componentes](#eliminar-componentes)
			- [Eliminar una Entidad](#eliminar-una-entidad)
		- [Grupos y Escenas](#grupos-y-escenas)
		- [Ejemplo completo](#ejemplo-completo)
	- [Componentes Base del Motor](#componentes-base-del-motor)
		- [Representation2D](#representation2d)
			- [Implementación](#implementación-2)
		- [Representacion3D](#representation3d)
	- [Sistemas Base del Motor](#sistemas-base-del-motor)
		- [CollisionSystem](#collisionsystem)
		- [Render2DSystem](#render2dsystem)
		- [Render3Dsystem](#render3dsystem)
- [Pipeline de generación de contenido](#pipeline-de-generación-de-contenido)

# Estructura de la solución y proyectos (y repositorios de Git) 

La compilación y generación de ejecutables de este proyecto estará controlada por un fichero "CMakeLists.txt".

## Librerías a usar
### Ogre3D
Usaremos ogre 3D para representar objetos 2D y 3D en el viewport. Y usaremos las AABBs que nos facilita para comprobar colisiones.
### SDL2
Usaremos SDL2 para manejar el input de teclado y ratón.
### Fmod
Usaremos Fmod para efectos de sonido y música.

## Interfaz de comunicación con el juego desde el motor
La clase principal del juego deberá heredar de la clase abstracta **MotorProgram**.
Esta clase definirá los metodos gameInit(), gameLoop() y gameEnd().
El motor llamará a estos métodos. Como se puede ver en el siguiente gráfico.

### Flujo de control Motor-Juego 

```txt
        |------------------------------------------> Time
        |
Game    |    1----2    3----o----4    5----6
        |    |    |    |         |    |    |
        |----|----|----|---------|----|----|------->
        |    |    |    |         |    |    |
Engine  0----1    2----3      <--4----5    6-------x
        |
        |------------------------------------------>

0: Main
    CONTROL: Engine
    Engine Initialization.

1: Game Main
    CONTROL: Engine to Game
    Gameplay Initialization.
	Función Asociada: initGame()

2: Engine Loop Start
    CONTROL: Game to Engine
    Stuff that needs to be done
    each frame before giving control
    back to game.

3: Game Loop Start
    CONTROL: Engine to Game
    Our game Gameplay Loop
    Includes doing things in/with
    SYSTEMS.
	Función Asociada: updateGame()

4: Game Loop End
    CONTROL: Game to Engine
    The game loop update function
    is DONE.
    Engine may do stuff about the frame,
    for example, clear temporary data.
    Here if the game has not signaled
    that it wants to EXIT, control goes
    back to the Engine Loop Start (2).
    If the game has signaled EXIT,
    control goes to Engine Shutdown (5).

5: Game Shutdown
    CONTROL: Engine to Game
    The game is exiting.
    Do any game-specific shutdown stuff,
    like saving game data.
	Función Asociada: exitGame()

6: Engine Shutdown
    CONTROL: Game to Engine
    The engine is exiting.
    Do any engine-specific shutdown stuff,
    like freeing engine resources.
```

## Uso de métodos del motor desde el juego
Cada uno de los métodos anteriormente mencionados (initGame(), updateGame() y exitGame()) recibirá como argumento un puntero o una referencia a un struct que contengan punteros a todas las funciones del motor que serán públicas. Esta estructura se llamará GameContext. De forma que desde las siguientes funciones se puede acceder a cualquiera de los métodos expuestos del motor con una sintaxis similar a esta: 
```cpp
gameContextRef->getEntitiesInGroup(X)
```

## Input
La lectura del input se hará mediante SDL. Una clase wraper registrará los inputs y permitirá acceder a los siguientes métodos:
- getKeyState(SDL_Keycode) => returns true si la tecla está pulsada
- getKeyDown(SDL_Keycode) => return true si la tecla ha sido pulsada este frame
- getKeyUp(SDL_Keycode) => return true si la tecla se ha dejado de pulsar este frame

Como todo SDL_Keycode normal y relevante al hacer juegos se puede almacenar en 8 bytes podemos usar los siguientes valores:
Por lo tanto esta clase ocupará 2^8 bytes * 3.
Pues necesitaremos 3 flags una por cosa a devolver.
Entonces tendremos 3 vectores de 256 bits. Cada bits será una flag.

Implementar esto con SDL será sencillo.
Obtendremos el keycode de la tecla que haya leido. Este codigo será el indice del array para esa tecla.
Después simplemente si el evento es que esa tecla se ha pulsado este frame se activa la flag del vector keydown y el flag de keystate, si hemos dejado de pulsar se activa la flag del vector keyup correspondiente y se pone a 0 la flag de keystate.
Lo único que nos queda sería resetear todas las flags de los vectores keydown y keyup cada frame. Notese que el vector de keystate conserva el estado del anterior frame.

# Estructura de las clases 

Documentación de Mermaid para construir los gráficos: 
	https://mermaid.js.org/syntax/classDiagram.html
---
## Leyenda de los diagramas
### Sintáxis
"*function() \: returnType*"

#### Prefijos
- \+ Public
- \- Private
- \# Protected

#### Sufijos
- \$ Static
- \* Abstract (Cursiva)

#### Relaciones
```mermaid
classDiagram
classA --|> classB : Inheritance
classC --* classD : Composition
classE --o classF : Aggregation
classG --> classH : Association
classI -- classJ : Link(Solid)
classK ..> classL : Dependency
classM ..|> classN : Realization
classO .. classP : Link(Dashed)
```
---

```mermaid
---
title: Class Diagram
---
classDiagram
	GameManager *-- EntityManager
	GameManager *-- ComponentManager
	GameManager *-- SystemManager
	SystemManager --> "0..*" System
	EntityManager --> "0..*" Entity
	ComponentManager *-- Transform3DComponent  
	ComponentManager *-- Transform2DComponent
	ComponentManager *-- CollisionComponent
	ComponentManager *-- ColliderComponent
	System <|-- CollisionSystem
	SparseSet <|-- SparseDataSet
	class Entity{
		-alive
		+isAlive() : bool
	}
	class LogManager{
		+constructor(string file_name)
		+print(string format, ...)$
	}
	class SystemManager{
		-vector~System~ mSystemList
		+update(double dt, GameManager&)
	}
	class System{
		+update(double dt, GameManager&)*
	}
	class ComponentManager{
		# these SparseSets are type erased,
		# size of component is passed at runtime
		-vector~SparseSet~ mComponentsPerEntity

		+get~Component~(int entityId, int componentId) Component [const]&
		+emplace~Component~(int entityId, int componentId) Component&
		+insert~Component~(int entityId, int componentId, Component const& component)
		+remove~Component~(int entityId, int componentId)
		+has~Component~(int entityId, int componentId) bool
	}
	class GameManager{
		# game manager owns its parts
		-EntityManager mEntityManager
		-ComponentManager mComponentManager
		-SystemManager mSystemManager
	}
    class EntityManager{
        -SparseSet~int~ allEntities
		-vector~SparseSet~Entity&~~ mGroups
		-vector~SparseSet~Entity&~~ mScenes
		+GetEntitiesInGroup(int entityGroupId) vector~int~&
		+GetEntitiesInScene(int entitySceneId) vector~int~&
		+markEntityAsDead(int entityId)
		+update()
		-mEraseAllDeadEntities()
    }
	class SparseSet{
		-vector~int~ mIdxDisperseSet
		-vector~int~ mBacklinksDenseSet
		+iterator
		+begin()
		+end()
		-insertElement(int index)
		-eraseElement(int index)
	}
    class SparseDataSet~T~{
		-vector~T~ mDataDenseSet
		+getElementByIdx(int index) T&
		-insertElement(int index)
		-eraseElement(int index)
    }
	class Transform3DComponent{
		+vector3~float~ position
		+vector3~float~ scale
		+Quaternion~float~ orientation
	}
	class Transform2DComponent{
		+vector2~float~ pos
		+vector2~float~ scale
		+float rotation
	}
	class CollisionComponent{
		int entitiesCollidedWith[10]
		uint8_t collisionNumber
	}
	class ColliderComponent{

	}
```

## RAII
Todas nuestras clases usarán la técnica de programación RAII: https://en.cppreference.com/w/cpp/language/raii.html.

### Aplicación de RAII
- Encapsular cada recurso en una clase, donde:
	- el constructor reserva el recurso y se asegura de instaurar todos los invariantes de representación o lanzar una excepción si esto es imposible
	- el destructor libera el recurso y nunca lanzará excepciones
- Siempre usar el recurso via una instancia de una clase que aplique RAII y que cumpla una de estas dos:
	- Tiene tiempo automatico de almacenamiento o tiempo de vida finito.
	- Tiene un tiempo de vida confinado por un objeto automático o de vida finita

Esto implica que aquellas clases que requieran reservar memoria para funcionar se ocuparan de liberarla automáticamente en su destrucción.
Es decir, el tiempo de vida de un recurso será menor o igual al tiempo de vida del objeto que lo contiene.

### Finalidad
El uso de RAII pretende conseguir:
- Que no haya memory leaks
- Que no pueda haber acceso a regiones de memoria sin inicializar o con basura

## Clases Importantes

### SystemInterface
Implementa: 
- initSystem() 
- updateSystem()
- destroySystem()
Todos los sistemas tanto del motor como de los juegos heredan de esta clase base.

### EntityManager
- Contiene la lista (SparseSet) con todas las entidades vivas.
- Todas las entidades que contiene serán siempre validas

### ComponentManager
- Contiene una lista por tipo de componente posible
- La misma posición de distintas listas de componentes serán componentes pertenecientes a la misma entidad. Esta posición además coincidirá con la posición de la entidad en la lista de entidades del EntityManager
- Las listas de componentes

### Componentes
- No heredarán de una clase base. Se recomienda que sean tan independientes como sea posible. Y que requieran el mínimo de información externa posible.
- Recomendable mantener la estructura y el alineamiento tan pequeño como se pueda.

### LogManager
- Todos los mensajes sacados por el motor o por el juego serán producidos por una instancia de esta clase
- Los mensajes serán reflejados en un fichero .log contenido en la carpeta logs del proyecto.
- Todos los mensajes impresos con esta clase llevarán hora, minutos y segundos desde que se inició el programa. Y se imprimirán en el orden en el que se hacen las llamadas al LogManager
- Usa la sintaxis del printf de c
- Se instancia al inicio con el motor, y se cierra con el motor
- Acceso al metodo print estatico de esta clase para que pueda escribir quien sea

## Colisiones
- Cuando hay colisión entre dos entidades se añade un componente (CollisionComponent) a cada una (si no lo tienen ya). En este componente hay un buffer de tamaño fijo que almacena los indices de los otros objetos contra los que se ha chocado en este frame. Al final de cada frame este componente se eliminará de todos los objetos que lo tengan
- A la hora de crear el juego se podrán consultar las colisiones de una entidad con getEntityCollisions(int entityId), que devolverá una lista de indices.
  
# **Estructura de componentes del motor y juegos**

## Arquitectura Escogida: ECS
Usaremos como base para nuestra arquitectura el modelo Entity Componente System o ECS.

Esta arquitectura tiene 3 componentes básicos:
- **Entidades**: la entidad es la unidad minima de existencia de nuestro juego. Para que algo exista, se renderice o pueda tener parametros asociados habrá de ser una entidad. 
Las entidades no albergan ningún tipo de información en su interior. Pero cada una tiene asignado un identificador implicito gracias a su representación con un SparseSet como se explicará más adelante.
- **Componentes**: contienen unicamente datos serializables y públicos. Es decir, no podrán contener referencias ni punteros. En caso de necesitar un array de datos tendrán un buffer de tamaño constante autocontenido dentro del componente. 
No podrán tener lógica, ni requerir información de otras instancias del mismo componente o de otros distintos. La única manera en la que podrán contener funciones o métodos es cuando estos sean atómicos (se modifican a si mismos para conservar los invariantes de representación) u obtengan infomación implicita en el componente.
Su tamaño debería ser el menor posible.
Cada entidad solo puede tener asociado un componente de cada tipo
- **Sistemas**: contenedores de toda la lógica del juego. No podrán hacer llamadas a otros sistemas, pero si podrán obtener información así como modificarla de los componentes de cualquier entidad existente.
Todos los sistemas llaman a su método initSystem() al crearse, después una vez por bucle de juego llamaran a updateSystem() y por último al finalizar la ejecución del problema llamaran a destroySystem(). 
Los sistemas tienen una flag active. El método update hará return en la primera linea sin hacer nada si esa flag no está activa, es decir si el sistema no está activo.
Una única instancia de cada sistema es creada y gestionada por el system manager. La memoría para todos los sistemas se reserva al comienzo de la ejecución y no se liberará hasta que no se cierre el juego

## Implementación
Usaremos extensivamente SparseSet para representar entidades, componentes y grupos de entidades.
### Estructura de Datos: SparseSet
- Referencia https://skypjack.github.io/2020-08-02-ecs-baf-part-9/
- Contiene un array disperso, de índices; un array denso, de datos(opcional); y un array de backlinks, denso también, de igual tamaño que el de datos, que contiene los índices que se corresponden en el array disperso
- El tamaño que ocupa el set de datos solo se conoceré en runtime, es decir, guardará objetos de tipo desconocido. Pero en ejecución será capaz de devolver el objeto del tipo que realmente almacena.

#### Características
- iteración sobre todos los elementos en O(N) y en memoria contigua
- acceso aleatorio en O(1)
- inserción en O(1)
- borrado en O(1)

#### Objetivo
Esta estructura a cambio de algo más de memoria nos permitirá mejorar el rendimiento.

Y nos facilitará la creación de varias características de nuestro motor. Como son las entidades, componentes, grupos y escenas.

Ser capaces de borrar entidades y componentes en tiempo de ejecución de forma sencilla e inmediata.

#### Implementación
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
##### Inserción en O(1)
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

##### Eliminación en O(1)
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

##### Iteración de todos sus elementos en O(N) y en memoria contigua
Para esto simplemente habremos de recorrer el array de backlinks denso desde el primer elemento hasta el último.

##### Añadiendo Datos
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

### Uso de SparseSet para Entidades y Componentes
Para hacer que buscar entidades con un mismo componente así como poder recorrer todas las entidades usaremos un SparseSet base para todas las entidades y uno por componente.

El **identificador** de cada <u>entidad</u> será el **indice** que ocupen en el <u>Index Disperse Array</u>

Los <u>componentes</u> que ocupen el **indice i** de su <u>array sparse</u> correspondiente serán componentes asociados a la entidad con **identificador i**

De forma que los sparseSet de entidades y componentes estan entrelazados de forma implicita.

#### Añadir Entidades
Para añadir una entidad la añadiremos al SparseSet de entidades.

#### Añadir Componentes
Para añadir un componente necesitamos el id de la entidad a la que queremos añadirselo.
De forma que haremos la operación insertar con el indice de dicha entidad en el SparseSet de ese tipo de componente.

#### Eliminar Componentes
Para eliminar un componente volvemos a necesitar el id de la entidad a la que queremos quitarselo.
Después simplemente haremos la operación eliminar con el indice de dicha entidad en el SparSet de ese tipo de componente.

#### Eliminar una Entidad
Para eliminar una entidad primero usaremos el indice de la entidad para eliminarla en todas los SparseSet de componentes que la contengan.
Después, la eliminaremos de la lista de entidades. 

### Grupos y escenas
Tanto los grupos como escenas serán meramente vectores con los identificadores de los objetos que contienen.

Podemos volver a usar la estructura SparseSet y modelarlos igual que componentes sin información (sin array adicional de datos o cuya suma del espacio en memoria de sus elementos es 0).

Aunque crearemos un capa de abstracción para que conceptualmente sean algo distinto.

### Ejemplo completo
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

## Componentes Base del Motor
### Representation2D
Almacena un textureId. Un textureId será un entero asignado en tiempo de ejecución.

Tiene un flag de un bit que indica si se dibuja en el viewport antes o después de los objetos 3D.

### Representation3D

## Sistemas Base del Motor

### CollisionSystem
Detecta colisiones entre objetos de dos grupos o escenas (no necesariamente distintos).

Contiene el método AddCollisionGroups(ComponentID1, ComponentID2). Ambos ID son enteros asignados en tiempo de ejecución que se corresponden con el id asignado a dichos componentes.

Al comienzo de cada ciclo de juego comprobará las colisiones entre todos los grupos de componentes que se le han añadido hasta el momento. En caso de que exista una colisión se realizará el comportamiento especificado en el apartado [Colisiones](#colisiones)

#### Raycast Collision
Ogre permite usar trazado de rayos para colisioner con las AABBs de objetos en escena: https://wiki.ogre3d.org/tiki-index.php?page=Raycasting+to+the+polygon+level#Method_for_raycast

### Render2DSystem
Itera sobre la lista de objetos con representación 2D y los plasma en pantalla.

Tiene 2 metodos:
- drawBackground(): que se ejecuta antes de hacer la llamada a dibujar los objetos 3D, y que por lo tanto quedará detrás de los objetos 3D.
- drawForeground(): que se ejecuta después de hacer la llamada a dibujar los objetos 3D, y que por lo tanto dibuja por encima de estos.

Si además estos objetos tienen un Transform2D usará la escala, rotación y posición para obtener donde pintar la textura en el Viewport.
En caso de no tener un Transform2D usará rotación 0, posición (0,0) y escala (1,1).

#### Implementación
Podríamos usar SDL para pintar cosas en 2D, pero ya que vamos a usar ogre para dibujar en 3D posiblemente sea más sencillo hacerlo todo con este ultimo.

Aquí hay un ejemplo de código que implementa sprites 2d en Ogre: https://wiki.ogre3d.org/tiki-index.php?page=SpriteManager2d&structure=Cookbook

Para poder decidir cuales se pintan antes que los objetos 3D y cuales después que los objetos 2D asignandoles distintos render queues IDs. Se renderiza del más bajo al más alto. Fuente: https://forums.ogre3d.org/viewtopic.php?p=265546

### Render3DSystem
Itera sobre la lista de objetos con representación 3D y los plasma en la pantalla.

Si además estos objetos tienen un Transform3D usará la escala, orientación y posición para obtener donde pintar el objeto 3D en el Viewport.
En caso de no tener un Transform3D usará rotación Quaternion.Identity, posición (0,0,0) y escala (1,1,1).

Dibujará los objetos teniendo en cuenta cuales son más cercanos a la cámara. Y por lo tanto ocultando aquellos que queden detras suyo con respecto a la posición de la cámara.


# **Pipeline de generación de contenido** 
En pipeline de generación de contenido el motor transforma los archivos externos del juego (mapas, prefabs, scripts y recursos) en entidades y componentes funcionales dentro de la escena.

El proceso será similar al siguiente:

flowchart TD
    A[Archivo de datos] --> B[Lectura]
    B -->|Error| X[Log por consola]
    B -->|OK| C[EntityManager]
    C --> D[ComponentManager]
    D --> E[Scene]

A. Creación de archivos de datos
Se crean los archivos de datos base (.txt, .material, .lua, .png, .wav, .mp3, etc.) que contienen la información necesaria para definir el contenido del juego.

B. Lectura e interpretación de la escena
Al iniciarse el motor, se carga el archivo de escena correspondiente (por ejemplo, un archivo Scene1.txt), el cual describe todas las entidades presentes en la escena, como el mapa del terreno, el jugador, los NPCs y el resto de elementos del juego.
Estos datos son interpretados por un sistema de carga, que valida la información y genera mensajes de log en caso de error (archivo inexistente, recurso no encontrado o formato incorrecto).

En caso de no producirse errores críticos, el sistema de carga crea entidades vacías en el EntityManager y les asigna componentes en función de los datos descritos en el fichero.

C. Creación y almacenamiento de componentes
Cada componente es creado y almacenado en el ComponentManager utilizando estructuras de tipo SparseSet, quedando asociado a su entidad mediante su identificador único.

D. Incorporación a la escena y ejecución
Una vez completada la carga, las entidades pasan a formar parte de la escena activa y pueden ser procesadas por los distintos sistemas del motor durante el bucle principal.