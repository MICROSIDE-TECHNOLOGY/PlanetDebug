/**
 * @file main.c
 * @brief Practica_1_Blink_LED.
 */
// ------------------------------------------------------- SECCION DE LIBRERIAS

// Librería de control de salidas por puerto
#include "drv_port.h"


// --------------------------------------------------------- SECCION DE OBJETOS
// Todos los objetos en MikroSDK siguen la estructura:
//                  nombreLibreria_t nombreVariable
// donde el sufijo "_t" indica tipo, nombreVariable es el nombre que asigna
// el programador para diferenciar un objeto de otro. A esta variable se le
// conoce como "manejadora" o "handler".

port_t LEDs;

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
    
    // La función port_init requiere el "handler", el nombre del puerto a
    // configurar, la "mascara":
    // 1 significa que el pin en esa posición va a configurarse, empezando de 
    // derecha a izquierda, el valor más a la derecha corresponde al Pin 0 del puerto
    // El último argumento indica si se configurará como salida o entrada.
    port_init( &LEDs, PORT_D, 0b11111111, GPIO_DIGITAL_OUTPUT);
}

/**
 * @brief Programa principal, se ejecuta indefinidamente.
 */
void application_init()
{
    // Cada objeto en MikroSDK tendrá funciones específicas de acuerdo
    // a las funciones que puede realizar. Consulta el explorador de código
    // "Code Explorer" en la barra contextual derecha para obtener una lista
    // de todas las funciones del objeto.
    
    // port_write modifica el estado de los pines, un 1 significa que ese pin
    // va a encenderse, un 0 indica que ese pin va a apagarse, empezando de 
    // derecha a izquierda, el valor más a la derecha corresponde al Pin 0 del puerto
    
    // Encender todos los leds
    port_write( &LEDs, 0b11111111 );
    
    Delay_1sec();
    
    // Apagar todos los leds
    port_write( &LEDs, 0b00000000 );
    
    Delay_1sec();
    
    // Patrón: recorrer led de izquierda a derecha y derecha a izquierda
    
    int i = 0b00000001;
    int j = 0b10000000;
    
    while ( 1 ) {
        port_write( &LEDs, i | j );
        Delay_ms(500);
        i = i<<1;
        j = j>>1;
        if ( i == 0b00000000 ) break;
    }
    
    // Patrón: Contador binario
    
    for (int i = 0; i < 0b11111111; i++) {
        port_write( &LEDs, i );
        Delay_ms(50);
    }
    
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
