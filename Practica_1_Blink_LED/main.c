/**
 * @file main.c
 * @brief Practica_1_Blink_LED.
 */
// ------------------------------------------------------- SECCION DE LIBRERIAS

// Librería de control de salidas individuales
#include "drv_digital_out.h"


// --------------------------------------------------------- SECCION DE OBJETOS
// Todos los objetos en MikroSDK siguen la estructura:
//                  nombreLibreria_t nombreVariable
// donde el sufijo "_t" indica tipo, nombreVariable es el nombre que asigna
// el programador para diferenciar un objeto de otro. A esta variable se le
// conoce como "manejadora" o "handler".

digital_out_t LED;

// ------------------------------------------------------- SECCION DE FUNCIONES

/**
 * @brief Funciones de inicialización. Se ejecuta una sola vez
 * al encender el dispositivo
 */
void board_init() 
{
    // En MikroSDK los objetos deben inicializarse, la estructura es:
    // nombreLibreria_init( &nombreVariable, &variableConfiguracion );
    // Algunos objetos más complejos requiren métodos adicionales para su
    // inicialización
    
    // La función digital_out_init solo requiere el "handler" y el pin que
    // el programador quiere controlar.
    digital_out_init( &LED, PB0 );
}

/**
 * @brief Programa principal, se ejecuta indefinidamente.
 */
void application_init()
{
    // Cada objeto en MikroSDK tendrá funciones especificas de acuerdo
    // a las funciones que puede realizar. Consulta el explorador de código
    // "Code Explorer" en la barra contextual derecha para obtener una lista
    // de todas las funciones del objeto.
    
    // digital_out_high enciende la salida
    digital_out_high( &LED );
    
    Delay_1sec();
    
    // digital_out_low apaga la salida
    digital_out_low( &LED );
    
    Delay_1sec();
    
}

/**
 * @brief Función main.
 */
int main(void)
{
    board_init();
    
    while (1) {
        application_init();
    }

    return 0;
}
