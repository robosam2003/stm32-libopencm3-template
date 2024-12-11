#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/timer.h>

#define LED_PORT        (GPIOE)
#define ORANGE_LED_PIN  (GPIO15)

static void rcc_setup(void) {
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);
}

static void clock_setup(void)
{
    /* Enable GPIOD clock for LED & USARTs. */
    rcc_periph_clock_enable(LED_PORT);
    rcc_periph_clock_enable(RCC_GPIOA);

    /* Enable clocks for USART2. */
    rcc_periph_clock_enable(RCC_USART2);
}

static void usart_setup(void)
{
    /* Setup USART2 parameters. */
    usart_set_baudrate(USART2, 115200);
    usart_set_databits(USART2, 8);
    usart_set_stopbits(USART2, USART_STOPBITS_1);
    usart_set_mode(USART2, USART_MODE_TX);
    usart_set_parity(USART2, USART_PARITY_NONE);
    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

    /* Finally enable the USART. */
    usart_enable(USART2);
}

static void gpio_setup(void)
{
    /* Setup GPIO pin GPIO12 on GPIO port D for LED. */
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, ORANGE_LED_PIN);

    /* Setup GPIO pins for USART2 transmit. */
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);

    /* Setup USART2 TX pin as alternate function. */
    gpio_set_af(GPIOA, GPIO_AF7, GPIO2);
}

// void delay_cycles(uint32_t cyc) {
//     for (uint32_t i = 0; i < cyc; i++) {
//         __asm__("nop");
//     }
// }

int main(void)
{
    int i, j = 0, c = 0;

    clock_setup();
    gpio_setup();
    // usart_setup();

    /* Blink the LED (PD12) on the board with every transmitted byte. */
    while (1) {
        gpio_toggle(GPIOD, GPIO12);	/* LED on/off */

        for (i = 0; i < 3000000; i++) {	/* Wait a bit. */
            __asm__("NOP");
        }
    }

    return 0;
}