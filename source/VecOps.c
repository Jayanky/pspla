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

void psplaVec4QuaternionLerp(float *v1, float *v2, float *s1, float *vout) {
    float sinv __attribute__((aligned(4))) = 1 - *s1;

    float v1scale[4] __attribute__((aligned(16)));
    float v2scale[4] __attribute__((aligned(16)));
    psplaVec4Scale(v1, &sinv, v1scale);
    psplaVec4Scale(v2, s1, v2scale);

    psplaVec4Add(v1scale, v2scale, vout);  
}

void psplaVec4QuaternionSlerp(float *v1, float *v2, float *s1, float *vout) {
    float v2c[4] __attribute__((aligned(16)));
    psplaVecCopy(v2, v2c);
        
    float omega __attribute__((aligned(4)));
    psplaVec4DotProduct(v1, v2c, &omega);

    if(omega < 0) {
        psplaVecNegate(v2c, v2c);
        psplaVec4DotProduct(v1, v2c, &omega);
    }

    psplaArccosine(&omega, &omega);

    float sinv __attribute__((aligned(4))) = 1 - *s1;

    float p1 __attribute__((aligned(4))) = sinv * omega;
    float p2 __attribute__((aligned(4))) = *s1 * omega;

    psplaSine(&omega, &omega);
    psplaSine(&p1, &p1);
    psplaSine(&p2, &p2);

    p1 /= omega;
    p2 /= omega;

    float v1scale[4] __attribute__((aligned(16)));
    float v2scale[4] __attribute__((aligned(16)));
    psplaVec4Scale(v1, &p1, v1scale);
    psplaVec4Scale(v2c, &p2, v2scale);

    psplaVec4Add(v1scale, v2scale, vout);    
}