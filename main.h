#include <time.h>
#include <stdio.h>
#include <string.h>
#include "lwip/dns.h"
#include "lwip/tcp.h"
#include "lwip/pbuf.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "lwip/apps/mqtt.h"
#include "lwip/altcp_tcp.h"
#include "lwip/altcp_tls.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/mqtt_priv.h"
#include "hardware/structs/rosc.h"
#include <stdlib.h>
#include <ctype.h>
#include "pico/binary_info.h"
#include "ssd1306/ssd1306.h"
#include "hardware/i2c.h"
#include "hardware/clocks.h"
#include "vl53l0x.h"

/* MACROS PI PICO */
#define LED_PIN_G 11
#define LED_PIN_B 12
#define LED_PIN_R 13
#define BUZZER_PIN 21
#define BUTTON5_PIN 5
#define BUTTON6_PIN 6
#define PWM_STEPS 2000
#define DEBOUNCE_DELAY_MS 700
#define FADE_STEP_DELAY (100) 
#define I2C_SDA 14
#define I2C_SCL 15
#define I2C_SDA_DISTANCE 0
#define I2C_SCL_DISTANCE 1

/* END */

/* MACROS MQTT */
#define DEBUG_printf printf
#define MQTT_SERVER_HOST "broker.emqx.io"
#define MQTT_SERVER_PORT 1883
#define MQTT_TLS 0
#define BUFFER_SIZE 256
/* END*/

/*VARIAVEIS*/
extern bool alarme;
typedef struct MQTT_CLIENT_T_ {
    ip_addr_t remote_addr;
    mqtt_client_t *mqtt_client;
    u32_t received;
    u32_t counter;
    u32_t reconnect;
} MQTT_CLIENT_T;
/* END */

/* FUNÇOES */
void pinos_start();
void gpio5_callback(uint gpio, uint32_t events);
static MQTT_CLIENT_T* mqtt_client_init(void);
void run_dns_lookup(MQTT_CLIENT_T *state);
void mqtt_run_test(MQTT_CLIENT_T *state);
void gpio_event_string(char *buf, uint32_t events);
void setup_pwm(uint gpio_pin);
void update_pwm(uint gpio_pin);
void pwm_led(uint gpio_pin, uint brilho);
/* END */