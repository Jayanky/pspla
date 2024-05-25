#ifndef PSPLA_H
#define PSPLA_H

/*
    Add two vectors.
    @param v1 first vector to add
    @param v2 second vector to add
    @param vout output vector
*/
void psplaVec2Add(float *v1, float *v2, float *vout);

/*
    Add two vectors.
    @param v1 first vector to add
    @param v2 second vector to add
    @param vout output vector
*/
void psplaVec3Add(float *v1, float *v2, float *vout);

/*
    Add two vectors.
    @param v1 first vector to add
    @param v2 second vector to add
    @param vout output vector
*/
void psplaVec4Add(float *v1, float *v2, float *vout);

/*
    Subtract one vector from another.
    @param v1 vector to subtract from
    @param v2 subtracting vector
    @param vout output vector
*/
void psplaVec2Subtract(float *v1, float *v2, float *vout);

/*
    Subtract one vector from another.
    @param v1 vector to subtract from
    @param v2 subtracting vector
    @param vout output vector
*/
void psplaVec3Subtract(float *v1, float *v2, float *vout);

/*
    Subtract one vector from another.
    @param v1 vector to subtract from
    @param v2 subtracting vector
    @param vout output vector
*/
void psplaVec4Subtract(float *v1, float *v2, float *vout);

/*
    Multiply two vectors.
    @param v1 first vector to multiply
    @param v2 second vector to multiply
    @param vout output vector
*/
void psplaVec2Multiply(float *v1, float *v2, float *vout);

/*
    Multiply two vectors.
    @param v1 first vector to multiply
    @param v2 second vector to multiply
    @param vout output vector
*/
void psplaVec3Multiply(float *v1, float *v2, float *vout);

/*
    Multiply two vectors.
    @param v1 first vector to multiply
    @param v2 second vector to multiply
    @param vout output vector
*/
void psplaVec4Multiply(float *v1, float *v2, float *vout);

/*
    Divide one vector by another.
    @param v1 vector numerator
    @param v2 vector denominator
    @param vout output vector
*/
void psplaVec2Divide(float *v1, float *v2, float *vout);

/*
    Divide one vector by another.
    @param v1 vector numerator
    @param v2 vector denominator
    @param vout output vector
*/
void psplaVec3Divide(float *v1, float *v2, float *vout);

/*
    Divide one vector by another.
    @param v1 vector numerator
    @param v2 vector denominator
    @param vout output vector
*/
void psplaVec4Divide(float *v1, float *v2, float *vout);

/*
    Creates a vector using the smaller of each corresponding element.
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec2Minimum(float *v1, float *v2, float *vout);

/*
    Creates a vector using the smaller of each corresponding element.
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec3Minimum(float *v1, float *v2, float *vout);

/*
    Creates a vector using the smaller of each corresponding element.
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec4Minimum(float *v1, float *v2, float *vout);

/*
    Creates a vector using the larger of each corresponding element.
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec2Maximum(float *v1, float *v2, float *vout);

/*
    Creates a vector using the larger of each corresponding element.
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec3Maximum(float *v1, float *v2, float *vout);

/*
    Creates a vector using the larger of each corresponding element.
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec4Maximum(float *v1, float *v2, float *vout);

/*
    Gets the cross product of two vectors.
    @param v1 first vector
    @param v2 second vector
    @param vout output vector
*/
void psplaVec3CrossProduct(float* v1, float* v2, float* vout);

/*
    Scale a vector by a scalar value.
    @param v1 vector to scale
    @param s1 scalar value
    @param vout output vector
*/
void psplaVec2Scale(float *v1, float *s1, float *vout);

/*
    Scale a vector by a scalar value.
    @param v1 vector to scale
    @param s1 scalar value
    @param vout output vector
*/
void psplaVec3Scale(float *v1, float *s1, float *vout);

/*
    Scale a vector by a scalar value.
    @param v1 vector to scale
    @param s1 scalar value
    @param vout output vector
*/
void psplaVec4Scale(float *v1, float *s1, float *vout);

/*
    Add all of the elements in a vector.
    @param v1 vector to sum
    @param sout output scalar
*/
void psplaVec2Sum(float *v1, float *sout);

/*
    Add all of the elements in a vector.
    @param v1 vector to sum
    @param sout output scalar
*/
void psplaVec3Sum(float *v1, float *sout);

/*
    Add all of the elements in a vector.
    @param v1 vector to sum
    @param sout output scalar
*/
void psplaVec4Sum(float *v1, float *sout);

/*
    Get the absolute value of each element in a vector.
    @param v1 input vector
    @param vout output vector
*/
void psplaVec2AbsoluteValue(float *v1, float *vout);

/*
    Get the absolute value of each element in a vector.
    @param v1 input vector
    @param vout output vector
*/
void psplaVec3AbsoluteValue(float *v1, float *vout);

/*
    Get the absolute value of each element in a vector.
    @param v1 input vector
    @param vout output vector
*/
void psplaVec4AbsoluteValue(float *v1, float *vout);

/*
    Get the dot product of two vectors.
    @param v1 first vector
    @param v2 second vector
    @param sout output scalar
*/
void psplaVec2DotProduct(float *v1, float *v2, float *sout);

/*
    Get the dot product of two vectors.
    @param v1 first vector
    @param v2 second vector
    @param sout output scalar
*/
void psplaVec3DotProduct(float *v1, float *v2, float *sout);

/*
    Get the dot product of two vectors.
    @param v1 first vector
    @param v2 second vector
    @param sout output scalar
*/
void psplaVec4DotProduct(float *v1, float *v2, float *sout);

/*
    Get the magnitude of a vector.
    @param v1 input vector
    @param sout output scalar
*/
void psplaVec2Magnitude(float *v1, float *sout);

/*
    Get the magnitude of a vector.
    @param v1 input vector
    @param sout output scalar
*/
void psplaVec3Magnitude(float *v1, float *sout);

/*
    Get the magnitude of a vector.
    @param v1 input vector
    @param sout output scalar
*/
void psplaVec4Magnitude(float *v1, float *sout);

/*
    Get the magnitude of a vector.
    @param v1 input quaternion
    @param sout output scalar
*/
void psplaVec4QuaternionNorm(float *v1, float *sout);

/*
    Get the unit vector of a vector.
    @param v1 input vector
    @param vout output vector
*/
void psplaVec2UnitVector(float *v1, float *vout);

/*
    Get the unit vector of a vector.
    @param v1 input vector
    @param vout output vector
*/
void psplaVec3UnitVector(float *v1, float *vout);

/*
    Get the unit vector of a vector.
    @param v1 input vector
    @param vout output vector
*/
void psplaVec4UnitVector(float *v1, float *vout);

/*
    Round each element of a vector to the nearest whole number.
    @param v1 input vector
    @param vout output vector
*/
void psplaVec2Round(float *v1, float *vout);

/*
    Round each element of a vector to the nearest whole number.
    @param v1 input vector
    @param vout output vector
*/
void psplaVec3Round(float *v1, float *vout);

/*
    Round each element of a vector to the nearest whole number.
    @param v1 input vector
    @param vout output vector
*/
void psplaVec4Round(float *v1, float *vout);

/*
    Do linear interpolation between two quaternions.
    @param v1 vector 1
    @param v2 vector 2
    @param s1 how close you want to go from vector 1 to vector 2 (0 = v1, 1 = v2).
    @param vout output vector
*/
void psplaVec4QuaternionLerp(float *v1, float *v2, float *s1, float *vout);

/*
    Do spherical linear interpolation between two quaternions.
    @param v1 vector 1
    @param v2 vector 2
    @param s1 how close you want to go from vector 1 to vector 2 (0 = v1, 1 = v2).
    @param vout output vector
*/
void psplaVec4QuaternionSlerp(float *v1, float *v2, float *s1, float *vout);

/*
    Get the unit norm of a quaternion.
    @param v1 input quaternion
    @param vout output quaternion
*/
void psplaVec4QuaternionUnitNorm(float *v1, float *vout);

/*
    Get the sine of a scalar in π/2 radians.
    @param s1 input scalar
    @param s2 output sine
*/
void psplaSine(float *s1, float *sout);

/*
    Get the cosine of a scalar in π/2 radians.
    @param s1 input scalar
    @param s2 output cosine
*/
void psplaCosine(float *s1, float *sout);

/*
    Get the sine of each vector element in π/2 radians.
    @param v1 input vector
    @param v2 output vector of sines
*/
void psplaVec2Sine(float *v1, float *vout);

/*
    Get the sine of each vector element in π/2 radians.
    @param v1 input vector
    @param v2 output vector of sines
*/
void psplaVec3Sine(float *v1, float *vout);

/*
    Get the sine of each vector element in π/2 radians.
    @param v1 input vector
    @param v2 output vector of sines
*/
void psplaVec4Sine(float *v1, float *vout);

/*
    Get the Cosine of each vector element in π/2 radians.
    @param v1 input vector
    @param v2 output vector of cosines
*/
void psplaVec2Cosine(float *v1, float *vout);

/*
    Get the Cosine of each vector element in π/2 radians.
    @param v1 input vector
    @param v2 output vector of cosines
*/
void psplaVec3Cosine(float *v1, float *vout);

/*
    Get the Cosine of each vector element in π/2 radians.
    @param v1 input vector
    @param v2 output vector of cosines
*/
void psplaVec4Cosine(float *v1, float *vout);

/*
    Get the Arcsine of a scalar in π/2 radians.
    @param s1 input vector
    @param sout output arcsine
*/
void psplaArcsine(float *s1, float *sout);

/*
    Get the Arccosine of a scalar in π/2 radians.
    @param s1 input vector
    @param sout output arccosine
*/
void psplaArccosine(float *s1, float *sout);

/*  
    Negate a vector.
    @param v1 input vector
    @param vout negated vector
*/
void psplaVecNegate(float *v1, float *vout);

/*
    Copy a vector.
    @param v1 source vector
    @param v2 destination vector
*/
void psplaVecCopy(float *v1, float *vout);

/*
    Create a 3x3 rotation matrix. Rotation vector values should be in π/2 radians.
    @param v1 rotation vector [x, y, z]
    @param mout output matrix
*/
void psplaVec3RotationMatrix(float *v1, float *mout);

/*
    Create a rotation quaternion. Rotation vector values should be in π/2 radians.
    @param v1 rotation vector [x, y, z]
    @param vout output quaternion [w, x, y, z]
*/
void psplaVec3RotationQuaternion(float *v1, float *vout);

/*
    Multiply two quaternions.
    @param v1 first quaternion to multiply
    @param v2 second quaternion to multiply
    @param vout output quaternion
*/
void psplaVec4QuaternionMultiply(float *v1, float *v2, float *vout);

/*
    Set quaternion to identity.
    @param v1 quaternion to set
*/
void psplaVec4QuaternionIdentity(float *v1);

/*
    Get the conjugate of a quaternion
    @param v1 input quaternion
    @param vout output conjugate
*/
void psplaVec4QuaternionConjugate(float *v1, float *vout);

/*
    Get the inverse of a quaternion
    @param v1 input quaternion
    @param vout output inverse
*/
void psplaVec4QuaternionInverse(float *v1, float *vout);

/*
    Add two matrices.
    @param m1 first matrix to add
    @param m2 second matrix to add
    @param mout output matrix
*/
void psplaMat2Add(float *m1, float *m2, float *mout);

/*
    Add two matrices.
    @param m1 first matrix to add
    @param m2 second matrix to add
    @param mout output matrix
*/
void psplaMat3Add(float *m1, float *m2, float *mout);

/*
    Add two matrices.
    @param m1 first matrix to add
    @param m2 second matrix to add
    @param mout output matrix
*/
void psplaMat4Add(float *m1, float *m2, float *mout);

/*
    Subtract one matrix from another.
    @param m1 matrix to subtract from
    @param m2 subtracting matrix
    @param mout output matrix
*/
void psplaMat2Subtract(float *m1, float *m2, float *mout);

/*
    Subtract one matrix from another.
    @param m1 matrix to subtract from
    @param m2 subtracting matrix
    @param mout output matrix
*/
void psplaMat3Subtract(float *m1, float *m2, float *mout);

/*
    Subtract one matrix from another.
    @param m1 matrix to subtract from
    @param m2 subtracting matrix
    @param mout output matrix
*/
void psplaMat4Subtract(float *m1, float *m2, float *mout);

/*
    Multiply a matrix by a scalar value.
    @param m1 matrix to scale
    @param s1 scalar value
    @param mout output matrix
*/
void psplaMat2ScalarMultiply(float *m1, float *s1, float *mout);

/*
    Multiply a matrix by a scalar value.
    @param m1 matrix to scale
    @param s1 scalar value
    @param mout output matrix
*/
void psplaMat3ScalarMultiply(float *m1, float *s1, float *mout);

/*
    Multiply a matrix by a scalar value.
    @param m1 matrix to scale
    @param s1 scalar value
    @param mout output matrix
*/
void psplaMat4ScalarMultiply(float *m1, float *s1, float *mout);

/*
    Multiply two row-major matrices.
    @param m1 left matrix
    @param m2 top matrix
    @param mout output matrix
*/
void psplaMat2Multiply(float *m1, float *m2, float *mout);

/*
    Multiply two row-major matrices.
    @param m1 left matrix
    @param m2 top matrix
    @param mout output matrix
*/
void psplaMat3Multiply(float *m1, float *m2, float *mout);

/*
    Multiply two row-major matrices.
    @param m1 left matrix
    @param m2 top matrix
    @param mout output matrix
*/
void psplaMat4Multiply(float *m1, float *m2, float *mout);

/*
    Set a matrix to an identity matrix.
    @param m1 matrix to set
*/
void psplaMat2IdentityMatrix(float *m1);

/*
    Set a matrix to an identity matrix.
    @param m1 matrix to set
*/
void psplaMat3IdentityMatrix(float *m1);

/*
    Set a matrix to an identity matrix.
    @param m1 matrix to set
*/
void psplaMat4IdentityMatrix(float *m1);

/*
    Get the determinant of a matrix.
    @param m1 input matrix
    @param sout determinant
*/
void psplaMat2Determinant(float *m1, float *sout);

/*
    Get the determinant of a matrix.
    @param m1 input matrix
    @param sout determinant
*/
void psplaMat3Determinant(float *m1, float *sout);

/*
    Get the determinant of a matrix.
    @param m1 input matrix
    @param sout determinant
*/
void psplaMat4Determinant(float *m1, float *sout);

/*
    Get the inverse of a matrix.
    Determinant must not be zero.
    @param m1 input matrix
    @param s1 determinant
    @param mout inverse matrix
*/
void psplaMat2Inverse(float *m1, float *s1, float *mout);

/*
    Get the inverse of a matrix.
    Determinant must not be zero.
    @param m1 input matrix
    @param s1 determinant
    @param mout inverse matrix
*/
void psplaMat3Inverse(float *m1, float *s1, float *mout);

/*
    Get the inverse of a matrix.
    Determinant must not be zero.
    @param m1 input matrix
    @param s1 determinant
    @param mout inverse matrix
*/
void psplaMat4Inverse(float *m1, float *s1, float *mout);

/*
    Transpose a matrix.
    Turns a row-major matrix to column-major and vice versa.
    @param m1 input matrix
    @param mout transposed matrix
*/
void psplaMat2Transpose(float *m1, float *mout);

/*
    Transpose a matrix.
    Turns a row-major matrix to column-major and vice versa.
    @param m1 input matrix
    @param mout transposed matrix
*/
void psplaMat3Transpose(float *m1, float *mout);

/*
    Transpose a matrix.
    Turns a row-major matrix to column-major and vice versa.
    @param m1 input matrix
    @param mout transposed matrix
*/
void psplaMat4Transpose(float *m1, float *mout);

/*
    Copy a matrix.
    @param m1 source matrix
    @param m2 destination matrix
*/
void psplaMat2Copy(float *m1, float *mout);

/*
    Copy a matrix.
    @param m1 source matrix
    @param m2 destination matrix
*/
void psplaMat3Copy(float *m1, float *mout);

/*
    Copy a matrix.
    @param m1 source matrix
    @param m2 destination matrix
*/
void psplaMat4Copy(float *m1, float *mout);

#endif