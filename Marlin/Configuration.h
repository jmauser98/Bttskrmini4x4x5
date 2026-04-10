/**
 * Marlin Firmware – Configuration.h
 *
 * Hardware:
 *   Printer  : Ender 3 (frame / kinematics)
 *   Board    : BigTreeTech SKR Mini E3 V3 (GD32 / STM32G0 variant)
 *   Display  : BigTreeTech TFT35 V3   (configured in Configuration_adv.h)
 *   Probe    : BLTouch (or CR Touch)
 *   Dual Z   : Two Z motors – use a Z-splitter cable (both driven by the
 *              single Z driver) OR wire the second motor to the E1 port and
 *              set NUM_Z_STEPPER_DRIVERS 2 below.
 *   Bed size : 400 x 400 mm
 *   Z travel : 500 mm
 *
 * Based on Marlin 2.1.x
 */
#pragma once

#define CONFIGURATION_H_VERSION 02010300

//===========================================================================
//============================= Getting Started =============================
//===========================================================================

// @section info
#define STRING_CONFIG_H_AUTHOR "(jmauser98, Ender3 400x400x500 BLTouch DualZ)"
#define CUSTOM_MACHINE_NAME "Ender-3 400x400x500"

//===========================================================================
//============================= Serial Settings =============================
//===========================================================================

// @section machine

/**
 * SERIAL_PORT selects which serial port should be used for primary host
 * communication.  -1 = USB CDC  (recommended for most setups)
 */
#define SERIAL_PORT -1

/**
 * SERIAL_PORT_2 is used for the BTT TFT35 V3 touchscreen.
 * On SKR Mini E3 V3 the TFT header is wired to USART2 → port 2.
 */
#define SERIAL_PORT_2 2

#define BAUDRATE 250000
#define BAUDRATE_2 115200

//===========================================================================
//============================== Board / MCU ================================
//===========================================================================

/**
 * BTT SKR Mini E3 V3.
 * Both the original STM32G0B1 and the GD32G0B0 variants use the same board
 * define.  The correct MCU target is selected when building with
 * PlatformIO env: STM32G0B1RE_btt or STM32G0B0RE_btt (GD variant).
 */
#ifndef MOTHERBOARD
  #define MOTHERBOARD BOARD_BTT_SKR_MINI_E3_V3_0
#endif

//===========================================================================
//============================== Extruder ===================================
//===========================================================================

// @section extruder
#define EXTRUDERS 1
#define DEFAULT_NOMINAL_FILAMENT_DIA 1.75

//===========================================================================
//=========================== Thermal Settings ==============================
//===========================================================================

// @section temperature

/**
 * Thermistor types:
 *   1  – EPCOS 100K NTC (stock Ender 3 thermistor)
 *   11 – QU-BD silicone heated bed thermistor (also works for stock bed)
 * Adjust if you have upgraded thermistors.
 */
#define TEMP_SENSOR_0 1   // Hotend
#define TEMP_SENSOR_BED 1 // Heated bed

// Hotend PID tuning – run M303 E0 S200 C8 to calibrate for your hotend.
#define PIDTEMP
#define PID_AUTOTUNE_MENU
#define DEFAULT_Kp  28.72
#define DEFAULT_Ki   2.62
#define DEFAULT_Kd  78.81

// Bed PID – enable for consistent bed temperatures (optional but recommended).
#define PIDTEMPBED
#define DEFAULT_bedKp  462.10
#define DEFAULT_bedKi   85.47
#define DEFAULT_bedKd  624.59

// Safety limits
#define HEATER_0_MAXTEMP 275
#define BED_MAXTEMP      120

// Prevent extrusion if the nozzle is too cold.
#define PREVENT_COLD_EXTRUSION
#define EXTRUDE_MINTEMP 170

// Thermal runaway protection – highly recommended.
#define THERMAL_PROTECTION_HOTENDS
#define THERMAL_PROTECTION_BED

//===========================================================================
//============================== Motion =====================================
//===========================================================================

// @section motion

/**
 * Default axis steps per unit (steps/mm).
 * Ender 3 stock values for X/Y/Z.  E steps depend on your extruder;
 * 93 works for the stock Bowden extruder.  Run M92 / M503 to verify.
 */
#define DEFAULT_AXIS_STEPS_PER_UNIT { 80, 80, 400, 93 }

/**
 * Max feedrates (mm/s).  These are hardware safety limits.
 */
#define DEFAULT_MAX_FEEDRATE { 500, 500, 5, 25 }

/**
 * Max acceleration (mm/s²).
 */
#define DEFAULT_MAX_ACCELERATION { 500, 500, 100, 5000 }

#define DEFAULT_ACCELERATION          500   // Printing acceleration
#define DEFAULT_RETRACT_ACCELERATION  500
#define DEFAULT_TRAVEL_ACCELERATION   1000

/** Jerk (mm/s) */
#define CLASSIC_JERK
#define DEFAULT_XJERK  8.0
#define DEFAULT_YJERK  8.0
#define DEFAULT_ZJERK  0.4
#define DEFAULT_EJERK  5.0

//===========================================================================
//============================= Z Probe / BLTouch ===========================
//===========================================================================

// @section probes

/**
 * BLTouch / CR Touch
 * The SKR Mini E3 V3 has a dedicated 5-pin BLTouch connector.
 * The servo signal pin (PC14) and Z-min endstop pin are pre-wired on that
 * connector – no additional pin definitions are needed here.
 */
#define BLTOUCH

/**
 * Probe offset from the nozzle tip (mm).
 * X: negative  = probe is to the LEFT  of the nozzle
 * Y: negative  = probe is in FRONT of the nozzle
 * Z: start at 0 and calibrate with the paper-test (G0 Z0 → baby-step).
 *
 * Typical values for a standard BLTouch mount on Ender 3 left-side:
 *   { -41.5, -7.0, 0.0 }
 * Adjust to match YOUR specific mount!
 */
#define NOZZLE_TO_PROBE_OFFSET { -41.5, -7.0, 0.0 }

#define PROBING_MARGIN 10    // (mm) minimum margin from bed edge when probing

// Probing speed
#define Z_PROBE_FEEDRATE_FAST (4*60)
#define Z_PROBE_FEEDRATE_SLOW (Z_PROBE_FEEDRATE_FAST / 2)

// Require a minimum number of probe passes
#define MULTIPLE_PROBING 2

// Use Z_MIN_PROBE connected to BLTouch port
#define USE_PROBE_FOR_Z_HOMING

//===========================================================================
//========================= Bed-Level / Auto-Leveling =======================
//===========================================================================

// @section calibration

/**
 * Bilinear Auto Bed Leveling (G29)
 * A 5×5 grid gives good compensation for a 400×400 bed.
 */
#define AUTO_BED_LEVELING_BILINEAR
#define RESTORE_LEVELING_AFTER_G28

// Bilinear grid size
#define GRID_MAX_POINTS_X 5
#define GRID_MAX_POINTS_Y GRID_MAX_POINTS_X

// Extrapolate beyond the probed area
#define EXTRAPOLATE_BEYOND_GRID

// Fade leveling correction over 10 mm of Z travel (optional but recommended)
#define ENABLE_LEVELING_FADE_HEIGHT
#define DEFAULT_LEVELING_FADE_HEIGHT 10.0

//===========================================================================
//============================= Motion Limits ===============================
//===========================================================================

// @section machine

/**
 * Axis direction – Ender 3 default.
 * Invert an axis if the motor moves the wrong way.
 */
#define INVERT_X_DIR false
#define INVERT_Y_DIR true
#define INVERT_Z_DIR false
#define INVERT_E0_DIR true

// Home direction
#define X_HOME_DIR -1
#define Y_HOME_DIR -1
#define Z_HOME_DIR -1

/** Travel limits (mm) after homing */
#define X_MIN_POS 0
#define Y_MIN_POS 0
#define Z_MIN_POS 0
#define X_MAX_POS 400
#define Y_MAX_POS 400
#define Z_MAX_POS 500

#define X_BED_SIZE X_MAX_POS
#define Y_BED_SIZE Y_MAX_POS

// Software endstops
#define MIN_SOFTWARE_ENDSTOPS
#define MAX_SOFTWARE_ENDSTOPS
#define SOFT_ENDSTOPS_MENU_ITEM

//===========================================================================
//========================== Dual Z Stepper Drivers =========================
//===========================================================================

// @section motion

/**
 * Dual Z motor configuration.
 *
 * OPTION A – Z-splitter cable (most common, no extra board needed):
 *   Both Z motors are connected to the single Z stepper driver via a
 *   Y-splitter cable.  No firmware change needed; leave NUM_Z_STEPPER_DRIVERS
 *   at 1 (default).  Z_STEPPER_AUTO_ALIGN cannot be used in this mode.
 *
 * OPTION B – Independent dual Z drivers (SKR Mini E3 V3 + E1 port as Z2):
 *   Uncomment the two lines below and wire the second Z motor to the E1 port.
 *   Marlin will use the E1 driver as the Z2 axis.
 *   This enables Z_STEPPER_AUTO_ALIGN (G34) for independent Z leveling.
 */
//#define NUM_Z_STEPPER_DRIVERS 2   // Uncomment for OPTION B
//#define Z_STEPPER_AUTO_ALIGN      // Uncomment for OPTION B

//===========================================================================
//=============================== Endstops ==================================
//===========================================================================

// @section endstops

// Use the BLTouch as the Z min probe (already set above); physical Z endstop
// is not needed when a probe is used for homing.
#define USE_XMIN_PLUG
#define USE_YMIN_PLUG
// #define USE_ZMIN_PLUG   // Not needed when using BLTouch for Z homing

// Endstop logic (normally-open stock Ender 3 switches)
#define X_MIN_ENDSTOP_INVERTING true
#define Y_MIN_ENDSTOP_INVERTING true
#define Z_MIN_ENDSTOP_INVERTING true

#define ENDSTOPPULLUPS

//===========================================================================
//=============================== LCD / TFT =================================
//===========================================================================

// @section lcd

/**
 * BTT TFT35 V3 display is handled entirely through the SERIAL_PORT_2 UART.
 * Enable the TFT_GENERIC option below so Marlin generates the correct
 * communication layer.  Graphical/touch features are managed by the TFT
 * firmware itself; no additional Marlin LCD type is needed.
 *
 * If you use the TFT in "Marlin Mode" (emulated 12864), additionally enable:
 *   #define REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER
 */
#define TFT_GENERIC
#define TFT_INTERFACE_UART

//===========================================================================
//=============================== EEPROM ====================================
//===========================================================================

// @section eeprom
#define EEPROM_SETTINGS
#define EEPROM_CHITCHAT
#define EEPROM_BOOT_SILENT

//===========================================================================
//========================== Preheat Constants ==============================
//===========================================================================

// @section preheat
#define PREHEAT_1_LABEL       "PLA"
#define PREHEAT_1_TEMP_HOTEND 200
#define PREHEAT_1_TEMP_BED     60
#define PREHEAT_1_FAN_SPEED     0

#define PREHEAT_2_LABEL       "PETG"
#define PREHEAT_2_TEMP_HOTEND 240
#define PREHEAT_2_TEMP_BED     85
#define PREHEAT_2_FAN_SPEED     0

//===========================================================================
//=========================== Filament Runout ===============================
//===========================================================================

// @section runout
// Uncomment and configure if you have a filament runout sensor wired.
//#define FILAMENT_RUNOUT_SENSOR

//===========================================================================
//============================== Fan Settings ===============================
//===========================================================================

// @section fans
#define FAN_SOFT_PWM
#define SOFT_PWM_SCALE 0
#define FAN_KICKSTART_TIME 100

//===========================================================================
//========================= Additional Features =============================
//===========================================================================

// @section extras
#define ARC_SUPPORT            // G2/G3 arc moves (required by many slicers)
#define BEZIER_CURVE_SUPPORT   // G5 spline moves
#define BABYSTEPPING           // Real-time Z offset during printing
#define BABYSTEP_MULTIPLICATOR_Z  1
#define BABYSTEP_MULTIPLICATOR_XY 1
#define DOUBLECLICK_FOR_Z_BABYSTEPPING
#define BABYSTEP_ALWAYS_AVAILABLE

#define NOZZLE_PARK_FEATURE    // G27 – park nozzle on cancel/pause
#define ADVANCED_PAUSE_FEATURE // M600 filament-change support
#define PARK_HEAD_ON_PAUSE

// @section motion
#define S_CURVE_ACCELERATION   // Smooth motion (alternative to classic jerk)

#define PRINTCOUNTER           // Track total print time / filament used
