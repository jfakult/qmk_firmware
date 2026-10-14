# Custom RGB animations (Framework Laptop 16 ANSI)

All effects live in `keyboards/framework/rgb_matrix_kb.inc` and are only compiled when
`RGB_MATRIX_JAKE_CUSTOM_EFFECTS` is defined (and `RGB_MATRIX_CUSTOM_KB = yes` in `jakef/rules.mk`).
Each effect needs an `RGB_MATRIX_EFFECT(name)` line near the top of the file. Cycle through them with the normal RGB effect keys.

## "Highlighted" keys
The `FWA_*` defines are LED indices of the keys my animations treat specially (FWA = FraMework ANSI):
F2=19, F3=18, F7=26, F8=67, K5=9, K6=14, KU=43, KH=49.
Key positions are in `keyboards/framework/ansi/ansi.c`.

## Effects
| Effect | What it does |
|---|---|
| `RAINBOW_MOVING_CHEVRON_jake` | Moving rainbow chevron (hue varies with distance from the center row and scrolls in x with time). The highlighted keys get hue +48 so they stand out. This is the angle-shifted variant of QMK's `RAINBOW_MOVING_CHEVRON`. |
| `my_cool_effect1_5` | Rotating rainbow (sin/cos based). Highlighted keys get hue +128 (opposite color). |
| `my_cool_effect` | Static grayscale gradient by x+y position; highlighted keys are magenta (255,0,255). |
| `my_cool_effect2` | Example from the QMK docs: all LEDs pink-to-purple cycling via a global counter. |
| `HUE_BREATHING1` | All LEDs breathe through a hue range (`huedelta` = 100). From a reddit r/olkb post. |
| `HUE_PENDULUM1` | Hue wave sweeping right then reversing. Same source. |
| `HUE_WAVE1` | Hue wave sweeping right. Same source. |
| `DVORAK_CLEAR_KEYCAP_HINTS` | In `jakef/animations/dvorak_clear_keycap_hints.[ch]`. Idea: for Dvorak users with clear keycaps, after inactivity pulse the keys whose legend differs (u, h, volume, brightness, 1/5/6/9); revert to a raindrops-style effect while typing. Work in progress; the `.h` has the declaration commented out and the effect is not registered in `rgb_matrix_kb.inc`. |

## Adding / tweaking
- Change the highlighted keys by editing the `FWA_*` defines and the `if (i == FWA_...)` checks (duplicated per effect).
- Change the shift by editing the `hsv.h += N` line in the effect's `_math` function.
- Build: `qmk compile -kb framework -km default -j 8` (output `framework_ansi_default.uf2`). See `readme.md` for flashing.
