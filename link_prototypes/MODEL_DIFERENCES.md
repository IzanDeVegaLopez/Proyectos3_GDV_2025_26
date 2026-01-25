## LINKTIME
Pedro Pablo mencionó que preferiría que usasemos otra opción

Uso de extern: https://learn.microsoft.com/es-es/cpp/cpp/extern-cpp?view=msvc-170

- Las funciones en los .h/.hpp deben ir precedidas del modificador extern
- La función main esta en el juego y llama a la función principal del motor
- Incluyen el .h con las funciones declaradas externas para poder usarlas
- El ejecutable es el juego

## LOADTIME

- El ejecutable es el motor.
- Uso de punteros a funciones
- Necesidad de pasarle al juego structs con punteros a las funciones que podría usar
- El juego necesita guardarse una referencia a aquella estructura que le pase el juego, o estar continuemente pasando esta estructura en las funciones
- El motor incluye el juego, y el juego el motor

## RUNTIME

uso de __dclspec (específico de microsoft) https://learn.microsoft.com/en-us/cpp/cpp/declspec?view=msvc-170

- El ejecutable es el motor.
- Las funciones en el game a las que deba poder acceder el motor (o viceversa) deberán ir precedidas de __dclspec(dllexport). Lo que en el motor final, serán a grandes rasgos gameInit(), gameLoop(), gameExit()
- Llamadas de c para cargar librerias (el juego). Y guardar funciones concretas del juego como punteros a zonas de memoria en ejecución. Las funciones se obtienen por string typing
- El juego tiene que incluir a la engine, pero no al reves.