#include "../pspla2.h"

void psplaQuatInverseU(float *q1, float *qout) {
    float conjugate[4] PSPLA_ALIGN;
    psplaQuatConjugateU(q1, conjugate);
    float norm = psplaQuatNormU(q1);

    norm = 1/(norm * norm);

    psplaVec4ScaleU(conjugate, norm, qout);
}

void psplaQuatInverseA(float *q1, float *qout) {
    float conjugate[4] PSPLA_ALIGN;
    psplaQuatConjugateA(q1, conjugate);
    float norm = psplaQuatNormA(q1);

    norm = 1/(norm * norm);

    psplaVecVScaleA(conjugate, norm, qout);
}

void psplaQuatSlerpU(float *q1, float *q2, float s1, float *qout) {
    float r1[4] PSPLA_ALIGN;
    float r2[4] PSPLA_ALIGN;

    float cosOmega = psplaVec4DotProductU(q1, q2);

    if(psplaAbsoluteValue(cosOmega) >= 1.0) {
        psplaVec4CopyU(q1, qout);
        return;
    }

    float omega = psplaArccosine(cosOmega);
    float sinOmega = psplaSquareRoot(1.0 - (cosOmega * cosOmega));

    float p1 = psplaSine(((1 - s1) * omega) / sinOmega);
    float p2 = psplaSine((s1 * omega) / sinOmega);

    psplaVec4ScaleU(q1, p1, r1);
    psplaVec4ScaleU(q2, p2, r2);
    psplaVec4AddU(r1, r2, qout);
}

void psplaQuatSlerpA(float *q1, float *q2, float s1, float *qout) {
    float r1[4] PSPLA_ALIGN;
    float r2[4] PSPLA_ALIGN;

    float cosOmega = psplaVec4DotProductA(q1, q2);

    if(psplaAbsoluteValue(cosOmega) >= 1.0) {
        psplaVecVCopyA(q1, qout);
        return;
    }

    float omega = psplaArccosine(cosOmega);
    float sinOmega = psplaSquareRoot(1.0 - (cosOmega * cosOmega));

    float p1 = psplaSine(((1 - s1) * omega) / sinOmega);
    float p2 = psplaSine((s1 * omega) / sinOmega);

    psplaVecVScaleA(q1, p1, r1);
    psplaVecVScaleA(q2, p2, r2);
    psplaVecVAddA(r1, r2, qout);
}

void psplaQuatRotateU(float *q1, float *q2, float *qout) {
    float q2c[4] PSPLA_ALIGN;
    psplaQuatConjugateU(q2, q2c);

    float accumulator[4] PSPLA_ALIGN;
    psplaQuatMultiplyU(q2, q1, accumulator);
    psplaQuatMultiplyA(accumulator, q2c, accumulator);
    psplaVec4CopyU(accumulator, qout);
}

void psplaQuatRotateA(float *q1, float *q2, float *qout) {
    float q2c[4] PSPLA_ALIGN;
    psplaQuatConjugateA(q2, q2c);

    float accumulator[4] PSPLA_ALIGN;
    psplaQuatMultiplyA(q2, q1, accumulator);
    psplaQuatMultiplyA(accumulator, q2c, accumulator);
    psplaVecVCopyA(accumulator, qout);
}