.macro singleOpVector op, w
    lv.q r000, 0($a0)
    lv.q r001, 0($a1)
    \op\().\w r002, r000, r001
    sv.q r002, 0($a2)
.endm

.macro singleOpScalar op, w
    lv.q r000, 0($a0)
    lv.q r001, 0($a1)
    \op\().\w s002, r000, r001
    sv.s s002, 0($a2)
.endm

.macro vectorScalarOp op, w
    lv.q r000, 0($a0)
    lv.s s001, 0($a1)
    \op\().\w r002, r000, s001
    sv.q r002, 0($a2)
.endm

.macro magnitudeOp w
    lv.q r000, 0($a0)
    vmul.\w r000, r000, r000
    vfad.\w s001, r000
    vsqrt.s s001, s001
    sv.s s001, 0($a1)
.endm

.macro unitVecOp w
    lv.q r000, 0($a0)
    vmul.\w r002, r000, r000
    vfad.\w s001, r002
    vsqrt.s s001, s001
    vmov.q r001, r001[x,x,x,x]
    vdiv.\w r001, r000, r001
    sv.q r001, 0($a1)
.endm

.macro trigOpVector op, w
    lv.q r000, 0($a0)
    \op\().\w r000, r000
    sv.q r000, 0($a1)
.endm

.macro mat2Load
    lv.q r100, 0($a0)
    vmov.p r101, r120
    lv.q r200, 0($a1)
    vmov.p r201, r220
.endm

.macro mat2Store
    sv.q r000, 0($a2)
    usv.q r001, 8($a2)
.endm

.macro mat3Load
    sub $sp, $sp, 8
    s.s $f0, 4($sp)
    s.s $f4, 0($sp)
    lv.q r100, 0($a0)
    ulv.q r101, 12($a0)
    ulv.q r102, 24($a0)
    lv.q r200, 0($a1)
    ulv.q r201, 12($a1)
    ulv.q r202, 24($a1)
.endm

.macro mat3Store
    sv.q r000, 0($a2)
    usv.q r001, 12($a2)
    usv.q r002, 24($a2)
    l.s $f4, 0($sp)
    l.s $f0, 4($sp)
    add $sp, $sp, 8
.endm

.macro mat4Load
    lv.q r100, 0($a0)
    lv.q r101, 16($a0)
    lv.q r102, 32($a0)
    lv.q r103, 48($a0)
    lv.q r200, 0($a1)
    lv.q r201, 16($a1)
    lv.q r202, 32($a1)
    lv.q r203, 48($a1)
.endm

.macro mat4Store
    sv.q r000, 0($a2)
    sv.q r001, 16($a2)
    sv.q r002, 32($a2)
    sv.q r003, 48($a2)
.endm

.macro mat3SingleOp op
    mat3Load
    \op\().t r000, r100, r200
    \op\().t r001, r101, r201
    \op\().t r002, r102, r202
    mat3Store
.endm

.macro mat4SingleOp op
    mat4Load
    \op\().q r000, r100, r200
    \op\().q r001, r101, r201
    \op\().q r002, r102, r202
    \op\().q r003, r103, r203
    mat4Store
.endm

.globl psplaVec2Add
psplaVec2Add:
    singleOpVector vadd, p
    jr $ra

.globl psplaVec3Add
psplaVec3Add:
    singleOpVector vadd, t
    jr $ra

.globl psplaMat2Add
.globl psplaVec4Add
psplaMat2Add:
psplaVec4Add:
    singleOpVector vadd, q
    jr $ra

.globl psplaVec2Subtract
psplaVec2Subtract:
    singleOpVector vsub, p
    jr $ra

.globl psplaVec3Subtract
psplaVec3Subtract:
    singleOpVector vsub, t
    jr $ra

.globl psplaMat2Subtract
.globl psplaVec4Subtract
psplaVec4Subtract:
psplaMat2Subtract:
    singleOpVector vsub, q
    jr $ra

.globl psplaVec2Multiply
psplaVec2Multiply:
    singleOpVector vmul, p
    jr $ra

.globl psplaVec3Multiply
psplaVec3Multiply:
    singleOpVector vmul, t
    jr $ra

.globl psplaVec4Multiply
psplaVec4Multiply:
    singleOpVector vmul, q
    jr $ra

.globl psplaVec2Divide
psplaVec2Divide:
    singleOpVector vdiv, p
    jr $ra

.globl psplaVec3Divide
psplaVec3Divide:
    singleOpVector vdiv, t
    jr $ra

.globl psplaVec4Divide
psplaVec4Divide:
    singleOpVector vdiv, q
    jr $ra

.globl psplaVec2Minimum
psplaVec2Minimum:
    singleOpVector vmin, p
    jr $ra

.globl psplaVec3Minimum
psplaVec3Minimum:
    singleOpVector vmin, t
    jr $ra

.globl psplaVec4Minimum
psplaVec4Minimum:
    singleOpVector vmin, q
    jr $ra

.globl psplaVec2Maximum
psplaVec2Maximum:
    singleOpVector vmax, p
    jr $ra

.globl psplaVec3Maximum
psplaVec3Maximum:
    singleOpVector vmax, t
    jr $ra

.globl psplaVec4Maximum
psplaVec4Maximum:
    singleOpVector vmax, q
    jr $ra

.globl psplaVec2Sum
psplaVec2Sum:
    lv.q r000, 0($a0)
    vfad.p s001, r000
    sv.s s001, 0($a1)
    jr $ra

.globl psplaVec3Sum
psplaVec3Sum:
    lv.q r000, 0($a0)
    vfad.t s001, r000
    sv.s s001, 0($a1)
    jr $ra

.globl psplaVec4Sum
psplaVec4Sum:
    lv.q r000, 0($a0)
    vfad.q s001, r000
    sv.s s001, 0($a1)
    jr $ra

.globl psplaVec3CrossProduct
psplaVec3CrossProduct:
    singleOpVector vcrsp, t
    jr $ra

.globl psplaVec2Scale
psplaVec2Scale:
    vectorScalarOp vscl, p
    jr $ra

.globl psplaVec3Scale
psplaVec3Scale:
    vectorScalarOp vscl, t
    jr $ra

.globl psplaMat2ScalarMultiply
.globl psplaVec4Scale
psplaMat2ScalarMultiply:
psplaVec4Scale:
    vectorScalarOp vscl, q
    jr $ra

.globl psplaVec2DotProduct
psplaVec2DotProduct:
    singleOpScalar vdot, p
    jr $ra

.globl psplaVec3DotProduct
psplaVec3DotProduct:
    singleOpScalar vdot, t
    jr $ra

.globl psplaVec4DotProduct
psplaVec4DotProduct:
    singleOpScalar vdot, q
    jr $ra

.globl psplaVec2Magnitude
psplaVec2Magnitude:
    magnitudeOp p
    jr $ra

.globl psplaVec3Magnitude
psplaVec3Magnitude:
    magnitudeOp t
    jr $ra

.globl psplaVec4QuaternionNorm
.globl psplaVec4Magnitude
psplaVec4QuaternionNorm:
psplaVec4Magnitude:
    magnitudeOp q
    jr $ra

.globl psplaVec2UnitVector
psplaVec2UnitVector:
    unitVecOp p
    jr $ra

.globl psplaVec3UnitVector
psplaVec3UnitVector:
    unitVecOp t
    jr $ra

.globl psplaVec4QuaternionUnitNorm
.globl psplaVec4UnitVector
psplaVec4QuaternionUnitNorm:
psplaVec4UnitVector:
    unitVecOp q
    jr $ra

.globl psplaSine
psplaSine:
    lv.s s000, 0($a0)
    vsin.s s000, s000
    sv.s s000, 0($a1)
    jr $ra

.globl psplaCosine
psplaCosine:
    lv.s s000, 0($a0)
    vcos.s s000, s000
    sv.s s000, 0($a1)
    jr $ra

.globl psplaVec2Sine
psplaVec2Sine:
    trigOpVector vsin, p
    jr $ra

.globl psplaVec3Sine
psplaVec3Sine:
    trigOpVector vsin, t
    jr $ra

.globl psplaVec4Sine
psplaVec4Sine:
    trigOpVector vsin, q
    jr $ra

.globl psplaVec2Cosine
psplaVec2Cosine:
    trigOpVector vcos, p
    jr $ra

.globl psplaVec3Cosine
psplaVec3Cosine:
    trigOpVector vcos, t
    jr $ra

.globl psplaVec4Cosine
psplaVec4Cosine:
    trigOpVector vcos, q
    jr $ra

.globl psplaVec3RotationMatrix
psplaVec3RotationMatrix:
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

.globl psplaVec3RotationQuaternion
psplaVec3RotationQuaternion:
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

.globl psplaVec4QuaternionMultiply
psplaVec4QuaternionMultiply:
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

.globl psplaVec4QuaternionIdentity
psplaVec4QuaternionIdentity:
    vidt.q r000
    sv.q r000, 0($a0)
    jr $ra

.globl psplaVec4QuaternionConjugate
psplaVec4QuaternionConjugate:
    lv.q r000, 0($a0)
    vneg.t r010, r010
    sv.q r000, 0($a1)
    jr $ra

.globl psplaMat3Add
psplaMat3Add:
    mat3SingleOp vadd
    jr $ra

.globl psplaMat4Add
psplaMat4Add:
    mat4SingleOp vadd
    jr $ra

.globl psplaMat3Subtract
psplaMat3Subtract:
    mat3SingleOp vsub
    jr $ra

.globl psplaMat4Subtract
psplaMat4Subtract:
    mat4SingleOp vsub
    jr $ra

.globl psplaMat3ScalarMultiply
psplaMat3ScalarMultiply:
    sub $sp, $sp, 4
    s.s $f0, 0($sp)
    lv.q r100, 0($a0)
    ulv.q r101, 12($a0)
    ulv.q r102, 24($a0)
    lv.s s200, 0($a1)
    vscl.t r000, r100, s200
    vscl.t r001, r101, s200
    vscl.t r002, r102, s200
    sv.q r000, 0($a2)
    usv.q r001, 12($a2)
    usv.q r002, 24($a2)
    l.s $f0, 0($sp)
    add $sp, $sp, 4
    jr $ra

.globl psplaMat4ScalarMultiply
psplaMat4ScalarMultiply:
    lv.q r100, 0($a0)
    lv.q r101, 16($a0)
    lv.q r102, 32($a0)
    lv.q r103, 48($a0)
    lv.s s200, 0($a1)
    vscl.q r000, r100, s200
    vscl.q r001, r101, s200
    vscl.q r002, r102, s200
    vscl.q r003, r103, s200
    sv.q r000, 0($a2)
    sv.q r001, 16($a2)
    sv.q r002, 32($a2)
    sv.q r003, 48($a2)
    jr $ra

.globl psplaMat2Multiply
psplaMat2Multiply:
    mat2Load
    vmmul.p m000, m100, m200
    mat2Store
    jr $ra

.globl psplaMat3Multiply
psplaMat3Multiply:
    mat3Load
    vmmul.t m000, m100, m200
    mat3Store
    jr $ra

.globl psplaMat4Multiply
psplaMat4Multiply:
    mat4Load
    vmmul.q m000, m100, m200
    mat4Store
    jr $ra

.globl psplaMat2IdentityMatrix
psplaMat2IdentityMatrix:
    vmidt.p m000
    sv.q r000, 0($a0)
    usv.q r001, 8($a0)
    jr $ra

.globl psplaMat3IdentityMatrix
psplaMat3IdentityMatrix:
    vmidt.t m000
    sv.q r000, 0($a0)
    usv.q r001, 12($a0)
    usv.q r002, 24($a0)
    jr $ra

.globl psplaMat4IdentityMatrix
psplaMat4IdentityMatrix:
    vmidt.q m000
    sv.q r000, 0($a0)
    sv.q r001, 16($a0)
    sv.q r002, 32($a0)
    sv.q r003, 48($a0)
    jr $ra

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

.globl psplaMat2Determinant
psplaMat2Determinant:
    lv.q r700, 0($a0)
    mat2Determinant 00, 10, 20, 30, s100
    sv.s s100, 0($a1)
    jr $ra

.globl psplaMat3Determinant
psplaMat3Determinant:
    sub $sp, $sp, 4
    s.s $f28, 0($sp)
    lv.q r700, 0($a0)
    ulv.q r701, 12($a0)
    ulv.q r702, 24($a0)
    mat3Determinant 01, 11, 21, 02, 12, 22, x, y, z, 00, s103
    sv.s s103, 0($a1)
    l.s $f28, 0($sp)
    add $sp, $sp, 4
    jr $ra

.globl psplaMat4Determinant
psplaMat4Determinant:
    lv.q r700, 0($a0)
    lv.q r701, 16($a0)
    lv.q r702, 32($a0)
    lv.q r703, 48($a0)
    mat4Determinant 02, 12, 22, 32, 03, 13, 23, 33, s300
    sv.s s300, 0($a1)
    jr $ra

.globl psplaMat2Inverse
psplaMat2Inverse:
    lv.s s100, 0($a1)
    lv.q r101, 0($a0)
    vfim.s s110, 1
    vdiv.s s120, s110, s100
    vscl.q r101, r101, s120
    vmov.q r101, r101[w,-y,-z,x]
    sv.q r101, 0($a2)
    jr $ra

.globl psplaMat3Inverse
psplaMat3Inverse:
    sub $sp, $sp, 4
    s.s $f28, 0($sp)
    lv.q r700, 0($a0)
    ulv.q r701, 12($a0)
    ulv.q r702, 24($a0)
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
    lv.s s300, 0($a1)
    vfim.s s310, 1
    vdiv.s s320, s310, s300
    vmscl.t m200, m200, s320
    sv.q r200, 0($a2)
    usv.q r201, 12($a2)
    usv.q r202, 24($a2)
    l.s $f28, 0($sp)
    add $sp, $sp, 4
    jr $ra

.globl psplaMat4Inverse
psplaMat4Inverse:
    lv.q r700, 0($a0)
    lv.q r701, 16($a0)
    lv.q r702, 32($a0)
    lv.q r703, 48($a0)
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
    lv.s s400, 0($a1)
    vfim.s s410, 1
    vdiv.s s420, s410, s400
    vmscl.q m300, m300, s420
    sv.q r300, 0($a2)
    sv.q r301, 16($a2)
    sv.q r302, 32($a2)
    sv.q r303, 48($a2)
    jr $ra

.globl psplaMat2Transpose
psplaMat2Transpose:
    lv.q r000, 0($a0)
    vmov.q r000, r000[x,z,y,w]
    sv.q r000, 0($a1)
    jr $ra

.globl psplaMat3Transpose
psplaMat3Transpose:
    sub $sp, $sp, 4
    s.s $f0, 0($sp)
    lv.q r000, 0($a0)
    ulv.q r001, 12($a0)
    ulv.q r002, 24($a0)
    vmov.t c100, r000
    vmov.t c110, r001
    vmov.t c120, r002
    sv.q r100, 0($a1)
    usv.q r101, 12($a1)
    usv.q r102, 24($a1)
    l.s $f0, 0($sp)
    add $sp, $sp, 4
    jr $ra

.globl psplaMat4Transpose
psplaMat4Transpose:
    lv.q r000, 0($a0)
    lv.q r001, 16($a0)
    lv.q r002, 32($a0)
    lv.q r003, 48($a0)
    vmov.q c100, r000
    vmov.q c110, r001
    vmov.q c120, r002
    vmov.q c130, r003
    sv.q r100, 0($a1)
    sv.q r101, 16($a1)
    sv.q r102, 32($a1)
    sv.q r103, 48($a1)
    jr $ra


