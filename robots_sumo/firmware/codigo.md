#include "pico/stdlib.h"

// ====== CONFIGURACIÓN DE PINES ======
#define MOTOR_IZQ_IN1  2   // GP2 -> IN1 del puente H
#define MOTOR_IZQ_IN2  3   // GP3 -> IN2 del puente H
#define MOTOR_DER_IN3  4   // GP4 -> IN3 del puente H
#define MOTOR_DER_IN4  5   // GP5 -> IN4 del puente H
// ======================================================

#define TIEMPO_MS 1000     // duración de cada movimiento 

// Inicializa los 4 pines como salida y los deja apagados
void motores_init(void) {
    const uint pines[] = {MOTOR_IZQ_IN1, MOTOR_IZQ_IN2, MOTOR_DER_IN3, MOTOR_DER_IN4};
    for (int i = 0; i < 4; i++) {
        gpio_init(pines[i]);
        gpio_set_dir(pines[i], GPIO_OUT);
        gpio_put(pines[i], 0);
    }
}

void parar(void) {
    gpio_put(MOTOR_IZQ_IN1, 0);
    gpio_put(MOTOR_IZQ_IN2, 0);
    gpio_put(MOTOR_DER_IN3, 0);
    gpio_put(MOTOR_DER_IN4, 0);
}

void adelante(void) {
    gpio_put(MOTOR_IZQ_IN1, 1);
    gpio_put(MOTOR_IZQ_IN2, 0);
    gpio_put(MOTOR_DER_IN3, 1);
    gpio_put(MOTOR_DER_IN4, 0);
}

void atras(void) {
    gpio_put(MOTOR_IZQ_IN1, 0);
    gpio_put(MOTOR_IZQ_IN2, 1);
    gpio_put(MOTOR_DER_IN3, 0);
    gpio_put(MOTOR_DER_IN4, 1);
}

// Gira sobre su eje: motor izquierdo atrás, derecho adelante
void izquierda(void) {
    gpio_put(MOTOR_IZQ_IN1, 0);
    gpio_put(MOTOR_IZQ_IN2, 1);
    gpio_put(MOTOR_DER_IN3, 1);
    gpio_put(MOTOR_DER_IN4, 0);
}

// Gira sobre su eje: motor izquierdo adelante, derecho atrás
void derecha(void) {
    gpio_put(MOTOR_IZQ_IN1, 1);
    gpio_put(MOTOR_IZQ_IN2, 0);
    gpio_put(MOTOR_DER_IN3, 0);
    gpio_put(MOTOR_DER_IN4, 1);
}
