CPP=i386-mingw32msvc-g++
GCC=i386-mingw32msvc-gcc

CFLAGS=-Wall -O2 -g -Werror
LDFLAGS=
LIBADD=-lgdi32

PROGRAM=eterforcetest

OBJECTS=eterforcetest.o etalon_measure.o test_string.o test_file.o test_time.o test_memory.o test_char.o test_encoding.o test_compare.o

.cpp.o:
	$(CPP) -c -o $@ $(CFLAGS) $<

.c.o:
	$(GCC) -c -o $@ $(CFLAGS) $<

$(PROGRAM).exe: $(OBJECTS)
	$(GCC) $^ -o $@ $(LDFLAGS) $(LIBADD)

clean:
	rm -f *.o $(PROGRAM).exe
