/** @file 
    @brief Low-level VFPU instruction macros.

    Because the PSPSDK toolchain lacks support for VFPU intrinsics, it is necessary to use either inline or out-of-line assembly to access
    its instruction set. The macros in this file are designed to hide clutter and improve readability and ease of use while writing VFPU
    code within C functions.

    Unfortunately GCC does not support assigning variables to VFPU registers, so these are a little bare compared to traditional macros.
    Luckily InputOperands for GPRs still works for load and store instructions, so pointers can be passed in directly.
*/

#ifndef PSPLA_VFPU_H_
#define PSPLA_VFPU_H_

#include "defines.h"

/** @defgroup vfpu VFPU
    Macros for inserting vector instructions into C functions
    @{
*/

/** @brief Assembly macro for VFPU loads and stores

    @param instruction The operation being used with this format
    @param rx Either the source or destination VFPU register
    @param offset The offset from the address in `ptr`
    @param ptr The address of the load or store
*/
#define pspla_vfpu_asm_memory_(instruction, rx, offset, ptr) __asm__ inline  volatile (#instruction " " #rx ", " #offset "(%0)" :: "r" (ptr))

/** @brief Assembly macro for any VFPU register operation

    @param instruction The operation being used with this format
    @param __VA_ARGS__ The VFPU registers being used with the operation
*/
#define pspla_vfpu_asm_register_(instruction, ...) __asm__ inline volatile (#instruction " " #__VA_ARGS__)

#define PSPLA_VFPU_PREFIX(...) [__VA_ARGS__]

// vmov.p c020, c010[y,x]

/** @brief Branch on a VFPU register being false

    @param imm3 VFPU CC register bit
    @param offset The offset of the destination from the current location
*/
#define pspla_vfpu_bvf_(imm3, offset) pspla_vfpu_asm_register_(bvf, imm3, offset)

/** @brief Branch on a VFPU register being likely false

    @param imm3 VFPU CC register bit
    @param offset The offset of the destination from the current location
*/
#define pspla_vfpu_bvfl_(imm3, offset) pspla_vfpu_asm_register_(bvfl, imm3, offset)

/** @brief Branch on a VFPU register being true

    @param imm3 VFPU CC register bit
    @param offset The offset of the destination from the current location
*/
#define pspla_vfpu_bvt_(imm3, offset) pspla_vfpu_asm_register_(bvf, imm3, offset)

/** @brief Branch on a VFPU register being likely true

    @param imm3 VFPU CC register bit
    @param offset The offset of the destination from the current location
*/
#define pspla_vfpu_bvtl_(imm3, offset) pspla_vfpu_asm_register_(bvfl, imm3, offset)

/** @brief Copy GPR to VFPU control register

    @note `cc_reg` is given as the absolute index of the control register, not it's name
    | value | register    |
    | ----: | :---------- |
    | 128   | VFPU_PFXS   |
    | 129   | VFPU_PFXT   |
    | 130   | VFPU_PFXD   |
    | 131   | VFPU_CC     |

    @param rt The GPR to copy
    @param cc_reg The destination control register
*/
#define pspla_vfpu_mtvc_(rt, cc_reg) pspla_vfpu_asm_register_(mtvc, rt, cc_reg)

/** @brief Copy VFPU control register to GPR

    @note `cc_reg` is given as the absolute index of the control register, not it's name
    | value | register    |
    | ----: | :---------- |
    | 128   | VFPU_PFXS   |
    | 129   | VFPU_PFXT   |
    | 130   | VFPU_PFXD   |
    | 131   | VFPU_CC     |

    @param rt The destination GPR
    @param cc_reg The control register to copy
*/
#define pspla_vfpu_mfvc_(rt, cc_reg) pspla_vfpu_asm_register_(mfvc, rt, cc_reg)

/** @brief Copy VFPU register to VFPU control register

    @note `cc_reg` is given as the absolute index of the control register, not it's name
    | value | register    |
    | ----: | :---------- |
    | 128   | VFPU_PFXS   |
    | 129   | VFPU_PFXT   |
    | 130   | VFPU_PFXD   |
    | 131   | VFPU_CC     |

    @param rt The VFPU register to copy
    @param cc_reg The destination control register
*/
#define pspla_vfpu_vmtvc_(cc_reg, rs) pspla_vfpu_asm_register_(vmtvc, cc_reg, rs)

/** @brief Copy VFPU control register to VFPU register

    @note `cc_reg` is given as the absolute index of the control register, not it's name
    | value | register    |
    | ----: | :---------- |
    | 128   | VFPU_PFXS   |
    | 129   | VFPU_PFXT   |
    | 130   | VFPU_PFXD   |
    | 131   | VFPU_CC     |

    @param rt The destination VFPU register
    @param cc_reg The control register to copy
*/
#define pspla_vfpu_vmfvc_(cc_reg, rs) pspla_vfpu_asm_register_(vmfvc, cc_reg, rs)

/** @brief Loads a scalar from memory into a VFPU register

    @param rd The destination VFPU register
    @param offset Number of bytes to offset from `ptr`
    @param ptr Pointer to 4-byte aligned scalar
*/
#define pspla_vfpu_lvs_(rd, offset, ptr) pspla_vfpu_asm_memory_(lv.s, rd, offset, ptr)

/** @brief Loads a 16-byte aligned vector from memory into a set of VFPU registers 

    @param rd The destination VFPU register
    @param offset Number of bytes to offset from `ptr`
    @param ptr Pointer to 16-byte aligned vector
*/
#define pspla_vfpu_lvq_(rd, offset, ptr) pspla_vfpu_asm_memory_(lv.q, rd, offset, ptr)

/** @brief Loads from the most significant 4-byte element down to the nearest 16-byte boundary into a set of VFPU registers

    @warning Instruction clobbers FPU registers on PSP-1000 models

    @param rd The destination VFPU register
    @param offset Number of bytes to offset from `ptr`
    @param ptr Pointer to vector
*/
#define pspla_vfpu_lvlq_(rd, offset, ptr) pspla_vfpu_asm_memory_(lvl.q, rd, offset, ptr)

/** @brief Loads from the least significant 4-byte element up to the nearest 16-byte boundary into a set of VFPU registers

    @warning Instruction clobbers FPU registers on PSP-1000 models

    @param rd The destination VFPU register
    @param offset Number of bytes to offset from `ptr`
    @param ptr Pointer to vector
*/
#define pspla_vfpu_lvrq_(rd, offset, ptr) pspla_vfpu_asm_memory_(lvr.q, rd, offset, ptr)

/** @brief Loads a 4-byte aligned vector from memory into a set of VFPU registers

    @warning Instruction clobbers FPU registers on PSP-1000 models

    @param rd The destination VFPU register
    @param offset Number of bytes to offset from `ptr`
    @param ptr Pointer to vector
*/
#define pspla_vfpu_ulvq_(rd, offset, ptr) pspla_vfpu_asm_memory_(ulv.q, rd, offset, ptr)

/** @brief Stores a scalar from a VFPU register into memory

    @param rs The source VFPU register
    @param offset Number of bytes to offset from `ptr`
    @param ptr Address scalar will be stored to
*/
#define pspla_vfpu_svs_(rs, offset, ptr) pspla_vfpu_asm_memory_(sv.s, rs, offset, ptr)

/** @brief Stores a vector from a VFPU register into a 16-byte aligned memory address

    @param rs The source VFPU register
    @param offset Number of bytes to offset from `ptr`
    @param ptr Address vector will be stored to
*/
#define pspla_vfpu_svq_(rs, offset, ptr) pspla_vfpu_asm_memory_(sv.q, rs, offset, ptr)

/** @brief Stores to the most significant 4-byte element down to the nearest 16-byte boundary from a set of VFPU registers

    @param rs The source VFPU register
    @param offset Number of bytes to offset from `ptr`
    @param ptr Pointer to vector
*/
#define pspla_vfpu_svlq_(rs, offset, ptr) pspla_vfpu_asm_memory_(svl.q, rs, offset, ptr)

/** @brief Stores to the least significant 4-byte element up to the nearest 16-byte boundary from a set of VFPU registers

    @param rs The source VFPU register
    @param offset Number of bytes to offset from `ptr`
    @param ptr Pointer to vector
*/
#define pspla_vfpu_svrq_(rs, offset, ptr) pspla_vfpu_asm_memory_(svr.q, rs, offset, ptr)

/** @brief Stores a 4-byte aligned vector from a set of VFPU registers into memory

    @param rd The source VFPU register
    @param offset Number of bytes to offset from `ptr`
    @param ptr Pointer to vector
*/
#define pspla_vfpu_usvq_(rs, offset, ptr) pspla_vfpu_asm_memory_(usv.q, rs, offset, ptr)

/** @brief Addition of a scalar to a scalar

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vadds_(rd, rs, rt) pspla_vfpu_asm_register_(vadd.s, rd, rs, rt)

/** @brief Element-wise addition of a 2D vector to a 2D vector

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vaddp_(rd, rs, rt) pspla_vfpu_asm_register_(vadd.p, rd, rs, rt)

/** @brief Element-wise addition of a 3D vector to a 3D vector

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vaddt_(rd, rs, rt) pspla_vfpu_asm_register_(vadd.t, rd, rs, rt)

/** @brief Element-wise addition of a 4D vector to a 4D vector

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vaddq_(rd, rs, rt) pspla_vfpu_asm_register_(vadd.q, rd, rs, rt)

/** @brief Subtraction of a scalar from a scalar

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vsubs_(rd, rs, rt) pspla_vfpu_asm_register_(vsub.s, rd, rs, rt)

/** @brief Element-wise subtraction of a 2D vector from a 2D vector

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vsubp_(rd, rs, rt) pspla_vfpu_asm_register_(vsub.p, rd, rs, rt)

/** @brief Element-wise subtraction of a 3D vector from a 3D vector

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vsubt_(rd, rs, rt) pspla_vfpu_asm_register_(vsub.t, rd, rs, rt)

/** @brief Element-wise subtraction of a 4D vector from a 4D vector

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vsubq_(rd, rs, rt) pspla_vfpu_asm_register_(vsub.q, rd, rs, rt)

/** @brief Multiplication of a scalar to a scalar

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vmuls_(rd, rs, rt) pspla_vfpu_asm_register_(vmul.s, rd, rs, rt)

/** @brief Element-wise multiplication of a 2D vector to a 2D vector

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vmulp_(rd, rs, rt) pspla_vfpu_asm_register_(vmul.p, rd, rs, rt)

/** @brief Element-wise multiplication of a 3D vector to a 3D vector

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vmult_(rd, rs, rt) pspla_vfpu_asm_register_(vmul.t, rd, rs, rt)

/** @brief Element-wise multiplication of a 4D vector to a 4D vector

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vmulq_(rd, rs, rt) pspla_vfpu_asm_register_(vmul.q, rd, rs, rt)

/** @brief Division of a scalar by a scalar

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vdivs_(rd, rs, rt) pspla_vfpu_asm_register_(vdiv.s, rd, rs, rt)

/** @brief Element-wise division of a 2D vector by a 2D vector

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vdivp_(rd, rs, rt) pspla_vfpu_asm_register_(vdiv.p, rd, rs, rt)

/** @brief Element-wise division of a 3D vector by a 3D vector

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vdivt_(rd, rs, rt) pspla_vfpu_asm_register_(vdiv.t, rd, rs, rt)

/** @brief Element-wise division of a 4D vector by a 4D vector

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vdivq_(rd, rs, rt) pspla_vfpu_asm_register_(vdiv.q, rd, rs, rt)

/** @brief Minimum of two scalars

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vmins_(rd, rs, rt) pspla_vfpu_asm_register_(vmin.s, rd, rs, rt)

/** @brief Element-wise minimum of two 2D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vminp_(rd, rs, rt) pspla_vfpu_asm_register_(vmin.p, rd, rs, rt)

/** @brief Element-wise minimum of two 3D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vmint_(rd, rs, rt) pspla_vfpu_asm_register_(vmin.t, rd, rs, rt)

/** @brief Element-wise minimum of two 4D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vminq_(rd, rs, rt) pspla_vfpu_asm_register_(vmin.q, rd, rs, rt)

/** @brief Maximum of two scalars

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vmaxs_(rd, rs, rt) pspla_vfpu_asm_register_(vmax.s, rd, rs, rt)

/** @brief Element-wise maximum of two 2D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vmaxp_(rd, rs, rt) pspla_vfpu_asm_register_(vmax.p, rd, rs, rt)

/** @brief Element-wise maximum of two 3D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vmaxt_(rd, rs, rt) pspla_vfpu_asm_register_(vmax.t, rd, rs, rt)

/** @brief Element-wise maximum of two 4D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vmaxq_(rd, rs, rt) pspla_vfpu_asm_register_(vmax.q, rd, rs, rt)

/** @brief Comparison of two scalars

    `rd` is 1.0 if `rs` > `rt`, 0.0 if `rs` == `rt`, and -1.0 if `rs` < `rt`.

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vscmps_(rd, rs, rt) pspla_vfpu_asm_register_(vscmp.s, rd, rs, rt)

/** @brief Comparison of 2D vectors

    `rd[i]` is 1.0 if `rs[i]` > `rt[i]`, 0.0 if `rs[i]` == `rt[i]`, and -1.0 if `rs[i]` < `rt[i]`.

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vscmpp_(rd, rs, rt) pspla_vfpu_asm_register_(vscmp.p, rd, rs, rt)

/** @brief Comparison of 3D vectors

    `rd[i]` is 1.0 if `rs[i]` > `rt[i]`, 0.0 if `rs[i]` == `rt[i]`, and -1.0 if `rs[i]` < `rt[i]`.

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vscmpt_(rd, rs, rt) pspla_vfpu_asm_register_(vscmp.t, rd, rs, rt)

/** @brief Comparison of 4D vectors

    `rd[i]` is 1.0 if `rs[i]` > `rt[i]`, 0.0 if `rs[i]` == `rt[i]`, and -1.0 if `rs[i]` < `rt[i]`.

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vscmpq_(rd, rs, rt) pspla_vfpu_asm_register_(vscmp.q, rd, rs, rt)

/** @brief `>=` comparison of two scalars

    `rd` is 1.0 if `rs` >= `rt`, and 0.0 otherwise.

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vsges_(rd, rs, rt) pspla_vfpu_asm_register_(vsge.s, rd, rs, rt)

/** @brief `>=` comparison of two 2D vectors

    `rd[i]` is 1.0 if `rs[i]` >= `rt[i]`, and 0.0 otherwise.

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vsgep_(rd, rs, rt) pspla_vfpu_asm_register_(vsge.p, rd, rs, rt)

/** @brief `>=` comparison of two 3D vectors

    `rd[i]` is 1.0 if `rs[i]` >= `rt[i]`, and 0.0 otherwise.

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vsget_(rd, rs, rt) pspla_vfpu_asm_register_(vsge.t, rd, rs, rt)

/** @brief `>=` comparison of two 4D vectors

    `rd[i]` is 1.0 if `rs[i]` >= `rt[i]`, and 0.0 otherwise.

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vsgeq_(rd, rs, rt) pspla_vfpu_asm_register_(vsge.q, rd, rs, rt)

/** @brief `<` comparison of two scalars

    `rd` is 1.0 if `rs` < `rt`, and 0.0 otherwise.

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vslts_(rd, rs, rt) pspla_vfpu_asm_register_(vslt.s, rd, rs, rt)

/** @brief `<` comparison of two 2D vectors

    `rd[i]` is 1.0 if `rs[i]` < `rt[i]`, and 0.0 otherwise.

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vsltp_(rd, rs, rt) pspla_vfpu_asm_register_(vslt.p, rd, rs, rt)

/** @brief `<` comparison of two 3D vectors

    `rd[i]` is 1.0 if `rs[i]` < `rt[i]`, and 0.0 otherwise.

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vsltt_(rd, rs, rt) pspla_vfpu_asm_register_(vslt.t, rd, rs, rt)

/** @brief `<` comparison of two 4D vectors

    `rd[i]` is 1.0 if `rs[i]` < `rt[i]`, and 0.0 otherwise.

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vsltq_(rd, rs, rt) pspla_vfpu_asm_register_(vslt.q, rd, rs, rt)

/** @brief Partial cross-product of two 3D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vcrst_(rd, rs, rt) pspla_vfpu_asm_register_(vcrs.t, rd, rs, rt)

/** @brief Cross-product of two 3D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vcrspt_(rd, rs, rt) pspla_vfpu_asm_register_(vcrsp.t, rd, rs, rt)

/** @brief Quaternion multiplication between two 4D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vqmulq_(rd, rs, rt) pspla_vfpu_asm_register_(vqmul.q, rd, rs, rt)

/** @brief Replace the exponent of a scalar

    @param rd The destination VFPU register
    @param rs The scalar value to adjust
    @param rt The integer exponent to use
*/
#define pspla_vfpu_vsbns_(rd, rs, rt) pspla_vfpu_asm_register_(vsbn.s, rd, rs, rt)

/** @brief Scale a 2D vector by a scalar value

    @param rd The destination VFPU register
    @param rs The vector to scale
    @param rt The scalar used to scale `rs`
*/
#define pspla_vfpu_vsclp_(rd, rs, rt) pspla_vfpu_asm_register_(vscl.p, rd, rs, rt)

/** @brief Scale a 3D vector by a scalar value

    @param rd The destination VFPU register
    @param rs The vector to scale
    @param rt The scalar used to scale `rs`
*/
#define pspla_vfpu_vsclt_(rd, rs, rt) pspla_vfpu_asm_register_(vscl.t, rd, rs, rt)

/** @brief Scale a 4D vector by a scalar value

    @param rd The destination VFPU register
    @param rs The vector to scale
    @param rt The scalar used to scale `rs`
*/
#define pspla_vfpu_vsclq_(rd, rs, rt) pspla_vfpu_asm_register_(vscl.q, rd, rs, rt)

/** @brief Dot-product of two 2D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vdotp_(rd, rs, rt) pspla_vfpu_asm_register_(vdot.p, rd, rs, rt)

/** @brief Dot-product of two 3D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vdott_(rd, rs, rt) pspla_vfpu_asm_register_(vdot.t, rd, rs, rt)

/** @brief Dot-product of two 4D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vdotq_(rd, rs, rt) pspla_vfpu_asm_register_(vdot.q, rd, rs, rt)

/** @brief 2x2 matrix determinant between two rows

    @param rd The destination VFPU register
    @param rs First row of matrix
    @param rt Second row of matrix
*/
#define pspla_vfpu_vdetp_(rd, rs, rt) pspla_vfpu_asm_register_(vdet.p, rd, rs, rt)

/** @brief Homogenous dot-product of two 2D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vhdpp_(rd, rs, rt) pspla_vfpu_asm_register_(vhdp.p, rd, rs, rt)

/** @brief Homogenous dot-product of two 3D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vhdpt_(rd, rs, rt) pspla_vfpu_asm_register_(vhdp.t, rd, rs, rt)

/** @brief Homogenous dot-product of two 4D vectors

    @param rd The destination VFPU register
    @param rs Source VFPU register 1
    @param rt Source VFPU register 2
*/
#define pspla_vfpu_vhdpq_(rd, rs, rt) pspla_vfpu_asm_register_(vhdp.q, rd, rs, rt)

/** @brief Copy of a scalar

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vmovs_(rd, rs) pspla_vfpu_asm_register_(vmov.s, rd, rs)

/** @brief Copy of a 2D vector

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vmovp_(rd, rs) pspla_vfpu_asm_register_(vmov.p, rd, rs)

/** @brief Copy of a 3D vector

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vmovt_(rd, rs) pspla_vfpu_asm_register_(vmov.t, rd, rs)

/** @brief Copy of a 4D vector

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vmovq_(rd, rs) pspla_vfpu_asm_register_(vmov.q, rd, rs)

/** @brief Absolute value of a scalar

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vabss_(rd, rs) pspla_vfpu_asm_register_(vabs.s, rd, rs)

/** @brief Absolute value of a 2D vector

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vabsp_(rd, rs) pspla_vfpu_asm_register_(vabs.p, rd, rs)

/** @brief Absolute value of a 3D vector

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vabst_(rd, rs) pspla_vfpu_asm_register_(vabs.t, rd, rs)

/** @brief Absolute value of a 4D vector

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vabsq_(rd, rs) pspla_vfpu_asm_register_(vabs.q, rd, rs)

/** @brief Negation of a scalar

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vnegs_(rd, rs) pspla_vfpu_asm_register_(vneg.s, rd, rs)

/** @brief Element-wise negation of a 2D vector

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vnegp_(rd, rs) pspla_vfpu_asm_register_(vneg.p, rd, rs)

/** @brief Element-wise negation of a 3D vector

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vnegt_(rd, rs) pspla_vfpu_asm_register_(vneg.t, rd, rs)

/** @brief Element-wise negation of a 4D vector

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vnegq_(rd, rs) pspla_vfpu_asm_register_(vneg.q, rd, rs)

/** @brief Saturated output of a scalar from 0.0 to 1.0

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsat0s_(rd, rs) pspla_vfpu_asm_register_(vsat0.s, rd, rs)

/** @brief Element-wise saturated output of a 2D vector from 0.0 to 1.0

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsat0p_(rd, rs) pspla_vfpu_asm_register_(vsat0.p, rd, rs)

/** @brief Element-wise saturated output of a 3D vector from 0.0 to 1.0

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsat0t_(rd, rs) pspla_vfpu_asm_register_(vsat0.t, rd, rs)

/** @brief Element-wise saturated output of a 4D vector from 0.0 to 1.0

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsat0q_(rd, rs) pspla_vfpu_asm_register_(vsat0.q, rd, rs)

/** @brief Saturated output of a scalar from -1.0 to 1.0

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsat1s_(rd, rs) pspla_vfpu_asm_register_(vsat1.s, rd, rs)

/** @brief Element-wise saturated output of a 2D vector from -1.0 to 1.0

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsat1p_(rd, rs) pspla_vfpu_asm_register_(vsat1.p, rd, rs)

/** @brief Element-wise saturated output of a 3D vector from -1.0 to 1.0

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsat1t_(rd, rs) pspla_vfpu_asm_register_(vsat1.t, rd, rs)

/** @brief Element-wise saturated output of a 4D vector from -1.0 to 1.0

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsat1q_(rd, rs) pspla_vfpu_asm_register_(vsat1.q, rd, rs)

/** @brief Reciprocal of a scalar

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vrcps_(rd, rs) pspla_vfpu_asm_register_(vrcp.s, rd, rs)

/** @brief Element-wise reciprocal of a 2D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vrcpp_(rd, rs) pspla_vfpu_asm_register_(vrcp.p, rd, rs)

/** @brief Element-wise reciprocal of a 3D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vrcpt_(rd, rs) pspla_vfpu_asm_register_(vrcp.t, rd, rs)

/** @brief Element-wise reciprocal of a 4D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vrcpq_(rd, rs) pspla_vfpu_asm_register_(vrcp.q, rd, rs)

/** @brief Reciprocal square root of a scalar

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vrsqs_(rd, rs) pspla_vfpu_asm_register_(vrsq.s, rd, rs)

/** @brief Element-wise reciprocal square root of a 2D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vrsqp_(rd, rs) pspla_vfpu_asm_register_(vrsq.p, rd, rs)

/** @brief Element-wise reciprocal square root of a 3D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vrsqt_(rd, rs) pspla_vfpu_asm_register_(vrsq.t, rd, rs)

/** @brief Element-wise reciprocal square root of a 4D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vrsqq_(rd, rs) pspla_vfpu_asm_register_(vrsq.q, rd, rs)

/** @brief Sine of a scalar * (π/2)

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsins_(rd, rs) pspla_vfpu_asm_register_(vsin.s, rd, rs)

/** @brief Element-wise sine of a 2D vector * (π/2)

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsinp_(rd, rs) pspla_vfpu_asm_register_(vsin.p, rd, rs)

/** @brief Element-wise sine of a 3D vector * (π/2)

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsint_(rd, rs) pspla_vfpu_asm_register_(vsin.t, rd, rs)

/** @brief Element-wise sine of a 4D vector * (π/2)

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsinq_(rd, rs) pspla_vfpu_asm_register_(vsin.q, rd, rs)

/** @brief Cosine of a scalar * (π/2)

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vcoss_(rd, rs) pspla_vfpu_asm_register_(vcos.s, rd, rs)

/** @brief Element-wise cosine of a 2D vector * (π/2)

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vcosp_(rd, rs) pspla_vfpu_asm_register_(vcos.p, rd, rs)

/** @brief Element-wise cosine of a 3D vector * (π/2)

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vcost_(rd, rs) pspla_vfpu_asm_register_(vcos.t, rd, rs)

/** @brief Element-wise cosine of a 4D vector * (π/2)

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vcosq_(rd, rs) pspla_vfpu_asm_register_(vcos.q, rd, rs)

/** @brief Base of 2 exponentiated by an integer scalar

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vexp2s_(rd, rs) pspla_vfpu_asm_register_(vexp2.s, rd, rs)

/** @brief Element-wise base of 2 exponentiated by an integer 2D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vexp2p_(rd, rs) pspla_vfpu_asm_register_(vexp2.p, rd, rs)

/** @brief Element-wise base of 2 exponentiated by an integer 3D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vexp2t_(rd, rs) pspla_vfpu_asm_register_(vexp2.t, rd, rs)

/** @brief Element-wise base of 2 exponentiated by an integer 4D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vexp2q_(rd, rs) pspla_vfpu_asm_register_(vexp2.q, rd, rs)

/** @brief Base-2 logarithm of a scalar

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vlog2s_(rd, rs) pspla_vfpu_asm_register_(vlog2.s, rd, rs)

/** @brief Element-wise base-2 logarithm of a 2D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vlog2p_(rd, rs) pspla_vfpu_asm_register_(vlog2.p, rd, rs)

/** @brief Element-wise base-2 logarithm of a 3D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vlog2t_(rd, rs) pspla_vfpu_asm_register_(vlog2.t, rd, rs)

/** @brief Element-wise base-2 logarithm of a 4D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vlog2q_(rd, rs) pspla_vfpu_asm_register_(vlog2.q, rd, rs)

/** @brief Base-2 exponent of the absolute value of a scalar, equivalent to the <math.h> logb function

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vlgbs_(rd, rs) pspla_vfpu_asm_register_(vlgb.s, rd, rs)

/** @brief Floating point modulus of a scalar

    @param rd The destination VFPU register
    @param rs The source VFPU register
    @param imval 8-bit immediate value
*/
#define pspla_vfpu_vwbns_(rd, rs, imval) pspla_vfpu_asm_register_(vlgb.s, rd, rs, imval)

/** @brief Square root of a scalar

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsqrts_(rd, rs) pspla_vfpu_asm_register_(vsqrt.s, rd, rs)

/** @brief Element-wise square root of a 2D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsqrtp_(rd, rs) pspla_vfpu_asm_register_(vsqrt.p, rd, rs)

/** @brief Element-wise square root of a 3D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsqrtt_(rd, rs) pspla_vfpu_asm_register_(vsqrt.t, rd, rs)

/** @brief Element-wise square root of a 4D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vsqrtq_(rd, rs) pspla_vfpu_asm_register_(vsqrt.q, rd, rs)

/** @brief Arcsine of a scalar * (π/2)

    @note The output of this instruction an approximation, and becomes inaccurate when `rs` is outside the range of [-0.5, 0.5].

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vasins_(rd, rs) pspla_vfpu_asm_register_(vasin.s, rd, rs)

/** @brief Arcsine of a 2D vector * (π/2)

    @note The output of this instruction an approximation, and becomes inaccurate when `rs` is outside the range of [-0.5, 0.5].

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vasinp_(rd, rs) pspla_vfpu_asm_register_(vasin.p, rd, rs)

/** @brief Arcsine of a 3D vector * (π/2)

    @note The output of this instruction an approximation, and becomes inaccurate when `rs` is outside the range of [-0.5, 0.5].

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vasint_(rd, rs) pspla_vfpu_asm_register_(vasin.t, rd, rs)

/** @brief Arcsine of a 4D vector * (π/2)

    @note The output of this instruction an approximation, and becomes inaccurate when `rs` is outside the range of [-0.5, 0.5].

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vasinq_(rd, rs) pspla_vfpu_asm_register_(vasin.q, rd, rs)

/** @brief Negated reciprocal of a scalar

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vnrcps_(rd, rs) pspla_vfpu_asm_register_(vnrcp.s, rd, rs)

/** @brief Element-wise negated reciprocal of a 2D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vnrcpp_(rd, rs) pspla_vfpu_asm_register_(vnrcp.p, rd, rs)

/** @brief Element-wise negated reciprocal of a 3D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vnrcpt_(rd, rs) pspla_vfpu_asm_register_(vnrcp.t, rd, rs)

/** @brief Element-wise negated reciprocal of a 4D vector

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vnrcpq_(rd, rs) pspla_vfpu_asm_register_(vnrcp.q, rd, rs)

/** @brief Negated sine of a scalar * (π/2)

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vnsins_(rd, rs) pspla_vfpu_asm_register_(vnsin.s, rd, rs)

/** @brief Negated sine of a 2D vector * (π/2)

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vnsinp_(rd, rs) pspla_vfpu_asm_register_(vnsin.p, rd, rs)

/** @brief Negated sine of a 3D vector * (π/2)

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vnsint_(rd, rs) pspla_vfpu_asm_register_(vnsin.t, rd, rs)

/** @brief Negated sine of a 4D vector * (π/2)

    @note The output of this instruction is a (close) approximation, not the exact value.

    @param rd The destination VFPU register
    @param rs The source VFPU register
*/
#define pspla_vfpu_vnsinq_(rd, rs) pspla_vfpu_asm_register_(vnsin.q, rd, rs)

/** TODO: Comment the rest of these macros */

#define pspla_vfpu_vrexp2s_(rd, rs) pspla_vfpu_asm_register_(vrexp2.s, rd, rs)
#define pspla_vfpu_vrexp2p_(rd, rs) pspla_vfpu_asm_register_(vrexp2.p, rd, rs)
#define pspla_vfpu_vrexp2t_(rd, rs) pspla_vfpu_asm_register_(vrexp2.t, rd, rs)
#define pspla_vfpu_vrexp2q_(rd, rs) pspla_vfpu_asm_register_(vrexp2.q, rd, rs)

#define pspla_vfpu_vsrt1q_(rd, rs) pspla_vfpu_asm_register_(vsrt1.q, rd, rs)
#define pspla_vfpu_vsrt2q_(rd, rs) pspla_vfpu_asm_register_(vsrt2.q, rd, rs)
#define pspla_vfpu_vsrt3q_(rd, rs) pspla_vfpu_asm_register_(vsrt3.q, rd, rs)
#define pspla_vfpu_vsrt4q_(rd, rs) pspla_vfpu_asm_register_(vsrt4.q, rd, rs)

#define pspla_vfpu_vbfy1p_(rd, rs) pspla_vfpu_asm_register_(vbfy1.p, rd, rs)
#define pspla_vfpu_vbfy1q_(rd, rs) pspla_vfpu_asm_register_(vbfy1.q, rd, rs)

#define pspla_vfpu_vbfy2q_(rd, rs) pspla_vfpu_asm_register_(vbfy2.q, rd, rs)

#define pspla_vfpu_vsgns_(rd, rs) pspla_vfpu_asm_register_(vsgn.s, rd, rs)
#define pspla_vfpu_vsgnp_(rd, rs) pspla_vfpu_asm_register_(vsgn.p, rd, rs)
#define pspla_vfpu_vsgnt_(rd, rs) pspla_vfpu_asm_register_(vsgn.t, rd, rs)
#define pspla_vfpu_vsgnq_(rd, rs) pspla_vfpu_asm_register_(vsgn.q, rd, rs)

#define pspla_vfpu_vocps_(rd, rs) pspla_vfpu_asm_register_(vocp.s, rd, rs)
#define pspla_vfpu_vocpp_(rd, rs) pspla_vfpu_asm_register_(vocp.p, rd, rs)
#define pspla_vfpu_vocpt_(rd, rs) pspla_vfpu_asm_register_(vocp.t, rd, rs)
#define pspla_vfpu_vocpq_(rd, rs) pspla_vfpu_asm_register_(vocp.q, rd, rs)

#define pspla_vfpu_vi2fs_(rd, rs, imval) pspla_vfpu_asm_register_(vi2f.s, rd, rs, imval)
#define pspla_vfpu_vi2fp_(rd, rs, imval) pspla_vfpu_asm_register_(vi2f.p, rd, rs, imval)
#define pspla_vfpu_vi2ft_(rd, rs, imval) pspla_vfpu_asm_register_(vi2f.t, rd, rs, imval)
#define pspla_vfpu_vi2fq_(rd, rs, imval) pspla_vfpu_asm_register_(vi2f.q, rd, rs, imval)

#define pspla_vfpu_vf2ins_(rd, rs, imval) pspla_vfpu_asm_register_(vf2in.s, rd, rs, imval)
#define pspla_vfpu_vf2inp_(rd, rs, imval) pspla_vfpu_asm_register_(vf2in.p, rd, rs, imval)
#define pspla_vfpu_vf2int_(rd, rs, imval) pspla_vfpu_asm_register_(vf2in.t, rd, rs, imval)
#define pspla_vfpu_vf2inq_(rd, rs, imval) pspla_vfpu_asm_register_(vf2in.q, rd, rs, imval)

#define pspla_vfpu_vf2izs_(rd, rs, imval) pspla_vfpu_asm_register_(vf2iz.s, rd, rs, imval)
#define pspla_vfpu_vf2izp_(rd, rs, imval) pspla_vfpu_asm_register_(vf2iz.p, rd, rs, imval)
#define pspla_vfpu_vf2izt_(rd, rs, imval) pspla_vfpu_asm_register_(vf2iz.t, rd, rs, imval)
#define pspla_vfpu_vf2izq_(rd, rs, imval) pspla_vfpu_asm_register_(vf2iz.q, rd, rs, imval)

#define pspla_vfpu_vf2ius_(rd, rs, imval) pspla_vfpu_asm_register_(vf2iu.s, rd, rs, imval)
#define pspla_vfpu_vf2iup_(rd, rs, imval) pspla_vfpu_asm_register_(vf2iu.p, rd, rs, imval)
#define pspla_vfpu_vf2iut_(rd, rs, imval) pspla_vfpu_asm_register_(vf2iu.t, rd, rs, imval)
#define pspla_vfpu_vf2iuq_(rd, rs, imval) pspla_vfpu_asm_register_(vf2iu.q, rd, rs, imval)

#define pspla_vfpu_vf2ids_(rd, rs, imval) pspla_vfpu_asm_register_(vf2id.s, rd, rs, imval)
#define pspla_vfpu_vf2idp_(rd, rs, imval) pspla_vfpu_asm_register_(vf2id.p, rd, rs, imval)
#define pspla_vfpu_vf2idt_(rd, rs, imval) pspla_vfpu_asm_register_(vf2id.t, rd, rs, imval)
#define pspla_vfpu_vf2idq_(rd, rs, imval) pspla_vfpu_asm_register_(vf2id.q, rd, rs, imval)

#define pspla_vfpu_vrotp_(rd, rs, imval) pspla_vfpu_asm_register_(vrot.p, rd, rs, imval)
#define pspla_vfpu_vrott_(rd, rs, imval) pspla_vfpu_asm_register_(vrot.t, rd, rs, imval)
#define pspla_vfpu_vrotq_(rd, rs, imval) pspla_vfpu_asm_register_(vrot.q, rd, rs, imval)

#define pspla_vfpu_vsocps_(rd, rs) pspla_vfpu_asm_register_(vsocp.s, rd, rs)
#define pspla_vfpu_vsocpp_(rd, rs) pspla_vfpu_asm_register_(vsocp.p, rd, rs)

#define pspla_vfpu_vavgp_(rd, rs) pspla_vfpu_asm_register_(vavg.p, rd, rs)
#define pspla_vfpu_vavgt_(rd, rs) pspla_vfpu_asm_register_(vavg.t, rd, rs)
#define pspla_vfpu_vavgq_(rd, rs) pspla_vfpu_asm_register_(vavg.q, rd, rs)

#define pspla_vfpu_vfadp_(rd, rs) pspla_vfpu_asm_register_(vfad.p, rd, rs)
#define pspla_vfpu_vfadt_(rd, rs) pspla_vfpu_asm_register_(vfad.t, rd, rs)
#define pspla_vfpu_vfadq_(rd, rs) pspla_vfpu_asm_register_(vfad.q, rd, rs)

#define pspla_vfpu_vcmps_(condition, rs, rt) pspla_vfpu_asm_register_(vf2id.s, condition, rs, rt)
#define pspla_vfpu_vcmpp_(condition, rs, rt) pspla_vfpu_asm_register_(vf2id.p, condition, rs, rt)
#define pspla_vfpu_vcmpt_(condition, rs, rt) pspla_vfpu_asm_register_(vf2id.t, condition, rs, rt)
#define pspla_vfpu_vcmpq_(condition, rs, rt) pspla_vfpu_asm_register_(vf2id.q, condition, rs, rt)

#define pspla_vfpu_vidtp_(rd) pspla_vfpu_asm_register_(vidt.p, rd)
#define pspla_vfpu_vidtq_(rd) pspla_vfpu_asm_register_(vidt.q, rd)

#define pspla_vfpu_vzeros_(rd) pspla_vfpu_asm_register_(vzero.s, rd)
#define pspla_vfpu_vzerop_(rd) pspla_vfpu_asm_register_(vzero.p, rd)
#define pspla_vfpu_vzerot_(rd) pspla_vfpu_asm_register_(vzero.t, rd)
#define pspla_vfpu_vzeroq_(rd) pspla_vfpu_asm_register_(vzero.q, rd)

#define pspla_vfpu_vones_(rd) pspla_vfpu_asm_register_(vone.s, rd)
#define pspla_vfpu_vonep_(rd) pspla_vfpu_asm_register_(vone.p, rd)
#define pspla_vfpu_vonet_(rd) pspla_vfpu_asm_register_(vone.t, rd)
#define pspla_vfpu_voneq_(rd) pspla_vfpu_asm_register_(vone.q, rd)

#define pspla_vfpu_vrndss_(rs) pspla_vfpu_asm_register_(vrnds.s, rs)

#define pspla_vfpu_vrndis_(rd) pspla_vfpu_asm_register_(vrndi.s, rd)
#define pspla_vfpu_vrndip_(rd) pspla_vfpu_asm_register_(vrndi.p, rd)
#define pspla_vfpu_vrndit_(rd) pspla_vfpu_asm_register_(vrndi.t, rd)
#define pspla_vfpu_vrndiq_(rd) pspla_vfpu_asm_register_(vrndi.q, rd)

#define pspla_vfpu_vrndf1s_(rd) pspla_vfpu_asm_register_(vrndf1.s, rd)
#define pspla_vfpu_vrndf1p_(rd) pspla_vfpu_asm_register_(vrndf1.p, rd)
#define pspla_vfpu_vrndf1t_(rd) pspla_vfpu_asm_register_(vrndf1.t, rd)
#define pspla_vfpu_vrndf1q_(rd) pspla_vfpu_asm_register_(vrndf1.q, rd)

#define pspla_vfpu_vrndf2s_(rd) pspla_vfpu_asm_register_(vrndf2.s, rd)
#define pspla_vfpu_vrndf2p_(rd) pspla_vfpu_asm_register_(vrndf2.p, rd)
#define pspla_vfpu_vrndf2t_(rd) pspla_vfpu_asm_register_(vrndf2.t, rd)
#define pspla_vfpu_vrndf2q_(rd) pspla_vfpu_asm_register_(vrndf2.q, rd)

#define pspla_vfpu_vmmulp_(rd, rs, rt) pspla_vfpu_asm_register_(vmmul.p, rd, rs, rt)
#define pspla_vfpu_vmmult_(rd, rs, rt) pspla_vfpu_asm_register_(vmmul.t, rd, rs, rt)
#define pspla_vfpu_vmmulq_(rd, rs, rt) pspla_vfpu_asm_register_(vmmul.q, rd, rs, rt)

#define pspla_vfpu_vmsclp_(rd, rs, rt) pspla_vfpu_asm_register_(vmscl.p, rd, rs, rt)
#define pspla_vfpu_vmsclt_(rd, rs, rt) pspla_vfpu_asm_register_(vmscl.t, rd, rs, rt)
#define pspla_vfpu_vmsclq_(rd, rs, rt) pspla_vfpu_asm_register_(vmscl.q, rd, rs, rt)

#define pspla_vfpu_vmmovp_(rd, rs) pspla_vfpu_asm_register_(vmmov.p, rd, rs)
#define pspla_vfpu_vmmovt_(rd, rs) pspla_vfpu_asm_register_(vmmov.t, rd, rs)
#define pspla_vfpu_vmmovq_(rd, rs) pspla_vfpu_asm_register_(vmmov.q, rd, rs)

#define pspla_vfpu_vmidtp_(rd) pspla_vfpu_asm_register_(vmidt.p, rd)
#define pspla_vfpu_vmidtt_(rd) pspla_vfpu_asm_register_(vmidt.t, rd)
#define pspla_vfpu_vmidtq_(rd) pspla_vfpu_asm_register_(vmidt.q, rd)

#define pspla_vfpu_vmzerop_(rd) pspla_vfpu_asm_register_(vmzero.p, rd)
#define pspla_vfpu_vmzerot_(rd) pspla_vfpu_asm_register_(vmzero.t, rd)
#define pspla_vfpu_vmzeroq_(rd) pspla_vfpu_asm_register_(vmzero.q, rd)

#define pspla_vfpu_vmonep_(rd) pspla_vfpu_asm_register_(vmone.p, rd)
#define pspla_vfpu_vmonet_(rd) pspla_vfpu_asm_register_(vmone.t, rd)
#define pspla_vfpu_vmoneq_(rd) pspla_vfpu_asm_register_(vmone.q, rd)

#define pspla_vfpu_vtfm2p_(rd, rs, rt) pspla_vfpu_asm_register_(vtfm2.p, rd, rs, rt)
#define pspla_vfpu_vtfm3t_(rd, rs, rt) pspla_vfpu_asm_register_(vtfm2.t, rd, rs, rt)
#define pspla_vfpu_vtfm4q_(rd, rs, rt) pspla_vfpu_asm_register_(vtfm2.q, rd, rs, rt)

#define pspla_vfpu_vhtfm2p_(rd, rs, rt) pspla_vfpu_asm_register_(vhtfm2.p, rd, rs, rt)
#define pspla_vfpu_vhtfm3t_(rd, rs, rt) pspla_vfpu_asm_register_(vhtfm2.t, rd, rs, rt)
#define pspla_vfpu_vhtfm4q_(rd, rs, rt) pspla_vfpu_asm_register_(vhtfm2.q, rd, rs, rt)

#define pspla_vfpu_vcmovfs_(rd, rs, cc_select) pspla_vfpu_asm_register_(vcmovf.s, rd, rs, cc_select)
#define pspla_vfpu_vcmovfp_(rd, rs, cc_select) pspla_vfpu_asm_register_(vcmovf.p, rd, rs, cc_select)
#define pspla_vfpu_vcmovft_(rd, rs, cc_select) pspla_vfpu_asm_register_(vcmovf.t, rd, rs, cc_select)
#define pspla_vfpu_vcmovfq_(rd, rs, cc_select) pspla_vfpu_asm_register_(vcmovf.q, rd, rs, cc_select)

#define pspla_vfpu_vcmovts_(rd, rs, cc_select) pspla_vfpu_asm_register_(vcmovt.s, rd, rs, cc_select)
#define pspla_vfpu_vcmovtp_(rd, rs, cc_select) pspla_vfpu_asm_register_(vcmovt.p, rd, rs, cc_select)
#define pspla_vfpu_vcmovtt_(rd, rs, cc_select) pspla_vfpu_asm_register_(vcmovt.t, rd, rs, cc_select)
#define pspla_vfpu_vcmovtq_(rd, rs, cc_select) pspla_vfpu_asm_register_(vcmovt.q, rd, rs, cc_select)

#define pspla_vfpu_vi2ucq_(rd, rs) pspla_vfpu_asm_register_(vi2uc.q, rd, rs)

#define pspla_vfpu_vi2cq_(rd, rs) pspla_vfpu_asm_register_(vi2c.q, rd, rs)

#define pspla_vfpu_vi2usp_(rd, rs) pspla_vfpu_asm_register_(vi2us.p, rd, rs)
#define pspla_vfpu_vi2usq_(rd, rs) pspla_vfpu_asm_register_(vi2us.q, rd, rs)

#define pspla_vfpu_vi2sp_(rd, rs) pspla_vfpu_asm_register_(vi2us.p, rd, rs)
#define pspla_vfpu_vi2sq_(rd, rs) pspla_vfpu_asm_register_(vi2us.q, rd, rs)

#define pspla_vfpu_vf2hp_(rd, rs) pspla_vfpu_asm_register_(vf2h.p, rd, rs)
#define pspla_vfpu_vf2hq_(rd, rs) pspla_vfpu_asm_register_(vf2h.q, rd, rs)

#define pspla_vfpu_vs2is_(rd, rs) pspla_vfpu_asm_register_(vs2i.s, rd, rs)
#define pspla_vfpu_vs2ip_(rd, rs) pspla_vfpu_asm_register_(vs2i.p, rd, rs)

#define pspla_vfpu_vus2is_(rd, rs) pspla_vfpu_asm_register_(vus2i.s, rd, rs)
#define pspla_vfpu_vus2ip_(rd, rs) pspla_vfpu_asm_register_(vus2i.p, rd, rs)

#define pspla_vfpu_vc2is_(rd, rs) pspla_vfpu_asm_register_(vc2i.s, rd, rs)

#define pspla_vfpu_vuc2ifs_(rd, rs) pspla_vfpu_asm_register_(vuc2if.s, rd, rs)

#define pspla_vfpu_vh2fs_(rd, rs) pspla_vfpu_asm_register_(vh2f.s, rd, rs)
#define pspla_vfpu_vh2fp_(rd, rs) pspla_vfpu_asm_register_(vh2f.p, rd, rs)

#define pspla_vfpu_vt4444q_(rd, rs) pspla_vfpu_asm_register_(vt4444.q, rd, rs)

#define pspla_vfpu_vt5551q_(rd, rs) pspla_vfpu_asm_register_(vt5551.q, rd, rs)

#define pspla_vfpu_vt5650q_(rd, rs) pspla_vfpu_asm_register_(vt5650.q, rd, rs)

#define pspla_vfpu_viims_(rd, imval) pspla_vfpu_asm_register_(viim.s, rd, imval)

#define pspla_vfpu_vfims_(rd, imval) pspla_vfpu_asm_register_(vfim.s, rd, imval)

#define pspla_vfpu_vcsts_(rd, imval) pspla_vfpu_asm_register_(vcst.s, rd, imval)
#define pspla_vfpu_vcstp_(rd, imval) pspla_vfpu_asm_register_(vcst.p, rd, imval)
#define pspla_vfpu_vcstt_(rd, imval) pspla_vfpu_asm_register_(vcst.t, rd, imval)
#define pspla_vfpu_vcstq_(rd, imval) pspla_vfpu_asm_register_(vcst.q, rd, imval)

#define pspla_vfpu_vnop_() pspla_vfpu_asm_register_(vnop)
#define pspla_vfpu_vflush_() pspla_vfpu_asm_register_(vflush)
#define pspla_vfpu_vsync_() pspla_vfpu_asm_register_(vsync)
#define pspla_vfpu_vpfxs_() pspla_vfpu_asm_register_(vpfxs)
#define pspla_vfpu_vpfxt_() pspla_vfpu_asm_register_(vpfxt)
#define pspla_vfpu_vpfxd_() pspla_vfpu_asm_register_(vpfxd)

/** }@ */

#endif