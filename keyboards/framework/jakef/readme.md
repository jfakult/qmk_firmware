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