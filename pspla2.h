#ifndef PSPLA2_H
#define PSPLA2_H

/*
    Aligns data to a 16-byte boundary
*/
#define PSPLA_ALIGN __attribute__((aligned(16)))

/*
    Copy a matrix - Unaligned
    @param m1 source matrix
    @param mout destination matrix
*/
void psplaMat2CopyU(float *m1, float *mout);

/*
    Copy a matrix - Unaligned
    @param m1 source matrix
    @param mout destination matrix
*/
void psplaMat3CopyU(float *m1, float *mout);

/*
    Copy a matrix - Unaligned
    @param m1 source matrix
    @param mout destination matrix
*/
void psplaMat4CopyU(float *m1, float *mout);

/*
    Copy a matrix - Aligned
    @param m1 source matrix
    @param mout destination matrix
*/
void psplaMat2CopyA(float *m1, float *mout);

/*
    Copy a matrix - Aligned
    @param m1 source matrix
    @param mout destination matrix
*/
void psplaMat3CopyA(float *m1, float *mout);

/*
    Copy a matrix - Aligned
    @param m1 source matrix
    @param mout destination matrix
*/
void psplaMat4CopyA(float *m1, float *mout);

/*
    Copy a vector - Unaligned
    @param v1 source vector
    @param vout destination vector
*/
void psplaVec2CopyU(float *v1, float *vout);

/*
    Copy a vector - Unaligned
    @param v1 source vector
    @param vout destination vector
*/
void psplaVec3CopyU(float *v1, float *vout);

/*
    Copy a vector - Unaligned
    @param v1 source vector
    @param vout destination vector
*/
void psplaVec4CopyU(float *v1, float *vout);

/*
    Copy a vector - Aligned
    @param v1 source vector
    @param vout destination vector
*/
void psplaVecVCopyA(float *v1, float *vout);

/*
    Add two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec2AddU(float *v1, float *v2, float *vout);

/*
    Add two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec3AddU(float *v1, float *v2, float *vout);

/*
    Add two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec4AddU(float *v1, float *v2, float *vout);

/*
    Add two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVecVAddA(float *v1, float *v2, float *vout);

/*
    Subtract two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec2SubtractU(float *v1, float *v2, float *vout);

/*
    Subtract two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec3SubtractU(float *v1, float *v2, float *vout);

/*
    Subtract two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec4SubtractU(float *v1, float *v2, float *vout);

/*
    Subtract two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVecVSubtractA(float *v1, float *v2, float *vout);

/*
    Multiply two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec2MultiplyU(float *v1, float *v2, float *vout);

/*
    Multiply two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec3MultiplyU(float *v1, float *v2, float *vout);

/*
    Multiply two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec4MultiplyU(float *v1, float *v2, float *vout);

/*
    Multiply two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVecVMultiplyA(float *v1, float *v2, float *vout);

/*
    Divide two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec2DivideU(float *v1, float *v2, float *vout);

/*
    Divide two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec3DivideU(float *v1, float *v2, float *vout);

/*
    Divide two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec4DivideU(float *v1, float *v2, float *vout);

/*
    Divide two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec2DivideA(float *v1, float *v2, float *vout);

/*
    Divide two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec3DivideA(float *v1, float *v2, float *vout);

/*
    Divide two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVec4DivideA(float *v1, float *v2, float *vout);

/*
    Divide two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @param vout result vector
*/
void psplaVecVDivideA(float *v1, float *v2, float *vout);

/*
    Construct a vector from the the element-wise minimum of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec2MinimumU(float *v1, float *v2, float *vout);

/*
    Construct a vector from the the element-wise minimum of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec3MinimumU(float *v1, float *v2, float *vout);

/*
    Construct a vector from the the element-wise minimum of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec4MinimumU(float *v1, float *v2, float *vout);

/*
    Construct a vector from the the element-wise minimum of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVecVMinimumA(float *v1, float *v2, float *vout);

/*
    Construct a vector from the the element-wise maximum of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec2MaximumU(float *v1, float *v2, float *vout);

/*
    Construct a vector from the the element-wise maximum of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec3MaximumU(float *v1, float *v2, float *vout);

/*
    Construct a vector from the the element-wise maximum of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec4MaximumU(float *v1, float *v2, float *vout);

/*
    Construct a vector from the the element-wise maximum of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVecVMaximumA(float *v1, float *v2, float *vout);

/*
    Get the average of the elements in a vector - Unaligned
    @param v1 input vector
    @return The average of each element
*/
float psplaVec2AverageU(float *v1);

/*
    Get the average of the elements in a vector - Unaligned
    @param v1 input vector
    @return The average of each element
*/
float psplaVec3AverageU(float *v1);

/*
    Get the average of the elements in a vector - Unaligned
    @param v1 input vector
    @return The average of each element
*/
float psplaVec4AverageU(float *v1);

/*
    Get the average of the elements in a vector - Aligned
    @param v1 input vector
    @return The average of each element
*/
float psplaVec2AverageA(float *v1);

/*
    Get the average of the elements in a vector - Aligned
    @param v1 input vector
    @return The average of each element
*/
float psplaVec3AverageA(float *v1);

/*
    Get the average of the elements in a vector - Aligned
    @param v1 input vector
    @return The average of each element
*/
float psplaVec4AverageA(float *v1);

/*
    Get the sum of the elements in a vector - Unaligned
    @param v1 input vector
    @return The sum of the elements
*/
float psplaVec2SumU(float *v1);

/*
    Get the sum of the elements in a vector - Unaligned
    @param v1 input vector
    @return The sum of the elements
*/
float psplaVec3SumU(float *v1);

/*
    Get the sum of the elements in a vector - Unaligned
    @param v1 input vector
    @return The sum of the elements
*/
float psplaVec4SumU(float *v1);

/*
    Get the sum of the elements in a vector - Aligned
    @param v1 input vector
    @return The sum of the elements
*/
float psplaVec2SumA(float *v1);

/*
    Get the sum of the elements in a vector - Aligned
    @param v1 input vector
    @return The sum of the elements
*/
float psplaVec3SumA(float *v1);

/*
    Get the sum of the elements in a vector - Aligned
    @param v1 input vector
    @return The sum of the elements
*/
float psplaVec4SumA(float *v1);

/*
    Get the absolute value of a scalar
    @param s1 input scalar
    @return The absolute value
*/
float psplaAbsoluteValue(float s1);

/*
    Get the absolute value of each element in a vector - Unaligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec2AbsoluteValueU(float *v1, float *vout);

/*
    Get the absolute value of each element in a vector - Unaligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec3AbsoluteValueU(float *v1, float *vout);

/*
    Get the absolute value of each element in a vector - Unaligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec4AbsoluteValueU(float *v1, float *vout);

/*
    Get the absolute value of each element in a vector - Aligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVecVAbsoluteValueA(float *v1, float *vout);

/*
    Get the cross product of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout cross product
*/
void psplaVec3CrossProductU(float *v1, float *v2, float *vout);

/*
    Get the cross product of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @param vout cross product
*/
void psplaVec3CrossProductA(float *v1, float *v2, float *vout);

/*
    Scale a vector by a scalar value - Unaligned
    @param v1 input vector
    @param s1 scale value
    @param vout output vector
*/
void psplaVec2ScaleU(float *v1, float s1, float *vout);

/*
    Scale a vector by a scalar value - Unaligned
    @param v1 input vector
    @param s1 scale value
    @param vout output vector
*/
void psplaVec3ScaleU(float *v1, float s1, float *vout);

/*
    Scale a vector by a scalar value - Unaligned
    @param v1 input vector
    @param s1 scale value
    @param vout output vector
*/
void psplaVec4ScaleU(float *v1, float s1, float *vout);

/*
    Scale a vector by a scalar value - Aligned
    @param v1 input vector
    @param s1 scale value
    @param vout output vector
*/
void psplaVecVScaleA(float *v1, float s1, float *vout);

/*
    Get the dot product of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return The dot product
*/
float psplaVec2DotProductU(float *v1, float *v2);

/*
    Get the dot product of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return The dot product
*/
float psplaVec3DotProductU(float *v1, float *v2);

/*
    Get the dot product of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return The dot product
*/
float psplaVec4DotProductU(float *v1, float *v2);

/*
    Get the dot product of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return The dot product
*/
float psplaVec2DotProductA(float *v1, float *v2);

/*
    Get the dot product of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return The dot product
*/
float psplaVec3DotProductA(float *v1, float *v2);

/*
    Get the dot product of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return The dot product
*/
float psplaVec4DotProductA(float *v1, float *v2);

/*
    Find the square root of a scalar
    @param s1 input scalar
    @return The square root
*/
float psplaSquareRoot(float s1);

/*
    Find the square roots of each element in a vector - Unaligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec2SquareRootU(float *v1, float *vout);

/*
    Find the square roots of each element in a vector - Unaligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec3SquareRootU(float *v1, float *vout);

/*
    Find the square roots of each element in a vector - Unaligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec4SquareRootU(float *v1, float *vout);

/*
    Find the square roots of each element in a vector - Aligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec2SquareRootA(float *v1, float *vout);

/*
    Find the square roots of each element in a vector - Aligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec3SquareRootA(float *v1, float *vout);

/*
    Find the square roots of each element in a vector - Aligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec4SquareRootA(float *v1, float *vout);

/*
    Find the square roots of each element in a vector - Aligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVecVSquareRootA(float *v1, float *vout);

/*
    Get the magnitude of a vector - Unaligned
    @param v1 input vector
    @return The magnitude
*/
float psplaVec2MagnitudeU(float *v1);

/*
    Get the magnitude of a vector - Unaligned
    @param v1 input vector
    @return The magnitude
*/
float psplaVec3MagnitudeU(float *v1);

/*
    Get the magnitude of a vector - Unaligned
    @param v1 input vector
    @return The magnitude
*/
float psplaVec4MagnitudeU(float *v1);

/*
    Get the magnitude of a vector - Aligned
    @param v1 input vector
    @return The magnitude
*/
float psplaVec2MagnitudeA(float *v1);

/*
    Get the magnitude of a vector - Aligned
    @param v1 input vector
    @return The magnitude
*/
float psplaVec3MagnitudeA(float *v1);

/*
    Get the magnitude of a vector - Aligned
    @param v1 input vector
    @return The magnitude
*/
float psplaVec4MagnitudeA(float *v1);

/*
    Get a vector of the same direction but with a magnitude of 1 - Unaligned
    @param v1 input vector
    @param vout normalized vector
*/
void psplaVec2NormalizeU(float *v1, float *vout);

/*
    Get a vector of the same direction but with a magnitude of 1 - Unaligned
    @param v1 input vector
    @param vout normalized vector
*/
void psplaVec3NormalizeU(float *v1, float *vout);

/*
    Get a vector of the same direction but with a magnitude of 1 - Unaligned
    @param v1 input vector
    @param vout normalized vector
*/
void psplaVec4NormalizeU(float *v1, float *vout);

/*
    Get a vector of the same direction but with a magnitude of 1 - Aligned
    @param v1 input vector
    @param vout normalized vector
*/
void psplaVec2NormalizeA(float *v1, float *vout);

/*
    Get a vector of the same direction but with a magnitude of 1 - Aligned
    @param v1 input vector
    @param vout normalized vector
*/
void psplaVec3NormalizeA(float *v1, float *vout);

/*
    Get a vector of the same direction but with a magnitude of 1 - Aligned
    @param v1 input vector
    @param vout normalized vector
*/
void psplaVec4NormalizeA(float *v1, float *vout);

/*
    Round each element in a vector to the nearest whole number - Unaligned
    @param v1 input vector
    @param vout rounded vector
*/
void psplaVec2RoundU(float *v1, float *vout);

/*
    Round each element in a vector to the nearest whole number - Unaligned
    @param v1 input vector
    @param vout rounded vector
*/
void psplaVec3RoundU(float *v1, float *vout);

/*
    Round each element in a vector to the nearest whole number - Unaligned
    @param v1 input vector
    @param vout rounded vector
*/
void psplaVec4RoundU(float *v1, float *vout);

/*
    Round each element in a vector to the nearest whole number - Aligned
    @param v1 input vector
    @param vout rounded vector
*/
void psplaVecVRoundA(float *v1, float *vout);

/*
    Round each element in a vector to zero - Unaligned
    @param v1 input vector
    @param vout truncated vector
*/
void psplaVec2FloorU(float *v1, float *vout);

/*
    Round each element in a vector to zero - Unaligned
    @param v1 input vector
    @param vout truncated vector
*/
void psplaVec3FloorU(float *v1, float *vout);

/*
    Round each element in a vector to zero - Unaligned
    @param v1 input vector
    @param vout truncated vector
*/
void psplaVec4FloorU(float *v1, float *vout);

/*
    Round each element in a vector to zero - Aligned
    @param v1 input vector
    @param vout truncated vector
*/
void psplaVecVFloorA(float *v1, float *vout);

/*
    Round each element in a vector to the next whole number - Unaligned
    @param v1 input vector
    @param vout truncated vector
*/
void psplaVec2CeilingU(float *v1, float *vout);

/*
    Round each element in a vector to the next whole number - Unaligned
    @param v1 input vector
    @param vout truncated vector
*/
void psplaVec3CeilingU(float *v1, float *vout);

/*
    Round each element in a vector to the next whole number - Unaligned
    @param v1 input vector
    @param vout truncated vector
*/
void psplaVec4CeilingU(float *v1, float *vout);

/*
    Round each element in a vector to the next whole number - Aligned
    @param v1 input vector
    @param vout truncated vector
*/
void psplaVecVCeilingA(float *v1, float *vout);

/*
    Get the sine of a value in π/2 radians
    @param s1 input value
    @return The sine value
*/
float psplaSine(float s1);

/*
    Get the cosine of a value in π/2 radians
    @param s1 input value
    @return The cosine value
*/
float psplaCosine(float s1);

/*
    Get the sine of each element in a vector in π/2 radians - Unaligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec2SineU(float *v1, float *vout);

/*
    Get the sine of each element in a vector in π/2 radians - Unaligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec3SineU(float *v1, float *vout);

/*
    Get the sine of each element in a vector in π/2 radians - Unaligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec4SineU(float *v1, float *vout);

/*
    Get the sine of each element in a vector in π/2 radians - Aligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec2SineA(float *v1, float *vout);

/*
    Get the sine of each element in a vector in π/2 radians - Aligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec3SineA(float *v1, float *vout);

/*
    Get the sine of each element in a vector in π/2 radians - Aligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec4SineA(float *v1, float *vout);

/*
    Get the cosine of each element in a vector in π/2 radians - Unaligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec2CosineU(float *v1, float *vout);

/*
    Get the cosine of each element in a vector in π/2 radians - Unaligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec3CosineU(float *v1, float *vout);

/*
    Get the cosine of each element in a vector in π/2 radians - Unaligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec4CosineU(float *v1, float *vout);

/*
    Get the cosine of each element in a vector in π/2 radians - Aligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec2CosineA(float *v1, float *vout);

/*
    Get the cosine of each element in a vector in π/2 radians - Aligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec3CosineA(float *v1, float *vout);

/*
    Get the cosine of each element in a vector in π/2 radians - Aligned
    @param v1 input vector
    @param vout output vector
*/
void psplaVec4CosineA(float *v1, float *vout);

/*
    Get the arcsine of a value
    @param s1 input value
    @return The arcsine value in π/2 radians
*/
float psplaArcsine(float s1);

/*
    Get the arccosine of a value
    @param s1 input value
    @return The arccosine value in π/2 radians
*/
float psplaArccosine(float s1);

/*
    Negate a vector - Unaligned
    @param v1 input vector
    @param vout negated vector
*/
void psplaVec2NegateU(float *v1, float *vout);

/*
    Negate a vector - Unaligned
    @param v1 input vector
    @param vout negated vector
*/
void psplaVec3NegateU(float *v1, float *vout);

/*
    Negate a vector - Unaligned
    @param v1 input vector
    @param vout negated vector
*/
void psplaVec4NegateU(float *v1, float *vout);

/*
    Negate a vector - Aligned
    @param v1 input vector
    @param vout negated vector
*/
void psplaVecVNegateA(float *v1, float *vout);

/*
    Get the element-wise '==' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-1 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec2EqualsU(float *v1, float *v2);

/*
    Get the element-wise '==' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-2 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec3EqualsU(float *v1, float *v2);

/*
    Get the element-wise '==' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-3 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec4EqualsU(float *v1, float *v2);

/*
    Get the element-wise '==' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-1 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec2EqualsA(float *v1, float *v2);

/*
    Get the element-wise '==' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-2 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec3EqualsA(float *v1, float *v2);

/*
    Get the element-wise '==' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-3 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec4EqualsA(float *v1, float *v2);

/*
    Get the element-wise '<' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-1 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec2LessThanU(float *v1, float *v2);

/*
    Get the element-wise '<' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-2 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec3LessThanU(float *v1, float *v2);

/*
    Get the element-wise '<' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-3 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec4LessThanU(float *v1, float *v2);

/*
    Get the element-wise '<' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-1 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec2LessThanA(float *v1, float *v2);

/*
    Get the element-wise '<' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-2 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec3LessThanA(float *v1, float *v2);

/*
    Get the element-wise '<' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-3 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec4LessThanA(float *v1, float *v2);

/*
    Get the element-wise '<=' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-1 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec2LessThanEqualU(float *v1, float *v2);

/*
    Get the element-wise '<=' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-2 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec3LessThanEqualU(float *v1, float *v2);

/*
    Get the element-wise '<=' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-3 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec4LessThanEqualU(float *v1, float *v2);

/*
    Get the element-wise '<=' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-1 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec2LessThanEqualA(float *v1, float *v2);

/*
    Get the element-wise '<=' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-2 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec3LessThanEqualA(float *v1, float *v2);

/*
    Get the element-wise '<=' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-3 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec4LessThanEqualA(float *v1, float *v2);

/*
    Get the element-wise '>' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-1 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec2GreaterThanU(float *v1, float *v2);

/*
    Get the element-wise '>' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-2 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec3GreaterThanU(float *v1, float *v2);

/*
    Get the element-wise '>' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-3 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec4GreaterThanU(float *v1, float *v2);

/*
    Get the element-wise '>' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-1 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec2GreaterThanA(float *v1, float *v2);

/*
    Get the element-wise '>' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-2 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec3GreaterThanA(float *v1, float *v2);

/*
    Get the element-wise '>' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-3 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec4GreaterThanA(float *v1, float *v2);

/*
    Get the element-wise '>=' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-1 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec2GreaterThanEqualU(float *v1, float *v2);

/*
    Get the element-wise '>=' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-2 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec3GreaterThanEqualU(float *v1, float *v2);

/*
    Get the element-wise '>=' comparison of two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-3 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec4GreaterThanEqualU(float *v1, float *v2);

/*
    Get the element-wise '>=' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-1 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec2GreaterThanEqualA(float *v1, float *v2);

/*
    Get the element-wise '>=' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-2 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec3GreaterThanEqualA(float *v1, float *v2);

/*
    Get the element-wise '>=' comparison of two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @return A bitfield of results. Bits 0-3 are the result of each comparison. Bits 4 and 5 are '||' and '&&' operations on the comparison bits.
*/
int psplaVec4GreaterThanEqualA(float *v1, float *v2);

/*
    Get the element wise comparison of two vectors (-1.0 for lt, 0.0 for eq, 1.0 for gt) - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec2CompareU(float *v1, float *v2, float *vout);

/*
    Get the element wise comparison of two vectors (-1.0 for lt, 0.0 for eq, 1.0 for gt) - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec3CompareU(float *v1, float *v2, float *vout);

/*
    Get the element wise comparison of two vectors (-1.0 for lt, 0.0 for eq, 1.0 for gt) - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec4CompareU(float *v1, float *v2, float *vout);

/*
    Get the element wise comparison of two vectors (-1.0 for lt, 0.0 for eq, 1.0 for gt) - Aligned
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVecVCompareA(float *v1, float *v2, float *vout);

/*
    Get a linear interpolation between two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param s1 weight
    @param vout interpolated vector
*/
void psplaVec2LerpU(float *v1, float *v2, float s1, float *vout);

/*
    Get a linear interpolation between two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param s1 weight
    @param vout interpolated vector
*/
void psplaVec3LerpU(float *v1, float *v2, float s1, float *vout);

/*
    Get a linear interpolation between two vectors - Unaligned
    @param v1 first vector
    @param v2 second vector
    @param s1 weight
    @param vout interpolated vector
*/
void psplaVec4LerpU(float *v1, float *v2, float s1, float *vout);

/*
    Get a linear interpolation between two vectors - Aligned
    @param v1 first vector
    @param v2 second vector
    @param s1 weight
    @param vout interpolated vector
*/
void psplaVecVLerpA(float *v1, float *v2, float s1, float *vout);

/*
    Clamp each element in a vector to a specified range - Unaligned
    @param v1 input vector
    @param s1 minimum
    @param s2 maximum
    @param vout clamped vector
*/
void psplaVec2ClampU(float *v1, float s1, float s2, float *vout);

/*
    Clamp each element in a vector to a specified range - Unaligned
    @param v1 input vector
    @param s1 minimum
    @param s2 maximum
    @param vout clamped vector
*/
void psplaVec3ClampU(float *v1, float s1, float s2, float *vout);

/*
    Clamp each element in a vector to a specified range - Unaligned
    @param v1 input vector
    @param s1 minimum
    @param s2 maximum
    @param vout clamped vector
*/
void psplaVec4ClampU(float *v1, float s1, float s2, float *vout);

/*
    Clamp each element in a vector to a specified range - Aligned
    @param v1 input vector
    @param s1 minimum
    @param s2 maximum
    @param vout clamped vector
*/
void psplaVecVClampA(float *v1, float s1, float s2, float *vout);

/*
    Generate a random floating pointer number
    @return A random number (0 <= x < 1)
*/
float psplaRandom();

/*
    Generate a vector of random floating point numbers (0 <= x < 1) - Unaligned
    @param vout output vector
*/
void psplaVec2RandomU(float *vout);

/*
    Generate a vector of random floating point numbers (0 <= x < 1) - Unaligned
    @param vout output vector
*/
void psplaVec3RandomU(float *vout);

/*
    Generate a vector of random floating point numbers (0 <= x < 1) - Unaligned
    @param vout output vector
*/
void psplaVec4RandomU(float *vout);

/*
    Generate a vector of random floating point numbers (0 <= x < 1) - Aligned
    @param vout output vector
*/
void psplaVec2RandomA(float *vout);

/*
    Generate a vector of random floating point numbers (0 <= x < 1) - Aligned
    @param vout output vector
*/
void psplaVec3RandomA(float *vout);

/*
    Generate a vector of random floating point numbers (0 <= x < 1) - Aligned
    @param vout output vector
*/
void psplaVec4RandomA(float *vout);

/*
    Generate a vector of random floating point numbers (0 <= x < 1) - Aligned
    @param vout output vector
*/
void psplaVecVRandomA(float *vout);

/*
    Set the VFPU's RNG seed
    @param s1 seed
*/
void psplaRandomSeed(int s1);

/*
    Get the reflection of a vector off of a surface normal - Unaligned
    @param v1 input vector
    @param v2 normalized surface normal
    @param vout reflected vector
*/
void psplaVec2ReflectU(float *v1, float *v2, float *vout);

/*
    Get the reflection of a vector off of a surface normal - Unaligned
    @param v1 input vector
    @param v2 normalized surface normal
    @param vout reflected vector
*/
void psplaVec3ReflectU(float *v1, float *v2, float *vout);

/*
    Get the reflection of a vector off of a surface normal - Unaligned
    @param v1 input vector
    @param v2 normalized surface normal
    @param vout reflected vector
*/
void psplaVec4ReflectU(float *v1, float *v2, float *vout);

/*
    Get the reflection of a vector off of a surface normal - Aligned
    @param v1 input vector
    @param v2 normalized surface normal
    @param vout reflected vector
*/
void psplaVec2ReflectA(float *v1, float *v2, float *vout);

/*
    Get the reflection of a vector off of a surface normal - Aligned
    @param v1 input vector
    @param v2 normalized surface normal
    @param vout reflected vector
*/
void psplaVec3ReflectA(float *v1, float *v2, float *vout);

/*
    Get the reflection of a vector off of a surface normal - Aligned
    @param v1 input vector
    @param v2 normalized surface normal
    @param vout reflected vector
*/
void psplaVec4ReflectA(float *v1, float *v2, float *vout);

/*
    Get a rotation matrix from a set of euler angles in π/2 radians - Unaligned
    @param v1 input vector
    @param mout rotation matrix
*/
void psplaVec3RotationMatrixU(float *v1, float *mout);

/*
    Get a rotation matrix from a set of euler angles in π/2 radians - Aligned
    @param v1 input vector
    @param mout rotation matrix
*/
void psplaVec3RotationMatrixA(float *v1, float *mout);

/*
    Get a rotation quaternion from a set of euler angles in π/2 radians - Unaligned
    @param v1 input vector [x,y,z]
    @param qout output quaternion [w,x,y,z]
*/
void psplaVec3RotationQuaternionU(float *v1, float *qout);

/*
    Get a rotation quaternion from a set of euler angles in π/2 radians - Aligned
    @param v1 input vector [x,y,z]
    @param qout output quaternion [w,x,y,z]
*/
void psplaVec3RotationQuaternionA(float *v1, float *qout);

/*
    Multiply two quaternions - Unaligned
    @param q1 first quaternion
    @param q2 second quaternion
    @param qout output quaternion
*/
void psplaQuatMultiplyU(float *q1, float *q2, float *qout);

/*
    Multiply two quaternions - Aligned
    @param q1 first quaternion
    @param q2 second quaternion
    @param qout output quaternion
*/
void psplaQuatMultiplyA(float *q1, float *q2, float *qout);

/*
    Set a quaternion to an identity quaternion - Unaligned
    @param qout output quaternion
*/
void psplaQuatIdentityU(float *qout);

/*
    Set a quaternion to an identity quaternion - Aligned
    @param qout output quaternion
*/
void psplaQuatIdentityA(float *qout);

/*
    Get the conjugate of a quaternion - Unaligned
    @param q1 input quaternion
    @param qout output quaternion
*/
void psplaQuatConjugateU(float *q1, float *qout);

/*
    Get the conjugate of a quaternion - Aligned
    @param q1 input quaternion
    @param qout output quaternion
*/
void psplaQuatConjugateA(float *q1, float *qout);

/*
    Get the norm of a quaternion - Unaligned
    @param q1 input quaternion
    @return The quaternion norm
*/
float psplaQuatNormU(float* q1);

/*
    Get the norm of a quaternion - Aligned
    @param q1 input quaternion
    @return The quaternion norm
*/
float psplaQuatNormA(float* q1);

/*
    Get the inverse of a quaternion - Unaligned
    @param q1 input quaternion
    @param qout inverse quaternion
*/
void psplaQuatInverseU(float *q1, float *qout);

/*
    Get the inverse of a quaternion - Aligned
    @param q1 input quaternion
    @param qout inverse quaternion
*/
void psplaQuatInverseA(float *q1, float *qout);

/*
    Get the linear interpolation of two quaternions based on a specified weight - Unaligned
    @param q1 first quaternion
    @param q2 second quaternion
    @param s1 weight
    @param qout interpolated quaternion
*/
void psplaQuatLerpU(float *q1, float *q2, float s1, float *qout);

/*
    Get the linear interpolation of two quaternions based on a specified weight - Aligned
    @param q1 first quaternion
    @param q2 second quaternion
    @param s1 weight
    @param qout interpolated quaternion
*/
void psplaQuatLerpA(float *q1, float *q2, float s1, float *qout);

/*
    Get the spherical linear interpolations of two quaternions based on a specified weight - Unaligned
    @param q1 first quaternion
    @param q2 second quaternion
    @param s1 weight
    @param qout interpolated quaternion
*/
void psplaQuatSlerpU(float *q1, float *q2, float s1, float *qout);

/*
    Get the spherical linear interpolations of two quaternions based on a specified weight - Aligned
    @param q1 first quaternion
    @param q2 second quaternion
    @param s1 weight
    @param qout interpolated quaternion
*/
void psplaQuatSlerpA(float *q1, float *q2, float s1, float *qout);

/*
    Get a rotation matrix from a quaternion - Unaligned
    @param q1 input quaternion
    @param mout output matrix
*/
void psplaQuatRotationMatrixU(float *q1, float *mout);

/*
    Get a rotation matrix from a quaternion - Aligned
    @param q1 input quaternion
    @param mout output matrix
*/
void psplaQuatRotationMatrixA(float *q1, float *mout);

/*
    Add two matrices - Unaligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat2AddU(float *m1, float *m2, float *mout);

/*
    Add two matrices - Unaligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat3AddU(float *m1, float *m2, float *mout);

/*
    Add two matrices - Unaligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat4AddU(float *m1, float *m2, float *mout);

/*
    Add two matrices - Aligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat2AddA(float *m1, float *m2, float *mout);

/*
    Add two matrices - Aligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat3AddA(float *m1, float *m2, float *mout);

/*
    Add two matrices - Aligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat4AddA(float *m1, float *m2, float *mout);

/*
    Subtract two matrices - Unaligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat2SubtractU(float *m1, float *m2, float *mout);

/*
    Subtract two matrices - Unaligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat3SubtractU(float *m1, float *m2, float *mout);

/*
    Subtract two matrices - Unaligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat4SubtractU(float *m1, float *m2, float *mout);

/*
    Subtract two matrices - Aligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat2SubtractA(float *m1, float *m2, float *mout);

/*
    Subtract two matrices - Aligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat3SubtractA(float *m1, float *m2, float *mout);

/*
    Subtract two matrices - Aligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat4SubtractA(float *m1, float *m2, float *mout);

/*
    Scale a matrix by a scalar value - Unaligned
    @param m1 input matrix
    @param s1 scale factor
    @param mout scaled matrix
*/
void psplaMat2ScaleU(float *m1, float s1, float *mout);

/*
    Scale a matrix by a scalar value - Unaligned
    @param m1 input matrix
    @param s1 scale factor
    @param mout scaled matrix
*/
void psplaMat3ScaleU(float *m1, float s1, float *mout);

/*
    Scale a matrix by a scalar value - Unaligned
    @param m1 input matrix
    @param s1 scale factor
    @param mout scaled matrix
*/
void psplaMat4ScaleU(float *m1, float s1, float *mout);

/*
    Scale a matrix by a scalar value - Aligned
    @param m1 input matrix
    @param s1 scale factor
    @param mout scaled matrix
*/
void psplaMat2ScaleA(float *m1, float s1, float *mout);

/*
    Scale a matrix by a scalar value - Aligned
    @param m1 input matrix
    @param s1 scale factor
    @param mout scaled matrix
*/
void psplaMat3ScaleA(float *m1, float s1, float *mout);

/*
    Scale a matrix by a scalar value - Aligned
    @param m1 input matrix
    @param s1 scale factor
    @param mout scaled matrix
*/
void psplaMat4ScaleA(float *m1, float s1, float *mout);

/*
    Multiply two matrices - Unaligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat2MultiplyU(float *m1, float *m2, float *mout);

/*
    Multiply two matrices - Unaligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat3MultiplyU(float *m1, float *m2, float *mout);

/*
    Multiply two matrices - Unaligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat4MultiplyU(float *m1, float *m2, float *mout);

/*
    Multiply two matrices - Aligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat2MultiplyA(float *m1, float *m2, float *mout);

/*
    Multiply two matrices - Aligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat3MultiplyA(float *m1, float *m2, float *mout);

/*
    Multiply two matrices - Aligned
    @param m1 first matrix
    @param m2 second matrix
    @param mout output matrix
*/
void psplaMat4MultiplyA(float *m1, float *m2, float *mout);

/*
    Set a matrix to an identity matrix - Unaligned
    @param mout output matrix
*/
void psplaMat2IdentityU(float *mout);

/*
    Set a matrix to an identity matrix - Unaligned
    @param mout output matrix
*/
void psplaMat3IdentityU(float *mout);

/*
    Set a matrix to an identity matrix - Unaligned
    @param mout output matrix
*/
void psplaMat4IdentityU(float *mout);

/*
    Set a matrix to an identity matrix - Aligned
    @param mout output matrix
*/
void psplaMat2IdentityA(float *mout);

/*
    Set a matrix to an identity matrix - Aligned
    @param mout output matrix
*/
void psplaMat3IdentityA(float *mout);

/*
    Set a matrix to an identity matrix - Aligned
    @param mout output matrix
*/
void psplaMat4IdentityA(float *mout);

/*
    Transpose a matrix - Unaligned
    @param m1 input matrix
    @param mout transposed matrix
*/
void psplaMat2TransposeU(float *m1, float *mout);

/*
    Transpose a matrix - Unaligned
    @param m1 input matrix
    @param mout transposed matrix
*/
void psplaMat3TransposeU(float *m1, float *mout);

/*
    Transpose a matrix - Unaligned
    @param m1 input matrix
    @param mout transposed matrix
*/
void psplaMat4TransposeU(float *m1, float *mout);

/*
    Get the determinant of a matrix - Unaligned
    @param m1 input matrix
    @return The determinant
*/
float psplaMat2DeterminantU(float *m1);

/*
    Get the determinant of a matrix - Unaligned
    @param m1 input matrix
    @return The determinant
*/
float psplaMat3DeterminantU(float *m1);

/*
    Get the determinant of a matrix - Unaligned
    @param m1 input matrix
    @return The determinant
*/
float psplaMat4DeterminantU(float *m1);

/*
    Get the determinant of a matrix - Aligned
    @param m1 input matrix
    @return The determinant
*/
float psplaMat2DeterminantA(float *m1);

/*
    Get the determinant of a matrix - Aligned
    @param m1 input matrix
    @return The determinant
*/
float psplaMat3DeterminantA(float *m1);

/*
    Get the determinant of a matrix - Aligned
    @param m1 input matrix
    @return The determinant
*/
float psplaMat4DeterminantA(float *m1);

/*
    Get the inverse of a matrix - Unaligned
    @param m1 input matrix
    @param s1 determinant
    @param mout inverse matrix
*/
void psplaMat2InverseU(float *m1, float s1, float *mout);

/*
    Get the inverse of a matrix - Unaligned
    @param m1 input matrix
    @param s1 determinant
    @param mout inverse matrix
*/
void psplaMat3InverseU(float *m1, float s1, float *mout);

/*
    Get the inverse of a matrix - Unaligned
    @param m1 input matrix
    @param s1 determinant
    @param mout inverse matrix
*/
void psplaMat4InverseU(float *m1, float s1, float *mout);

/*
    Get the inverse of a matrix - Aligned
    @param m1 input matrix
    @param s1 determinant
    @param mout inverse matrix
*/
void psplaMat2InverseA(float *m1, float s1, float *mout);

/*
    Get the inverse of a matrix - Aligned
    @param m1 input matrix
    @param s1 determinant
    @param mout inverse matrix
*/
void psplaMat3InverseA(float *m1, float s1, float *mout);

/*
    Get the inverse of a matrix - Aligned
    @param m1 input matrix
    @param s1 determinant
    @param mout inverse matrix
*/
void psplaMat4InverseA(float *m1, float s1, float *mout);

/*
    Convert a matrix 2 to a matrix 3 - Unaligned
    @param m1 input matrix
    @param mout output matrix
*/
void psplaMat2ToMatrix3U(float *m1, float *mout);

/*
    Convert a matrix 2 to a matrix 3 - Aligned
    @param m1 input matrix
    @param mout output matrix
*/
void psplaMat2ToMatrix3A(float *m1, float *mout);

/*
    Convert a matrix 2 to a matrix 4 - Unaligned
    @param m1 input matrix
    @param mout output matrix
*/
void psplaMat2ToMatrix4U(float *m1, float *mout);

/*
    Convert a matrix 2 to a matrix 4 - Aligned
    @param m1 input matrix
    @param mout output matrix
*/
void psplaMat2ToMatrix4A(float *m1, float *mout);

/*
    Convert a matrix 3 to a matrix 4 - Unaligned
    @param m1 input matrix
    @param mout output matrix
*/
void psplaMat3ToMatrix4U(float *m1, float *mout);

/*
    Convert a matrix 3 to a matrix 4 - Aligned
    @param m1 input matrix
    @param mout output matrix
*/
void psplaMat3ToMatrix4A(float *m1, float *mout);

#endif