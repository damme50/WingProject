
#pragma once


#define NULL 0

#ifndef M_PI
#define M_PI       3.14159265358979323846f
#endif /* M_PI */

#define RADX10 (M_PI / 1800.0f)                  // 0.001745329252f
#define RAD    (M_PI / 180.0f)

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(x) ((x) > 0 ? (x) : -(x))



typedef enum {
    ALIGN_DEFAULT = 0,                                      // driver-provided alignment
    CW0_DEG = 1,
    CW90_DEG = 2,
    CW180_DEG = 3,
    CW270_DEG = 4,
    CW0_DEG_FLIP = 5,
    CW90_DEG_FLIP = 6,
    CW180_DEG_FLIP = 7,
    CW270_DEG_FLIP = 8
} sensor_align_e;


typedef enum {
    X = 0,
    Y,
    Z
} sensor_axis_e;




#include "stm32f10x.h"


typedef void (*sensorInitFuncPtr)(sensor_align_e align);   // sensor init prototype
typedef void (*sensorReadFuncPtr)(int16_t *data);          // sensor read and align prototype
typedef void (*baroOpFuncPtr)(void);                       // baro start operation
typedef void (*baroCalculateFuncPtr)(int32_t *pressure, int32_t *temperature);             // baro calculation (filled params are pressure and temperature)
typedef void (*serialReceiveCallbackPtr)(uint16_t data);   // used by serial drivers to return frames to app
typedef uint16_t (*rcReadRawDataPtr)(uint8_t chan);        // used by receiver driver to return channel data
typedef void (*pidControllerFuncPtr)(void);                // pid controller function prototype


typedef struct sensor_t {
    sensorInitFuncPtr init;                                 // initialize function
    sensorReadFuncPtr read;                                 // read 3 axis data function
    sensorReadFuncPtr temperature;                          // read temperature if available
    float scale;                                            // scalefactor (currently used for gyro only, todo for accel)
} sensor_t;




#define LED0
#define LED1

#define USE_LAME_PRINTF





#include "stm32f10x_i2c.h"
#include "stdbool.h"
//#include <stdlib.h>
#include <math.h>

#include "serial.h"
#include "printf.h"

#include "drv_gpio.h"
#include "drv_system.h"
#include "drv_i2c.h"
#include "drv_hmc5883l.h"


#define LED0_GPIO   GPIOC
#define LED0_PIN    Pin_9 // PB3 (LED)
#define LED1_GPIO   GPIOC
#define LED1_PIN    Pin_8 // PB4 (LED)
#define BEEP_GPIO   GPIOA
#define BEEP_PIN    Pin_12 // PA12 (Buzzer)
#define BARO_GPIO   GPIOC
#define BARO_PIN    Pin_13
#define INV_PIN     Pin_2 // PB2 (BOOT1) abused as inverter select GPIO
#define INV_GPIO    GPIOB



// Helpful macros
#ifdef LED0
#define LED0_TOGGLE              digitalToggle(LED0_GPIO, LED0_PIN);
#define LED0_OFF                 digitalHi(LED0_GPIO, LED0_PIN);
#define LED0_ON                  digitalLo(LED0_GPIO, LED0_PIN);
#else
#define LED0_TOGGLE
#define LED0_OFF
#define LED0_ON
#endif

#ifdef LED1
#define LED1_TOGGLE              digitalToggle(LED1_GPIO, LED1_PIN);
#define LED1_OFF                 digitalHi(LED1_GPIO, LED1_PIN);
#define LED1_ON                  digitalLo(LED1_GPIO, LED1_PIN);
#else
#define LED1_TOGGLE
#define LED1_OFF
#define LED1_ON
#endif

