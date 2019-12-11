# Librería Arduino Stopwatch
Librería para Arduino que permite registrar el tiempo transcurrido en la ejecución del código, obteniendo el resultado como milisegundos transcurridos o como frecuencia en Hz. Con esta librería podemos medir el tiempo de forma sencilla, liberando de estas funciones al flujo principal.

Más información https://www.luisllamas.es/libreria-arduino-stopwatch/

## Instrucciones de uso
La clase Stopwatch resulta de utilidad, ejemplo, para realizar encoders, un tacómetro, o determinar la frecuencia de una señal. Además, podemos tener varias instancias ejecutándose simultáneamente, y combinarlo con otras librerías como Debounce Filter o Histeresis. 

La clase Stopwatch dispone de dos modos de funcionamiento. Uno es mediante el uso de las funciones de `Reset()` y `Update()` que, respectivamente, inicializa el tiempo de comiendo de la medición y registra el tiempo pasado. Por tanto, el tiempo registrado es el transcurrido entre la llamada a `Reset()` y `Update()`.

El otro modo de funcionamiento es mediante el uso de la función `Measure()`, que recibe como parámetro una funcion `void(*)()` para medir. Stopwatch registra el tiempo empleado para la ejecución de la función pasada como parámetro. 

En cualquiera de los dos casos, el tiempo registrado se obtiene mediante `GetElapsed()` y `GetFrequency()` que obtienen, respectivamente, el tiempo en milisegundos y la frecuencia en Hz.

### Constructor
```c++
Stopwatch();
```

### Usar Stopwatch
```c++
// Registra el instante actual como comienzo de la medición
void Reset();
 
// Registra el instante actual como fin de la medición
void Update();
 
// Registra la medición de la función pasada como parámetro
void Measure(StopwatchAction action);
 
// Obtiene el tiempo transcurrido en milisegundos
unsigned long GetElapsed() const;
 
// Obtiene el tiempo transcurrido como frecuencia en Hz
float GetFrequency() const;
```

## Ejemplos
La librería Stopwatch incluye los siguientes ejemplos para ilustrar su uso.
* ResetUpdate: Ejemplo de uso mediante `Reset()` y `Update()`
```c++
#include "StopwatchLib.h"

Stopwatch stopwatch;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	//delay(20) simula la tarea a medir
	stopwatch.Reset();
	delay(20);
	stopwatch.Update();
	
	Serial.print(stopwatch.GetElapsed()); 
	Serial.print('\t'); 
	Serial.println(stopwatch.GetFrequency());
	Serial.println();
}
```
* Measure: Ejemplo de uso mediante `Measure()`
```c++
#include "StopwatchLib.h"

Stopwatch stopwatch;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	//delay(20) simula la tarea a medir
	stopwatch.Measure([]() {delay(20);});
	
	Serial.print(stopwatch.GetElapsed()); 
	Serial.print('\t'); 
	Serial.println(stopwatch.GetFrequency());
	Serial.println();
}
```
