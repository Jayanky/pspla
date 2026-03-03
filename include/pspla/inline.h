/** @file */

#ifndef PSPLA_VEC_H_
#define PSPLA_VEC_H_

#include "defines.h"
#include "types.h"
#include "vfpu.h"

#define PSPLA_VEC_QWORD_FN_WORD(name, operation, type_in, type_out) \
    static PSPLA_ALWAYS_INLINE type_out name(type_in a) {           \
        type_out qword_out;                                         \
        pspla_vfpu_lvs_(s000, 0, &a);                               \
        operation(c010, s000);                                      \
        pspla_vfpu_svq_(c010, 0, &qword_out);                       \
        return qword_out;                                           \
    }

#define PSPLA_VEC_WORD_FN_QWORD(name, operation, type_in, type_out) \
    static PSPLA_ALWAYS_INLINE type_out name(type_in a) {           \
        type_out word_out;                                          \
        pspla_vfpu_lvq_(c000, 0, &a);                               \
        operation(s010, c000);                                      \
        pspla_vfpu_svs_(s010, 0, &word_out);                        \
        return word_out;                                            \
    }

#define PSPLA_VEC_QWORD_FN_QWORD(name, operation, type_in, type_out)    \
    static PSPLA_ALWAYS_INLINE type_out name(type_in a) {               \
        type_out qword_out;                                             \
        pspla_vfpu_lvq_(c000, 0, &a);                                   \
        operation(c010, c000);                                          \
        pspla_vfpu_svq_(c010, 0, &qword_out);                           \
        return qword_out;                                               \
    }

#define PSPLA_VEC_QWORD_FN_2QWORD(name, operation, type_in, type_out)   \
    static PSPLA_ALWAYS_INLINE type_out name(type_in a, type_in b) {    \
        type_out qword_out;                                             \
        pspla_vfpu_lvq_(c000, 0, &a);                                   \
        pspla_vfpu_lvq_(c010, 0, &b);                                   \
        operation(c020, c000, c010);                                    \
        pspla_vfpu_svq_(c020, 0, &qword_out);                           \
        return qword_out;                                               \
    }

#define PSPLA_VEC_QWORD_FN_QWORD_WORD(name, operation, type_in_a, type_in_b, type_out)  \
    static PSPLA_ALWAYS_INLINE type_out name(type_in_a a, type_in_b b) {                \
        type_out qword_out;                                                             \
        pspla_vfpu_lvq_(c000, 0, &a);                                                   \
        pspla_vfpu_lvs_(s010, 0, &b);                                                   \
        operation(c020, c000, s010);                                                    \
        pspla_vfpu_svq_(c020, 0, &qword_out);                                           \
        return qword_out;                                                               \
    }

#define PSPLA_VEC_QWORD_FN_WORD_DECL(name, operation, type_in, type_out) \
    PSPLA_VEC_QWORD_FN_WORD(pspla_##type_in##_##name, pspla_vfpu_##operation##_, pspla_##type_in##_t, pspla_##type_out##_t)

#define PSPLA_VEC_WORD_FN_QWORD_DECL(name, operation, type_in, type_out) \
    PSPLA_VEC_WORD_FN_QWORD(pspla_##type_in##_##name, pspla_vfpu_##operation##_, pspla_##type_in##_t, pspla_##type_out##_t)

#define PSPLA_VEC_QWORD_FN_QWORD_DECL(name, operation, type_in, type_out) \
    PSPLA_VEC_QWORD_FN_QWORD(pspla_##type_in##_##name, pspla_vfpu_##operation##_, pspla_##type_in##_t, pspla_##type_out##_t)

#define PSPLA_VEC_QWORD_FN_2QWORD_DECL(name, operation, type_in, type_out) \
    PSPLA_VEC_QWORD_FN_2QWORD(pspla_##type_in##_##name, pspla_vfpu_##operation##_, pspla_##type_in##_t, pspla_##type_out##_t)

#define PSPLA_VEC_QWORD_FN_QWORD_WORD_DECL(name, operation, type_in_a, type_in_b, type_out) \
    PSPLA_VEC_QWORD_FN_QWORD_WORD(pspla_##type_in_a##_##name, pspla_vfpu_##operation##_, pspla_##type_in_a##_t, pspla_##type_in_b##_t, pspla_##type_out##_t)

static PSPLA_ALWAYS_INLINE pspla_f32_t pspla_m2f32_determinant(pspla_m2f32_t a) {
    pspla_f32_t word_out;
    pspla_vfpu_lvq_(c000, 0, &a);
    pspla_vfpu_vmulp_(c010, c000, c002 PSPLA_VFPU_PREFIX(y, x));
    pspla_vfpu_vsubs_(s020, s010, s011);
    pspla_vfpu_svs_(s020, 0, &word_out);
    return word_out;
}

PSPLA_VEC_QWORD_FN_2QWORD_DECL(add, vaddp, v2f32, v2f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(add, vaddt, v3f32, v3f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(add, vaddq, v4f32, v4f32)

PSPLA_VEC_QWORD_FN_2QWORD_DECL(subtract, vsubp, v2f32, v2f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(subtract, vsubt, v3f32, v3f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(subtract, vsubq, v4f32, v4f32)

PSPLA_VEC_QWORD_FN_2QWORD_DECL(multiply, vmulp, v2f32, v2f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(multiply, vmult, v3f32, v3f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(multiply, vmulq, v4f32, v4f32)

PSPLA_VEC_QWORD_FN_2QWORD_DECL(divide, vdivp, v2f32, v2f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(divide, vdivt, v3f32, v3f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(divide, vdivq, v4f32, v4f32)

PSPLA_VEC_QWORD_FN_2QWORD_DECL(minimum, vminp, v2f32, v2f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(minimum, vmint, v3f32, v3f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(minimum, vminq, v4f32, v4f32)

PSPLA_VEC_QWORD_FN_2QWORD_DECL(maximum, vmaxp, v2f32, v2f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(maximum, vmaxt, v3f32, v3f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(maximum, vmaxq, v4f32, v4f32)

PSPLA_VEC_QWORD_FN_2QWORD_DECL(compare, vcmpp, v2f32, v2f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(compare, vcmpt, v3f32, v3f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(compare, vcmpq, v4f32, v4f32)

PSPLA_VEC_QWORD_FN_2QWORD_DECL(cross, vcrspt, v3f32, v3f32)

PSPLA_VEC_QWORD_FN_2QWORD_DECL(quat_multiply, vqmulq, v4f32, v4f32)

PSPLA_VEC_QWORD_FN_QWORD_WORD_DECL(scale, vsclp, v2f32, f32, v2f32)
PSPLA_VEC_QWORD_FN_QWORD_WORD_DECL(scale, vsclt, v3f32, f32, v3f32)
PSPLA_VEC_QWORD_FN_QWORD_WORD_DECL(scale, vsclq, v4f32, f32, v4f32)

PSPLA_VEC_QWORD_FN_2QWORD_DECL(dot, vdotp, v2f32, f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(dot, vdott, v3f32, f32)
PSPLA_VEC_QWORD_FN_2QWORD_DECL(dot, vdotq, v4f32, f32)

PSPLA_VEC_QWORD_FN_WORD_DECL(tof32, vh2fs, v2f16, v2f32)
PSPLA_VEC_QWORD_FN_QWORD_DECL(tof32, vh2fp, v3f16, v3f32)
PSPLA_VEC_QWORD_FN_QWORD_DECL(tof32, vh2fp, v4f16, v4f32)

PSPLA_VEC_WORD_FN_QWORD_DECL(tof16, vf2hp, v2f32, v2f16)
PSPLA_VEC_QWORD_FN_QWORD_DECL(tof16, vf2hq, v3f32, v3f16)
PSPLA_VEC_QWORD_FN_QWORD_DECL(tof16, vf2hq, v4f32, v4f16)

#endif