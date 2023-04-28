/*!
 * \file 
 * \brief G2C Click & Environment click example
 * 
 * # Description
 * This example reads and processes data from the Environment click
 * then it sends them to the G2C clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and power module.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - g2c_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * ## Note
 * - WiFi credentials for Planet Debug utilization: username: MikroE Public
 *                                                  password: mikroe.guest
 * 
 * 
 * \author Microside Technology based on the Mikroe provided example
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "g2c.h"
#include "environment.h"
#include "string.h"
#include "conversions.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

static g2c_t g2c;
static environment_t environment;
static float temperature;
static float pressure;
static float humidity;
static int32_t gas;
static log_t logger;

// AT commands
#define ATE               "ATE1"
#define AT                "AT"
#define AT_CEN            "AT+CEN=1"
#define AT_NWCR           "AT+NWCR"
#define AT_NWC            "AT+NWC=1"
#define AT_BRCR           "AT+BRCR"
#define AT_BRC            "AT+BRC=1"
#define AT_DSET           "AT+DSET"
#define AT_PUB            "AT+PUB"

// Sensor/Actuator reference
#define TEMPERATURE_REF     "temp_ref"
#define HUMIDTY_REF         "humidity_ref"
#define PRESSURE_REF        "pressure_ref"
#define GAS_RESISTANCE_REF  "gas_resistance_ref"


// Operator settings
#define NETWORK_USERNAME  "wifi_ssid"
#define NETWORK_PASSWORD  "wifi_pass"

// Broker(device) settings
#define DEVICE_KEY        "device_key"
#define DEVICE_PASSWORD   "device_password"

static char data_buf[ 20 ] = "";
static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void g2c_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = g2c_generic_read( &g2c, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }
            log_printf( &logger, "%s", uart_rx_buffer );

            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_parser_buf, uart_rx_buffer, rsp_size );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_100ms( );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    g2c_cfg_t cfg;
    environment_cfg_t env_cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  G2C initialization.

    g2c_cfg_setup( &cfg );
    G2C_MAP_MIKROBUS( cfg, MIKROBUS_5 );
    g2c_init( &g2c, &cfg );

    // Power module.

    g2c_module_power( &g2c, true, 0 );
    g2c_reset( &g2c );
    
    // Send command.

    log_printf( &logger, ">> ATE \r\n" );
    g2c_send_command( &g2c, ATE );
    Delay_ms( 3000 );
    g2c_process( );

    log_printf( &logger, ">> AT \r\n" );
    g2c_send_command( &g2c, AT );
    Delay_ms( 3000 );
    g2c_process( );

    log_printf( &logger, ">> AT_CEN \r\n" );
    g2c_send_command( &g2c, AT_CEN );
    g2c_process( );

    log_printf( &logger, ">> NETWORK \r\n" );
    g2c_send_operator_cfg( &g2c, NETWORK_USERNAME, NETWORK_PASSWORD );
    g2c_process( );

    log_printf( &logger, ">> AT NWC \r\n" );
    g2c_send_command( &g2c, AT_NWC );
    g2c_process( );

    log_printf( &logger, ">> DEVICE \r\n" );
    g2c_send_broker_cfg( &g2c, DEVICE_KEY, DEVICE_PASSWORD );
    g2c_process( );

    log_printf( &logger, ">> AT BRC \r\n" );
    g2c_send_command( &g2c, AT_BRC ); 
    g2c_process( );
    
    //  Environment initialization.

    environment_cfg_setup( &env_cfg );
    ENVIRONMENT_MAP_MIKROBUS( env_cfg, MIKROBUS_4 );
    environment_init( &environment , &env_cfg );
    environment_default_cfg( &environment );

    Delay_ms( 3000 );
}

void application_task ( void )
{
    g2c_process( );
    
    if ( send_data_cnt == 5 )
    {
        temperature = environment_get_temperature( &environment);
        log_printf( &logger, " Temperature : %.2fC", temperature);
        
        float_to_str(temperature, data_buf);
        
        log_printf( &logger, ">> TEMPERATURE REF \r\n" );  
        g2c_send_data_ref( &g2c, TEMPERATURE_REF, data_buf );
        g2c_process( );

        log_printf( &logger, ">> AT PUB \r\n" );
        g2c_send_command( &g2c, AT_PUB );
        g2c_process( );

        humidity = environment_get_humidity( &environment );
        log_printf( &logger, "      Humidity : %f%%", humidity);
        
        float_to_str(humidity, data_buf);
        
        log_printf( &logger, ">> HUMIDITY REF \r\n" );  
        g2c_send_data_ref( &g2c, HUMIDTY_REF, data_buf );
        g2c_process( );

        log_printf( &logger, ">> AT PUB \r\n" );
        g2c_send_command( &g2c, AT_PUB );
        g2c_process( );

        pressure = environment_get_pressure( &environment );
        log_printf( &logger, "      Pressure : %.3fmbar", pressure);
        
        float_to_str(pressure, data_buf);
        
        log_printf( &logger, ">> PRESSURE REF \r\n" );  
        g2c_send_data_ref( &g2c, PRESSURE_REF, data_buf );
        g2c_process( );

        log_printf( &logger, ">> AT PUB \r\n" );
        g2c_send_command( &g2c, AT_PUB );
        g2c_process( );

        gas = environment_get_gas_resistance( &environment );
        log_printf( &logger, "      Gas Resistance : %ld\r\n", gas);
        
        float_to_str((float)gas, data_buf);
        
        log_printf( &logger, ">> GAS RESISTANCE REF \r\n" );  
        g2c_send_data_ref( &g2c, GAS_RESISTANCE_REF, data_buf );
        g2c_process( );

        log_printf( &logger, ">> AT PUB \r\n" );
        g2c_send_command( &g2c, AT_PUB );
        g2c_process( );
        
        send_data_cnt = 0;
    }
    send_data_cnt++;
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
