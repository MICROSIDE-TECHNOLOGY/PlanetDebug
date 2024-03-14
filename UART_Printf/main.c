/*!
 * \file 
 * \brief Using printf on MikroSDK
 * 
 * # Description
 * This application implements a printf function to ease working with UART
 * formatting.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes UART interface and performs a device configurations.
 * 
 * ## Application Task  
 * Generates random values then outputs them as ASCII characters over UART.
 * 
 * *note:* 
 * Printf implementation suitable for Embedded devices by Marco Paland
 * https://github.com/mpaland/printf
 * printf is usually considered unsafe, there are many reasons, howver
 * given small stack size of some MCU it might cause a stackoverflow,
 * be aware of this and use it with caution
 * 
 * \author Microside Technology
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "MikroSDK.Driver.UART"
#include "printf.h"

// ------------------------------------------------------------------ VARIABLES

static uart_t uart;  // UART driver context structure.
static uart_config_t uart_cfg;  // UART driver config context structure.

static uint8_t uart_rx_buffer[128];
static uint8_t uart_tx_buffer[128];
static uint8_t buffer[32];

void application_init()
{
    // Default config
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    uart.tx_ring_buffer = uart_tx_buffer;
    uart.rx_ring_buffer = uart_rx_buffer;

    uart_cfg.tx_pin = MIKROBUS_5_TX;  // UART TX pin.
    uart_cfg.rx_pin = MIKROBUS_5_RX;  // UART RX pin.

    uart_cfg.tx_ring_size = sizeof( uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( uart_rx_buffer );

    if( ACQUIRE_FAIL == uart_open( &uart, &uart_cfg ) ) {
        while(1);
    }

    //------------------------------------------------------------------------
    // UART settings
    //------------------------------------------------------------------------

    // Set baud rate.
    if ( UART_SUCCESS != uart_set_baud( &uart, 115200 ) ) {
        while(1);
    }

    // Set data parity. ( no parity )
    if ( UART_SUCCESS != uart_set_parity( &uart, UART_PARITY_DEFAULT ) ) {
        while(1);
    };

    // Set stop bits. ( one stop bit )
    if ( UART_SUCCESS != uart_set_stop_bits( &uart, UART_STOP_BITS_DEFAULT ) ) {
        while(1);
    }

    // Set data bits. ( 8-bit data )
    if ( UART_SUCCESS != uart_set_data_bits( &uart, UART_DATA_BITS_DEFAULT ) ) {
        while(1);
    }
}

void application_task ( )
{
    Delay_1sec();
    int random = rand();

    float someValue = random / 100.00f;

    uart_printf( &uart, "Floating value: %0.2f, Integer: %i\r\n", someValue, random );

}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END