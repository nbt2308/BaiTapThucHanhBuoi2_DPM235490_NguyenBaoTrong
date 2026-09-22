#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  pin_t vcc;
  pin_t vee;

  pin_t in_a_plus;
  pin_t in_a_minus;
  pin_t out_a;

  pin_t in_b_plus;
  pin_t in_b_minus;
  pin_t out_b;

  timer_t timer;
} chip_state_t;

static void update_opamp(chip_state_t *chip) {
  float vcc = pin_adc_read(chip->vcc);
  float vee = pin_adc_read(chip->vee);

  float in_plus = pin_adc_read(chip->in_a_plus);
  float in_minus = pin_adc_read(chip->in_a_minus);

  float out;

  if (in_plus > in_minus) {
    out = vcc;
  } else {
    out = vee;
  }

  pin_dac_write(chip->out_a, out);

  printf("VCC=%.2f IN+=%.2f IN-=%.2f OUT=%.2f\n",
         vcc, in_plus, in_minus, out);
}

void chip_timer_event(void *user_data) {
  chip_state_t *chip = (chip_state_t *)user_data;

  update_opamp(chip);
}

void chip_init() {
  chip_state_t *chip = malloc(sizeof(chip_state_t));

  chip->vcc = pin_init("VCC", ANALOG);
  chip->vee = pin_init("VEE", ANALOG);

  chip->in_a_plus = pin_init("IN_A+", ANALOG);
  chip->in_a_minus = pin_init("IN_A-", ANALOG);
  chip->out_a = pin_init("OUT_A", ANALOG);

  chip->in_b_plus = pin_init("IN_B+", ANALOG);
  chip->in_b_minus = pin_init("IN_B-", ANALOG);
  chip->out_b = pin_init("OUT_B", ANALOG);

  timer_config_t config = {
    .callback = chip_timer_event,
    .user_data = chip,
  };

  chip->timer = timer_init(&config);
  timer_start(chip->timer, 1000, true);

  printf("LM358 initialized\n");
}