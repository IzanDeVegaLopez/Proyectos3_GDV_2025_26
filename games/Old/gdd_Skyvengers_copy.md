# Skyvengers - Game Design Document

### Equipo de desarrollo: 


**Integrantes:**  
- Paula Alemany Rodríguez
- Óscar Melquiades Durán Narganes 
- Denisa Juarranz Berindea  
- José Narciso Robles Durán
- Izan de Vega López   
- David Palacios Daza
- Amiel Ramos Juez  
- Álvaro Piña Sánchez-Sierra
- Hugo de Brito Rocha

## ÍNDICE  
1. [Resumen](#1-resumen)  
   1.1. [Descripción](#11-descripción)  
   1.2. [Género](#12-género)  
   1.3. [Público objetivo](#13-público-objetivo)  
   1.4. [Setting](#14-setting)  
   1.5. [Características principales](#15-características-principales)  

2. [Gameplay](#2-gameplay)  
   2.1. [Objetivo del juego](#21-objetivo-del-juego)  
   2.2. [Core loops](#22-core-loops)  

3. [Mecánicas](#3-mecánicas)  
   3.1. [Mecánica 1](#31-mecánica-1)  

4. [Interfaz](#4-interfaz)  
   4.1. [Controles](#41-controles)  
   4.2. [Cámara](#42-cámara)  
   4.3. [HUD](#43-hud)  
   4.4. [Menús](#44-menús)  

5. [Mundo del juego](#5-mundo-del-juego)  
   5.1. [Personajes](#51-personajes)  
   5.2. [Niveles](#52-niveles)  

6. [Experiencia de juego](#6-experiencia-de-juego)  
   6.1. [Dinámicas Buscadas](#61-dinámicas-buscadas)  
   6.2. [Descripción de Partida](#62-descripción-de-partida)

7. [Estética y contenido](#7-estética-y-contenido)  

8. [Referencias](#8-referencias)  

9. [Testing](#9-testing)  


## 1. Resumen  


### 1.1. Descripción  
   Juego de carreras de aviones en el que el jugador compite contra pilotos controlados por inteligencia artificial con el objetivo de completar un número determinado de vueltas en el menor tiempo posible.
### 1.2. Género  
   Carreras
### 1.3. Público objetivo

### 1.4. Setting  
   Circuitos pequeños y cerrados en torno a un aeródromo, con giros y obstáculos que dificultarán el paso.
### 1.5. Características principales  
- Un jugador
- Colisiones con el entorno
- Aceleración gradual

## 2. Gameplay  

### 2.1. Objetivo del juego   
Completar un número determinado de vueltas antes que los contrincantes. Para ello, el jugador debe atravesar todo el circuito y pasar la línea de salida y meta tantas veces como vueltas haya.

### 2.2. Core loops  

1. Menú principal
2. Comenzar carrera
3. Partir desde la salida
4. Atravesar el circuito
5. Llegar a la meta
6. Si el número de vueltas completadas es igual al número de vueltas requerido, continuar. De lo contrario, volver al paso 3.
7. Concluir carrera
8. Recibir resultados
9. Volver al paso 1

- El bucle será interrumpido en el caso de que el jugador quiera salir del juego, independientemente de su estado actual.


## 3. Mecánicas  

### 3.1. Movimiento
Cada avión se propulsará hacia delante automáticamente, acumulando velocidad sin necesitar ninguna intervención por parte del jugador. Este únicamente será capaz de rotar su propio avión, cambiando la dirección en la que se propulsa continuamente; así como frenarlo en el caso de que quiera realizar movimientos de mayor precisión. Esto no detendrá el avión completamente, pero disminuirá su velocidad.

### 3.2. Colisiones
Los aviones serán capaces de entrar en contacto con obstáculos, incluyendo las paredes del circuito. En el caso de chocarse contra un obstáculo, el avión será frenado y deberá acumular velocidad de nuevo.

## 4. Interfaz  

### 4.1. Controles  
- Movimiento: ASD / LS.  El jugador únicamente puede rotar y frenar el avión, por lo que no existe un botón para acelerar.

### 4.2. Cámara  
- La cámara será isométrica y con vista de pájaro, y tendrá una posición definida por la interpolación entre el centro del mapa y la posición del avión pilotado por el jugador. Esto permitirá tener al jugador como punto de enfoque sin limitar el campo de visión excesivamente.

### 4.3. HUD  
- La interfaz del juego mostrará tres elementos de interés: El número de vueltas actual del jugador; el número de vueltas total; y el tiempo total transcurrido.

//insertar ruta absoluta de la imagen 
![HUD](https://github.com/...)

### 4.4. Menús  
- **Menú principal**
    - Jugar.
    - Salir.
![image]()

- **Menú de Fin de Juego**
    - Menú principal.
    - Salir del Juego.
![Boceto HUD]()

## 5. Mundo del juego  

### 5.1. Personajes  
- **Jugador:** 


- **Enemigos:**

### 5.2. Niveles  

## 6. Experiencia de juego  

### 6.1. Dinámicas Buscadas
- Aceleración gradual y rápida
- Pruebas de habilidad puntuales
- Tensión continua

### 6.2. Descripción de Partida
Los aviones comienzan cada carrera desde la línea de salida y meta. A lo largo de cada vuelta, tanto el jugador como los aviones controlados por IA deben tomar varios giros con suficiente velocidad para no quedarse atrás; pero al mismo tiempo con cuidado de no entrar con demasiada velocidad y chocarse con los bordes, lo que resultará en una pérdida mayor. Cuando el jugador pasa la línea de meta, el contador de vueltas aumenta, finalmente concluyendo la carrera una vez se hayan completado todas las vueltas requeridas. Cuando se dé este evento, el jugador será calificado en función de su posición final, tras lo que puede volver al menú principal y comenzar otra carrera.

## 7. Estética y contenido  
**Estética:**


**Contenido:**  

  

## 8. Referencias  
- Later Skater - Minijuego de Mario Party 5 (2003)

##  9. Testing
