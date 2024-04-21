CC = gcc
CFLAGS = -Wall -Wextra -I. -I/usr/include -I/usr/local/include
LDFLAGS = -L. -ldsc -lm

LIBNAME = libdsc.a
SONAME = libdsc.so
DIST_NAME = libdsc-0.1.0-alpha

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

TEST_SRCS = $(wildcard tests/test_*.c)
TESTS = $(TEST_SRCS:.c=)

ifeq ($(shell uname), Darwin)
RPATH = -Wl,-rpath,@executable_path
else
RPATH = -Wl,-rpath,'$$ORIGIN'
endif

all: static shared

static: $(LIBNAME)
$(LIBNAME): $(OBJS)
	ar rcs $@ $^

shared: $(SONAME)
$(SONAME): $(OBJS)
	$(CC) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

install: all
	sudo install -m 644 $(LIBNAME) /usr/local/lib/
	sudo install -m 644 $(SONAME) /usr/local/lib/
	sudo install -m 644 include/*.h /usr/local/include/

clean:
	rm -f $(OBJS) $(LIBNAME) $(SONAME) $(TESTS)
	rm -f $(DIST_NAME).tar.gz $(DIST_NAME).zip
	rm -f $(DIST_NAME)*.deb
	rm -f *.rpm
	rm -f *.dmg
	rm -rf $(DIST_NAME)

.PHONY: all static shared install clean test dist deb rpm dmg

test: $(LIBNAME) $(TESTS)
	for test in $(TESTS); do ./$$test; done

build-tests: $(TESTS)

tests/test_dsc_list: tests/test_dsc_list.c $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(RPATH)

tests/test_dsc_vector: tests/test_dsc_vector.c $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(RPATH)

tests/test_dsc_stack: tests/test_dsc_stack.c $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(RPATH)

tests/test_dsc_queue: tests/test_dsc_queue.c $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(RPATH)

tests/test_dsc_map: tests/test_dsc_map.c $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(RPATH)

tests/test_dsc_set: tests/test_dsc_set.c $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(RPATH)

$(TESTS): $(LIBNAME)

dist: clean
	mkdir -p $(DIST_NAME)
	cp -r include src tests docs Makefile README.md CHANGELOG.md LICENSE $(DIST_NAME)/
	tar -czf $(DIST_NAME).tar.gz $(DIST_NAME)
	zip -r $(DIST_NAME).zip $(DIST_NAME)
	rm -rf $(DIST_NAME)

deb: $(DIST_NAME).tar.gz
	tar -xzf $(DIST_NAME).tar.gz
	mkdir -p $(DIST_NAME)/DEBIAN
	cp packaging/debian/control $(DIST_NAME)/DEBIAN/
	dpkg-deb --build $(DIST_NAME)
	mv $(DIST_NAME).deb $(DIST_NAME)_$(shell dpkg --print-architecture).deb
	mv $(DIST_NAME)_$(shell dpkg --print-architecture).deb $(DIST_NAME).deb
	rm -rf $(DIST_NAME)

rpm: $(DIST_NAME).tar.gz
	tar -xzf $(DIST_NAME).tar.gz
	mkdir -p $(DIST_NAME)/SPECS
	cp packaging/rpm/libdsc.spec $(DIST_NAME)/SPECS/
	rpmbuild -bb --define "_topdir $(PWD)/$(DIST_NAME)" $(DIST_NAME)/SPECS/libdsc.spec
	mv $(DIST_NAME)/RPMS/*/*.rpm .
	rm -rf $(DIST_NAME)

dmg: $(DIST_NAME).tar.gz
	tar -xzf $(DIST_NAME).tar.gz
	mkdir -p $(DIST_NAME)/package
	cp -r $(DIST_NAME)/* $(DIST_NAME)/package/
	hdiutil create -volname "libdsc" -srcfolder $(DIST_NAME)/package -ov -format UDZO "libdsc-0.1.0.dmg"
	rm -rf $(DIST_NAME)

.PHONY: test dist deb rpm dmg
