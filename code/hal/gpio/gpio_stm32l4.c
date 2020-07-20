#include "gpio/gpio.h"
#include "board/board.h"
#include <stdint.h>

void gpio_init(void)
{
  // Enable clocks
  LL_AHB2_GRP1_EnableClock(
    LL_AHB2_GRP1_PERIPH_GPIOA | LL_AHB2_GRP1_PERIPH_GPIOB | LL_AHB2_GRP1_PERIPH_GPIOC);

  // ADC pins
  LL_GPIO_InitTypeDef adc_init_struct = ADC_PIN_CFG;
  adc_init_struct.Pin = ADC_A_MASK;
  LL_GPIO_Init(ADC_A_PORT, &adc_init_struct);
  adc_init_struct.Pin = ADC_B_MASK;
  LL_GPIO_Init(ADC_B_PORT, &adc_init_struct);

  // ALERT, SWITCH, PGOOD, STAT1, STAT2: input, pullup, interrupt
  LL_GPIO_InitTypeDef in_init_struct = IN_PU_PIN_CFG;
  in_init_struct.Pin = ALERT_MASK;
  LL_GPIO_Init(ALERT_PORT, &in_init_struct);

  in_init_struct.Pin = SWITCH_MASK;
  LL_GPIO_Init(SWITCH_PORT, &in_init_struct);

  in_init_struct.Pin = CHARGE_PGOOD_MASK;
  LL_GPIO_Init(CHARGE_PGOOD_PORT, &in_init_struct);

  in_init_struct.Pin = CHARGE_ISNS_MASK;
  LL_GPIO_Init(CHARGE_ISNS_PORT, &in_init_struct);

  in_init_struct.Pin = CHARGE_STAT_MASK;
  LL_GPIO_Init(CHARGE_STAT_PORT, &in_init_struct);
  // TODO - EXTI

  // MOTOR_IN_A/B, LCD, CE_CONTROL, ALERT_ENABLE, LED: output
  LL_GPIO_InitTypeDef out_init_struct = OUT_PIN_CFG;

  out_init_struct.Pin = MOTOR_IN_MASK;
  LL_GPIO_Init(MOTOR_IN_PORT, &out_init_struct);

  out_init_struct.Pin = LCD_MASK;
  LL_GPIO_Init(LCD_PORT, &out_init_struct);

  out_init_struct.Pin = CHARGE_CONTROL_MASK;
  LL_GPIO_Init(CHARGE_CONTROL_PORT, &out_init_struct);

  out_init_struct.Pin = ALERT_ENABLE_N_MASK;
  LL_GPIO_Init(ALERT_ENABLE_N_PORT, &out_init_struct);

  out_init_struct.Pin = LED_MASK;
  LL_GPIO_Init(LED_PORT, &out_init_struct);

  // UART
  LL_GPIO_InitTypeDef uart_tx_init_struct = UART_TX_PIN_CFG;
  LL_GPIO_Init(UART_PORT, &uart_tx_init_struct);
  LL_GPIO_InitTypeDef uart_rx_init_struct = UART_RX_PIN_CFG;
  LL_GPIO_Init(UART_PORT, &uart_rx_init_struct);

  // USB - TODO

  // MOTOR_PWM
  LL_GPIO_InitTypeDef motor_pwm_init_struct = MOTOR_PWM_PIN_CFG;
  LL_GPIO_Init(MOTOR_PWM_PORT, &motor_pwm_init_struct);
}

void gpio_set_mask(gpio_register_t port, register_size_t pin_mask)
{
  LL_GPIO_SetOutputPin(port, pin_mask);
}

void gpio_clear_mask(gpio_register_t port, register_size_t pin_mask)
{
  LL_GPIO_ResetOutputPin(port, pin_mask);
}

void gpio_write_mask(gpio_register_t port, register_size_t pin_mask)
{
  LL_GPIO_WriteOutputPort(port, pin_mask);
}

register_size_t gpio_read_mask(gpio_register_t port, register_size_t pin_mask)
{
  return LL_GPIO_IsInputPinSet(port, pin_mask);
}

void gpio_set_pin(gpio_register_t port, uint8_t pin_number)
{
  LL_GPIO_SetOutputPin(port, (1u << pin_number));
}

void gpio_clear_pin(gpio_register_t port, uint8_t pin_number)
{
  LL_GPIO_ResetOutputPin(port, (1u << pin_number));
}

uint8_t gpio_read_pin(gpio_register_t port, uint8_t pin_number)
{
  uint8_t return_val = 0u;

  if (LL_GPIO_IsInputPinSet(port, (1u << pin_number)))
  {
    return_val = 1u;
  }

  return return_val;
}
