/**
 * @file main.c
 * @brief Practica_1_Blink_LED.
 */
// ------------------------------------------------------- SECCION DE LIBRERIAS

// Librería de control de salidas por puerto
// TODO: Revisa tu tarjeta en Planet Debug y escoge un Click Board sobre el cual
//       quieras trabajar.
// Una vez seleccionado dirígete al administrador de paquetes:
// Show->Package manager
// Introduce el nombre del Click Board y presiona el botón "Install"
// Una vez finalice la instalación dirígete al administrador de librerías:
// Show->Library Manager
// Marca la casilla con la librería que instalaste. Si no están marcadas, marca
// las casillas "Board", "Log" y "Plot" en la sección "MikroSDK"

#include "board.h"
#include "log.h"
#include "plot.h"

// Reemplaza "libreria.h" por el nombre el nombre de la librería, en MikroSDK
// el nombre de la librería es el nombre del Click Board en minúscula, p. ej:
// Click Board: Environment Click
// Librería: environment.h

#include "libreria.h"

// --------------------------------------------------------- SECCION DE OBJETOS
// Todos los objetos en MikroSDK siguen la estructura:
//                  nombreLibreria_t nombreVariable
// donde el sufijo "_t" indica tipo, nombreVariable es el nombre que asigna
// el programador para diferenciar un objeto de otro. A esta variable se le
// conoce como "manejadora" o "handler".

static log_t logger;

// Reemplaza "libreria_t" por el nombre del objeto, p. ej:
// Click Board: Environment Click
// Librería: environment.h
// Objeto: environment_t

static libreria_t clickboard;

// ------------------------------------------------------- SECCION DE FUNCIONES

/**
 * @brief Funciones de inicialización. Se ejecuta una sola vez
 * al encender el dispositivo
 */
void board_init() 
{
    // En MikroSDK los objetos deben inicializarse, la estructura es:
    // nombreLibreria_init( &nombreVariable, &variableConfiguracion );
    // Algunos objetos más complejos requieren métodos adicionales para su
    // inicialización
    
    log_cfg_t log_cfg;
    
    // TODO: Reemplaza "libreria_cfg_t" por el nombre de la variable
    // de configuración, p. ej:
    // Click Board: Environment Click
    // Librería: environment.h
    // Objeto: environment_t
    // Variable de configuración: environment_cfg_t
    libreria_cfg_t clickboard_cfg;
    
    /** 
     * Inicialización del logger.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    
    //TODO: Inicializa el objeto, en MikroSDK las librerías de los
    // Click Board suelen utilizar al menos tres funciones:
    // + libreria_cfg_setup
    // + LIBRERIA_MAP_MIKROBUS
    // + libreria_init
    // Si tienes dudas revisa el ejemplo de la librería desde
    // el administrador de paquetes.
    
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
    
    // Genera una salida de texto en la pestaña: 3 Application Output
    // Puedes mostrar valores de variables siguiendo las reglas
    // de la función printf
    log_printf( &logger, "HOLA MUNDO: %i\n\r", 25);
    
    // Genera una salida en el gráficador: Plot (Ctrl + 0)
    // El primer argumento es la etiqueta, el segundo argumento es el valor
    plot("Etiqueta", 15);
    
    // TODO: Genera el código para interactuar con tu Click Board.
    // Apóyate del Explorador de código y/o el ejemplo de la librería desde
    // el administrador de paquetes.

    
    
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
