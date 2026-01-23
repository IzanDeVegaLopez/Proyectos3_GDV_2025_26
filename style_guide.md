## **Reglas Generales:**

**Se utilizará camel case en todo el proyecto** a menos que se diga lo contrario en alguna parte de este documento. Snake case es “miVariable”

Todos los nombres han de ser claros de su función o contenido. Además todos los métodos públicos de una clase deberán tener una descripción de uso.

Obviamente habrán de usarse comentarios para clarificar el uso del código producido. 

## **Prefijos:**

Si varios prefijos aplicarían a un mismo nombre. Se colocan uno detrás de otro omitiendo barras bajas entre ellos en el orden en el que se listan aquí.  
Ejemplo: Si es un puntero estático y protegido el prefijo sería “spm”

### **Marcador de estático:**

Prefijadas por “s”

### **Prefijos según contenido:**

- punteros: “p”  
- referencias: “r”

### **Prefijos comunes según privacidad:**

- privadas: prefijadas por “m” . Ejemplo: “mAtributo”  
- protected: prefijadas por “m” . Ejemplo: “mHp”  
- públicas: sin prefijo. Ejemplo: “attackDamage”

## **Variables:**

Las variables tienen que comenzar con un nombre como primera palabra

- Constantes: nombre completo en mayúsculas y separado por barras bajas (los prefijos no cambian a mayúsculas aunque sean constantes). Ejemplo: “VALOR\_CONSTANTE”

## **Clases:**

Las clases tienen que comenzar con un nombre como primera palabra y usar “Pascal Case”. Es decir. La primera letra es mayúscula. Ejemplo: “BombaAmarilla”

## **Métodos y funciones:**

Tienen que comenzar por un verbo. Ejemplo: “explotarBomba”