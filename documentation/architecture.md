# Indice

**[Estructura de la solución y proyectos (y repositorios de Git)	2](#estructura-de-la-solución-y-proyectos-\(y-repositorios-de-git\))**

[**Estructura de las clases	3**](#estructura-de-las-clases)

[**Estructura de componentes del motor y juegos	4**](#estructura-de-componentes-del-motor-y-juegos)

[**Pipeline de generación de contenido	5**](#pipeline-de-generación-de-contenido)

# 

# **Estructura de la solución y proyectos (y repositorios de Git)**  {#estructura-de-la-solución-y-proyectos-(y-repositorios-de-git)}

# **Estructura de las clases**  {#estructura-de-las-clases}

# **Estructura de componentes del motor y juegos**  {#estructura-de-componentes-del-motor-y-juegos}

Arquitectura basada en:  
EC:  
	**Componentes**: contienen datos y lógica  
ECS: ←  
**Componentes**: contienen datos. Hay listas que contienen todos los elementos con un mismo componente.  
**Sistemas**: contienen lógica. Se decide el orden de procesamiento de los sistemas. Y una única instancia de cada sistema (no pueden existir más) se ejecutará una vez por cada vuelta del bucle jugable. Los sistemas pueden acceder a las listas de todas las entidades con un mismo componente. Y obtener a partir de una entidad otros componentes de esta.

# **Pipeline de generación de contenido**  {#pipeline-de-generación-de-contenido}