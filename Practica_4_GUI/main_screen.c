#include "main_screen.h"
#include "scr_main_screen.h"

static vtft_t *_vtft;

void main_screen_show( vtft_t *vtft )
{
    _vtft = vtft;
    initialize_main_screen();
    
    vtft_set_current_screen( _vtft, main_screen.screen_data );
}

void set_temp_value(vtft_t *vtft, float value ) {
    
    if(value >= 100) value = 99.99;
    if(value < 0) value = 0;
    
    _vtft = vtft;
    
    // Conversión de valores de tipo entero
    // en unidades y decenas
    uint8_t ten = 0;
    uint8_t unit = 0;
    uint8_t tenths = 0;
    uint8_t hundredths = 0;
    
    ten = (uint8_t)((int)value/10);
    unit = (uint8_t)((int)value%10);
    
    float decimalPart = value - (int)value;
    
    decimalPart *= 100;
    
    tenths = (uint8_t)(decimalPart / 10);
    hundredths = (uint8_t)((int)decimalPart % 10);
    
    // Revisa la jerarquía de los objetos:
    // main_screen: Incluye todos los objetos en pantalla
    // temp_value: Es un objeto tipo "label"
    // text: Es un objeto que contiene la fuente y posición del texto
    // caption: Es el conjunto de caracteres que se muestran en pantalla

    // Editamos el arreglo de caracteres de acuerdo a la tabla ASCII
    // para mostrar valores númericos.
    main_screen.temp_value->text->caption[0] = '0' + ten;
    main_screen.temp_value->text->caption[1] = '0' + unit;
    main_screen.temp_value->text->caption[3] = '0' + tenths;
    main_screen.temp_value->text->caption[4] = '0' + hundredths;
    
    // Borramos la sección de la pantalla donde se muestra el "label"
    vtft_draw_component(_vtft, main_screen.temp_mask);
    // Redibujamos el "label" con los valores actualizados
    vtft_draw_component(_vtft, main_screen.temp_value);
}

void set_hum_value(vtft_t *vtft, float value ) {
    
    if(value >= 100) value = 99.99;
    if(value < 0) value = 0;

    _vtft = vtft;
    
    // Conversión de valores de tipo entero
    // en unidades y decenas
    uint8_t ten = 0;
    uint8_t unit = 0;
    uint8_t tenths = 0;
    uint8_t hundredths = 0;
    
    ten = (uint8_t)((int)value/10);
    unit = (uint8_t)((int)value%10);
    
    float decimalPart = value - (int)value;
    
    decimalPart *= 100;
    
    tenths = (uint8_t)(decimalPart / 10);
    hundredths = (uint8_t)((int)decimalPart % 10);
    
    // Revisa la jerarquía de los objetos:
    // main_screen: Incluye todos los objetos en pantalla
    // temp_value: Es un objeto tipo "label"
    // text: Es un objeto que contiene la fuente y posición del texto
    // caption: Es el conjunto de caracteres que se muestran en pantalla

    // Editamos el arreglo de caracteres de acuerdo a la tabla ASCII
    // para mostrar valores númericos.
    main_screen.hum_value->text->caption[0] = '0' + ten;
    main_screen.hum_value->text->caption[1] = '0' + unit;
    main_screen.hum_value->text->caption[3] = '0' + tenths;
    main_screen.hum_value->text->caption[4] = '0' + hundredths;
    
    // Borramos la sección de la pantalla donde se muestra el "label"
    vtft_draw_component(_vtft, main_screen.hum_mask);
    // Redibujamos el "label" con los valores actualizados
    vtft_draw_component(_vtft, main_screen.hum_value);
}

void set_time_value ( vtft_t *vtft, uint32_t time_in_seconds ) {
    
    // Obtenes las horas y los minutos
    uint8_t hours = (uint8_t)(time_in_seconds / 3600);
    uint8_t minutes = (uint8_t)((time_in_seconds % 3600)/60);
    uint8_t ampm = 'A';
    
    // Convertimos en formato AM y PM
    if( hours > 12 ) {
        hours = hours - 12;
        ampm = 'P';
    }

    // Dividimos en decenas y unidades de las horas y minutos
    uint8_t tensHours = '0' + (hours / 10);
    uint8_t unitsHours = '0' + hours % 10;
    uint8_t tensMinutes = '0' + (minutes / 10);
    uint8_t unitsMinutes = '0' + (minutes % 10);
    
    // Copiamos el valor actual de las decenas de las horas
    uint8_t buf = main_screen.tensHours_value->text->caption[0];
    
    // Si el valor no ha cambiado, no se actualiza la pantalla
    if( tensHours != buf ) {
        main_screen.tensHours_value->text->caption[0] = tensHours;
        vtft_draw_component(_vtft, main_screen.tensHours_mask);
        vtft_draw_component(_vtft, main_screen.tensHours_value);
    }
    
    buf = main_screen.unitsHours_value->text->caption[0];
    
    if( unitsHours != buf ) {
        main_screen.unitsHours_value->text->caption[0] = unitsHours;
        vtft_draw_component(_vtft, main_screen.unitsHours_mask);
        vtft_draw_component(_vtft, main_screen.unitsHours_value);
    }
    
    buf = main_screen.tensMinutes_value->text->caption[0];
    
    if( tensMinutes != buf ) {
        main_screen.tensMinutes_value->text->caption[0] = tensMinutes;
        vtft_draw_component(_vtft, main_screen.tensMinutes_mask);
        vtft_draw_component(_vtft, main_screen.tensMinutes_value);
    }
    
    buf = main_screen.unitsMinutes_value->text->caption[0];
    
    if( unitsMinutes != buf ) {
        main_screen.unitsMinutes_value->text->caption[0] = unitsMinutes;
        vtft_draw_component(_vtft, main_screen.unitsMinutes_mask);
        vtft_draw_component(_vtft, main_screen.unitsMinutes_value);
    }
    
    buf = main_screen.ampm_value->text->caption[0];
    
    if( ampm != buf ) {
        main_screen.ampm_value->text->caption[0] = ampm;
        vtft_draw_component(_vtft, main_screen.ampm_mask);
        vtft_draw_component(_vtft, main_screen.ampm_value);
    }
}
