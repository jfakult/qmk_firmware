Copyright <year> <name> <email> @<github_username>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


# Jake's customizations (summary)

Fork of FrameworkComputer/qmk_firmware (Framework Laptop 16 keyboard). Branches:
- `jakes_animations`: original custom branch (based on fl16 v0.2.9).
- `jakes_animations_2026`: same + merge of `fw/fl16-2026-f9` (Framework v0.3.1, Feb 2026). Current.

Remotes: `origin` = jfakult/qmk_firmware, `fw` = FrameworkComputer/qmk_firmware (to update: `git fetch fw && git merge fw/<branch>`).

Changed files / folders:
- `keyboards/framework/rgb_matrix_kb.inc`: custom RGB effects. `RAINBOW_MOVING_CHEVRON_jake` is the chevron rainbow
  that shifts hue by +48 on the keys FWA_F2, F3, F7, F8, K5, K6, KU, KH (the dvorak/home-row hint keys).
  `my_cool_effect*` are older experiments. New effects need an `RGB_MATRIX_EFFECT(name)` line at the top.
- `keyboards/framework/jakef/animations.md`: per-effect documentation of all custom animations.
- `keyboards/framework/jakef/`: my keymap-independent config (`config.h`, `rules.mk` enabling `RGB_MATRIX_CUSTOM_KB`),
  `animations/dvorak_clear_keycap_hints.[ch]`, and this readme.
- `keyboards/framework/ansi/keymaps/default/keymap.c`: trivial comment change.
- `lib/python/qmk/math.py`: `ast.Num` -> `ast.Constant` so the old QMK CLI lib runs on Python 3.12+ (was failing on 3.14).
- `util/uf2conv.py`: raw-string regex fix.
- Other keyboards under `keyboards/` were deleted on this branch to keep it small.

# To clean up all other keyboard files

```
cd keyboards
ls . | grep -v framework | xargs rm -rf
```

# Enable custom animations: config.h and jakef/rules.mk
# Custom animation location: rgb_matrix_kb.inc


# To Build:
No need to include the .inc file from anywhere.
If RGB_MATRIX_CUSTOM_KB = yes (rules.mk) it will be imported from quantum/rgb_matrix/rgb_matrix.c

Build the firmware

`qmk compile -kb framework -km default -j 8`

On Framework Laptop 16 Keyboard: Hold down left ALT and right ALT while installing the module.

Make sure the thing is mounted
`lsblk`

`udiskie`

Pull a backup (needs external keyboard, or just send it with the flash):

`picotool save backup_firmware.bin --all`

Optional:

`python util/uf2conv.py -c backup_firmware.bin -o backup_firmware.uf2`

Finally:

`qmk flash --dry-run .build/framework_ansi_default.uf2`