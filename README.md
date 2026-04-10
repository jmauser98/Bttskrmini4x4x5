# Ender 3 – BTT SKR Mini E3 V3 – 400×400×500 – BLTouch – Dual Z – TFT35 V3

Marlin 2.1.x configuration files for a heavily modified Ender 3.

---

## Hardware

| Component       | Part                                  |
|-----------------|---------------------------------------|
| Printer frame   | Ender 3                               |
| Mainboard       | BigTreeTech SKR Mini E3 V3 (GD variant) |
| Display         | BigTreeTech TFT35 V3                  |
| Auto-leveling   | BLTouch (or CR Touch)                 |
| Z motors        | Dual Z (splitter cable or E1-port Z2) |
| Build volume    | 400 × 400 × 500 mm                    |

---

## Files

```
Marlin/
  Configuration.h       ← main configuration (board, bed, probe, axes, dual Z)
  Configuration_adv.h   ← TMC2209 UART, BLTouch advanced, TFT35, stepper currents
```

These files replace the default `Configuration.h` / `Configuration_adv.h` inside
the [Marlin firmware source tree](https://github.com/MarlinFirmware/Marlin).

---

## How to build

1. Download [Marlin 2.1.x](https://github.com/MarlinFirmware/Marlin/releases/latest).
2. Copy `Marlin/Configuration.h` and `Marlin/Configuration_adv.h` from this repo
   into the `Marlin/` folder of the Marlin source, replacing the existing files.
3. Open the project in [VSCode + Auto Build Marlin](https://marlinfw.org/docs/basics/auto_build_marlin.html).
4. Select the correct environment:
   - `STM32G0B1RE_btt` – for the standard STM32 chip
   - `STM32G0B0RE_btt` – for the **GD32** (GD) chip variant
5. Click **Build** (or `pio run -e STM32G0B0RE_btt`).
6. Copy the resulting `firmware.bin` to the root of a FAT32-formatted microSD card.
7. Insert the SD card into the SKR Mini E3 V3 and power-cycle the board.
   The firmware flashes automatically; the file is renamed to `FIRMWARE.CUR` when done.

---

## Key settings

### Bed & travel
| Setting            | Value    |
|--------------------|----------|
| `X_BED_SIZE`       | 400 mm   |
| `Y_BED_SIZE`       | 400 mm   |
| `Z_MAX_POS`        | 500 mm   |

### BLTouch / CR Touch
The probe offset is set to `{ -41.5, -7.0, 0.0 }` as a starting point for a
standard left-side mount.  **You must calibrate the Z offset** with the paper
test after flashing:
```gcode
G28         ; home all axes
G29         ; run bilinear bed leveling
M851 Z-x.xx ; set your measured Z offset
M500        ; save to EEPROM
```

### Dual Z – choose one option

**Option A – Z-splitter cable** (most common, no firmware change):
Wire both Z motors to a single Y-splitter cable connected to the Z driver port.
Leave `NUM_Z_STEPPER_DRIVERS` commented out (defaults to 1).

**Option B – Independent Z2 via E1 port** (enables G34 auto-alignment):
Wire the second Z motor to the E1 motor connector, then in `Configuration.h`
uncomment:
```cpp
#define NUM_Z_STEPPER_DRIVERS 2
```
And in `Configuration_adv.h` uncomment:
```cpp
#define Z_STEPPER_AUTO_ALIGN
```

### BTT TFT35 V3
The display is connected to the **TFT header** on the SKR Mini E3 V3 (USART2).
`SERIAL_PORT_2 2` and `BAUDRATE_2 115200` are already configured.
- **Touch Mode** (BTT color UI) works out of the box — no extra Marlin LCD option needed.
- **Marlin Mode** (128×64 emulated display): uncomment
  `REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER` in `Configuration_adv.h`.

### TMC2209 UART
Driver run currents are set in `Configuration_adv.h`:
- X / Y: 580 mA
- Z: 800 mA
- E0: 650 mA

Adjust to suit your specific motors if they run hot or lose steps.

---

## After flashing – first-time setup

```gcode
M502        ; load firmware defaults
M500        ; save to EEPROM
G28         ; home all axes
G29         ; bilinear bed leveling (5×5 grid)
M500        ; save leveling mesh
```

Then tune the Z offset and PID values:
```gcode
M303 E0 S200 C8 U1   ; autotune hotend PID at 200 °C
M303 E-1 S60 C8 U1   ; autotune bed PID at 60 °C
M500                 ; save
```
