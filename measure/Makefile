CPP=i386-mingw32msvc-g++
GCC=i386-mingw32msvc-gcc

PROGRAM=eterforcetest

.cpp.o:
	$(CPP) -c -o $@ $<

.c.o:
	$(GCC) -c -o $@ $<

$(PROGRAM).exe: eterforcetest.o etalon_measure.o
	$(GCC) $^ -o $@ -lgdi32

clean:
	rm -f *.o $(PROGRAM).exe
