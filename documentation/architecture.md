# Indice

**[Estructura de la solución y proyectos (y repositorios de Git)	2](#estructura-de-la-solución-y-proyectos-\(y-repositorios-de-git\))**

[**Estructura de las clases	3**](#estructura-de-las-clases)

[**Estructura de componentes del motor y juegos	4**](#estructura-de-componentes-del-motor-y-juegos)

[**Pipeline de generación de contenido	5**](#pipeline-de-generación-de-contenido)

# 

# **Estructura de la solución y proyectos (y repositorios de Git)**  {#estructura-de-la-solución-y-proyectos-(y-repositorios-de-git)}

# **Estructura de las clases**  {#estructura-de-las-clases}

---
**Leyenda de los diagramas:**

"*function() \: returnType*"

Prefijos:
- \+ Public
- \- Private
- \# Protected

Sufijos
- \$ Static
- \* Abstract
---

```mermaid
---
title: Class Diagram
---
classDiagram
    note "From Duck till Zebra"
    Animal <|-- Duck
    note for Duck "can fly\ncan swim\ncan dive\ncan help in debugging"
    Animal <|-- Fish
    Animal <|-- Zebra
    Animal : +int age
    Animal : +String gender
    Animal: +isMammal()
    Animal: +mate()
    class EntityManager{
        -SparseSet allEntities
		-vector<EntityList&> mGroups
		-vector<EntityList&> mScenes
		+Component& getComponent(int entityId)
		+GetEntitiesInGroup(int entityGroupId) DenseArray~EntityId~&
		+GetEntitiesInScene(int entitySceneId) DenseArray~EntityId~&
		+markEntityAsDead(int entityId)
		+update()
		-mEraseAllDeadEntities()
    }
    class SparseSet{
		+vector<int> mDenseList
		+vector<int> mSparseSet
		+iterator
		+begin()
		+end()
    }
    class DenseArray~T~{
        +vector~T~ mVector
		+int nElementos
		+begin()
		+end()
		+mEraseElement(int index)
    }
```

**Clases Importantes**

*EntityManager*
- Contiene la lista (SparseSet) con todas las entidades vivas.
- Contiene los grupos y escenas. Estos solo son listas con los identificadores de las entidades que contienen
- Es el responsable de que todas las entidades que contiene sean validas. Para ello en su update, al inicio de cada bucle de juego recorrera todos los grupos y escenas eliminando de ellos las entidades marcadas como muertas. Después de esto y secuencialmente eliminará dichas entidades del SparseSet allEntities.
- Una vez haya eliminado todas las entidades muertas procederá a insertar en los grupos y escenas correspondientes a todas aquellas entidades que fueron creadas durante el anterior frame. Estas se almacenan en entitiesCreatedLastFrameQueue

*DenseArray*
- Almacena un vector con capacidad de borrar y añadir elementos
- Al añadir el elemento se coloca el último en el vector
- Al eliminar un elemento, el último del vector se coloca en la posición del eliminado. Y después el número de elementos del vector se reduce en 1. El tamaño real del vector no se reduce, pero posteriormente al intentar acceder a un elemento guardado en un indice no inferior al número de elementos se lanzará un error
- Permiten recorrerlos con iteradores. Los iteradores tienen en cuenta el número de elementos para finalizar su recorrido


# **Estructura de componentes del motor y juegos**  {#estructura-de-componentes-del-motor-y-juegos}

Arquitectura basada en:  
EC:  
	**Componentes**: contienen datos y lógica  
ECS: ←  
**Componentes**: contienen datos. Hay listas que contienen todos los elementos con un mismo componente.  
**Sistemas**: contienen lógica. Se decide el orden de procesamiento de los sistemas. Y una única instancia de cada sistema (no pueden existir más) se ejecutará una vez por cada vuelta del bucle jugable. Los sistemas pueden acceder a las listas de todas las entidades con un mismo componente. Y obtener a partir de una entidad otros componentes de esta.

# **Pipeline de generación de contenido**  {#pipeline-de-generación-de-contenido}
