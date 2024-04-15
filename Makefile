CC = clang
CFLAGS = -Wall -Wextra -I.
LDFLAGS = -L. -ldsc

LIBNAME = libdsc.a
SONAME = libdsc.so

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

all: static shared

static: $(LIBNAME)
$(LIBNAME): $(OBJS)
	ar rcs $@ $^

shared: $(SONAME)
$(SONAME): $(OBJS)
	$(CC) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install: all
	sudo install -m 644 $(LIBNAME) /usr/local/lib/
	sudo install -m 644 $(SONAME) /usr/local/lib/
	sudo install -m 644 include/*.h /usr/local/include/

clean:
	rm -f $(OBJS) $(LIBNAME) $(SONAME)

.PHONY: all static shared install clean

test: $(LIBNAME) test_list
	./test_list

test_list: tests/test_dsc_list.c $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $^ -lcheck

.PHONY: test