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
