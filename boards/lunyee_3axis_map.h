/*
  lunyee_3axis_map.h - driver code for STM32F103xx ARM processors

  Lunyee / ANNOY TOOLS 3-axis 5.2 control board, silkscreen LY-3axis-5.2-V3.4
  (as fitted to the Lunyee 3020 Nova). GD32F303CCT6 running the STM32F103RC
  build at 72 MHz, three A4988 drivers with one common enable, CH340 USB on
  USART1 (shared with the offline plug). Pin map taken from the vendor's V3.4
  board design files, 2026-10-03.

  Part of grblHAL

  grblHAL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  grblHAL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with grblHAL. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef STM32F103xE
#error "This board has a GD32F303CCT6 (256K flash), select the STM32F103RC build!"
#endif

// PA0/PA1 (A step/dir) and PB15 (A limit) are not wired on the V3.4 board.
#if N_ABC_MOTORS > 0 || N_GANGED
#error "Axis configuration is not supported!"
#endif

#if EEPROM_ENABLE
#error "EEPROM plugin not supported!"
#endif

#define BOARD_NAME "Lunyee LY-3axis-5.2 V3.4"
#define BOARD_URL "https://github.com/mojavemesa-lgtm/lunyee-3020-grblhal"

#define SERIAL_PORT 1 // GPIOA: TX = 9, RX = 10 -> CH340 (USB-B) and the offline plug

// Define step pulse output pins.
#define STEP_PORT               GPIOA
#define X_STEP_PIN              6
#define Y_STEP_PIN              4 // drives both Y motors (Y1 and Y2 are paralleled on the board)
#define Z_STEP_PIN              2
#define STEP_OUTMODE            GPIO_MAP

// Define step direction output pins.
#define DIRECTION_PORT          GPIOA
#define X_DIRECTION_PIN         7
#define Y_DIRECTION_PIN         5
#define Z_DIRECTION_PIN         3
#define DIRECTION_OUTMODE       GPIO_MAP

// Define stepper driver enable/disable output pin (one line to all A4988s, active low).
#define STEPPERS_ENABLE_PORT    GPIOB
#define STEPPERS_ENABLE_PIN     0

// Define homing/hard limit switch input pins (the X+/X- etc. plugs are paralleled on the board).
#define LIMIT_PORT              GPIOB
#define X_LIMIT_PIN             12
#define Y_LIMIT_PIN             13
#define Z_LIMIT_PIN             14
#define LIMIT_INMODE            GPIO_SHIFT12

#define AUXOUTPUT0_PORT         GPIOA // Spindle PWM (TIM1_CH1): all laser PWM pins and the spindle MOSFET
#define AUXOUTPUT0_PIN          8
#define AUXOUTPUT1_PORT         GPIOB // Spindle enable: no such output on the board, PB7 is an unfitted buzzer pad
#define AUXOUTPUT1_PIN          7

// Define driver spindle pins
#if DRIVER_SPINDLE_ENABLE & SPINDLE_ENA
#define SPINDLE_ENABLE_PORT     AUXOUTPUT1_PORT
#define SPINDLE_ENABLE_PIN      AUXOUTPUT1_PIN
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_PWM
#define SPINDLE_PWM_PORT_BASE   GPIOA_BASE
#define SPINDLE_PWM_PORT        AUXOUTPUT0_PORT
#define SPINDLE_PWM_PIN         AUXOUTPUT0_PIN
#endif

#define AUXINPUT0_PORT          GPIOB // Probe: front panel "S" / "-" and the PROBE plug
#define AUXINPUT0_PIN           5
#define AUXINPUT1_PORT          GPIOB // Reset: RESET plug, K2 button, CH340 DTR and offline plug pin 5
#define AUXINPUT1_PIN           6
#define AUXINPUT2_PORT          GPIOB // Feed hold: HOLD plug
#define AUXINPUT2_PIN           3
#define AUXINPUT3_PORT          GPIOB // Cycle start: RUN plug
#define AUXINPUT3_PIN           4

// Define user-control controls (cycle start, reset, feed hold) input pins.
#if CONTROL_ENABLE & CONTROL_HALT
#define RESET_PORT              AUXINPUT1_PORT
#define RESET_PIN               AUXINPUT1_PIN
#endif
#if CONTROL_ENABLE & CONTROL_FEED_HOLD
#define FEED_HOLD_PORT          AUXINPUT2_PORT
#define FEED_HOLD_PIN           AUXINPUT2_PIN
#endif
#if CONTROL_ENABLE & CONTROL_CYCLE_START
#define CYCLE_START_PORT        AUXINPUT3_PORT
#define CYCLE_START_PIN         AUXINPUT3_PIN
#endif

#if PROBE_ENABLE
#define PROBE_PORT              AUXINPUT0_PORT
#define PROBE_PIN               AUXINPUT0_PIN
#endif

#if SAFETY_DOOR_ENABLE
#error "Safety door input is not available on this board!"
#endif

#if KEYPAD_ENABLE == 1
#error "I2C keypad mode is not supported!"
#endif

#if SDCARD_ENABLE
#error "SD card is not supported!"
#endif

/**/
