CC=clang

CFLAGS := -std=gnu99 -fno-stack-protector -fshort-enums -fpack-struct=1
LDFLAGS := -lm

SOURCES := $(wildcard src/*.c src/*/*.c)
HEADERS := $(wildcard src/*.h src/*/*.h)
OBJECTS := $(subst .c,.o, $(subst src,build, $(SOURCES)))

.Phony: clean

default: ff

ff: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

$(OBJECTS): ./build/%.o: ./src/%.c
	mkdir -p $(@D)
	$(CC) -MMD -MP -c $< -o $@ $(CFLAGS)

clean:
	rm -f ff
	rm -rf build
