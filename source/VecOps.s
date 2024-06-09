# Unaligned and aligned loads for matrices
# Figured that splitting these up better allows for choosing between speed and flexibility
.macro lm2u mat, src
    ulv.q r\mat\()00, 0(\src\())
    ulv.q r\mat\()01, 8(\src\())
.endm

.macro lm3u mat, src
    ulv.q r\mat\()00, 0(\src\())
    ulv.q r\mat\()01, 12(\src\())
    ulv.q r\mat\()02, 24(\src\())
.endm

.macro lm4u mat, src
    ulv.q r\mat\()00, 0(\src\())
    ulv.q r\mat\()01, 16(\src\())
    ulv.q r\mat\()02, 32(\src\())
    ulv.q r\mat\()03, 48(\src\())
.endm

.macro lm2a mat, src
    lv.q r\mat\()00, 0(\src\())
    vmov.p r\mat\()01, r\mat\()20
.endm

.macro lm3a mat, src
    lv.q r\mat\()00, 0(\src\())
    lv.q r\mat\()01, 16(\src\())
    lv.s s\mat\()22, 32(\src\())
    vmov.p r\mat\()02, r\mat\()21
    vmov.t r\mat\()11, r\mat\()01
    vmov.s s\mat\()01, s\mat\()30
.endm

.macro lm4a mat, src
    lv.q r\mat\()00, 0(\src\())
    lv.q r\mat\()01, 16(\src\())
    lv.q r\mat\()02, 32(\src\())
    lv.q r\mat\()03, 48(\src\())
.endm

# Reduce function header redundancy
.macro gfunc name
.globl \name
\name\():
.endm

# Slightly compact saving for Vec2 and Vec3 unaligned functions
.macro svp reg1, reg2, dest, off
    sv.s \reg1\(), (\off\() + 0)(\dest\())
    sv.s \reg2\(), (\off\() + 4)(\dest\())
.endm

.macro svt reg1, reg2, reg3, dest, off
    svp \reg1\(), \reg2\(), \dest\(), \off\()
    sv.s \reg3\(), (\off\() + 8)(\dest\())
.endm

# Pushing and popping corrupted registers to and from the stack
.macro pushf reg
    sub $sp, $sp, 4
    s.s \reg\(), 0($sp)
.endm

.macro popf reg
    l.s \reg\(), 0($sp)
    add $sp, $sp, 4
.endm

# For functions that are take two vectors and output a vector
.macro singleOpVecU op
    pushf $f0
    ulv.q r000, 0($a0)
    ulv.q r001, 0($a1)
    popf $f0
    \op\() r002, r000, r001
.endm

.macro singleOpVec2U op
    singleOpVecU \op\()
    svp s002, s012, $a2, 0
.endm

.macro singleOpVec3U op
    singleOpVecU \op\()
    svt s002, s012, s022, $a2, 0
.endm

.macro singleOpVec4U op
    singleOpVecU \op\()
    usv.q r002, 0($a2)
.endm

.macro singleOpVecVA op
    lv.q r000, 0($a0)
    lv.q r001, 0($a1)
    \op\() r002, r000, r001
    sv.q r002, 0($a2)
.endm

# For functions that take a single vector and output a scalar
.macro singleOpScaVU op
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0    
    \op\() s001, r000
    mfv $t0, s001
    mtc1 $t0, $f0
.endm

.macro singleOpScaVA op
    lv.q r000, 0($a0)
    \op\() s001, r000
    mfv $t0, s001
    mtc1 $t0, $f0
.endm

# For functions that take two vectors and output a scalar
.macro singleOpScaDVU op
    pushf $f0
    ulv.q r000, 0($a0)
    ulv.q r001, 0($a1)
    popf $f0    
    \op\() s002, r000, r001
    mfv $t0, s002
    mtc1 $t0, $f0
.endm

.macro singleOpScaDVA op
    lv.q r000, 0($a0)
    lv.q r001, 0($a1) 
    \op\() s002, r000, r001
    mfv $t0, s002
    mtc1 $t0, $f0
.endm

# For functions that take a single vector and return a single vector
.macro singleOpSVecU op
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    \op\() r002, r000
.endm

.macro singleOpSVec2U op
    singleOpSVecU \op\()
    svp s002, s012, $a1, 0
.endm

.macro singleOpSVec3U op
    singleOpSVecU \op\()
    svt s002, s012, s022, $a1, 0
.endm

.macro singleOpSVec4U op
    singleOpSVecU \op\()
    usv.q r002, 0($a1)
.endm

.macro singleOpSVecVA op
    lv.q r000, 0($a0)
    \op\() r002, r000
    sv.q r002, 0($a1)
.endm

# For functions that take a vector and scalar as arguments, and return a vector
.macro singleOpVecScaU op
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    mfc1 $t0, $f12
    mtv $t0, s001
    \op\() r002, r000, s001
.endm

.macro singleOpVec2ScaU op
    singleOpVecScaU \op\()
    svp s002, s012, $a1, 0
.endm

.macro singleOpVec3ScaU op
    singleOpVecScaU \op\()
    svt s002, s012, s022, $a1, 0
.endm

.macro singleOpVec4ScaU op
    singleOpVecScaU \op\()
    usv.q r002, 0($a1)
.endm

.macro singleOpVecVScaA op
    lv.q r000, 0($a0)
    mfc1 $t0, $f12
    mtv $t0, s001
    \op\() r002, r000, s001
    sv.q r002, 0($a1)
.endm

# For functions that take a scalar and return a scalar
.macro singleOpSca2Sca op
    mfc1 $t0, $f12
    mtv $t0, s000
    \op\() s001, s000
    mfv $t0, s001
    mtc1 $t0, $f0
.endm

# For Round, Floor, and Ceiling functions
.macro truncateOpVecU op
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    \op\() r000, r000, 0
    vi2f.q r000, r000, 0
.endm

.macro truncateOpVec2U op
    truncateOpVecU \op\()
    svp s000, s010, $a1, 0
.endm

.macro truncateOpVec3U op
    truncateOpVecU \op\()
    svt s000, s010, s020, $a1, 0
.endm

.macro truncateOpVec4U op
    truncateOpVecU \op\()
    usv.q r000, 0($a1)
.endm

.macro truncateOpVecVA op
    lv.q r000, 0($a0)
    \op\() r000, r000, 0
    vi2f.q r000, r000, 0
    sv.q r000, 0($a1)
.endm

# For comparison functions
.macro comparisonOpVecU inst op
    pushf $f0
    ulv.q r000, 0($a0)
    ulv.q r001, 0($a1)
    popf $f0
    viim.s s003, 0
    vmtvc $131, s003
    \inst\() \op\(), r000, r001
    vnop
    mfvc $v0, $131
.endm

.macro comparisonOpVecA inst op
    lv.q r000, 0($a0)
    lv.q r001, 0($a1)
    viim.s s003, 0
    vmtvc $131, s003
    \inst\() \op\(), r000, r001
    vnop
    mfvc $v0, $131
.endm

# For mat3 and mat4 element-wise functions
.macro singleOpMat3U op
    sub $sp, $sp, 8
    s.s $f0, 4($sp)
    s.s $f4, 0($sp)
    lm3u 0, $a0
    lm3u 1, $a1
    l.s $f4, 0($sp)
    l.s $f0, 4($sp)
    add $sp, $sp, 8
    \op\().t r200, r000, r100
    \op\().t r201, r001, r101
    \op\().t r202, r002, r102
    usv.q r200, 0($a2)
    usv.q r201, 12($a2)
    svt s202, s212, s222, $a2, 24
.endm

.macro singleOpMat4U op
    sub $sp, $sp, 8
    s.s $f0, 4($sp)
    s.s $f4, 0($sp)
    lm4u 0, $a0
    lm4u 1, $a1
    l.s $f4, 0($sp)
    l.s $f0, 4($sp)
    add $sp, $sp, 8
    \op\().q r200, r000, r100
    \op\().q r201, r001, r101
    \op\().q r202, r002, r102
    \op\().q r203, r003, r103
    usv.q r200, 0($a2)
    usv.q r201, 16($a2)
    usv.q r202, 32($a2)
    usv.q r203, 48($a2)
.endm

.macro singleOpMat3A op
    lm3a 0, $a0
    lm3a 1, $a1
    \op\().t r200, r000, r100
    \op\().t r201, r001, r101
    \op\().t r202, r002, r102
    sv.q r200, 0($a2)
    usv.q r201, 12($a2)
    usv.q r202, 24($a2)
.endm

.macro singleOpMat4A op
    lm4a 0, $a0
    lm4a 1, $a1
    \op\().q r200, r000, r100
    \op\().q r201, r001, r101
    \op\().q r202, r002, r102
    \op\().q r203, r003, r103
    sv.q r200, 0($a2)
    sv.q r201, 16($a2)
    sv.q r202, 32($a2)
    sv.q r203, 48($a2)  
.endm

# For determinant and inverse functions
.macro mat2Determinant a, b, c, d, out
    vmov.s s000, s7\a
    vmov.s s010, s7\d
    vmov.s s001, s7\b
    vmov.s s011, s7\c
    vmul.p c020, c000, c010
    vfad.p \out, c020[x,-y]
.endm

.macro mat3Determinant d, e, f, g, h, i, j, k, l, mlt, out
    mat2Determinant \e, \f, \h, \i, s100
    mat2Determinant \d, \f, \g, \i, s101
    mat2Determinant \d, \e, \g, \h, s102
    vmov.q c110, r7\mlt\()[\j,\k,\l,0]
    vmul.t c120, c110, c100
    vfad.t \out, c120[x,-y,z]
.endm

.macro mat4Determinant e, f, g, h, i, j, k, l, out
    mat3Determinant \f, \g, \h, \j, \k, \l, y, z, w, 01, s200
    mat3Determinant \e, \g, \h, \i, \k, \l, x, z, w, 01, s201
    mat3Determinant \e, \f, \h, \i, \j, \l, x, y, w, 01, s202
    mat3Determinant \e, \f, \g, \i, \j, \k, x, y, z, 01, s203
    vmov.q c210, r700
    vmul.q c220, c210, c200
    vfad.q \out, c220[x,-y,z,-w]
.endm

#
# Start of functions
#
gfunc psplaMat3CopyU
    pushf $f0
    lm3u 0, $a0
    popf $f0    
    usv.q r000, 0($a1)
    usv.q r001, 12($a1)
    svt s002, s012, s022, $a1, 24
    jr $ra

gfunc psplaMat4CopyU
    pushf $f0
    lm4u 0, $a0
    popf $f0    
    usv.q r000, 0($a1)
    usv.q r001, 16($a1)
    usv.q r002, 32($a1)
    usv.q r003, 48($a1)
    jr $ra

gfunc psplaMat3CopyA
    lm3a 0, $a0
    sv.q r000, 0($a1)
    usv.q r001, 12($a1)
    usv.q r002, 24($a1)
    jr $ra

gfunc psplaMat4CopyA
    lm4a 0, $a0
    sv.q r000, 0($a1)
    sv.q r001, 16($a1)
    sv.q r002, 32($a1)
    sv.q r003, 48($a1)
    jr $ra

gfunc psplaVec2CopyU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0    
    svp s000, s010, $a1, 0
    jr $ra

gfunc psplaVec3CopyU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0    
    svt s000, s010, s020, $a1, 0
    jr $ra

gfunc psplaMat2CopyU
gfunc psplaVec4CopyU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0    
    usv.q r000, 0($a1)
    jr $ra

gfunc psplaMat2CopyA
gfunc psplaVecVCopyA
    lv.q r000, 0($a0)
    sv.q r000, 0($a1)
    jr $ra

gfunc psplaVec2AddU
    singleOpVec2U vadd.p
    jr $ra

gfunc psplaVec3AddU
    singleOpVec3U vadd.t
    jr $ra

gfunc psplaMat2AddU
gfunc psplaVec4AddU
    singleOpVec4U vadd.q
    jr $ra

gfunc psplaMat2AddA
gfunc psplaVecVAddA
    singleOpVecVA vadd.q
    jr $ra

gfunc psplaVec2SubtractU
    singleOpVec2U vsub.p
    jr $ra

gfunc psplaVec3SubtractU
    singleOpVec3U vsub.t
    jr $ra

gfunc psplaMat2SubtractU
gfunc psplaVec4SubtractU
    singleOpVec4U vsub.q
    jr $ra

gfunc psplaMat2SubtractA
gfunc psplaVecVSubtractA
    singleOpVecVA vsub.q
    jr $ra

gfunc psplaVec2MultiplyU
    singleOpVec2U vmul.p
    jr $ra

gfunc psplaVec3MultiplyU
    singleOpVec3U vmul.t
    jr $ra

gfunc psplaVec4MultiplyU
    singleOpVec4U vmul.q
    jr $ra

gfunc psplaVecVMultiplyA
    singleOpVecVA vmul.q
    jr $ra

gfunc psplaVec2DivideU
    singleOpVec2U vdiv.p
    jr $ra

gfunc psplaVec3DivideU
    singleOpVec3U vdiv.t
    jr $ra

gfunc psplaVec4DivideU
    singleOpVec4U vdiv.q
    jr $ra

gfunc psplaVec2DivideA
    singleOpVecVA vdiv.p
    jr $ra

gfunc psplaVec3DivideA
    singleOpVecVA vdiv.t
    jr $ra

gfunc psplaVecVDivideA
gfunc psplaVec4DivideA
    singleOpVecVA vdiv.q
    jr $ra

gfunc psplaVec2MinimumU
    singleOpVec2U vmin.p
    jr $ra

gfunc psplaVec3MinimumU
    singleOpVec3U vmin.t
    jr $ra

gfunc psplaVec4MinimumU
    singleOpVec4U vmin.q
    jr $ra

gfunc psplaVecVMinimumA
    singleOpVecVA vmin.q
    jr $ra

gfunc psplaVec2MaximumU
    singleOpVec2U vmax.p
    jr $ra

gfunc psplaVec3MaximumU
    singleOpVec3U vmax.t
    jr $ra

gfunc psplaVec4MaximumU
    singleOpVec4U vmax.q
    jr $ra

gfunc psplaVecVMaximumA
    singleOpVecVA vmax.q
    jr $ra

gfunc psplaVec2AverageU
    singleOpScaVU vavg.p
    jr $ra

gfunc psplaVec3AverageU
    singleOpScaVU vavg.t
    jr $ra

gfunc psplaVec4AverageU
    singleOpScaVU vavg.q
    jr $ra

gfunc psplaVec2AverageA
    singleOpScaVA vavg.p
    jr $ra

gfunc psplaVec3AverageA
    singleOpScaVA vavg.t
    jr $ra

gfunc psplaVec4AverageA
    singleOpScaVA vavg.q
    jr $ra

gfunc psplaVec2SumU
    singleOpScaVU vfad.p
    jr $ra

gfunc psplaVec3SumU
    singleOpScaVU vfad.t
    jr $ra

gfunc psplaVec4SumU
    singleOpScaVU vfad.q
    jr $ra

gfunc psplaVec2SumA
    singleOpScaVA vfad.p
    jr $ra

gfunc psplaVec3SumA
    singleOpScaVA vfad.t
    jr $ra

gfunc psplaVec4SumA
    singleOpScaVA vfad.q
    jr $ra

gfunc psplaAbsoluteValue
    singleOpSca2Sca vabs.s
    jr $ra

gfunc psplaVec2AbsoluteValueU
    singleOpSVec2U vabs.p
    jr $ra

gfunc psplaVec3AbsoluteValueU
    singleOpSVec3U vabs.t
    jr $ra

gfunc psplaVec4AbsoluteValueU
    singleOpSVec4U vabs.q
    jr $ra

gfunc psplaVecVAbsoluteValueA
    singleOpSVecVA vabs.q
    jr $ra

gfunc psplaVec3CrossProductU
    singleOpVec3U vcrsp.t
    jr $ra

gfunc psplaVec3CrossProductA
    singleOpVecVA vcrsp.t
    jr $ra

gfunc psplaVec2ScaleU
    singleOpVec2ScaU vscl.p
    jr $ra

gfunc psplaVec3ScaleU
    singleOpVec3ScaU vscl.t
    jr $ra

gfunc psplaMat2ScaleU
gfunc psplaVec4ScaleU
    singleOpVec4ScaU vscl.q
    jr $ra

gfunc psplaMat2ScaleA
gfunc psplaVecVScaleA
    singleOpVecVScaA vscl.q
    jr $ra

gfunc psplaVec2DotProductU
    singleOpScaDVU vdot.p
    jr $ra

gfunc psplaVec3DotProductU
    singleOpScaDVU vdot.t
    jr $ra

gfunc psplaVec4DotProductU
    singleOpScaDVU vdot.q
    jr $ra

gfunc psplaVec2DotProductA
    singleOpScaDVA vdot.p
    jr $ra

gfunc psplaVec3DotProductA
    singleOpScaDVA vdot.t
    jr $ra

gfunc psplaVec4DotProductA
    singleOpScaDVA vdot.q
    jr $ra

gfunc psplaSquareRoot
    singleOpSca2Sca vsqrt.s
    jr $ra

gfunc psplaVec2SquareRootU
    singleOpSVec2U vsqrt.p
    jr $ra

gfunc psplaVec3SquareRootU
    singleOpSVec3U vsqrt.t
    jr $ra

gfunc psplaVec4SquareRootU
    singleOpSVec4U vsqrt.q
    jr $ra

gfunc psplaVec2SquareRootA
    singleOpSVecVA vsqrt.p
    jr $ra

gfunc psplaVec3SquareRootA
    singleOpSVecVA vsqrt.t
    jr $ra

gfunc psplaVecVSquareRootA
gfunc psplaVec4SquareRootA
    singleOpSVecVA vsqrt.q
    jr $ra

gfunc psplaVec2MagnitudeU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    vmul.p r001, r000, r000
    vfad.p s002, r001
    vsqrt.s s003, s002
    mfv $t0, s003
    mtc1 $t0, $f0
    jr $ra

gfunc psplaVec3MagnitudeU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    vmul.t r001, r000, r000
    vfad.t s002, r001
    vsqrt.s s003, s002
    mfv $t0, s003
    mtc1 $t0, $f0
    jr $ra

gfunc psplaQuatNormU
gfunc psplaVec4MagnitudeU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    vmul.q r001, r000, r000
    vfad.q s002, r001
    vsqrt.s s003, s002
    mfv $t0, s003
    mtc1 $t0, $f0
    jr $ra

gfunc psplaVec2MagnitudeA
    lv.q r000, 0($a0)
    vmul.p r001, r000, r000
    vfad.p s002, r001
    vsqrt.s s003, s002
    mfv $t0, s003
    mtc1 $t0, $f0
    jr $ra

gfunc psplaVec3MagnitudeA
    lv.q r000, 0($a0)
    vmul.t r001, r000, r000
    vfad.t s002, r001
    vsqrt.s s003, s002
    mfv $t0, s003
    mtc1 $t0, $f0
    jr $ra

gfunc psplaQuatNormA
gfunc psplaVec4MagnitudeA
    lv.q r000, 0($a0)
    vmul.q r001, r000, r000
    vfad.q s002, r001
    vsqrt.s s003, s002
    mfv $t0, s003
    mtc1 $t0, $f0
    jr $ra

gfunc psplaVec2NormalizeU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    vmul.p r001, r000, r000
    vfad.p s002, r001
    vsqrt.s s003, s002
    vfim.s s002, 1
    vdiv.s s013, s002, s003
    vscl.p r000, r000, s013
    svp s000, s010, $a1, 0
    jr $ra

gfunc psplaVec3NormalizeU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    vmul.t r001, r000, r000
    vfad.t s002, r001
    vsqrt.s s003, s002
    vfim.s s002, 1
    vdiv.s s013, s002, s003
    vscl.t r000, r000, s013
    svt s000, s010, s020, $a1, 0
    jr $ra

gfunc psplaQuatNormalizeU
gfunc psplaVec4NormalizeU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    vmul.p r001, r000, r000
    vfad.p s002, r001
    vsqrt.s s003, s002
    vfim.s s002, 1
    vdiv.s s013, s002, s003
    vscl.p r000, r000, s013
    usv.q r000, 0($a1)
    jr $ra

gfunc psplaVec2NormalizeA
    lv.q r000, 0($a0)
    vmul.p r001, r000, r000
    vfad.p s002, r001
    vsqrt.s s003, s002
    vfim.s s002, 1
    vdiv.s s013, s002, s003
    vscl.p r000, r000, s013
    sv.q r000, 0($a1)
    jr $ra

gfunc psplaVec3NormalizeA
    lv.q r000, 0($a0)
    vmul.t r001, r000, r000
    vfad.t s002, r001
    vsqrt.s s003, s002
    vfim.s s002, 1
    vdiv.s s013, s002, s003
    vscl.t r000, r000, s013
    sv.q r000, 0($a1)
    jr $ra

gfunc psplaQuatNormalizeA
gfunc psplaVec4NormalizeA
    lv.q r000, 0($a0)
    vmul.q r001, r000, r000
    vfad.q s002, r001
    vsqrt.s s003, s002
    vfim.s s002, 1
    vdiv.s s013, s002, s003
    vscl.q r000, r000, s013
    sv.q r000, 0($a1)
    jr $ra

gfunc psplaVec2RoundU
    truncateOpVec2U vf2in.p
    jr $ra

gfunc psplaVec3RoundU
    truncateOpVec3U vf2in.t
    jr $ra

gfunc psplaVec4RoundU
    truncateOpVec4U vf2in.q
    jr $ra

gfunc psplaVecVRoundA
    truncateOpVecVA vf2in.q
    jr $ra

gfunc psplaVec2FloorU
    truncateOpVec2U vf2iz.p
    jr $ra

gfunc psplaVec3FloorU
    truncateOpVec3U vf2iz.t
    jr $ra

gfunc psplaVec4FloorU
    truncateOpVec4U vf2iz.q
    jr $ra

gfunc psplaVecVFloorA
    truncateOpVecVA vf2iz.q
    jr $ra

gfunc psplaVec2CeilingU
    truncateOpVec2U vf2iu.p
    jr $ra

gfunc psplaVec3CeilingU
    truncateOpVec3U vf2iu.t
    jr $ra

gfunc psplaVec4CeilingU
    truncateOpVec4U vf2iu.q
    jr $ra

gfunc psplaVecVCeilingA
    truncateOpVecVA vf2iu.q
    jr $ra

gfunc psplaSine
    singleOpSca2Sca vsin.s
    jr $ra

gfunc psplaCosine
    singleOpSca2Sca vcos.s
    jr $ra

gfunc psplaVec2SineU
    singleOpSVec2U vsin.p
    jr $ra

gfunc psplaVec3SineU
    singleOpSVec3U vsin.t
    jr $ra

gfunc psplaVec4SineU
    singleOpSVec4U vsin.q
    jr $ra

gfunc psplaVec2SineA
    singleOpSVecVA vsin.p
    jr $ra

gfunc psplaVec3SineA
    singleOpSVecVA vsin.t
    jr $ra

gfunc psplaVecVSineA
gfunc psplaVec4SineA
    singleOpSVecVA vsin.q
    jr $ra

gfunc psplaVec2CosineU
    singleOpSVec2U vcos.p
    jr $ra

gfunc psplaVec3CosineU
    singleOpSVec3U vcos.t
    jr $ra

gfunc psplaVec4CosineU
    singleOpSVec4U vcos.q
    jr $ra

gfunc psplaVec2CosineA
    singleOpSVecVA vcos.p
    jr $ra

gfunc psplaVec3CosineA
    singleOpSVecVA vcos.t
    jr $ra

gfunc psplaVecVCosineA
gfunc psplaVec4CosineA
    singleOpSVecVA vcos.q
    jr $ra

gfunc psplaArcsine
    mfc1 $t0, $f12
    mtv $t0, s000
    vfim.s s001, 0    
    vfim.s s002, 0
    vfim.s s003, 30
    vfim.s s020, 1
Arcsine_loop:
    vcmp.s lt, s002, s003
    vadd.s s002, s002, s020
    vsin.s s010, s001
    vsub.s s010, s010, s000
    vcos.s s011, s001
    vdiv.s s012, s010, s011
    vsub.s s001, s001, s012
    bvtl 0, Arcsine_loop
    mfv $t0, s001
    mtc1 $t0, $f0
    jr $ra

gfunc psplaArccosine
    mfc1 $t0, $f12
    mtv $t0, s000
    vfim.s s001, 1    
    vfim.s s002, 0
    vfim.s s003, 30
    vfim.s s020, 1
Arccosine_loop:
    vcmp.s lt, s002, s003
    vadd.s s002, s002, s020
    vcos.s s010, s001
    vsub.s s010, s010, s000
    vsin.s s011, s001
    vneg.s s011, s011
    vdiv.s s012, s010, s011
    vsub.s s001, s001, s012
    bvtl 0, Arccosine_loop
    mfv $t0, s001
    mtc1 $t0, $f0
    jr $ra

gfunc psplaVec2NegateU
    singleOpSVec2U vneg.p
    jr $ra

gfunc psplaVec3NegateU
    singleOpSVec3U vneg.t
    jr $ra

gfunc psplaVec4NegateU
    singleOpSVec4U vneg.q
    jr $ra

gfunc psplaVecVNegateA
    singleOpSVecVA vneg.q
    jr $ra

gfunc psplaVec2EqualsU
    comparisonOpVecU vcmp.p, eq
    jr $ra

gfunc psplaVec3EqualsU
    comparisonOpVecU vcmp.t, eq
    jr $ra

gfunc psplaVec4EqualsU
    comparisonOpVecU vcmp.q, eq
    jr $ra

gfunc psplaVec2EqualsA
    comparisonOpVecA vcmp.p, eq
    jr $ra

gfunc psplaVec3EqualsA
    comparisonOpVecA vcmp.t, eq
    jr $ra

gfunc psplaVec4EqualsA
    comparisonOpVecA vcmp.q, eq
    jr $ra

gfunc psplaVec2LessThanU
    comparisonOpVecU vcmp.p, lt
    jr $ra

gfunc psplaVec3LessThanU
    comparisonOpVecU vcmp.t, lt
    jr $ra

gfunc psplaVec4LessThanU
    comparisonOpVecU vcmp.q, lt
    jr $ra

gfunc psplaVec2LessThanA
    comparisonOpVecA vcmp.p, lt
    jr $ra

gfunc psplaVec3LessThanA
    comparisonOpVecA vcmp.t, lt
    jr $ra

gfunc psplaVec4LessThanA
    comparisonOpVecA vcmp.q, lt
    jr $ra

gfunc psplaVec2LessThanEqualU
    comparisonOpVecU vcmp.p, le
    jr $ra

gfunc psplaVec3LessThanEqualU
    comparisonOpVecU vcmp.t, le
    jr $ra

gfunc psplaVec4LessThanEqualU
    comparisonOpVecU vcmp.q, le
    jr $ra

gfunc psplaVec2LessThanEqualA
    comparisonOpVecA vcmp.p, le
    jr $ra

gfunc psplaVec3LessThanEqualA
    comparisonOpVecA vcmp.t, le
    jr $ra

gfunc psplaVec4LessThanEqualA
    comparisonOpVecA vcmp.q, le
    jr $ra

gfunc psplaVec2GreaterThanU
    comparisonOpVecU vcmp.p, gt
    jr $ra

gfunc psplaVec3GreaterThanU
    comparisonOpVecU vcmp.t, gt
    jr $ra

gfunc psplaVec4GreaterThanU
    comparisonOpVecU vcmp.q, gt
    jr $ra

gfunc psplaVec2GreaterThanA
    comparisonOpVecA vcmp.p, gt
    jr $ra

gfunc psplaVec3GreaterThanA
    comparisonOpVecA vcmp.t, gt
    jr $ra

gfunc psplaVec4GreaterThanA
    comparisonOpVecA vcmp.q, gt
    jr $ra

gfunc psplaVec2GreaterThanEqualU
    comparisonOpVecU vcmp.p, ge
    jr $ra

gfunc psplaVec3GreaterThanEqualU
    comparisonOpVecU vcmp.t, ge
    jr $ra

gfunc psplaVec4GreaterThanEqualU
    comparisonOpVecU vcmp.q, ge
    jr $ra

gfunc psplaVec2GreaterThanEqualA
    comparisonOpVecA vcmp.p, ge
    jr $ra

gfunc psplaVec3GreaterThanEqualA
    comparisonOpVecA vcmp.t, ge
    jr $ra

gfunc psplaVec4GreaterThanEqualA
    comparisonOpVecA vcmp.q, ge
    jr $ra

gfunc psplaVec2CompareU
    singleOpVec2U vscmp.p
    jr $ra

gfunc psplaVec3CompareU
    singleOpVec3U vscmp.t
    jr $ra

gfunc psplaVec4CompareU
    singleOpVec4U vscmp.q
    jr $ra

gfunc psplaVecVCompareA
    singleOpVecVA vscmp.q
    jr $ra

gfunc psplaVec2LerpU
    pushf $f0
    ulv.q r000, 0($a0)
    ulv.q r001, 0($a1)
    popf $f0
    mfc1 $t0, $f12
    mtv $t0, s002
    vfim.s s012, 1
    vscl.p r001, r001, s002 
    vsub.s s012, s012, s002
    vscl.p r000, r000, s012
    vadd.p r003, r000, r001
    svp s003, s013, $a2, 0
    jr $ra

gfunc psplaVec3LerpU
    pushf $f0
    ulv.q r000, 0($a0)
    ulv.q r001, 0($a1)
    popf $f0
    mfc1 $t0, $f12
    mtv $t0, s002
    vfim.s s012, 1
    vscl.t r001, r001, s002 
    vsub.s s012, s012, s002
    vscl.t r000, r000, s012
    vadd.t r003, r000, r001
    svt s003, s013, s023, $a2, 0
    jr $ra

gfunc psplaQuatLerpU
gfunc psplaVec4LerpU
    pushf $f0
    ulv.q r000, 0($a0)
    ulv.q r001, 0($a1)
    popf $f0
    mfc1 $t0, $f12
    mtv $t0, s002
    vfim.s s012, 1
    vscl.q r001, r001, s002 
    vsub.s s012, s012, s002
    vscl.q r000, r000, s012
    vadd.q r003, r000, r001
    usv.q r003, 0($a2)
    jr $ra

gfunc psplaQuatLerpA
gfunc psplaVecVLerpA
    lv.q r000, 0($a0)
    lv.q r001, 0($a1)
    mfc1 $t0, $f12
    mtv $t0, s002
    vfim.s s012, 1   
    vscl.q r001, r001, s002 
    vsub.s s012, s012, s002
    vscl.q r000, r000, s012
    vadd.q r003, r000, r001
    sv.q r003, 0($a2)
    jr $ra

gfunc psplaVec2ClampU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    mfc1 $t0, $f12
    mtv $t0, s002
    mfc1 $t1, $f13
    mtv $t1, s003
    vmov.s s012, s002
    vmov.s s013, s003
    vcmp.p lt, r000, r002
    vcmovt.p r000, r002, 6
    vcmp.p gt, r000, r003
    vcmovt.p r000, r003, 6
    svp s000, s010, $a1, 0
    jr $ra

gfunc psplaVec3ClampU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    mfc1 $t0, $f12
    mtv $t0, s002
    mfc1 $t1, $f13
    mtv $t1, s003
    vmov.t r002, r002[x,x,x]
    vmov.t r003, r003[x,x,x]
    vcmp.t lt, r000, r002
    vcmovt.t r000, r002, 6
    vcmp.t gt, r000, r003
    vcmovt.t r000, r003, 6
    svt s000, s010, s020, $a1, 0
    jr $ra

gfunc psplaVec4ClampU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    mfc1 $t0, $f12
    mtv $t0, s002
    mfc1 $t1, $f13
    mtv $t1, s003
    vmov.q r002, r002[x,x,x,x]
    vmov.q r003, r003[x,x,x,x]
    vcmp.q lt, r000, r002
    vcmovt.q r000, r002, 6
    vcmp.q gt, r000, r003
    vcmovt.q r000, r003, 6
    usv.q r000, 0($a1)
    jr $ra

gfunc psplaVecVClampA
    lv.q r000, 0($a0)
    mfc1 $t0, $f12
    mtv $t0, s002
    mfc1 $t1, $f13
    mtv $t1, s003
    vmov.q r002, r002[x,x,x,x]
    vmov.q r003, r003[x,x,x,x]
    vcmp.q lt, r000, r002
    vcmovt.q r000, r002, 6
    vcmp.q gt, r000, r003
    vcmovt.q r000, r003, 6
    sv.q r000, 0($a1)
    jr $ra

gfunc psplaVec2ReorderU
    vfim.s s003, 4
    pushf $f0
    ulv.q r000, 0($a1)
    popf $f0
    vscl.p r000, r000, s003
    mfv $t0, s000
    mfv $t1, s010
    add $t0, $t0, $a0
    add $t1, $t1, $a0
    lv.s s001, 0($t0)
    lv.s s011, 0($t1)
    svp s001, s011, $a2, 0
    jr $ra

gfunc psplaVec3ReorderU
    vfim.s s003, 4
    pushf $f0
    ulv.q r000, 0($a1)
    popf $f0
    vscl.t r000, r000, s003
    mfv $t0, s000
    mfv $t1, s010
    mfv $t2, s020
    add $t0, $t0, $a0
    add $t1, $t1, $a0
    add $t2, $t2, $a0
    lv.s s001, 0($t0)
    lv.s s011, 0($t1)
    lv.s s021, 0($t2)
    svt s001, s011, s021, $a2, 0
    jr $ra

gfunc psplaVec4ReorderU
    vfim.s s003, 4
    pushf $f0
    ulv.q r000, 0($a1)
    popf $f0
    vscl.q r000, r000, s003
    mfv $t0, s000
    mfv $t1, s010
    mfv $t2, s020
    mfv $t3, s030
    add $t0, $t0, $a0
    add $t1, $t1, $a0
    add $t2, $t2, $a0
    add $t3, $t3, $a0
    lv.s s001, 0($t0)
    lv.s s011, 0($t1)
    lv.s s021, 0($t2)
    lv.s s031, 0($t3)
    usv.q r001, 0($a2)
    jr $ra

gfunc psplaVec2ReorderA
    vfim.s s003, 4
    lv.q r000, 0($a1)
    vscl.p r000, r000, s003
    mfv $t0, s000
    mfv $t1, s010
    add $t0, $t0, $a0
    add $t1, $t1, $a0
    lv.s s001, 0($t0)
    lv.s s011, 0($t1)
    sv.q r001, 0($a2)
    jr $ra

gfunc psplaVec3ReorderA
    vfim.s s003, 4
    lv.q r000, 0($a1)
    vscl.t r000, r000, s003
    mfv $t0, s000
    mfv $t1, s010
    mfv $t2, s020
    add $t0, $t0, $a0
    add $t1, $t1, $a0
    add $t2, $t2, $a0
    lv.s s001, 0($t0)
    lv.s s011, 0($t1)
    lv.s s021, 0($t2)
    sv.q r001, 0($a2)
    jr $ra

gfunc psplaVec4ReorderA
    vfim.s s003, 4
    lv.q r000, 0($a1)
    vscl.q r000, r000, s003
    mfv $t0, s000
    mfv $t1, s010
    mfv $t2, s020
    mfv $t3, s030
    add $t0, $t0, $a0
    add $t1, $t1, $a0
    add $t2, $t2, $a0
    add $t3, $t3, $a0
    lv.s s001, 0($t0)
    lv.s s011, 0($t1)
    lv.s s021, 0($t2)
    lv.s s031, 0($t3)
    sv.q r001, 0($a2)
    jr $ra

gfunc psplaRandom
    vrndf1.s s000
    vsub.s s000, s000, s000[1]
    mfv $t0, s000
    mtc1 $t0, $f0
    jr $ra

gfunc psplaVec2RandomU
    vrndf1.p r000
    vsub.p r000, r000, r000[1,1]
    svp s000, s010, $a0, 0
    jr $ra

gfunc psplaVec3RandomU
    vrndf1.t r000
    vsub.t r000, r000, r000[1,1,1]
    svt s000, s010, s020, $a0, 0
    jr $ra

gfunc psplaVec4RandomU
    vrndf1.q r000
    vsub.q r000, r000, r000[1,1,1,1]
    usv.q r000, 0($a0)
    jr $ra

gfunc psplaVec2RandomA
    vrndf1.p r000
    vsub.p r000, r000, r000[1,1]
    sv.q r000, 0($a0)
    jr $ra

gfunc psplaVec3RandomA
    vrndf1.t r000
    vsub.t r000, r000, r000[1,1,1]
    sv.q r000, 0($a0)
    jr $ra

gfunc psplaVecVRandomA
gfunc psplaVec4RandomA
    vrndf1.q r000
    vsub.q r000, r000, r000[1,1,1,1]
    sv.q r000, 0($a0)
    jr $ra

gfunc psplaRandomSeed
    mtv $a0, s000
    vrnds.s s000
    jr $ra

gfunc psplaVec2ReflectU
    pushf $f0
    ulv.q r000, 0($a0)
    ulv.q r001, 0($a1)
    popf $f0
    vfim.s s003, 2
    vdot.p s002, r000, r001
    vscl.p r001, r001, s002
    vscl.p r001, r001, s003
    vsub.p r000, r000, r001
    svp s000, s010, $a2, 0
    jr $ra

gfunc psplaVec3ReflectU
    pushf $f0
    ulv.q r000, 0($a0)
    ulv.q r001, 0($a1)
    popf $f0
    vfim.s s003, 2
    vdot.t s002, r000, r001
    vscl.t r001, r001, s002
    vscl.t r001, r001, s003
    vsub.t r000, r000, r001
    svt s000, s010, s020, $a2, 0
    jr $ra

gfunc psplaVec4ReflectU
    pushf $f0
    ulv.q r000, 0($a0)
    ulv.q r001, 0($a1)
    popf $f0
    vfim.s s003, 2
    vdot.q s002, r000, r001
    vscl.q r001, r001, s002
    vscl.q r001, r001, s003
    vsub.q r000, r000, r001
    usv.q r000, 0($a2)
    jr $ra

gfunc psplaVec2ReflectA
    lv.q r000, 0($a0)
    lv.q r001, 0($a1)
    vfim.s s003, 2
    vdot.p s002, r000, r001
    vscl.p r001, r001, s002
    vscl.p r001, r001, s003
    vsub.p r000, r000, r001
    sv.q r000, 0($a2)
    jr $ra

gfunc psplaVec3ReflectA
    lv.q r000, 0($a0)
    lv.q r001, 0($a1)
    vfim.s s003, 2
    vdot.t s002, r000, r001
    vscl.t r001, r001, s002
    vscl.t r001, r001, s003
    vsub.t r000, r000, r001
    sv.q r000, 0($a2)
    jr $ra

gfunc psplaVec4ReflectA
    lv.q r000, 0($a0)
    lv.q r001, 0($a1)
    vfim.s s003, 2
    vdot.q s002, r000, r001
    vscl.q r001, r001, s002
    vscl.q r001, r001, s003
    vsub.q r000, r000, r001
    sv.q r000, 0($a2)
    jr $ra

gfunc psplaVec3RotationMatrixU
    pushf $f0
    ulv.q r001, 0($a0)
    popf $f0
    vsin.t r002, r001
    vcos.t r003, r001
    vmidt.q m100
    vmidt.q m200
    vmidt.q m300
    vmov.q c110[m, , ,m], c000[0,w,z,0]
    vmov.q c120[m, , ,m], c000[0,-z,w,0]
    vmov.q c200[ ,m, ,m], c010[w,0,-z,0]
    vmov.q c220[ ,m, ,m], c010[z,0,w,0]
    vmov.q c300[ , ,m,m], c020[w,z,0,0]
    vmov.q c310[ , ,m,m], c020[-z,w,0,0]
    vmmul.t m400, m100, m200
    vmmul.t m500, m400, m300
    sv.q r500, 0($a1)
    usv.q r501, 12($a1)
    usv.q r502, 24($a1)
    jr $ra

gfunc psplaVec3RotationMatrixA
    lv.q r001, 0($a0)
    vsin.t r002, r001
    vcos.t r003, r001
    vmidt.q m100
    vmidt.q m200
    vmidt.q m300
    vmov.q c110[m, , ,m], c000[0,w,z,0]
    vmov.q c120[m, , ,m], c000[0,-z,w,0]
    vmov.q c200[ ,m, ,m], c010[w,0,-z,0]
    vmov.q c220[ ,m, ,m], c010[z,0,w,0]
    vmov.q c300[ , ,m,m], c020[w,z,0,0]
    vmov.q c310[ , ,m,m], c020[-z,w,0,0]
    vmmul.t m400, m100, m200
    vmmul.t m500, m400, m300
    sv.q r500, 0($a1)
    usv.q r501, 12($a1)
    usv.q r502, 24($a1)
    jr $ra

gfunc psplaVec3RotationQuaternionU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    vfim.s s003, 0.5
    vscl.t r000, r000, s003
    vsin.t r001, r000
    vcos.t r002, r000
    vmov.q c100, c000[z,y,z,y]
    vmov.q c110, c010[z,z,y,y]
    vmov.q c120, c020[z,z,z,z]
    vmul.q c200, c100, c110
    vmul.q c200, c200, c120
    vmov.q c100, c000[y,z,y,z]
    vmov.q c110, c010[y,y,z,z]
    vmov.q c120, c020[y,y,y,y] 
    vmul.q c210, c100, c110
    vmul.q c210, c210, c120
    vadd.q c220, c200, c210[-x,y,-z,w]
    usv.q c220, 0($a1) 
    jr $ra

gfunc psplaVec3RotationQuaternionA
    lv.q r000, 0($a0)
    vfim.s s003, 0.5
    vscl.t r000, r000, s003
    vsin.t r001, r000
    vcos.t r002, r000
    vmov.q c100, c000[z,y,z,y]
    vmov.q c110, c010[z,z,y,y]
    vmov.q c120, c020[z,z,z,z]
    vmul.q c200, c100, c110
    vmul.q c200, c200, c120
    vmov.q c100, c000[y,z,y,z]
    vmov.q c110, c010[y,y,z,z]
    vmov.q c120, c020[y,y,y,y] 
    vmul.q c210, c100, c110
    vmul.q c210, c210, c120
    vadd.q c220, c200, c210[-x,y,-z,w]
    sv.q c220, 0($a1) 
    jr $ra

gfunc psplaQuatMultiplyU
    pushf $f0
    ulv.q r000, 0($a0)
    ulv.q r001, 0($a1)
    popf $f0
    vdot.t s002, r010, r011
    vcrsp.t r012, r010, r011
    vmul.s s100, s000, s001
    vsub.s s100, s100, s002
    vscl.t r110, r010, s001
    vscl.t r111, r011, s000
    vadd.t r110, r110, r111
    vadd.t r110, r110, r012
    usv.q r100, 0($a2)
    jr $ra

gfunc psplaQuatMultiplyA
    lv.q r000, 0($a0)
    lv.q r001, 0($a1)
    vdot.t s002, r010, r011
    vcrsp.t r012, r010, r011
    vmul.s s100, s000, s001
    vsub.s s100, s100, s002
    vscl.t r110, r010, s001
    vscl.t r111, r011, s000
    vadd.t r110, r110, r111
    vadd.t r110, r110, r012
    sv.q r100, 0($a2)
    jr $ra

gfunc psplaQuatIdentityU
    vidt.q r000
    usv.q r000, 0($a0)
    jr $ra

gfunc psplaQuatIdentityA
    vidt.q r000
    sv.q r000, 0($a0)
    jr $ra

gfunc psplaQuatConjugateU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    vneg.t r010, r010
    usv.q r000, 0($a1)

gfunc psplaQuatConjugateA
    lv.q r000, 0($a0)
    vneg.t r010, r010
    sv.q r000, 0($a1)
    jr $ra

gfunc psplaQuatRotationMatrixU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    vfim.s s001, 2
    vfim.s s011, 1
    vmul.q r100, r000[x,y,y,0], r000[x,z,w,0]
    vmul.q r101, r000[y,x,x,0], r000[y,w,z,0]
    vmul.q r200, r000[y,x,z,0], r000[z,x,w,0]
    vmul.q r201, r000[x,z,x,0], r000[w,z,y,0]
    vmul.q r300, r000[y,z,x,0], r000[w,w,x,0]
    vmul.q r301, r000[x,x,w,0], r000[z,y,w,0]
    vadd.t r102, r100, r101[x,-y,z]
    vadd.t r202, r200, r201[x,y,-z]
    vadd.t r302, r300, r301[-x,y,z]
    vscl.t r102, r102, s001
    vscl.t r202, r202, s001
    vscl.t r302, r302, s001
    vsub.s s102, s102, s011
    vsub.s s212, s212, s011
    vsub.s s322, s322, s011
    usv.q r102, 0($a1)
    usv.q r202, 12($a1)
    svt s302, s312, s322, $a1, 24
    jr $ra

gfunc psplaQuatRotationMatrixA
    lv.q r000, 0($a0)
    vfim.s s001, 2
    vfim.s s011, 1
    vmul.q r100, r000[x,y,y,0], r000[x,z,w,0]
    vmul.q r101, r000[y,x,x,0], r000[y,w,z,0]
    vmul.q r200, r000[y,x,z,0], r000[z,x,w,0]
    vmul.q r201, r000[x,z,x,0], r000[w,z,y,0]
    vmul.q r300, r000[y,z,x,0], r000[w,w,x,0]
    vmul.q r301, r000[x,x,w,0], r000[z,y,w,0]
    vadd.t r102, r100, r101[x,-y,z]
    vadd.t r202, r200, r201[x,y,-z]
    vadd.t r302, r300, r301[-x,y,z]
    vscl.t r102, r102, s001
    vscl.t r202, r202, s001
    vscl.t r302, r302, s001
    vsub.s s102, s102, s011
    vsub.s s212, s212, s011
    vsub.s s322, s322, s011
    sv.q r102, 0($a1)
    usv.q r202, 12($a1)
    svt s302, s312, s322, $a1, 24
    jr $ra

gfunc psplaMat3AddU
    singleOpMat3U vadd
    jr $ra

gfunc psplaMat4AddU
    singleOpMat4U vadd
    jr $ra

gfunc psplaMat3AddA
    singleOpMat3A vadd
    jr $ra

gfunc psplaMat4AddA
    singleOpMat4A vadd
    jr $ra

gfunc psplaMat3SubtractU
    singleOpMat3U vsub
    jr $ra

gfunc psplaMat4SubtractU
    singleOpMat4U vsub
    jr $ra

gfunc psplaMat3SubtractA
    singleOpMat3A vsub
    jr $ra

gfunc psplaMat4SubtractA
    singleOpMat4A vsub
    jr $ra

gfunc psplaMat3ScaleU
    pushf $f0
    lm3u 0, $a0
    popf $f0
    mfc1 $t0, $f12
    mtv $t0, s200
    vmscl.t m100, m000, s200
    usv.q r100, 0($a1)
    usv.q r101, 12($a1)
    svt s102, s112, s122, $a1, 24
    jr $ra

gfunc psplaMat4ScaleU
    pushf $f0
    lm4u 0, $a0
    popf $f0
    mfc1 $t0, $f12
    mtv $t0, s200
    vmscl.q m100, m000, s200
    usv.q r100, 0($a1)
    usv.q r101, 16($a1)
    usv.q r102, 32($a1)
    usv.q r103, 48($a1)
    jr $ra

gfunc psplaMat3ScaleA
    lm3a 0, $a0
    mfc1 $t0, $f12
    mtv $t0, s200
    vmscl.t m100, m000, s200
    sv.q r100, 0($a1)
    usv.q r101, 12($a1)
    usv.q r102, 24($a1) 
    jr $ra

gfunc psplaMat4ScaleA
    lm4a 0, $a0
    mfc1 $t0, $f12
    mtv $t0, s200
    vmscl.q m100, m000, s200
    sv.q r100, 0($a1)
    sv.q r101, 16($a1)
    sv.q r102, 32($a1)
    sv.q r103, 48($a1)
    jr $ra

gfunc psplaMat2MultiplyU
    sub $sp, $sp, 8
    s.s $f0, 4($sp)
    s.s $f4, 0($sp)
    lm2u 0, $a0
    lm2u 1, $a1
    l.s $f4, 0($sp)
    l.s $f0, 4($sp)
    add $sp, $sp, 8
    vmmul.p m200, m000, m100
    vmov.p r220, r201
    usv.q r200, 0($a2)
    jr $ra

gfunc psplaMat3MultiplyU
    sub $sp, $sp, 8
    s.s $f0, 4($sp)
    s.s $f4, 0($sp)
    lm3u 0, $a0
    lm3u 1, $a1
    l.s $f4, 0($sp)
    l.s $f0, 4($sp)
    add $sp, $sp, 8
    vmmul.t m200, m000, m100
    usv.q r200, 0($a2)
    usv.q r201, 12($a2)
    svt s202, s212, s222, $a2, 24
    jr $ra

gfunc psplaMat4MultiplyU
    sub $sp, $sp, 8
    s.s $f0, 4($sp)
    s.s $f4, 0($sp)
    lm4u 0, $a0
    lm4u 1, $a1
    l.s $f4, 0($sp)
    l.s $f0, 4($sp)
    add $sp, $sp, 8
    vmmul.q m200, m000, m100
    usv.q r200, 0($a2)
    usv.q r201, 16($a2)
    usv.q r202, 32($a2)
    usv.q r203, 48($a2)
    jr $ra

gfunc psplaMat2MultiplyA
    lm2a 0, $a0
    lm2a 1, $a1
    vmmul.p m200, m000, m100
    vmov.p r220, r201
    sv.q r200, 0($a2)
    jr $ra

gfunc psplaMat3MultiplyA
    lm3a 0, $a0
    lm3a 1, $a1
    vmmul.t m200, m000, m100
    sv.q r200, 0($a2)
    usv.q r201, 12($a2)
    usv.q r202, 24($a2)
    jr $ra

gfunc psplaMat4MultiplyA
    lm4a 0, $a0
    lm4a 1, $a1
    vmmul.q m200, m000, m100
    sv.q r200, 0($a2)
    sv.q r201, 16($a2)
    sv.q r202, 32($a2)
    sv.q r203, 48($a2)
    jr $ra

gfunc psplaMat2IdentityU
    vmidt.p m000
    vmov.p r020, r001
    usv.q r000, 0($a0)
    jr $ra

gfunc psplaMat3IdentityU
    vmidt.t m000
    usv.q r000, 0($a0)
    usv.q r001, 12($a0)
    svt s002, s012, s022, $a0, 24
    jr $ra

gfunc psplaMat4IdentityU
    vmidt.q m000
    usv.q r000, 0($a0)
    usv.q r001, 16($a0)
    usv.q r002, 32($a0)
    usv.q r003, 48($a0)
    jr $ra

gfunc psplaMat2IdentityA
    vmidt.p m000
    vmov.p r020, r001
    sv.q r000, 0($a0)
    jr $ra

gfunc psplaMat3IdentityA
    vmidt.t m000
    sv.q r000, 0($a0)
    usv.q r001, 12($a0)
    usv.q r002, 24($a0)
    jr $ra

gfunc psplaMat4IdentityA
    vmidt.q m000
    sv.q r000, 0($a0)
    sv.q r001, 16($a0)
    sv.q r002, 32($a0)
    sv.q r003, 48($a0)
    jr $ra

gfunc psplaMat2TransposeU
    pushf $f0
    ulv.q r000, 0($a0)
    popf $f0
    vmov.q r000, r000[x,z,y,w]
    usv.q r000, 0($a1)
    jr $ra

gfunc psplaMat3TransposeU
    pushf $f0
    lm3u 0, $a0
    popf $f0
    vmov.t c100, r000
    vmov.t c110, r001
    vmov.t c120, r002
    usv.q r100, 0($a1)
    usv.q r101, 12($a1)
    svt s102, s112, s122, $a1, 24
    jr $ra

gfunc psplaMat4TransposeU
    pushf $f0
    lm4u 0, $a0
    popf $f0
    vmov.q c100, r000
    vmov.q c110, r001
    vmov.q c120, r002
    vmov.q c130, r003
    usv.q r100, 0($a1)
    usv.q r101, 16($a1)
    usv.q r102, 32($a1)
    usv.q r103, 48($a1)
    jr $ra

gfunc psplaMat2DeterminantU
    pushf $f28
    ulv.q r700, 0($a0)
    popf $f28
    mat2Determinant 00, 10, 20, 30, s100
    mfv $t0, s100
    mtc1 $t0, $f0
    jr $ra

gfunc psplaMat3DeterminantU
    pushf $f28
    lm3u 7, $a0
    popf $f28
    mat3Determinant 01, 11, 21, 02, 12, 22, x, y, z, 00, s103
    mfv $t0, s103
    mtc1 $t0, $f0
    jr $ra

gfunc psplaMat4DeterminantU
    pushf $f28
    lm4u 7, $a0
    popf $f28
    mat4Determinant 02, 12, 22, 32, 03, 13, 23, 33, s300
    mfv $t0, s300
    mtc1 $t0, $f0
    jr $ra

gfunc psplaMat2DeterminantA
    lv.q r700, 0($a0)
    mat2Determinant 00, 10, 20, 30, s100
    mfv $t0, s100
    mtc1 $t0, $f0
    jr $ra

gfunc psplaMat3DeterminantA
    lm3a 7, $a0
    mat3Determinant 01, 11, 21, 02, 12, 22, x, y, z, 00, s103
    mfv $t0, s103
    mtc1 $t0, $f0
    jr $ra

gfunc psplaMat4DeterminantA
    lm4a 7, $a0
    mat4Determinant 02, 12, 22, 32, 03, 13, 23, 33, s300
    mfv $t0, s300
    mtc1 $t0, $f0
    jr $ra

gfunc psplaMat2InverseU
    mfc1 $t0, $f12
    mtv $t0, s100
    pushf $f4
    ulv.q r101, 0($a0)
    popf $f4
    vfim.s s110, 1
    vdiv.s s120, s110, s100
    vscl.q r101, r101, s120
    vmov.q r101, r101[w,-y,-z,x]
    usv.q r101, 0($a1)
    jr $ra

gfunc psplaMat3InverseU
    pushf $f28
    lm3u 7, $a0
    popf $f28
    mat2Determinant 11, 21, 12, 22, s100
    mat2Determinant 01, 21, 02, 22, s110
    mat2Determinant 01, 11, 02, 12, s120
    mat2Determinant 10, 20, 12, 22, s101
    mat2Determinant 00, 20, 02, 22, s111
    mat2Determinant 00, 10, 02, 12, s121
    mat2Determinant 10, 20, 11, 21, s102
    mat2Determinant 00, 20, 01, 21, s112
    mat2Determinant 00, 10, 01, 11, s122
    vmov.t c200, r100[x,-y,z]
    vmov.t c210, r101[-x,y,-z]
    vmov.t c220, r102[x,-y,z]
    mfc1 $t0, $f12
    mtv $t0, s300
    vfim.s s310, 1
    vdiv.s s320, s310, s300
    vmscl.t m200, m200, s320
    usv.q r200, 0($a1)
    usv.q r201, 12($a1)
    svt s202, s212, s222, $a1, 24
    jr $ra

gfunc psplaMat4InverseU
    pushf $f28
    lm4u 7, $a0
    popf $f28
    mat3Determinant 12, 22, 32, 13, 23, 33, y, z, w, 01, s200
    mat3Determinant 02, 22, 32, 03, 23, 33, x, z, w, 01, s210
    mat3Determinant 02, 12, 32, 03, 13, 33, x, y, w, 01, s220
    mat3Determinant 02, 12, 22, 03, 13, 23, x, y, z, 01, s230
    mat3Determinant 12, 22, 32, 13, 23, 33, y, z, w, 00, s201
    mat3Determinant 02, 22, 32, 03, 23, 33, x, z, w, 00, s211
    mat3Determinant 02, 12, 32, 03, 13, 33, x, y, w, 00, s221
    mat3Determinant 02, 12, 22, 03, 13, 23, x, y, z, 00, s231
    mat3Determinant 11, 21, 31, 13, 23, 33, y, z, w, 00, s202
    mat3Determinant 01, 21, 31, 03, 23, 33, x, z, w, 00, s212
    mat3Determinant 01, 11, 31, 03, 13, 33, x, y, w, 00, s222
    mat3Determinant 01, 11, 21, 03, 13, 23, x, y, z, 00, s232
    mat3Determinant 11, 21, 31, 12, 22, 32, y, z, w, 00, s203
    mat3Determinant 01, 21, 31, 02, 22, 32, x, z, w, 00, s213
    mat3Determinant 01, 11, 31, 02, 12, 32, x, y, w, 00, s223
    mat3Determinant 01, 11, 11, 02, 12, 22, x, y, z, 00, s233
    vmov.q c300, r200[x,-y,z,-w]
    vmov.q c310, r201[-x,y,-z,w]
    vmov.q c320, r202[x,-y,z,-w]
    vmov.q c330, r203[-x,y,-z,w]
    mfc1 $t0, $f12
    mtv $t0, s400
    vfim.s s410, 1
    vdiv.s s420, s410, s400
    vmscl.q m300, m300, s420
    usv.q r300, 0($a1)
    usv.q r301, 16($a1)
    usv.q r302, 32($a1)
    usv.q r303, 48($a1)
    jr $ra

gfunc psplaMat2InverseA
    mfc1 $t0, $f12
    mtv $t0, s100
    lv.q r101, 0($a0)
    vfim.s s110, 1
    vdiv.s s120, s110, s100
    vscl.q r101, r101, s120
    vmov.q r101, r101[w,-y,-z,x]
    sv.q r101, 0($a1)
    jr $ra

gfunc psplaMat3InverseA
    lm3a 7, $a0
    mat2Determinant 11, 21, 12, 22, s100
    mat2Determinant 01, 21, 02, 22, s110
    mat2Determinant 01, 11, 02, 12, s120
    mat2Determinant 10, 20, 12, 22, s101
    mat2Determinant 00, 20, 02, 22, s111
    mat2Determinant 00, 10, 02, 12, s121
    mat2Determinant 10, 20, 11, 21, s102
    mat2Determinant 00, 20, 01, 21, s112
    mat2Determinant 00, 10, 01, 11, s122
    vmov.t c200, r100[x,-y,z]
    vmov.t c210, r101[-x,y,-z]
    vmov.t c220, r102[x,-y,z]
    mfc1 $t0, $f12
    mtv $t0, s300
    vfim.s s310, 1
    vdiv.s s320, s310, s300
    vmscl.t m200, m200, s320
    sv.q r200, 0($a1)
    usv.q r201, 12($a1)
    usv.q r202, 24($a1)
    jr $ra

gfunc psplaMat4InverseA
    lm4a 7, $a0
    mat3Determinant 12, 22, 32, 13, 23, 33, y, z, w, 01, s200
    mat3Determinant 02, 22, 32, 03, 23, 33, x, z, w, 01, s210
    mat3Determinant 02, 12, 32, 03, 13, 33, x, y, w, 01, s220
    mat3Determinant 02, 12, 22, 03, 13, 23, x, y, z, 01, s230
    mat3Determinant 12, 22, 32, 13, 23, 33, y, z, w, 00, s201
    mat3Determinant 02, 22, 32, 03, 23, 33, x, z, w, 00, s211
    mat3Determinant 02, 12, 32, 03, 13, 33, x, y, w, 00, s221
    mat3Determinant 02, 12, 22, 03, 13, 23, x, y, z, 00, s231
    mat3Determinant 11, 21, 31, 13, 23, 33, y, z, w, 00, s202
    mat3Determinant 01, 21, 31, 03, 23, 33, x, z, w, 00, s212
    mat3Determinant 01, 11, 31, 03, 13, 33, x, y, w, 00, s222
    mat3Determinant 01, 11, 21, 03, 13, 23, x, y, z, 00, s232
    mat3Determinant 11, 21, 31, 12, 22, 32, y, z, w, 00, s203
    mat3Determinant 01, 21, 31, 02, 22, 32, x, z, w, 00, s213
    mat3Determinant 01, 11, 31, 02, 12, 32, x, y, w, 00, s223
    mat3Determinant 01, 11, 11, 02, 12, 22, x, y, z, 00, s233
    vmov.q c300, r200[x,-y,z,-w]
    vmov.q c310, r201[-x,y,-z,w]
    vmov.q c320, r202[x,-y,z,-w]
    vmov.q c330, r203[-x,y,-z,w]
    mfc1 $t0, $f12
    mtv $t0, s400
    vfim.s s410, 1
    vdiv.s s420, s410, s400
    vmscl.q m300, m300, s420
    sv.q r300, 0($a1)
    sv.q r301, 16($a1)
    sv.q r302, 32($a1)
    sv.q r303, 48($a1)
    jr $ra

gfunc psplaMat2ToMatrix3U
    pushf $f0
    lm2u 0, $a0
    popf $f0
    vidt.q c020
    vidt.q r002
    usv.q r000, 0($a1)
    usv.q r001, 12($a1)
    svt s002, s012, s022, $a1, 24
    jr $ra

gfunc psplaMat2ToMatrix3A
    lm2a 0, $a0
    vidt.q c020
    vidt.q r002
    sv.q r000, 0($a1)
    usv.q r001, 12($a1)
    usv.q r002, 24($a1)
    jr $ra

gfunc psplaMat2ToMatrix4U
    pushf $f0
    lm2u 0, $a0
    popf $f0
    vidt.q c020
    vidt.q r002
    vidt.q c030
    vidt.q r003
    usv.q r000, 0($a1)
    usv.q r001, 16($a1)
    usv.q r002, 32($a1)
    usv.q r003, 48($a1)
    jr $ra

gfunc psplaMat2ToMatrix4A
    lm2a 0, $a0
    vidt.q c020
    vidt.q r002
    vidt.q c030
    vidt.q r003
    sv.q r000, 0($a1)
    sv.q r001, 16($a1)
    sv.q r002, 32($a1)
    sv.q r003, 48($a1)
    jr $ra

gfunc psplaMat3ToMatrix4U
    pushf $f0
    lm3u 0, $a0
    popf $f0
    vidt.q c030
    vidt.q r003
    usv.q r000, 0($a1)
    usv.q r001, 16($a1)
    usv.q r002, 32($a1)
    usv.q r003, 48($a1)
    jr $ra

gfunc psplaMat3ToMatrix4A
    lm3a 0, $a0
    vidt.q c030
    vidt.q r003
    sv.q r000, 0($a1)
    sv.q r001, 16($a1)
    sv.q r002, 32($a1)
    sv.q r003, 48($a1)
    jr $ra

gfunc psplaMat2Vector2MultiplyU
    pushf $f0
    lm2u 0, $a0
    ulv.q r002, 0($a1)
    popf $f0
    vdot.p s100, r000, r002
    vdot.p s110, r001, r002
    svp s100, s110, $a2, 0
    jr $ra

gfunc psplaMat3Vector3MultiplyU
    pushf $f0
    lm3u 0, $a0
    ulv.q r003, 0($a1)
    popf $f0
    vdot.t s100, r000, r003
    vdot.t s110, r001, r003
    vdot.t s120, r002, r003
    svt s100, s110, s120, $a2, 0
    jr $ra

gfunc psplaMat4Vector4MultiplyU
    sub $sp, $sp, 8
    s.s $f0, 4($sp)
    s.s $f4, 0($sp)
    lm4a 0, $a0
    ulv.q r100, 0($a1)
    l.s $f4, 0($sp)
    l.s $f0, 4($sp)
    add $sp, $sp, 8
    vdot.q s101, r000, r100
    vdot.q s111, r001, r100
    vdot.q s121, r002, r100
    vdot.q s131, r003, r100
    usv.q r101, 0($a2)
    jr $ra

gfunc psplaMat2Vector2MultiplyA
    lm2a 0, $a0
    lv.q r002, 0($a1)
    vdot.p s100, r000, r002
    vdot.p s110, r001, r002
    sv.q r100, 0($a2)
    jr $ra   

gfunc psplaMat3Vector3MultiplyA
    lm3a 0, $a0
    lv.q r003, 0($a1)
    vdot.t s100, r000, r003
    vdot.t s110, r001, r003
    vdot.t s120, r002, r003
    sv.q r100, 0($a2)
    jr $ra 

gfunc psplaMat4Vector4MultiplyA
    lm4a 0, $a0
    lv.q r100, 0($a1)
    vdot.q s101, r000, r100
    vdot.q s111, r001, r100
    vdot.q s121, r002, r100
    vdot.q s131, r003, r100
    sv.q r101, 0($a2)
    jr $ra
