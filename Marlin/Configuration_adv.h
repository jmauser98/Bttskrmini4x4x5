/**
 * Marlin Firmware – Configuration_adv.h
 *
 * Hardware:
 *   Printer  : Ender 3 (frame / kinematics)
 *   Board    : BigTreeTech SKR Mini E3 V3 (GD32 / STM32G0 variant)
 *   Display  : BigTreeTech TFT35 V3
 *   Probe    : BLTouch (or CR Touch)
 *   Dual Z   : Two Z motors (Z-splitter or independent – see Configuration.h)
 *   Bed size : 400 x 400 mm
 *   Z travel : 500 mm
 *
 * Based on Marlin 2.1.x
 */
#pragma once

#define CONFIGURATION_ADV_H_VERSION 02010300

//===========================================================================
//============================= Thermal Settings ============================
//===========================================================================

// @section temperature

// Thermal runaway protection thresholds.
#define THERMAL_PROTECTION_PERIOD        40    // Seconds
#define THERMAL_PROTECTION_HYSTERESIS     4    // Degrees Celsius
#define WATCH_TEMP_PERIOD                20    // Seconds
#define WATCH_TEMP_INCREASE               2    // Degrees Celsius

#define THERMAL_PROTECTION_BED_PERIOD    20
#define THERMAL_PROTECTION_BED_HYSTERESIS 2
#define WATCH_BED_TEMP_PERIOD            60
#define WATCH_BED_TEMP_INCREASE           2

//===========================================================================
//=============================== Stepper Motor =============================
//===========================================================================

// @section stepper drivers

/**
 * BTT SKR Mini E3 V3 uses TMC2209 drivers on X, Y, Z, E0.
 * UART mode enables sensorless homing, stealthChop, and run-current control.
 */
#define X_DRIVER_TYPE  TMC2209
#define Y_DRIVER_TYPE  TMC2209
#define Z_DRIVER_TYPE  TMC2209
#define E0_DRIVER_TYPE TMC2209

// @section tmc/config

/**
 * TMC2209 run currents (mA RMS).
 * Typical Ender 3 motors: ~580 mA for X/Y, ~800 mA for Z.
 * Lower current = cooler, quieter but less torque.  Adjust as needed.
 */
#define X_CURRENT       580
#define X_CURRENT_HOME  X_CURRENT
#define X_MICROSTEPS     16

#define Y_CURRENT       580
#define Y_CURRENT_HOME  Y_CURRENT
#define Y_MICROSTEPS     16

#define Z_CURRENT       800
#define Z_CURRENT_HOME  Z_CURRENT
#define Z_MICROSTEPS     16

#define E0_CURRENT      650
#define E0_MICROSTEPS    16

/**
 * Z2 settings – only used when NUM_Z_STEPPER_DRIVERS is set to 2 (Option B).
 * Match Z2 current and microsteps to Z1 for consistent behavior.
 */
#define Z2_CURRENT       800
#define Z2_CURRENT_HOME  Z2_CURRENT
#define Z2_MICROSTEPS    16

// StealthChop (quiet mode) – disable on axes that need higher speed/torque.
#define STEALTHCHOP_XY
#define STEALTHCHOP_Z
#define STEALTHCHOP_E

// Hybrid threshold: switch from StealthChop to SpreadCycle above this speed.
#define HYBRID_THRESHOLD
#define X_HYBRID_THRESHOLD     100
#define Y_HYBRID_THRESHOLD     100
#define Z_HYBRID_THRESHOLD       3
#define E0_HYBRID_THRESHOLD     30

// TMC UART addresses (must match jumper/solder-bridge settings on the board).
#define X_SLAVE_ADDRESS  0
#define Y_SLAVE_ADDRESS  2
#define Z_SLAVE_ADDRESS  1
#define E0_SLAVE_ADDRESS 3

//===========================================================================
//========================= BLTouch / Probe Advanced ========================
//===========================================================================

// @section bltouch

/**
 * BLTouch high-speed mode (HS mode).
 * Speeds up probing but may reduce repeatability on some probe hardware.
 * Enable only if your probe is reliable in HS mode.
 */
//#define BLTOUCH_HS_MODE true

/**
 * Delay after deploying/stowing the probe (ms).
 * Increase if the probe is unreliable (false triggers or no triggers).
 */
#define BLTOUCH_DELAY 500

//===========================================================================
//========================= Z Stepper Auto Align ============================
//===========================================================================

// @section motion

/**
 * G34 – Z Stepper Auto Alignment.
 * Only meaningful when NUM_Z_STEPPER_DRIVERS is set to 2 in Configuration.h
 * (independent dual Z drivers via E1 port).
 * Uncomment to enable auto-align when using Option B dual Z.
 */
//#define Z_STEPPER_AUTO_ALIGN

#ifdef Z_STEPPER_AUTO_ALIGN
  #define Z_STEPPER_ALIGN_ITERATIONS   5
  #define Z_STEPPER_ALIGN_ACC          0.02
  #define RESTORE_LEVELING_AFTER_G34
#endif

//===========================================================================
//========================== Input Shaping (MRR) ============================
//===========================================================================

// @section input shaping
// Uncomment and tune if you notice resonance / ringing artefacts.
//#define INPUT_SHAPING_X
//#define INPUT_SHAPING_Y

//===========================================================================
//========================= Advanced Pause / M600 ===========================
//===========================================================================

// @section advanced pause
#define ADVANCED_PAUSE_PURGE_LENGTH   30    // (mm) purge length on resume
#define FILAMENT_CHANGE_FAST_LOAD_LENGTH 60 // (mm)
#define PAUSE_PARK_RETRACT_LENGTH      2    // (mm) retract at pause
#define FILAMENT_CHANGE_SLOW_LOAD_LENGTH 5  // (mm)

//===========================================================================
//============================== BTT TFT35 V3 ===============================
//===========================================================================

// @section lcd

/**
 * BTT TFT35 V3 – Unified Marlin Serial Display.
 *
 * The TFT35 V3 communicates with the board through the TFT UART header
 * (SERIAL_PORT_2, set to port 2 in Configuration.h, BAUDRATE_2 115200).
 *
 * The display firmware supports two UI modes selectable from its menu:
 *
 *   1. Touch Mode  – native BTT TFT UI (color touch interface).  No extra
 *      Marlin LCD option is needed; Marlin only needs SERIAL_PORT_2 open.
 *
 *   2. Marlin Mode – emulated 128×64 character display using the UART
 *      bridge.  Enable REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER below
 *      for a Marlin-hosted graphical UI through the TFT serial bridge.
 */
// #define REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER  // Marlin emulated LCD mode

/**
 * TFT touch calibration persistence.
 * Keep the touch calibration values across reboots via EEPROM.
 */
#define TOUCH_CALIBRATION_AUTO_SAVE

//===========================================================================
//============================= Fan / Cooling ===============================
//===========================================================================

// @section fans

// Part-cooling fan minimum PWM.  Values 0-255; 0 = fan off below minimum.
#define FAN_MIN_PWM  35

// Cooldown period after print completes (seconds).
#define TEMP_IDLE_PERIOD  120

//===========================================================================
//============================= Print Counter ===============================
//===========================================================================

// @section stats
// Already enabled in Configuration.h via PRINTCOUNTER.
// Stats are saved to EEPROM automatically.

//===========================================================================
//=========================== G-code Parser =================================
//===========================================================================

// @section gcode
#define GCODE_CASE_INSENSITIVE  // Accept lowercase G-code commands
#define FASTER_GCODE_PARSER

//===========================================================================
//======================== Filament Width Sensor ============================
//===========================================================================

// @section extras
// Uncomment to enable if you have a filament width sensor.
//#define FILAMENT_WIDTH_SENSOR

//===========================================================================
//===================== Unified Bed Leveling (UBL) ==========================
//===========================================================================

// @section leveling
// UBL is an alternative to bilinear leveling – more powerful but more
// complex to set up.  To use UBL, disable AUTO_BED_LEVELING_BILINEAR in
// Configuration.h and enable the block below.
//
// #define AUTO_BED_LEVELING_UBL
// #define MESH_BED_LEVELING
