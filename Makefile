CC=clang

CFLAGS := -std=gnu99 -fno-stack-protector -fshort-enums -fpack-struct=1
LDFLAGS := -lm

SOURCES := $(wildcard src/*.c src/*/*.c)
HEADERS := $(wildcard src/*.h src/*/*.h)
OBJECTS := $(subst .c,.o, $(subst src,build, $(SOURCES)))

PREFIX=/usr/local

.Phony: clean install uninstall

default: ff

ff: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

$(OBJECTS): ./build/%.o: ./src/%.c
	mkdir -p $(@D)
	$(CC) -MMD -MP -c $< -o $@ $(CFLAGS)

clean:
	rm -f ff
	rm -rf build

install: ff
	cp ff $(PREFIX)/bin
	cp ./docs/ff.1 $(PREFIX)/share/man/man1

uninstall: 
	rm -fv $(PREFIX)/bin/ff
	rm -fv $(PREFIX)/share/man/man1/ff.1
