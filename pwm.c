// Bibliotecas necessárias para o funcionamento do código
#include <stdio.h>               
#include "pico/stdlib.h"         
#include "hardware/pwm.h"        // Biblioteca de hardware do Raspberry Pi Pico para controle de PWM (modulação por largura de pulso)

// Definição do pino onde o servo motor está conectado
#define SERVO_PIN 22

// Definição dos valores de largura de pulso (em microssegundos) para diferentes ângulos do servo motor
#define PULSE_0_DEG    500    // Pulso correspondente a aproximadamente 180° no servo
#define PULSE_90_DEG   1470   // Pulso correspondente a aproximadamente 90° no servo
#define PULSE_180_DEG  2400   // Pulso correspondente a aproximadamente 0° no servo

/*
   O servo motor utilizado neste código opera com uma frequência de 50 Hz.
   Isso significa que ele precisa receber um sinal PWM com um período de 20 ms (20000 µs).
   
   Para gerar esse sinal, o Raspberry Pi Pico configurará o PWM da seguinte maneira:
   - O "top" do contador PWM será definido como 20000, correspondendo ao período de 20 ms.
   - O clock do Raspberry Pi Pico será dividido por 125 para reduzir sua frequência (~125 MHz) para 1 MHz.
   - Com isso, cada incremento do contador PWM corresponderá exatamente a 1 µs, permitindo controle preciso do servo.
*/

// Função para configurar o PWM no pino especificado
void setup_pwm(uint gpio) {
    // Obtém o número do slice de PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(gpio);

    // Configura o pino para a função de PWM
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    // Desabilita temporariamente o PWM para configurar corretamente
    pwm_set_enabled(slice_num, false);

    // Define o "top" do contador PWM como 20000 (correspondente a 20 ms de período)
    pwm_set_wrap(slice_num, 20000);

    // Define o divisor de clock como 125 para obter uma frequência de 1 MHz
    pwm_set_clkdiv(slice_num, 125.0f);

    // Inicializa o PWM com um duty cycle de 0%
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), 0);

    // Habilita o PWM no pino configurado
    pwm_set_enabled(slice_num, true);
}

// Função para ajustar a largura de pulso do PWM em microssegundos
void set_servo_pulse_us(uint gpio, uint16_t us) {
    uint slice_num = pwm_gpio_to_slice_num(gpio);  // Obtém o número do slice do PWM
    uint channel = pwm_gpio_to_channel(gpio);      // Obtém o canal do PWM associado ao pino

    // Define o nível do canal PWM para corresponder ao tempo de pulso desejado
    pwm_set_chan_level(slice_num, channel, us);
}

// Função principal do programa
int main() {
    stdio_init_all();  // Inicializa a entrada e saída padrão (para depuração via USB)

    // Configura o pino do servo para operar com PWM
    setup_pwm(SERVO_PIN);

    // --- PARTE 1: Movimentação para posições fixas com intervalos de 5 segundos ---
    
    // 1) Define o servo para 180° (pulso de 2400 µs)
    printf("0 \n");
    set_servo_pulse_us(SERVO_PIN, PULSE_180_DEG);
    sleep_ms(5000);  // Aguarda 5 segundos antes de continuar

    // 2) Define o servo para 90° (pulso de 1470 µs)
    printf("90 \n");
    set_servo_pulse_us(SERVO_PIN, PULSE_90_DEG);
    sleep_ms(5000);  // Aguarda 5 segundos antes de continuar

    // 3) Define o servo para 0° (pulso de 500 µs)
    printf("180 \n");
    set_servo_pulse_us(SERVO_PIN, PULSE_0_DEG);
    sleep_ms(5000);  // Aguarda 5 segundos antes de continuar

    // --- PARTE 2: Movimentação suave do servo entre 0° e 180° repetidamente ---
    
    while (true) {
        // Movimenta o servo de 0° (500 µs) até 180° (2400 µs) com incrementos pequenos
        printf("Movimentação suave de 180 até 0 graus \n");
        for (uint16_t pulse = PULSE_0_DEG; pulse <= PULSE_180_DEG; pulse += 5) {
            set_servo_pulse_us(SERVO_PIN, pulse); // Ajusta a posição do servo
            sleep_ms(10); // Pequeno atraso para suavizar a movimentação
        }

        printf("Movimentação suave de 0 até 180 graus \n");
        // Movimenta o servo de volta de 180° (2400 µs) até 0° (500 µs) suavemente
        for (uint16_t pulse = PULSE_180_DEG; pulse >= PULSE_0_DEG; pulse -= 5) {
            set_servo_pulse_us(SERVO_PIN, pulse); // Ajusta a posição do servo
            sleep_ms(10); // Pequeno atraso para suavizar a movimentação
        }
    }

    return 0;  // Retorno padrão da função main (não será alcançado devido ao loop infinito)
}
