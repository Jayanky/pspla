>[!WARNING]
>pspla3 is very early in development, and its use is not recommended for large-scale PSP projects.
<img width="2227" height="300" alt="PSPLA" src="https://github.com/user-attachments/assets/f2606b73-58aa-4546-8e59-1f12d2d4843e" />

# Description
PSPLA is a library designed to accelerate vector, matrix, and quaternion math through the PSP's [*Vector Floating-Point Unit*](https://pspdev.github.io/vfpu-docs/) (or VFPU).

Because GCC is not designed around the PSP, it lacks the ability to generate VFPU instructions through C code.
The lack of support for this instruction set outside of assembly leads to an entire co-processor being completely unused in many PSP applications.
PSPLA is a header-only library designed to enable developers to take full advantage of the system's unique hardware to create more performant software.

# Usage
PSPLA contains two ways to interface with the VFPU: directly through VFPU instruction macros, or indirectly though a higher-level math library.

>[!NOTE]
>When using the inline functions, save out any needed data from the VFPU first. Higher-level functions are allowed to clobber any VFPU register within a thread.

## Assembly Macros
Written as `pspla_vfpu_<operation>_`, these macros allow direct access to the full instruction set and registers of the co-processor.
These are recommended for building out higher-level routines that speed up utilization by reducing loads and stores, along with operations that can make use of register prefixes.

## Inline Functions
Written as `pspla_<type>_<operation>`, these functions expose a high-level interface for VFPU instructions.
These functions store out to memory after every operation, so it is recommended to chain together multiple operations on a single variable to keep the data in the cache.
