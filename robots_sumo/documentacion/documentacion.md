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
