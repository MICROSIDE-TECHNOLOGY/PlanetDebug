#ifndef _main_screen_H_

#include "vtft.h"

void main_screen_show(vtft_t *vtft);

void set_temp_value(vtft_t *vtft, float value );
void set_hum_value(vtft_t *vtft, float value );
void set_time_value ( vtft_t *vtft, uint32_t time_in_seconds );

#endif // !_main_screen_H_
