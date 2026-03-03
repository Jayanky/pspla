/** @file */

#ifndef PSPLA_TYPES_H_
#define PSPLA_TYPES_H_

#include "defines.h"

#include <stdint.h>

/** Regular precision float type */
typedef float pspla_f32_t;

/** Half precision float type

    @note This type should only be accessed through VFPU operations, as the FPU isn't able to work with half-precision floats.
*/
typedef uint16_t pspla_f16_t;

/** 16-byte aligned 2D vector of 32-bit floats */
typedef struct pspla_v2f32_t {
    union {
        struct {
            pspla_f32_t x; /**< Vector x-component */
            pspla_f32_t y; /**< Vector y-component */
        };

        pspla_f32_t e[2] /**< 2D vector component array */;
    };
} PSPLA_QWORD_ALIGNMENT pspla_v2f32_t;

/** 16-byte aligned 3D vector of 32-bit floats */
typedef struct pspla_v3f32_t {
    union {
        struct {
            pspla_f32_t x; /**< Vector x-component */
            pspla_f32_t y; /**< Vector y-component */
            pspla_f32_t z; /**< Vector z-component */
        };

        pspla_f32_t e[3]; /**< 3D vector component array */
    };
} PSPLA_QWORD_ALIGNMENT pspla_v3f32_t;

/** 16-byte aligned 4D vector of 32-bit floats */
typedef struct pspla_v4f32_t {
    union {
        struct {
            pspla_f32_t x; /**< Vector x-component */
            pspla_f32_t y; /**< Vector y-component */
            pspla_f32_t z; /**< Vector z-component */
            pspla_f32_t w; /**< Vector w-component */
        };

        pspla_f32_t e[4]; /**< 4D vector component array */
    };
} PSPLA_QWORD_ALIGNMENT pspla_v4f32_t;

/** 16-byte aligned column-major 2x2 matrix of 32-bit floats */
typedef struct pspla_m2f32_t {
    union {
        struct {
            pspla_v2f32_t a; /**< Matrix a-vector */
            pspla_v2f32_t b; /**< Matrix b-vector */
        };

        pspla_v2f32_t v[2]; /**< 2x2 matrix vector array */
    };
} PSPLA_QWORD_ALIGNMENT pspla_m2f32_t;

/** 16-byte aligned column-major 3x3 matrix of 32-bit floats */
typedef struct pspla_m3f32_t {
    union {
        struct {
            pspla_v3f32_t a; /**< Matrix a-vector */
            pspla_v3f32_t b; /**< Matrix b-vector */
            pspla_v3f32_t c; /**< Matrix c-vector */
        };

        pspla_v3f32_t v[3]; /**< 3x3 matrix vector array */
    };
} PSPLA_QWORD_ALIGNMENT pspla_m3f32_t;

/** 16-byte aligned column-major 4x4 matrix of 32-bit floats */
typedef struct pspla_m4f32_t {
    union {
        struct {
            pspla_v4f32_t a; /**< Matrix a-vector */
            pspla_v4f32_t b; /**< Matrix b-vector */
            pspla_v4f32_t c; /**< Matrix c-vector */
            pspla_v4f32_t d; /**< Matrix d-vector */
        };

        pspla_v4f32_t v[4]; /**< 4x4 matrix vector array */
    };
} PSPLA_QWORD_ALIGNMENT pspla_m4f32_t;

/** 4-byte aligned 2D vector of 16-bit floats */
typedef struct pspla_v2f16_t {
    union {
        struct {
            pspla_f16_t x; /**< First vector component */
            pspla_f16_t y; /**< Second vector component */
        };

        pspla_f16_t e[2]; /**< 2D vector component array */
    };
} PSPLA_WORD_ALIGNMENT pspla_v2f16_t;

/** 16-byte aligned 3D vector of 16-bit floats */
typedef struct pspla_v3f16_t {
    union {
        struct {
            pspla_f16_t x; /**< First vector component */
            pspla_f16_t y; /**< Second vector component */
            pspla_f16_t z; /**< Third vector component */
        };

        pspla_f16_t e[3]; /**< 3D vector component array */
    };
} PSPLA_QWORD_ALIGNMENT pspla_v3f16_t;

/** 16-byte aligned 4D vector of 16-bit floats */
typedef struct pspla_v4f16_t {
    union {
        struct {
            pspla_f16_t x; /**< First vector component */
            pspla_f16_t y; /**< Second vector component */
            pspla_f16_t z; /**< Third vector component */
            pspla_f16_t w; /**< Fourth vector component */
        };

        pspla_f16_t e[4]; /**< 3D vector component array */
    };
} PSPLA_QWORD_ALIGNMENT pspla_v4f16_t;

/** 16-byte aligned triple-2D vector of 16-bit floats */
typedef struct pspla_3v2f16_t {
    union {
        struct {
            pspla_v2f16_t a; /**< First 2D vector */
            pspla_v2f16_t b; /**< Second 2D vector */
            pspla_v2f16_t c; /**< Third 2D vector */
        };

        pspla_v2f16_t v[3]; /**< Array of 2D vector components */
        pspla_f16_t e[6]; /**< Array of 16-bit float components */
    };
} PSPLA_QWORD_ALIGNMENT pspla_3v2f16_t;

/** 16-byte aligned quadruple-2D vector of 16-bit floats */
typedef struct pspla_4v2f16_t {
    union {
        struct {
            pspla_v2f16_t a; /**< First 2D vector */
            pspla_v2f16_t b; /**< Second 2D vector */
            pspla_v2f16_t c; /**< Third 2D vector */
            pspla_v2f16_t d; /**< Fourth 2D vector */
        };

        pspla_v2f16_t v[4]; /**< Array of 2D vector components */
        pspla_f16_t e[8]; /**< Array of 16-bit float components */
    };
} PSPLA_QWORD_ALIGNMENT pspla_4v2f16_t;

#endif