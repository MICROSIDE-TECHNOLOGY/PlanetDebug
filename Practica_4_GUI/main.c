/**
 * @file main.c
 * @brief Main function for Practica_4_GUI TFT Designer Application.
 */

// ------------------------------------------------------- SECCION DE LIBRERIAS

// Incluye librerías gráficas
#include "vtft.h"
#include "gl.h"
#include "main_screen.h"
#include "touch_controller.h"

// --------------------------------------------------------- SECCION DE OBJETOS

// Incluye objetos controlador de la pantalla 
static gl_driver_t display_driver;
static tp_t tp;
static vtft_t vtft;
static tp_drv_t tp_interface;

// ------------------------------------------------------- SECCION DE VARIABLES

uint32_t tick_count = 0;  // Contador de ciclos en application_task
uint32_t time = 0;        // Tiempo en segundos

// Variables a mostrar
float temperature = 0;
float humidity = 99;

void board_init()
{
    // Inicializar la pantalla TFT y el panel táctil
    touch_controller_init(&display_driver, TFT_MAX_BACKLIGHT);
    gl_set_driver(&display_driver);
    touch_controller_tp_init(&tp, &tp_interface);
}

/**
 * @brief Application initialization function.
 */
void application_init()
{
    board_init();

    // Inicializar la librería de gráficos y renderizar
    // la pantalla principal
    vtft_init(&vtft, &tp);
    main_screen_show(&vtft);
}

/**
 * @brief Application task function.
 */
void application_task()
{
    // Debe ejecutarse para mantener activa la pantalla TFT
    vtft_process(&vtft);
    
    // Incrementa el contador de ciclos
    tick_count++;
    
    // 2000 ciclos ~= 1 segundo, ajustar el valor dependiendo
    // del MCU a utilizar
    if(tick_count >= 2000) {
        tick_count = 0;
        
        // TODO: Obtén los valores de un sensor
        set_hum_value(&vtft, temperature);
        humidity = humidity - 1;
        if(humidity <= 0) humidity = 99;
        
        set_temp_value(&vtft, humidity);
        temperature = temperature + 1;
        if(temperature >= 99) temperature = 0;
        
        // TODO: Obtener el tiempo de un Click Board RTC
        set_time_value(&vtft, time);
        time++;
        if(time > 86400) {
            time = 0;
        }
    }
}

/**
 * @brief Application main function.
 */
void main()
{
    application_init();

    while (1)
    {
        application_task();
    }
}
