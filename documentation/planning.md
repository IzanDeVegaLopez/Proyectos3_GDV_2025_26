# Índice
- [Metas por hito](#metas-por-hito)
    - [Hito 0](#hito-0)
        - [Arquitectura](#arquitectura)
        - [GDD](#gdd)
        - [Presentación](#presentación)
    - [Hito 1](#hito-1)
    - [Hito 2](#hito-2)
    - [Hito 3](#hito-3)

# Metas por Hito
## Hito 0

- Fecha límite: Viernes 6 de febrero.
- Objetivos: 
    - Planificar el desarrollo del proyecto a lo largo de los tres hitos.
    - Realizar decisiones críticas respecto a las based del motor, incluyendo los siguientes paradigmas de programación:
        - Motor gráfico (OGRE vs Raylib).
        - Patrón de desarrollo (EC vs ECS).
        - Lenguajes de programación a usar en cada apartado del mismo.
        - Convenios de programación y guía de estilo.
    - Redactar documentos relevantes a cada uno de los ámbitos del proyecto.
    - Establecer fechas orientativas y límite para cada uno de los requisitos.
    - Crear grupos especializados en ciertos ámbitos del desarrollo.

### Arquitectura

- Fecha orientativa: Martes 3 de febrero.
- Objetivos:
    - Definir el funcionamiento interno del motor.
    - Determinar el bucle de control del motor y el juego, así como la relación entre estos dos.
    - Establecer el modelo de clases a utilizar en el desarrollo del mismo.
    - Incluir cualquier librería adicional necesaria.

### GDD

- Fecha orientativa: Martes 3 de febrero.
- Objetivos:
    - Definir dos juegos distintos a desarrollar con el motor creado.
    - Establecer su mecánica, dinámica y estética, así como funciones específicas que el motor requiera para que sean realizados.
    - Pesar su alcance y ajustar acorde a las restricciones de tiempo.


### Presentación

- Fecha orientativa: Jueves 5 de febrero.
- Objetivos:
    - Preparar diapositivas con las que demostrar la organización y el progreso actual del proyecto.
    - Asegurarse de que todo el grupo tiene claros los contenidos de la presentación de cara a la exposición oral.

## Hito 1:   
- Fecha límite: Viernes 6 de marzo.
- Objetivos:
    - Librerías compiladas y compilación automática   
    - Primeros componentes sencillos (¡incluso vacíos\!).   
    - Carga de mapas con esos componentes.   
    - “Juegos” en los repositorios con “componentes” (aunque sean vacíos) cargados desde mapas.   
    - Puesta en marcha y bucle principal.  
    - Escenas.

## Hito 2:   

- Fecha límite: Martes 14 de abril.
- Objetivos:
    - Componentes y resto del motor.
    - Avances (seguramente pequeños) en los juegos.

## Hito 3:   

- Fecha límite: Viernes 8 de mayo.
- Objetivos:
    - Juegos y pruebas.
    - 

# Planificación de un hito
La planificación de un hito se hará en el plazo de los tres primeros días de ese hito (Viernes-Sabado-Domingo habitualmente)
Durante esos 3 primeros días se organizará lo siguiente
- Backlog de tareas a realizar en ese hito
- Posibles divisiones del grupo en función de la tareas

Cada hito estará dividido en sprints de una semana de duración.

# Planificación de un sprint
El primer día del sprint deberán quedar fijadas todas las tareas a llevar a cabo durante esa semana. 
El primer día del sprint (Viernes) cada persona deberá tener asignada una tarea por la que comenzar.

## Objetivo
- Tener un ejecutable estable al final de la semana. El commit a partir del que se pueda generar este ejecutable estará marcado con un tag.
- Avanzar en el desarrollo todo lo posible
- Encontrar y arreglar los bugs la semana en la que surjan.

## Fechas
- Día 1: planificación
- Día 5: todas las tareas completadas y revisión de tareas
- Día 6-7: Revisión - Bugfixing - Generar ejecutable en debug y en release y comprobar que funciona

Si durante el día 6-7 sobra tiempo se hará la planificación del siguiente sprint. Y si sigue sobrando se podrán comenzar las tareas del siguiente sprint, pero deberá hacerse en un rama para tener un ejecutable estable por semana.

Para organizar el sprint se usará la pizarra de tareas del github desktop
## Pizarra de tareas
### Normas de uso
- Cada persona podrá tener una única tarea asignada a la vez
- Cada tarea podrá tener una única persona asignada a la vez
### Columnas
- Backlog --> tareas por realizar durante el hito actual
- Todo --> tareas por realizar durante el sprint actual
- Current --> tareas con persona asignada y en las que se está trabajando actualmente
- Revision --> tareas consideradas terminadas por la persona que las hizo. Otra persona diferente tiene que revisarlas, cuando lo haga se podrán mover a terminadas
- Bugs --> tareas creadas especificamente tras detectar un error. Al detectar un error habrá que escribir un aviso en el canal bugs de discord con el link a esta tarea.
- Finished --> tareas revisadas y terminadas

# Planificación de una tarea
## Características de una tarea
- **Titulo:** Nombre descriptivo. Debe dejar claro de que area de especialización es la tarea. 
- **Peso:** Deberá estar pesada en días que se tarda en realizarla. La escala es la siguiente ( < 1 día, 1 día, 2 días, 4 días, 1 semana). **No podrá haber tareas con duración mayor a una semana** si esto se da habrá que dividir la tarea en otras más pequeñas de forma inmediata
- **Descripción:** Descripción a fondo de la tarea, si se ha planteado alguna forma de resolver alguno de los problemas que plantea deberá exponerse aquí
- **Checklist:** Lista ordenada por orden de implementación. Para que una tarea se considere terminada debe cumplir todas las condiciones en esta lista.
- **Fecha:** Fecha en la que tiene que estar finalizada la tarea. Esta fecha es una semana que corresponderá con uno de los sprints del hito.
- **Prioridad:** importancia de la tarea.
    - Urgente: tiene otras del mismo sprint que depende de ella
    - Alta: otras tareas del siguiente sprint lo hacen.
    - Media: otras tareas del hito depende de ella.
    - Baja: solo dependen de ella tareas del siguiente hito
    - Muy baja: es opcional
- **Asignado:** persona que se encargará de ella. Este campo debería estar vacio si no hay nadie trabajando en ella del momento
- **Revisor:** persona que la revisará y la dará por finalizada. Este campo debería estar vacio si se sigue trabajando en la tarea.
- **Relaciones:** tareas de las que depende. Si una tarea no se puede comenzar hasta que no se terminen otras. Esas otras deberán estar en ese campo.

# Bugs
Cuando surja un bug se deberá crear una nueva tarea en la columna de bugs y avisar con un mensaje en el canal bugs de discord (con un link a esa tarea)

# Ejecutables Estables
Al final de cada semana se generará un ejecutable funcional y estable. El commit a partir del cual se pueda generar dicho ejecutable estará marcado por un tag.

El tag tendrá el siguiente nombre:

X.Y.Z
- X será el hito en el que se hace
- Y será la semana de dicho hito (con índice 0)
- Z será la versión que de dicho ejecutable (con indice 0). Este último número solo está por si se consiguen implementar alguna cosa que inicialmente no se preveyese en el primer ejecutable de esa semana.
