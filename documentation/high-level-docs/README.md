# ECSTasy: Documentación de API top-level

## Tipo `tasy::engine`

### Ejemplos

<!-- TODO -->

### Tipos relacionados

#### Tipo `tasy::entity`

`tasy::entity` es el identificador de una entidad en el motor. Dependiendo del estado del motor podría hacer referencia a una entidad válida (existente) o a una entidad no válida (no existente).

Se garantiza que el tipo `tasy::entity` es un tipo de datos trivial. Se puede copiar, mover, comparar sin ningún "overhead". Se puede pensar en el tipo como un número entero. Su implementación podría ser:

```c++
using entity = std::uint64_t;
```

<!-- TODO: stability -->

### Inicialización y deinicialización

<!-- TODO -->

### Entidades

<!-- TODO -->

### Componentes

<!-- TODO -->

#### Componentes built-in

<!-- TODO -->

### Recursos

<!-- TODO -->

### Funciones

#### Función `tasy::engine::allocate_entity`

```c++
tasy::entity tasy::engine::allocate_entity(void);
```

Reserva una nueva entidad en el motor y devuelve su identificador.

Tras obtener la entidad garantiza que ninguna llamada sucesiva a `tasy::engine::allocate_entity` devolverá el mismo identificador de entidad, a menos que se haya liberado explícitamente la entidad previamente reservada con `tasy::engine::free_entity`.

Solo se aloca el identificador de entidad. No se reserva ningún tipo de memoria adicional para componentes que esta pueda tener. Por lo que esta llamada tiene un coste amortizado `O(1*)`.

#### Función `tasy::engine::free_entity`

```c++
void tasy::engine::free_entity(const tasy::entity entity);
```

Libera una entidad previamente reservada con `tasy::engine::allocate_entity`.

Implica que tras liberar la entidad el mismo identificador de entidad podría volver a ser reservado y devuelto al usuario nuevamente con `tasy::engine::allocate_entity`.

<!-- #####  TODO: Errores? Abortar? Condiciones? -->
