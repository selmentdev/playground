CXXFLAGS := \
	-fno-rtti \
	-fno-exceptions \
	-O1 -g \
	-std=c++20 \
	-fno-omit-frame-pointer \
	-fsanitize=address

CXX := clang++

LD := clang

LDFLAGS := \
	-lstdc++ \
	-fsanitize=address

SOURCES := main.cxx

OBJECTS := $(SOURCES:%=obj/%.o)

obj/%.cxx.o: %.cxx
	mkdir -p $(dir $(@))
	$(CXX) $(CXXFLAGS) -c $(<) -o $(@)

bin/main.elf: $(OBJECTS)
	mkdir -p $(dir $(@))
	$(LD) $(LDFLAGS) $(^) -o $(@)

all: bin/main.elf

run: all
	./bin/main.elf

clean:
	rm ./bin/main.elf
	rm -rf ./obj
