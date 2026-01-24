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

## **Clases (y Structs) :**

Las clases tienen que comenzar con un nombre como primera palabra y usar “Pascal Case”. Es decir. La primera letra es mayúscula. Ejemplo: “BombaAmarilla”

## **Enums:**

Los tipos creados por un enum se nombran igual que las clases, con Pascal Case (p.ej: MiEnumerado) y deberan comenzar por un sustantivo.
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

Tienen que comenzar por un verbo. Ejemplo: “explotarBomba”
