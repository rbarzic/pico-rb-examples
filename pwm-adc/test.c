#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "pico/binary_info.h"


const uint LED_PIN = 14;
const uint PWM_PIN = 15;

// const uint PWM_TOP=1024;
const uint32_t _PWM_TOP=1024-1;

int main() {
  
  bi_decl(bi_program_description("This is a test binary."));
  bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

  
  stdio_init_all();

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);



  // gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
  gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);


  
  
  // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
  uint slice_num = pwm_gpio_to_slice_num(LED_PIN);

  // Set period of 4 cycles (0 to 3 inclusive)
  pwm_set_wrap(slice_num, _PWM_TOP);
  // Set channel A output high for one cycle before dropping
  // pwm_set_chan_level(slice_num, PWM_CHAN_A, 256);
  // Set initial B output high for three cycles before dropping
  pwm_set_chan_level(slice_num, PWM_CHAN_B, 512);
  // Set the PWM running
  pwm_set_enabled(slice_num, true);
  

    adc_init();
 
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    adc_select_input(0);

  
  
  while (1) {
    gpio_put(LED_PIN, 0);
    sleep_ms(250);
    gpio_put(LED_PIN, 1);
    
    sleep_ms(250);

     // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
    const float conversion_factor = 3.3f / (1 << 12);
    uint16_t result = adc_read();
    printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
    sleep_ms(500);
  }
}

