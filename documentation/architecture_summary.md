# Resumen

## Características del Motor
- Sonido
- Carga y renderizado de Mallas 3D
- Renderizado 2D de texturas en pantalla (UI)
- Lectura de escenas por medio de ficheros LUA
- Input de teclado y ratón
- Detección de colisiones 3D y evitar que unos objetos se metan dentro de otros (que alguien encuentre la palabra chula para esto)
- Hacer código con cpp

## Librerias usadas
- Ogre3D -> render 2D y 3D, uso de AABB para colisiones
- SDL -> input
- FMOD -> sonido

## Uso de LUA
Carga de mapas.
Receta para crear entidades con componentes con atributos determinados

Con interprete SWIG --> permite conservar el alineamiento de los componentes entre LUA y cpp

## Arquitectura
ECS
- Entidades: son solo un ID
- Componentes: solo contienen datos serializables y públicos
- Sistemas: pueden acceder a los datos almacenados por cualquier componente de cualquier entidad

## Estructura de Datos SparseSet
A cambio de un poco de memoria extra nos dan mucho mejor rendimiento
(Incluir imagen simplificada con flechitas del esquema de la estructura)

Los componentes de la entidad i tienen todos indice i en su array disperso
Operaciones básicas en O(1) -> inserción, eliminación y acceso aleatorio
Memoria de datos contigua

## Comunicación Motor-Juego
Main en el motor

El **juego** expone al motor solo 3 funciones:
- initGame()
- updateGame()
- exitGame()
El motor busca en el dll las funciones en runtime por nombre. Solo puede haber una de cada y tienen que tener el nombre correcto.

Motor expone funciones al juego con una macro
__declspec(dllexport) / __declspec(dllimport)

## Ogre
Usaremos **escenas aditivas** con una stack de escenas.

Tendremos una pila de vectores de SceneNodes. Cada escena es un vector en la pila. Y el motor guardará internamente los scene nodes asociados al componente tasy_node de cada entidad.