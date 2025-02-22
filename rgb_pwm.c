// Embarcatech 2025 - Projeto Final - Filipe Alves de Sousa
// Sistema de Iluminação Adaptativa com LEDs RGB para Aplicação em Estudos do Comportamento de Crianças com TDAH

#include <stdio.h>                      // Inclui a biblioteca padrão para funções de entrada/saída (ex: printf)
#include "pico/stdlib.h"                // Inclui funções padrão da placa Pico, como inicialização e delay
#include "hardware/pwm.h"               // Inclui funções para controle de PWM (modulação por largura de pulso)
#include "hardware/i2c.h"               // Inclui funções para comunicação I2C (usada pelo display OLED)
#include "inc/ssd1306.h"                // Inclui as declarações e definições para controlar o display OLED SSD1306
#include <string.h>                     // Inclui funções para manipulação de strings e buffers (ex: memset)

//==================================================================================// 

// Definições dos pinos físicos usados no projeto:
// Cada #define cria um nome para um número de pino específico na placa.
#define LED_RED    13                  // Pino do LED vermelho
#define LED_GREEN  11                  // Pino do LED verde
#define LED_BLUE   12                  // Pino do LED azul
#define BUTTON_DEC 5                   // Pino do botão para diminuir o brilho do LED azul
#define BUTTON_INC 6                   // Pino do botão para aumentar o brilho do LED azul

// Parâmetros do PWM (controle de intensidade dos LEDs)
// Define os valores máximo, mínimo e o quanto se altera a cada clique (passo)
#define PWM_MAX 0xFFFF                 // Valor máximo para o PWM (intensidade máxima)
#define PWM_MIN 0x0000                 // Valor mínimo para o PWM (intensidade mínima)
#define PWM_STEP 0x0800                // Incremento ou decremento aplicado a cada botão pressionado

// Variáveis globais para armazenar os níveis de PWM dos LEDs.
// Cada canal (vermelho, verde, azul) inicia com metade do valor máximo.
uint16_t pwm_r = PWM_MAX / 2;          // Intensidade inicial do LED vermelho
uint16_t pwm_g = PWM_MAX / 2;          // Intensidade inicial do LED verde
uint16_t pwm_b = PWM_MAX / 2;          // Intensidade inicial do LED azul

// Cria um buffer (um array de bytes) para armazenar a imagem que será exibida no display OLED.
// O tamanho do buffer é definido pela biblioteca (dependendo da resolução do display).
uint8_t oled_buffer[ssd1306_buffer_length];

// Define a "área de renderização" para o display OLED.
// Essa estrutura informa quais colunas e páginas (linhas de 8 pixels) serão atualizadas.
// Aqui, cobre todo o display: das colunas 0 até a última, e de 0 até o número de páginas menos um.
struct render_area oled_area = {
    .start_column = 0,                     // Inicia na primeira coluna
    .end_column = ssd1306_width - 1,         // Termina na última coluna (largura do display - 1)
    .start_page = 0,                       // Inicia na primeira página (cada página contém 8 pixels de altura)
    .end_page = ssd1306_n_pages - 1          // Termina na última página
};

//----------------------------------------------------------
// Função: setup_pwm
// Objetivo: Configurar um pino para funcionar com PWM (para controlar a intensidade do LED)
//----------------------------------------------------------
void setup_pwm(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);          // Configura o pino para usar a função PWM
    uint slice = pwm_gpio_to_slice_num(gpio);          // Determina qual "slice" (grupo de canais PWM) o pino usa
    pwm_config config = pwm_get_default_config();      // Pega a configuração padrão do PWM
    pwm_config_set_clkdiv(&config, 4.f);                // Ajusta o divisor de clock para alterar a frequência do PWM
    pwm_init(slice, &config, true);                    // Inicializa o PWM com a configuração e inicia a contagem
}

//----------------------------------------------------------
// Função: update_leds
// Objetivo: Atualizar os níveis de PWM dos LEDs RGB de acordo com as variáveis pwm_r, pwm_g, pwm_b
//----------------------------------------------------------
void update_leds() {
    pwm_set_gpio_level(LED_RED, pwm_r);   // Define a intensidade do LED vermelho
    pwm_set_gpio_level(LED_GREEN, pwm_g); // Define a intensidade do LED verde
    pwm_set_gpio_level(LED_BLUE, pwm_b);  // Define a intensidade do LED azul
}

//----------------------------------------------------------
// Função: update_oled
// Objetivo: Atualizar o display OLED com informações interativas e os valores atuais do LED azul
//----------------------------------------------------------
void update_oled() {
    // Limpa (zera) o buffer que será enviado ao display
    memset(oled_buffer, 0, sizeof(oled_buffer));
    
    // Cria mensagens de texto que serão exibidas no display
    char instrucao[45] = "Embarcatech2025";    // Mensagem com o nome ou marca do projeto
    char instrucao2[20] = "---------------";    // Linha separadora para organização visual
    char instrucao3[30] = "B1: diminuir";         // Instrução: pressione B1 para diminuir o brilho
    char instrucao4[30] = "B2: aumentar";          // Instrução: pressione B2 para aumentar o brilho

    // Calcula a porcentagem do duty cycle para o LED azul
    // Duty cycle é a relação entre o valor atual e o valor máximo, multiplicada por 100 para converter em porcentagem
    float duty_percent = ((float)pwm_b / PWM_MAX) * 100.0f;
    char duty_str[40];
    sprintf(duty_str, "luz Azul: %3.0f%%", duty_percent);  // Cria uma string que mostra a porcentagem
    
    // Desenha as mensagens no buffer do display
    // Os números (5, 0), (5, 10), etc., indicam a posição (x, y) em pixels onde o texto será exibido.
    ssd1306_draw_string(oled_buffer, 5, 0, instrucao);     // Desenha o primeiro texto na linha superior
    ssd1306_draw_string(oled_buffer, 5, 10, instrucao2);     // Desenha a linha separadora logo abaixo
    ssd1306_draw_string(oled_buffer, 5, 20, instrucao3);     // Desenha a instrução para diminuir
    ssd1306_draw_string(oled_buffer, 5, 30, instrucao4);     // Desenha a instrução para aumentar
    ssd1306_draw_string(oled_buffer, 5, 50, duty_str);       // Desenha a porcentagem do duty cycle na parte inferior

    // Recalcula o tamanho da área de renderização do display, caso haja alguma alteração
    calculate_render_area_buffer_length(&oled_area);
    
    // Envia o conteúdo do buffer para o display, atualizando o que é mostrado
    render_on_display(oled_buffer, &oled_area);
}

//----------------------------------------------------------
// Função: setup_buttons
// Objetivo: Configurar os pinos dos botões para leitura (entrada) com resistor pull-up
//----------------------------------------------------------
void setup_buttons() {
    gpio_init(BUTTON_DEC);                 // Inicializa o pino do botão de diminuir
    gpio_init(BUTTON_INC);                 // Inicializa o pino do botão de aumentar
    gpio_set_dir(BUTTON_DEC, GPIO_IN);     // Configura o pino do botão de diminuir como entrada
    gpio_set_dir(BUTTON_INC, GPIO_IN);     // Configura o pino do botão de aumentar como entrada
    gpio_pull_up(BUTTON_DEC);              // Ativa resistor interno de pull-up para o botão de diminuir
    gpio_pull_up(BUTTON_INC);              // Ativa resistor interno de pull-up para o botão de aumentar
}

//----------------------------------------------------------
// Função: main (ponto de entrada do programa)
//----------------------------------------------------------
int main() {
    stdio_init_all();                      // Inicializa os sistemas de entrada/saída padrão (por exemplo, USB)

    // Configura a comunicação I2C para o display OLED:
    // Inicializa o I2C1 com a frequência definida (convertida de milissegundos para Hz)
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    // Configura os pinos 14 e 15 para funcionar como I2C (SDA e SCL, respectivamente)
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_pull_up(14);                      // Ativa resistor de pull-up no pino SDA
    gpio_pull_up(15);                      // Ativa resistor de pull-up no pino SCL

    // Configura os pinos para controle de PWM dos LEDs RGB
    setup_pwm(LED_RED);                    // Configura o pino do LED vermelho para PWM
    setup_pwm(LED_GREEN);                  // Configura o pino do LED verde para PWM
    setup_pwm(LED_BLUE);                   // Configura o pino do LED azul para PWM

    // Inicializa os botões de controle
    setup_buttons();

    // Inicializa o display OLED enviando os comandos iniciais
    ssd1306_init();
    // Atualiza o display com as mensagens e informações atuais
    update_oled();

    // Loop principal que roda indefinidamente
    while (true) {
        // Se o botão de diminuir (B1) for pressionado (gpio_get retorna 0 quando pressionado, pois há pull-up)
        if (gpio_get(BUTTON_DEC) == 0) {
            // Se o valor do LED azul for maior que o mínimo mais um passo, diminui o valor
            if (pwm_b > PWM_MIN + PWM_STEP)
                pwm_b -= PWM_STEP;
            else
                pwm_b = PWM_MIN;           // Caso contrário, define como mínimo
            update_leds();                 // Atualiza os níveis dos LEDs com o novo valor
            update_oled();                 // Atualiza o display OLED com os novos dados
            sleep_ms(300);                 // Aguarda 300 milissegundos para evitar múltiplas leituras (debounce)
        }
        // Se o botão de aumentar (B2) for pressionado
        if (gpio_get(BUTTON_INC) == 0) {
            // Se o valor do LED azul for menor que o máximo menos um passo, aumenta o valor
            if (pwm_b < PWM_MAX - PWM_STEP)
                pwm_b += PWM_STEP;
            else
                pwm_b = PWM_MAX;           // Caso contrário, define como máximo
            update_leds();                 // Atualiza os LEDs com o novo valor
            update_oled();                 // Atualiza o display OLED com as informações atualizadas
            sleep_ms(300);                 // Aguarda 300 milissegundos para debounce
        }
        sleep_ms(50);                      // Pequeno delay para que o loop não fique rodando muito rápido
    }
    return 0;                              // Retorna 0 (normalmente nunca alcançado, pois o loop é infinito)
}
