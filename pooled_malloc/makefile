SANITIZER := \
	-fsanitize=address

CXXFLAGS := \
	-fno-rtti \
	-fno-exceptions \
	-O1 -g \
	-std=c++20 \
	-fno-omit-frame-pointer

CXX := clang++

LD := clang

LDFLAGS := \
	-lstdc++

SOURCES := main.cxx

OBJECTS := $(SOURCES:%=obj/%.o)

obj/%.cxx.o: %.cxx
	mkdir -p $(dir $(@))
	$(CXX) $(CXXFLAGS) $(SANITIZER) -c $(<) -o $(@)

bin/main.elf: $(OBJECTS)
	mkdir -p $(dir $(@))
	$(LD) $(LDFLAGS) $(SANITIZER) $(^) -o $(@)

all: bin/main.elf

run: all
	./bin/main.elf

clean:
	-rm ./bin/main.elf
	-rm -rf ./obj
