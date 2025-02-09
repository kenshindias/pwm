#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// GPIO onde o servo está conectado
#define SERVO_PIN 22

// Valores de pulso em microssegundos
#define PULSE_0_DEG    500    // Aproximadamente 0°
#define PULSE_90_DEG   1470   // Aproximadamente 90°
#define PULSE_180_DEG  2400   // Aproximadamente 180°

/*
   Frequência do servo: 50 Hz -> Período de 20ms (20000 us)
   - Configuração do PWM:
     - Top = 20000
     - Divisor = 125 (para reduzir clock ~125MHz -> 1MHz)
     - freq = 1MHz / (20000) = 50 Hz
*/

// Função para configurar o PWM no pino especificado
// com "top" fixo em 20000 (20ms).
void setup_pwm(uint gpio) {
    // Obtém o slice de PWM a partir do GPIO
    uint slice_num = pwm_gpio_to_slice_num(gpio);

    // Configura a função do pino como PWM
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    // Desabilita o PWM enquanto configura
    pwm_set_enabled(slice_num, false);

    // Define o "top" em 20000 (para 20ms)
    pwm_set_wrap(slice_num, 20000);

    // Ajusta o divisor de clock para 125
    // (clock padrão ~125MHz => 125MHz/125 = 1MHz)
    pwm_set_clkdiv(slice_num, 125.0f);

    // Inicia com duty cycle em zero
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), 0);

    // Habilita o PWM
    pwm_set_enabled(slice_num, true);
}

// Ajusta a largura de pulso em microssegundos
void set_servo_pulse_us(uint gpio, uint16_t us) {
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    uint channel = pwm_gpio_to_channel(gpio);

    // "us" será diretamente o valor (0 a 20000)
    pwm_set_chan_level(slice_num, channel, us);
}

int main() {
    stdio_init_all();

    // Inicializa o PWM no pino do servo
    setup_pwm(SERVO_PIN);

    // --- Parte 1: Ângulos fixos por 5 segundos cada ---
    // 1) 180° -> 2400us
    set_servo_pulse_us(SERVO_PIN, PULSE_180_DEG);
    sleep_ms(5000);

    // 2) 90° -> 1470us
    set_servo_pulse_us(SERVO_PIN, PULSE_90_DEG);
    sleep_ms(5000);

    // 3) 0° -> 500us
    set_servo_pulse_us(SERVO_PIN, PULSE_0_DEG);
    sleep_ms(5000);

    // --- Parte 2: Movimentação contínua de 0° a 180° e vice-versa ---
    // Incrementos de 5us a cada 10ms para um movimento suave.
    while (true) {
        // Sobe de 500us (0°) até 2400us (180°)
        for (uint16_t pulse = PULSE_0_DEG; pulse <= PULSE_180_DEG; pulse += 5) {
            set_servo_pulse_us(SERVO_PIN, pulse);
            sleep_ms(10);
        }
        // Desce de 2400us (180°) até 500us (0°)
        for (uint16_t pulse = PULSE_180_DEG; pulse >= PULSE_0_DEG; pulse -= 5) {
            set_servo_pulse_us(SERVO_PIN, pulse);
            sleep_ms(10);
        }
    }

    return 0;
}
