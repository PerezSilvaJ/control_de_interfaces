# Estructura del Robot y Modificaciones del Proyecto

Este documento registra las decisiones de diseño estructural, el circuito eléctrico y el análisis de restricciones temporales del proyecto "Robots Sumo".

## 1. Contexto Temporal y Análisis de Viabilidad
* **Planificación original:** El proyecto contaba con un total de **6 clases** (aproximadamente 24 horas de trabajo en equipo) para el diseño, armado y programación completa del robot de sumo.
* **Imprevistos y clases perdidas:** Por diversos motivos, el tiempo real de trabajo se vio drásticamente reducido a solo **2 clases efectivas**.
* **Decisión final conjunta del equipo:** Debido a la severa reducción de tiempo disponible, se tomó la decisión de **conservar la estructura mecánica provista por el taller**. Consideramos que modificar el chasis desde cero en tan solo 2 clases corre el riesgo de dejar el robot inconcluso o con fallas estructurales críticas.

## 2. Restricciones de Diseño y Reglamentación
A pesar de mantener la estructura base proporcionada, se verificó el cumplimiento de las normas de la competencia:
* **Integridad del robot rival:** Ningún agregado físico o elemento estructural puede ser diseñado para dañar o romper deliberadamente al robot contrincante en la arena de sumo.
* **Interferencia inalámbrica:** Se analizó que los componentes y la ubicación de los elementos no interfieran de ninguna manera con la señal **Bluetooth** utilizada para el control remoto del robot.

## 3. Diagrama Esquemático
* **Responsable:** Pérez Silva, Joaquín
### Proceso de Diseño y Evolución del Diagrama

Durante la fase inicial del proyecto de diseño del robot de sumo, nos enfrentamos al desafío de conectar todos los componentes (Raspberry Pi Pico W, Puente H, motores y fuente de alimentación), en el cual surgieron algunas dificultades y posteriormente soluciones.

### 1. El Borrador Inicial y sus Dificultades
* **Estado inicial:** El primer diagrama se realizó de forma intuitiva, lo que generó un esquema desordenado, con cables cruzados y superpuestos que dificultaban la lectura de las señales lógicas y de potencia; el cual no se terminó al verificar que no era la forma correcta de realizarlo.

<img width="900" height="1600" alt="image" src="https://github.com/user-attachments/assets/2dfd5e26-7855-4ee7-b0df-e1d1f89e83c7" />

* **Fallos detectados:** 
  * Confusión en el sentido de las salidas hacia los motores (OUT1 a OUT4), lo que habría provocado que un motor girara al revés respecto al otro (efecto trompo).
  * Falta de claridad inicial del conocimiento de la unificación de las masas (GND), un punto crítico para asegurar que las señales de control de 3.3V de la Raspberry Pi Pico W fueran interpretadas correctamente por el módulo de potencia.
  * Cables superpuestos, lo cual dificultaba su entendimiento para cualquier persona que lo vea.

### 2. Asesoramiento y Corrección 
* Mediante la consulta directa con la profesora del taller, pudimos revisar los errores del diagrama preliminar.
* **Correcciones aplicadas:**
  * Se reorganizó el circuito en bloques funcionales claros.
  * Se corrigió la simetría en los terminales de salida hacia los motores para garantizar el avance rectilíneo.
  * Se reconfirmó la correcta asignación de pines GPIO con PWM (GP4 y GP8) y pines de dirección (GP2, GP3, GP6, GP7).
  * Se aclararon dudas sobre la alineación de GND y otras disposciones.

### 3. Diagrama Esquemático Definitivo

<img width="900" height="1600" alt="image" src="https://github.com/user-attachments/assets/d0ff2731-bbf9-43ce-bf1b-e216ed5746f1" />
