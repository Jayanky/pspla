# This file should be used for building the EBOOT.PBP file.
# Calls CMake's Makefile for building C files and linking with PSPSDK.
# This Makefile mainly builds the assembly files into a library for linking.

ASMSRCS := source/VecOps.s	
CSRCS := source/VecOps.c
ASMOBJ := asmpspla.o
COBJ := cpspla.o
AR := psp-ar
AS := psp-as
GCC := psp-gcc
LIB := libpspla.a

all: $(ASMOBJ) $(COBJ)
	$(AR) -rcs $(LIB) $(ASMOBJ) $(COBJ)
	rm -f $(ASMOBJ)
	rm -f $(COBJ)

$(ASMOBJ) $(COBJ): $(ASMSRCS)
	$(AS) -o $(ASMOBJ) -g $(ASMSRCS)
	$(GCC) -o $(COBJ) -c $(CSRCS) -O2

clean:
	rm -f $(LIB)