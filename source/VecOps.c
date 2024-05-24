#include "../pspla.h"

void psplaVec4QuaternionInverse(float *v1, float *vout) {
    float conjugate[4] __attribute__((aligned(16)));
    float norm __attribute__((aligned(4)));
    psplaVec4QuaternionConjugate(v1, conjugate);
    psplaVec4QuaternionNorm(v1, &norm);

    norm*=norm;
    norm=1/norm;

    psplaVec4Scale(conjugate, &norm, vout);
}
