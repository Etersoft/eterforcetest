include Makefile.mingw

PUBDIR=/var/ftp/pub/Etersoft/Eterforcetest

CFLAGS+=-Wall -O0 -g -Werror
LDFLAGS=
LIBADD=-lgdi32 -lole32 $(MINGWLIBDIR)/libuuid.a

PROGRAM=eterforcetest

OBJECTS=eterforcetest.o etalon_measure.o test_string.o test_file.o test_time.o test_memory.o test_char.o test_encoding.o test_compare.o test_window.o test_font.o test_menu.o test_message.o test_dialog.o test_x11dc.o test_memdc.o test_reg.o test_ole32.o

.cpp.o:
	$(CXX) -c -o $@ $(CFLAGS) $<

.c.o:
	$(CC) -c -o $@ $(CFLAGS) $<

$(PROGRAM).exe: $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS) $(LIBADD)

clean:
	rm -f *.o $(PROGRAM).exe

strip:
	$(STRIP) $(PROGRAM).exe

publish: strip
	cp -f $(PROGRAM).exe $(PUBDIR)/
