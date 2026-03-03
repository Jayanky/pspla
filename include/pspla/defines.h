/** @file */

#ifndef PSPLA_DEFINES_H_
#define PSPLA_DEFINES_H_

/** @brief Alignment requirement for the `lv.q` instruction

    16-byte VFPU loads require 16-byte alignment, otherwise a hardware exception will be generated.
*/
#define PSPLA_QWORD_ALIGNMENT __attribute__((aligned(16)))

/** @brief Alignment requirement for the `lv.s` instruction

    4-byte VFPU loads require 4-byte alignment, otherwise a hardware exception will be generated.
*/
#define PSPLA_WORD_ALIGNMENT __attribute__((aligned(4)))

/** Suggest that the compiler inline a function */
#define PSPLA_INLINE inline

/** Force GCC to inline a function */
#define PSPLA_ALWAYS_INLINE inline __attribute__((always_inline))

#define PSPLA_STRINGIFY(x) #x

#define PSPLA_TOSTRING(x) PSPLA_STRINGIFY(x)

/** Type commas in macro arguments */
#define PSPLA_COMMA ,

#endif