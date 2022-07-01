# BLIS_PREFIX = ./blis
# BLIS_INC = $(BLIS_PREFIX)/include/haswell
# BLIS_LIB = $(BLIS_PREFIX)/lib/haswell/libblis.a

OTHER_LIBS = -L/usr/lib -lm -lpthread

# indicate how the object files are to be created
CC         := icc
#CFLAGS     := -g -O3 -axCORE-AVX2  -qopenmp
# CFLAGS     := -g -O0 -I$(BLIS_INC)
# CFLAGS     := -g -O3
# CFLAGS     := -O3
CFLAGS     := -g -O3 -axCORE-AVX2  -qopenmp


OBJECT_FILES := saxpy.o driver.o helper.o sgemv.o sscal.o dscal.o daxpy.o sgemm.o 

saxpy: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) $(BLIS_LIB) $(OTHER_LIBS) -o saxpy

# saxpy.o : saxpy.c
# 	$(CC) $(CFLAGS) -c saxpy.c

# driver.o : driver.c
# 	$(CC) $(CFLAGS) -c driver.c

# helper.o : helper.c
# 	$(CC) $(CFLAGS) -c helper.c

clean:
	rm *.o 
