## **Reglas Generales:**

### Idioma
#### Código y Comentarios: Inglés
Tanto el código como los comentarios se escribirán en **inglés**. 
#### Documentación: Español
Los únicos documentos de todo el proyecto en español serán la documentación como este documento, GDDs y otros en esta misma carpeta.


### Forma
**Se utilizará camel case en todo el proyecto** a menos que se diga lo contrario en alguna parte de este documento. Camel Case es todo minusculas excepto la primera letra de cada palabra a partir de la primera, por ejemplo “exampleVariable”.

### Nombramiento
Todos los nombres han de ser claros de su función o contenido. Además todos los métodos públicos de una clase deberán tener una descripción de uso (comentario). 

**Importante** ningún nombre de variable, enum, clase, etc, etc. Podrá tener como primera palabra adverbios, determinantes, pronombres, preposiciones o conjunciones.
Los únicos tipos de palabras que pueden encabezar un nombre son:
- Sustantivos o adjetivos (variables, atributos, clases y enumerados). El conjunto del nombre tendrá que ser un sintagma nominal.
- Verbos (funciones y métodos). El conjunto del nombre tendrá que ser un sintagma verbal.

## **Prefijos:**

Si varios prefijos aplicarían a un mismo nombre. Se colocan uno detrás de otro en el orden en el que se listan aquí. Para recordarlo podeis pensar en la palabra "spam".
Ejemplo: Si es un puntero estático y protegido el prefijo sería “spm”

### **Marcador de estático:**

Prefijadas por “s”

### **Prefijos según contenido:**

- punteros: “p”  
- referencias: “r”

### **Prefijos comunes según privacidad:**

- privadas: prefijadas por “m” . Ejemplo: “mAtribute”  
- protected: prefijadas por “m” . Ejemplo: “mHp”  
- públicas: sin prefijo. Ejemplo: “attackDamage”

## **Variables:**

Las variables tienen que comenzar con un sustantivo o un adjetivo como primera palabra.

El conjunto del nombre ha de ser un sintagma nominal

- Constantes: nombre completo en mayúsculas y separado por barras bajas (los prefijos no cambian a mayúsculas aunque sean constantes). Ejemplo: “CONSTANT\_VALUE"

## **Clases (y Structs):**

Las clases tienen que comenzar con un sustantivo o un adjetivo como primera palabra y usar “Pascal Case”. Es decir, camel case, pero la primera letra es también mayúscula. Ejemplo: “YellowBomb”.

El conjunto del nombre ha de ser un sintagma nominal

## **Enums:**

Los tipos creados por un enum se nombran igual que las clases, con Pascal Case (p.ej: ExampleEnum) y deberan comenzar por un sustantivo o un adjetivo.

El conjunto del nombre ha de ser un sintagma nominal

Cada uno de los nombres de los valores dentro de un enum se nombran como una constante. Y todos los valores de un enumerado deberán estar precedidos por el mismo prefijo integramente en mayusculas. Este prefijo deberá mostrar a que enumerado hacen referencian. Esto es así para evitar conflictos entre constantes enumeradas en el caso de usar namespaces.

Preferiblemente escribid dentras del nombre del tipo ": int_type". Para así acotar el tamaño de vuestro enumerado según el rango de valores que pueda tomar. Generalmente sobrará con uint8_t (necesario incluir stdint), pero en el caso de hacer flags binarias, el número de bits del tipo, será el número de posibles valores.

Por ejemplo:
```cpp
enum AttackType : uint8_t{
  ATKTYPE_SLASH = 1,
  ATKTYPE_ARCANE = 1 << 1,
  ATKTYPE_SLIME = 1 << 2 
}
```

## **Métodos y funciones:**

Tienen que comenzar por un verbo. Ejemplo: "explodeYellowBomb"

El conjunto del nombre ha de ser un sintagma verbal
