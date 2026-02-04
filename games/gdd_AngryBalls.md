# Angry Balls
***Subtítulo Página Web*** 🌐 **[Página web del juego](https://www.youtube.com/watch?v=dQw4w9WgXcQ)**  


---
# *Documento de diseño del juego*
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
   1.4. [Ambientación y tono](#14-Ambientación-y-tono)  
   1.5. [Características principales](#15-características-principales)  

2. [Jugabilidad](#2-Jugabilidad)  
   2.1. [Objetivo del juego](#21-objetivo-del-juego)  
   2.2. [Ciclo de juego](#22-Ciclo-de-juego)  

3. [Mecánicas](#3-mecánicas)  
   3.1. [Movimiento](#31-Movimiento)  

4. [Interfaz](#4-interfaz)  
   4.1. [Controles](#41-controles)  
   4.2. [Cámara](#42-cámara)  
   4.3. [HUD](#43-hud)  
   4.4. [Menús](#44-menús)  

5. [Mundo del juego](#5-mundo-del-juego)  
   5.1. [Personajes](#51-personajes)  
   5.2. [Niveles](#52-niveles)  

6. [Experiencia de juego](#6-experiencia-de-juego)  

7. [Estética y contenido](#7-estética-y-contenido)  

8. [Referencias](#8-referencias)  

9. [Testing](#9-testing)  


## 1. Resumen  

### 1.1. Descripción  
Eres un caza demonios que busca capturar todos los AngryBalls posibles. Para ello destroza a los enemigos con tu ametralladora y trata de evitar que te maten escondiendote entre muros.

### 1.2. Género  
FPS arcade

### 1.3. Público objetivo
Adultos

### 1.4. Ambientación y tono  
La acción se desarrolla dentro de una torre antigüa con una estética algo oscura.

### 1.5. Características principales  
- //Tampoco se muy bien que esperais aqui

## 2. Jugabilidad  
Consiste en una vista en primera persona con una mirilla para apuntar y disparar. Hay que moverse por el escenario ocultandose en las diferentes coberturas para matar a los enemigos disparandoles y evitar que te den sus balas. Cuando una sala termina podrás subir una escalera para pasar a la siguiente y así hasta morir o llegar al final.

### 2.1. Objetivo del juego   
Conseguir la mayor cantidad de AngryBalls posibles.

### 2.2. Ciclo de juego
//insertar ruta absoluta de la imagen en el proyecto
![Diagrama de flujo](https://github.com/organizacion/repo/blob/main/docs/img/imagen.jpg)

1. Empiezas una sala nueva.
2. Matas a los enemigos pertinentes.
3. Aparece un enemigo un poco más fuerte.
4. Consigues una recompensa.
5. Pasas a la siguiente sala.

//Podría ser interesante que puedas cambiar de sala cuando despejas a los enemigos y que el "boss" sea opcional para conseguir más puntuación, por ahora lo dejo como idea hasta esta noche


## 3. Mecánicas  

### 3.1. Movimiento

**Parámetros:**  
-  Posición (x, y) (ignoramos la altura)
-  Velocidad
El jugador y los enemigos podrán moverse por el plano (x, y) con libertad.

### 3.2. Disparo

**Parámetros:**  
-  Posición (x, y)
-  Velocidad
-  Dirección
-  Origen (Si es un disparo enemigo o del jugador)
El jugador y los enemigos podrán disparar un máximo de 3 balas a la vez, es decir, cada personaje solo podrá "tener" 3 balas en pantalla.
Si una bala enemiga colisiona con el jugador le quitará parte de la vida y lo mismo sucederá a la inversa con las balas del jugador y los enemigos.


## 4. Interfaz  

### 4.1. Controles  
- Movimiento: WASD.
- Disparo: click izquierdo del ratón.

### 4.2. Cámara  
La cámara es en primera persona y se moverá con el ratón y siempre se dispara en la dirección del centro de la cámara.


### 4.3. HUD  
//insertar ruta absoluta de la imagen 
![HUD](https://github.com/...)

//Habría que poner un esquemita o algo de como se ve la vida del jugador la puntuación y esas cosas

### 4.4. Menús  
- **Menú principal**
    - Jugar.
    - Salir.
    - Estadísticas.
![image]()

- **Menú de Fin de Juego**
    - Menú principal.
    - Salir del Juego.
![Boceto HUD]()

## 5. Mundo del juego  

### 5.1. Personajes  
- **Jugador:** 
  //imagenes
  <img src="https://github.com/ruta.png" alt="Jugador 1" />

- **Enemigos:**
  //imagenes
  <img src="https://github.com/ruta.png" alt="Enemigo 1" />

### 5.2. Niveles 
- **Nivel 1:**
- **Nivel 2:**

### 5.3. Objetos del mundo 
- **Coberturas:**
   Existen dos tipos de cobertura: la cobertura completa y la cobertura parcial.
   **Cobertura completa:** Las balas de los enemigos no podrán darte de ninguna manera.
   **Cobertura parcial:** Existe un 50% de probabilidad de que la bala golpeé la cobertura o la sobrepase.
  
- **Cofres:**
   Los cofres podrán contener dos cosas: Objetos o angryballs. No sirven como cobertura y una vez abiertos desaparecerán del escenario.
  
- **Objetos:**
   En el mapa podrás encontrar cruzes rojas que representan objetos de curación, estos recuperarán un 15% de la vida máxima del jugador.

## 6. Experiencia de juego  
**Dinámicas Buscadas**
Se busca que el jugador aproveche las coberturas de manera estratégica para pasarse el nivel.

//Si se añade lo del tiempo y la vida habría que explicarlo aquí y en el ciclo de juego cuando se explique mejor cada sección en la recompensa


**Descripción de Partida**
Entras a La Torre y te encuentras una sala, matas a todos los enemigos (mientras puedes ir buscando cofres por la sala), al matarlos a todos se desbloquen las escaleras y aparece un mini jefe opcional, puedes o pasar de nivel o enfrentarte a él por más angryballs. En la sala final se encontrará un jefe al que se debe derrotar para finalizar el nivel.

## 7. Estética y contenido  
**Estética:**
- Música 
- SFX 
- Paleta de colores //Ahora mismo no se poner una imagen pero tengo la paleta

**Contenido:**  
-
-
  

## 8. Referencias  


##  9. Testing
