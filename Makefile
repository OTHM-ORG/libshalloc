# See LICENSE file for copyright and liscense details.

include config.mk

SRC = shalloc.c
OBJ = $(SRC:.c=.o)

LIB = libshalloc.a
INC = shalloc.h

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) -rcs $@ $(OBJ)

shalloctest: shalloctest.o $(LIB)
	$(CC) -o $@ shalloctest.o $(LIB)

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

clean:
	rm -f $(LIB) shalloctest shalloctest.o $(OBJ)
