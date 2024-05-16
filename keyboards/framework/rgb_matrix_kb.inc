// List all animations you would like included here

// #include "jakef/animations/dvorak_clear_keycap_hints.h"

// #include "quantum/rgb_matrix/rgb_matrix.h"

//#include <stdbool.h>
// #include "quantum.h"
// #include "rgb_matrix.h"
#include "quantum/rgb_matrix/rgb_matrix.h"

RGB_MATRIX_EFFECT(DVORAK_CLEAR_KEYCAP_HINTS)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#include "jakef/animations/dvorak_clear_keycap_hints.c"
#endif