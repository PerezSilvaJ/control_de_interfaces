# Introducción

Este es el documento de documentación, en el cual se expresan las investigaciones para realizar el proyecto de robot sumo. Para organizarlo de forma clara, cada tema cuenta con los siguientes puntos:

* **Tema:** El encabezado que indica de qué parte o componente estamos hablando.
* **Integrante:** Qué compañero del equipo hizo la investigación.
* **Objetivo:** Qué es lo que buscábamos averiguar o lograr con esa investigación.
* **Apuntes Teóricos:** La explicación de cómo funciona el componente o la teoría que investigamos.
* **Aplicación:** Cómo se usa o se implementa eso en nuestro robot (si es que corresponde).

## 1. Microcontrolador: Raspberry Pi Pico W
* **Investigado por:** Rubil, Mateo
* **Objetivo:** Conocer la placa que usaremos como "cerebro" del robot, identificar la distribución de sus pines (pinout) y entender cómo nos permitirá controlarlo de forma inalámbrica.

### Apuntes teóricos e investigación
La **Raspberry Pi Pico W** es una placa de desarrollo pequeña pero muy potente. Su microcontrolador principal es el **RP2040** (diseñado por Raspberry Pi), y además cuenta con un chip integrado para conectividad **Bluetooth y Wi-Fi (BLE)**. 

En nuestro proyecto de sumo, la conexión Bluetooth es fundamental porque será el medio mediante el cual controlaremos los movimientos del robot de forma remota durante la competencia.

#### Características principales de la placa:
* **Microcontrolador:** RP2040 con un procesador de doble núcleo ARM Cortex-M0+.
* **Memoria:** Cuenta con memoria interna para almacenar el programa que escribamos.
* **Alimentación y Voltaje:** Trabaja con una lógica digital de **3.3V**. Esto es muy importante tenerlo en cuenta para no quemar ningún pin conectando componentes de 5V directamente sin protección.

#### Análisis del Pinout (Distribución de Pines)


<img width="842" height="590" alt="image" src="https://github.com/user-attachments/assets/d5415b38-6851-4c66-a027-7b25d005cf05" />

La placa tiene un total de **40 pines físicos** distribuidos a los lados, entre los cuales destacan:
1. **Pines de Alimentación y Energía:**
   * **VBUS (Pin 40):** Nos entrega 5V directamente desde el puerto USB cuando la conectamos a la PC.
   * **VSYS (Pin 39):** Sirve para alimentar la placa utilizando una batería externa.
   * **3V3 (Pin 36):** Es una salida regulada de 3.3V que podemos usar para alimentar los sensores o la lógica de otros módulos pequeños.
   * **GND:** Los pines de masa o tierra, necesarios para cerrar todos los circuitos eléctricos del robot.
2. **Pines GPIO y PWM:**
   * Los pines **GPIO** se pueden configurar como entradas (para leer pulsadores o sensores) o salidas (para encender LEDs o activar motores).
   * Varios de estos pines soportan **PWM** por hardware, lo que nos dará la capacidad de regular la velocidad de los motores de tracción con precisión.
3. **Pines de Comunicación:**
   * Dispone de pines para protocolos estándar como **UART, I2C y SPI**, que sirven para conectar posibles futuros sensores de distancia o módulos adicionales.

## 2. Etapa de Potencia: El Puente H 
* **Investigado por:** Virgilio, Benjamin.
* **Objetivo:** Analizar el funcionamiento del circuito Puente H para la inversión de marcha y control de dirección de los motores DC.

### Apuntes teóricos e investigación
Un **Puente H** es una red de conmutación electrónica formada por 4 interruptores (transistores MOSFET o BJT) dispuestos en forma de "H". Su función fundamental es controlar la dirección de la corriente que fluye a través de una carga inductiva (como un motor de corriente continua).

<img width="1024" height="1024" alt="image" src="https://github.com/user-attachments/assets/67be4cd6-64dc-4490-96a7-a9818a393e71" />

#### Principio de Funcionamiento
* **Avanzar (Giro Horario):** Se cierran los interruptores **S1** y **S4**. La corriente fluye de izquierda a derecha.
* **Retroceder (Giro Antihorario):** Se cierran los interruptores **S3** y **S2**. La corriente fluye de derecha a izquierda.
* **Freno Activo:** Se cierran **S1 y S2** o **S3 y S4** a la vez, cortocircuitando los bornes del motor.
* **Prohibición (Cortocircuito):** Nunca deben cerrarse **S1 y S3** (o **S2 y S4**) simultáneamente, ya que provocaría un cortocircuito directo entre Vcc y GND (*Shoot-through*).

#### Aislamiento y Módulos integrados
En nuestro proyecto se utiliza un módulo controlador basado en puente H
* **Lógica de control:** Aislada y operada a 3.3V desde la Raspberry Pi Pico W.
* **Etapa de potencia:** Recibe la energía directamente de la batería del robot para alimentar los motores.
* **Diodos Flyback:** Incorpora diodos de protección en paralelo a los transistores para suprimir las picos de tensión inductiva producidos por el bobinado de los motores al detenerse.

#### Integración Práctica en el Robot de Sumo
En la implementación real de un robot de competencia, el Puente H no trabaja solo:
1. **Control de Velocidad (Pin Enable / ENA-ENB):** Mientras que los pines de entrada (IN1, IN2) deciden la dirección (girando los interruptores del puente), el pin de habilitación o *Enable* del módulo recibe la señal **PWM** investigada por el equipo. Esto permite modular la potencia que llega al motor sin perder la capacidad de invertir la marcha.
2. **Lógica y Potencia:** El módulo permite separar la lógica de control de bajo voltaje (que proviene de la placa) de la alimentación directa de potencia para los motores.

## 3. Control de Velocidad: Modulación por Ancho de Pulso (PWM)
* **Investigado por:** Primus, Francisco
* **Objetivo:** Investigar cómo funciona la técnica PWM para poder regular la velocidad de los motores del robot de sumo de forma eficiente y precisa.

### Apuntes Teóricos: ¿Cómo funciona el PWM y los tiempos de la señal?
Cuando controlamos los motores usando pines con capacidad PWM, la Raspberry Pi Pico W no entrega un voltaje fijo, sino una **señal digital cuadrada** que se prende y se apaga muy rápidamente.

Esta señal se puede imaginar como una onda que sube y baja constantemente:
* **Cuando la señal está arriba (HIGH):** El motor recibe energía y empuja.
* **Cuando la señal está abajo (LOW):** El motor se queda sin energía por un instante.

La clave de esta investigación es saber que **esos tiempos (cuánto tiempo pasa la señal arriba y cuánto abajo) se pueden alargar o achicar según lo que necesitemos**:
1. **Si se alarga el tiempo en que la señal está arriba:** El motor recibe energía durante más porción de cada ciclo. En promedio, le llega más voltaje y **gira más rápido** (por ejemplo, al 80% o 90% de potencia para ir al ataque).
2. **Si se achica el tiempo en que la señal está arriba:** El motor recibe impulsos muy cortos de energía. En promedio, le llega menos voltaje y **gira más lento** (por ejemplo, al 30% de potencia para maniobrar con precisión dentro de la pista).

A esta relación entre el tiempo que la señal pasa arriba frente al tiempo total se le conoce técnicamente como **Ciclo de Trabajo (*Duty Cycle*)**.

<img width="446" height="446" alt="image" src="https://github.com/user-attachments/assets/6942cba3-ab21-4abc-af0d-7d3b9d9eade6" />


### Aplicación Práctica en el Robot de Sumo
* Gracias a la variación de estos tiempos por código, evitamos que los motores giren siempre al 100% de su capacidad de golpe, lo que volvería al robot demasiado brusco e incontrolable.
* Nos permite programar distintas velocidades de desplazamiento y empuje para adaptarnos de forma táctica a la competencia.

## 4. Alimentacion de la Raspberry Pi Pico W
* **Investigado por:** Virgilio, Benjamin.
* **Objetivo:** Conocer las diferentes formas de alimentar la Raspberry Pi Pico W, identificar las tensiones adecuadas para su funcionamiento y aprender a realizar las conexiones eléctricas de manera segura, evitando daños en la placa y sus componentes
* # Alimentación de la Raspberry Pi Pico W

## Introducción

La Raspberry Pi Pico W es una placa de desarrollo electrónico que permite realizar proyectos de programación, automatización y conexión inalámbrica mediante Wi-Fi y Bluetooth. Para funcionar, necesita recibir energía eléctrica mediante una fuente de alimentación adecuada.

## Formas de alimentación

La Raspberry Pi Pico W puede alimentarse de tres maneras principales:

### 1. Alimentación por micro-USB

Es la forma más sencilla y utilizada. Se conecta la placa a una computadora o a un cargador USB de 5 V mediante un cable micro-USB. Además de suministrar energía, permite programar la placa y transferir datos.

### 2. Alimentación mediante el pin VSYS

El pin VSYS permite alimentar la placa utilizando una fuente externa o una batería. Admite una tensión de entre 1,8 V y 5,5 V. El positivo de la fuente se conecta a VSYS y el negativo a GND (tierra).

### 3. Alimentación mediante el pin 3V3

También es posible alimentar la placa a través del pin 3V3, aplicando una tensión regulada de 3,3 V. Para utilizar este método, se necesita una fuente estable y correctamente regulada, ya que una tensión incorrecta puede dañar la placa.

## Precauciones de seguridad

Es importante respetar los límites de tensión de la placa. Los pines GPIO funcionan con señales de 3,3 V y no toleran directamente 5 V. Además, se debe evitar conectar fuentes de alimentación simultáneamente sin verificar que la conexión sea segura.

## Conclusión

La Raspberry Pi Pico W puede alimentarse mediante micro-USB, el pin VSYS o el pin 3V3. Para comenzar a trabajar con ella, se recomienda utilizar el puerto micro-USB, porque es un método simple y práctico que permite alimentar y programar la placa al mismo tiempo.


