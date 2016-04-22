# See LICENSE file for copyright and liscense details.

include config.mk

SRC = shalloc.c
OBJ = $(SRC:.c=.o)

LIB = libshalloc.a
INC = shalloc.h

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) -rcs $@ $(OBJ)

testpass: testpass.o $(LIB)
	$(CC) -o $@ testpass.o $(LIB)

testcatch: testcatch.o $(LIB)
	$(CC) -o $@ testcatch.o $(LIB)

testexec: testexec.o $(LIB)
	$(CC) -o $@ testexec.o $(LIB)
.c.o:
	$(CC) $(CFLAGS) -c $<

install: $(LIB) $(INC)
	@echo @ install libshalloc to $(DESTDIR)$(PREFIX)
	@mkdir -p $(DESTDIR)$(PREFIX)/lib
	@cp $(LIB) $(DESTDIR)$(PREFIX)/lib/$(LIB)
	@mkdir -p $(DESTDIR)$(PREFIX)/include
	@cp $(INC) $(DESTDIR)$(PREFIX)/include/$(INC)

uninstall:
	@echo @ uninstall libshalloc to $(DESTDIR)$(PREFIX)
	@rm -f $(DESTDIR)$(PREFIX)/lib/$(LIB)
	@rm -f $(DESTDIR)$(PREFIX)/include/$(INC)

test-pass: testpass testcatch
	./testpass | ./testcatch

test-exec: testexec
	./testexec 42 | ./testexec

clean:
	rm -f $(LIB) testpass testcatch testexec *.o

.PHONY: install uninstall test clean
