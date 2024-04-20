CC = gcc
CFLAGS = -Wall -Wextra -I.
LDFLAGS = -L. -ldsc -lcheck

LIBNAME = libdsc.a
SONAME = libdsc.so

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

TEST_SRCS = $(wildcard tests/test_*.c)
TESTS = $(TEST_SRCS:.c=)

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
	rm -f $(OBJS) $(LIBNAME) $(SONAME) $(TESTS)

.PHONY: all static shared install clean test

test: $(TESTS)
	for test in $(TESTS); do ./$$test; done

tests/test_dsc_list: tests/test_dsc_list.c $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

tests/test_dsc_vector: tests/test_dsc_vector.c $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

tests/test_dsc_stack: tests/test_dsc_stack.c $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

tests/test_dsc_queue: tests/test_dsc_queue.c $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

tests/test_dsc_map: tests/test_dsc_map.c $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

tests/test_dsc_set: tests/test_dsc_set.c $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: test
