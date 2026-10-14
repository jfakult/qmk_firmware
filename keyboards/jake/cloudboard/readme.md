# cloudboard

Custom split keyboard (RP2040, 4 rows x 7 cols per half, 56 matrix positions) in `keyboards/jake/cloudboard`.
This folder is untracked in the qmk_firmware git checkout (not committed anywhere).

## Files
- `keyboard.json`: RP2040 / `rp2040` bootloader, matrix pins (rows GP2 GP3 GP4 GP26, cols GP5 GP6 GP7 GP8 GP27 GP28 GP29),
  COL2ROW diodes, WS2812 on GP9, 8 RGB LEDs, and the `LAYOUT` (56 keys).
- `gen_layout.py`: prints the `LAYOUT` JSON (left half rows 0-3, right half rows 4-7 shifted 8 units right). Paste into `keyboard.json`.
- `config.h`: RGBW strip, RGB brightness limit 180, `MASTER_LEFT`, soft-serial on GP0, RP2040 double-tap reset (250 ms).
- `rules.mk`: split keyboard, `RGBLIGHT_ENABLE`, LTO, vendor serial driver.
- `cloudboard.c`: empty placeholder.
- `keymaps/default/keymap.c`: a single QWERTY-ish base layer. `housekeeping_task_user` runs a rotating rainbow across the 8 LEDs
  (rgblight set to static mode so built-in effects don't fight it).

## Build
`qmk compile -kb jake/cloudboard -km default`

Output: `jake_cloudboard_default.uf2` (hold BOOTSEL or double-tap reset to enter the bootloader, then copy the file over).
