<!-- TOC start (generated with https://github.com/derlin/bitdowntoc) -->
# Índice

- [Metas por Hito](#metas-por-hito)
   * [Hito 0](#hito-0)
      + [Arquitectura](#arquitectura)
      + [GDD](#gdd)
      + [Presentación](#presentación)
   * [Hito 1:   ](#hito-1)
   * [Hito 2:   ](#hito-2)
   * [Hito 3:   ](#hito-3)
- [Metas por semanas](#metas-por-semanas)
   * [Semana 6-2](#semana-6-2)
   * [Semana 13-2](#semana-13-2)
   * [Semana 20-2](#semana-20-2)
   * [Semana 27-2](#semana-27-2)
   * [Semana 6-3](#semana-6-3)
   * [Semana 13-3](#semana-13-3)
   * [Semana 20-3](#semana-20-3)
   * [Semana 27-3](#semana-27-3)
- [Planificación de un hito](#planificación-de-un-hito)
- [Planificación de un sprint](#planificación-de-un-sprint)
   * [Objetivo](#objetivo)
   * [Fechas](#fechas)
   * [Pizarra de tareas](#pizarra-de-tareas)
      + [Normas de uso](#normas-de-uso)
      + [Columnas](#columnas)
- [Planificación de una tarea](#planificación-de-una-tarea)
   * [Características de una tarea](#características-de-una-tarea)
- [Bugs](#bugs)
- [Ejecutables estables](#ejecutables-estables)
- [Comunicación](#comunicación)
- [Presentaciones](#presentaciones)
- [Sistema de control de versiones](#sistema-de-control-de-versiones)
   * [Remoto y Local](#remoto-y-local)
   * [Ramas](#ramas)
- [Compilación y Ejecución del proyecto](#compilación-y-ejecución-del-proyecto)
- [Documentación del código](#documentación-del-código)

<!-- TOC end -->

<!-- TOC --><a name="metas-por-hito"></a>
# Metas por Hito
<!-- TOC --><a name="hito-0"></a>
## Hito 0

- Fecha límite: Viernes 6 de febrero.
- Objetivos: 
    - Planificar el desarrollo del proyecto a lo largo de los tres hitos.
    - Realizar decisiones críticas respecto a las bases del motor, incluyendo los siguientes paradigmas de programación:
        - Motor gráfico (OGRE vs Raylib).
        - Patrón de desarrollo (EC vs ECS).
        - Lenguajes de programación a usar en cada apartado del mismo.
        - Convenios de programación y guía de estilo.
    - Redactar documentos relevantes a cada uno de los ámbitos del proyecto.
    - Establecer fechas orientativas y límite para cada uno de los requisitos.
    - Crear grupos especializados en ciertos ámbitos del desarrollo.

<!-- TOC --><a name="arquitectura"></a>
### Arquitectura

- Fecha orientativa: Miércoles 4 de febrero.
- Objetivos:
    - Definir el funcionamiento interno del motor.
    - Determinar el bucle de control del motor y el juego, así como la relación entre estos dos.
    - Establecer el modelo de clases a utilizar en el desarrollo del mismo.
    - Incluir cualquier librería adicional necesaria.

<!-- TOC --><a name="gdd"></a>
### GDD

- Fecha orientativa: Miércoles 4 de febrero.
- Objetivos:
    - Definir dos juegos distintos a desarrollar con el motor creado.
    - Establecer su mecánica, dinámica y estética, así como funciones específicas que el motor requiera para que sean realizados.
    - Pesar su alcance y ajustar acorde a las restricciones de tiempo.


<!-- TOC --><a name="presentación"></a>
### Presentación

- Fecha orientativa: Jueves 5 de febrero.
- Objetivos:
    - Preparar diapositivas con las que demostrar la organización y el progreso actual del proyecto.
    - Asegurarse de que todo el grupo tiene claros los contenidos de la presentación de cara a la exposición oral.
    - Dividir la presentación y los contenidos en tres bloques diferenciados.

<!-- TOC --><a name="hito-1"></a>
## Hito 1:   
- Fecha límite: Viernes 6 de marzo.
- Objetivos:
    - Librerías compiladas y compilación automática
    - Primeros componentes sencillos (¡incluso vacíos\!).
    - Prototipo de carga de mapas básicos con esos componentes (LUA).
    - “Juegos” en los repositorios con “componentes” (aunque sean vacíos) cargados desde mapas.
    - Puesta en marcha y bucle principal.  
    - Escenas (idealmente con alguna malla que vayamos a utilizar renderizada)

<!-- TOC --><a name="hito-2"></a>
## Hito 2:   

- Fecha límite: Martes 14 de abril.
- Objetivos:
    - Componentes y resto del motor.
    - Avances (medianos/grandes) en los juegos.

<!-- TOC --><a name="hito-3"></a>
## Hito 3:   

- Fecha límite: Viernes 8 de mayo.
- Objetivos:
    - Juegos y pruebas.

<!-- TOC --><a name="metas-por-semanas"></a>
# Metas por semanas
<!-- TOC --><a name="semana-6-2"></a>
## Semana 6-2
- Lectura de datos de un fichero lua interpretado
- Estructura de datos Sparse Set
- Estructura de datos any_vector
- Asignación automática de ID de las entidades
- Componentes unidos a entidades
- Llamadas a funciones especiales del juego desde el motor
- Llamadas a funciones del motor desde el juego
- Creación y llamadas a sistemas del motor en el main
- Organización en carpetas
<!-- TOC --><a name="semana-13-2"></a>
## Semana 13-2
- Unión con Ogre
- Unión con SDL para el input
- Unión con FMOD
- Compilación automática
<!-- TOC --><a name="semana-20-2"></a>
## Semana 20-2
<!-- TOC --><a name="semana-27-2"></a>
## Semana 27-2
<!-- TOC --><a name="semana-6-3"></a>
## Semana 6-3
<!-- TOC --><a name="semana-13-3"></a>
## Semana 13-3
<!-- TOC --><a name="semana-20-3"></a>
## Semana 20-3
<!-- TOC --><a name="semana-27-3"></a>
## Semana 27-3



<!-- TOC --><a name="planificación-de-un-hito"></a>
# Planificación de un hito
La planificación de un hito se hará en el plazo de los tres primeros días de ese hito (Viernes-Sabado-Domingo habitualmente)
Durante esos 3 primeros días se organizará lo siguiente:
- Backlog de tareas a realizar en ese hito en la pizarra de tareas de GitHub.
- Posibles divisiones del grupo en función de las tareas.
- Planificación del primer sprint.

Cada hito estará dividido en sprints de una semana de duración.

<!-- TOC --><a name="planificación-de-un-sprint"></a>
# Planificación de un sprint
El primer día del sprint deberán quedar fijadas todas las tareas a llevar a cabo durante esa semana.
El primer día del sprint cada persona deberá tener asignada una tarea por la que comenzar.

<!-- TOC --><a name="objetivo"></a>
## Objetivo
- Tener un ejecutable estable al final de la semana. El commit a partir del que se pueda generar este ejecutable estará marcado con un tag.
- Avanzar en el desarrollo todo lo posible.
- Encontrar y arreglar los bugs la semana en la que surjan.

<!-- TOC --><a name="fechas"></a>
## Fechas
- Día 1: planificación.
- Día 5: todas las tareas completadas y revisión de tareas.
- Día 6-7: Revisión - Bugfixing - Generar ejecutable en debug y en release y comprobar que funciona.

Si durante el día 6-7 sobra tiempo se hará la planificación del siguiente sprint. Y si sigue sobrando se podrán comenzar las tareas del siguiente sprint, pero deberá hacerse en un rama para tener un ejecutable estable por semana.

En este caso, los sprints empezarán los viernes.

Para organizar el sprint se usará la pizarra de tareas del Github desktop.
<!-- TOC --><a name="pizarra-de-tareas"></a>
## Pizarra de tareas
<!-- TOC --><a name="normas-de-uso"></a>
### Normas de uso
- Cada persona podrá tener una única tarea asignada a la vez.
- Cada tarea podrá tener una única persona asignada a la vez.
<!-- TOC --><a name="columnas"></a>
### Columnas
- Backlog --> tareas por realizar durante el hito actual.
- Todo --> tareas por realizar durante el sprint actual.
- Current --> tareas con persona asignada y en las que se está trabajando actualmente.
- Revision --> tareas consideradas terminadas por la persona que las hizo. Otra persona diferente tiene que revisarlas, cuando lo haga se podrán mover a terminadas.
- Bugs --> tareas creadas específicamente tras detectar un error. Al detectar un error habrá que escribir un aviso en el canal bugs de Discord con el link a esta tarea.
- Finished --> tareas revisadas y terminadas.

<!-- TOC --><a name="planificación-de-una-tarea"></a>
# Planificación de una tarea
<!-- TOC --><a name="características-de-una-tarea"></a>
## Características de una tarea
- **Titulo:** Nombre descriptivo. Debe dejar claro el área de especialización de la tarea. 
- **Peso:** Deberá estar pesada en días que se tarda en realizarla. La escala es la siguiente ( < 1 día, 1 día, 2 días, 4 días, 1 semana). **No podrá haber tareas con duración mayor a una semana.** Si esto se da habrá que dividir la tarea en otras más pequeñas de forma inmediata.
- **Descripción:** Descripción a fondo de la tarea. Si se ha planteado alguna forma de resolver alguno de los problemas que plantea deberá exponerse aquí.
- **Checklist:** Lista ordenada por orden de implementación. Para que una tarea se considere terminada debe cumplir todas las condiciones en esta lista.
- **Fecha:** Fecha en la que tiene que estar finalizada la tarea. Esta fecha es una semana que corresponderá con uno de los sprints del hito.
- **Prioridad:** importancia de la tarea:
    - Urgente: tiene otras del mismo sprint que depende de ella.
    - Alta: otras tareas del siguiente sprint lo hacen.
    - Media: otras tareas del hito depende de ella.
    - Baja: solo dependen de ella tareas del siguiente hito.
    - Muy baja: es opcional
- **Asignado:** persona que se encargará de ella. Este campo debería estar vacío si no hay nadie trabajando en ella del momento.
- **Revisor:** persona que la revisará y la dará por finalizada. Este campo debería estar vacío si se sigue trabajando en la tarea.
- **Relaciones:** tareas de las que depende. Si una tarea no se puede comenzar hasta que no se terminen otras. Esas otras deberán estar en ese campo.

<!-- TOC --><a name="bugs"></a>
# Bugs
Cuando surja un bug se deberá crear una nueva tarea en la columna de bugs y avisar con un mensaje en el canal bugs de discord (con un link a esa tarea).

En la descripción de esa tarea se explicará:
- Qué es lo que se esperaba que pasase.
- Qué ha pasado
- Cómo se ha desencadenado el bug.
- Cómo replicarlo (si se conoce la manera).
- La frecuencia en la que ocurre. 

<!-- TOC --><a name="ejecutables-estables"></a>
# Ejecutables estables
Al final de cada semana se generará un ejecutable funcional y estable. El commit a partir del cual se pueda generar dicho ejecutable estará marcado por un tag.

El tag tendrá el siguiente nombre:

X.Y.Z
- X será el hito en el que se hace.
- Y será la semana de dicho hito (con índice 0).
- Z será la versión de dicho ejecutable (con índice 0). Este último número solo está por si se consigue implementar alguna cosa que inicialmente no se anticipó en el primer ejecutable de esa semana.

<!-- TOC --><a name="comunicación"></a>
# Comunicación
Usaremos Discord para hablar entre nosotros.

Dividiremos las conversaciones por distintos canales e hilos según creamos conveniente.

Hemos añadido un bot (https://readybot.io) al server para que mande un mensaje con los titulos de los commits que hagamos en main.

<!-- TOC --><a name="presentaciones"></a>
# Presentaciones
Usaremos Canva para crear las presentaciones de los hitos.

<!-- TOC --><a name="sistema-de-control-de-versiones"></a>
# Sistema de control de versiones
Usaremos Github aprovechando que nos da la pizarra de tareas integrada, y el uso de Github Desktop para simplificar los trámites.

<!-- TOC --><a name="remoto-y-local"></a>
## Remoto y Local
De forma normal solo se podrá pushear al repositorio remoto cuando la tarea completa se consideré terminada por quien la hizo.
Cuando quiera pushear primero deberá:
- Hacer fetch y pull del remoto.
- Comprobar que se puede compilar.
- Comprobar que se puede ejecutar.
- Comprobar que todo funciona sin errores apreciables y como era la intención.
Después de todo esto podrá pushear a main.

<!-- TOC --><a name="ramas"></a>
## Ramas
En nuestro proyecto no crearemos ramas en remoto a la hora de desarrollar a menos que sea necesario.

Casos en los que se considera válido pushear un rama a remoto:
- Para continuar adelantando trabajo para el siguiente sprint después de generar el ejecutable. Así conseguiremos que la última versión en main sea el ejecutable de esa semana.
- Para debuggear problemas en el desarrollo de una tarea realizada por un compañero. La rama se destruirá en cuanto se arregle el problema y pueda ser pusheado a main.
- Para guardar temporalmente trabajo inacabado en los laboratorios.

<!-- TOC --><a name="compilación-y-ejecución-del-proyecto"></a>
# Compilación y Ejecución del proyecto
Usaremos Cmake. Esto nos permitirá desarrollar en distintos IDEs, conseguir la estructura de carpetas que buscamos y ejecutar el proyecto cargando las librerías o ficheros necesarios (entre los que se encuentran los juegos). Todo esto de forma lightweight.

<!-- TOC --><a name="documentación-del-código"></a>
# Documentación del código
Todas las funciones, clases, métodos y atributos públicos no triviales deberán estar acompañadas de un comentario que explique su finalidad, parámetros y forma de uso. De forma que cualquier persona pueda usarlas fácilmente con tan solo ver el comentario.

Los nombres de los parámetros, métodos y clases deberán ser autoexplicativos para facilitar la comprensión.

Para más detalles sobre la sintaxis ver el documento [style_guide.md](style-guide.md).
