#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

/**
 * @brief Programa principal
*/
int main(void) {
  // Inicializo el USB
  stdio_init_all();
  cyw43_arch_init();

  // Mensaje por USB
  printf("\nHola mundo!\n");

  while (true) {
    // Prendo LED
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    // Mensaje por USB
    printf("LED on\n");
    
    int pbp=0;
    
    // Demora
    sleep_ms(2000);
    // Apago LED
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    // Mensaje por USB
    printf("LED off\n");
    // Demora
    sleep_ms(2000);
   
    pbp = pbp + 1;

    printf("%d pbp\n", pbp);
  
  }
  return 0;
}