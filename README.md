# pspla
A VFPU accelerated linear algebra &amp; quaternion library for the PlayStation Portable.

## Usage
### Getting Started
All you need to do to get started is to include the `pspla.h` header file, and to link with the pspla library.

### Data Formatting
Firstly, all vector and matrix data passed to pspla functions must be 16-byte aligned, as the VFPU will generate a fault if it is not.

Similarly, all scalar values passed to pspla functions must be 4-byte aligned.

Wrong:
```
float vector[4] = {...};
float scalar = 0;
```
Correct:
```
float vector[4] __attribute__((aligned(16))) = {...};
float scalar __attribute__((aligned(4))) = 0;
```
### Finding a function
All functions are prefixed with `pspla`, and are then followed by the type of data they are used for.

The types of data are `Vec2`, `Vec3`, `Vec4`, `Mat2`, `Mat3`, and `Mat4`.

Quaternions fall under the `Vec4` category.

### Getting data to and from a function
In pspla, all values are passed to and from a function by reference.

Example:
```
psplaVec3Scale(inputVector, &inputScalar, outputVector);
```
