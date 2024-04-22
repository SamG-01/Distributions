# by default, make will try to build the first target it encounters.
# here we make up a dummy name "ALL" (note: this is not a special make
# name, it is just commonly used).

ALL: Distribution

# find all of the source files and header files

SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.h)

# create a list of object files by replacing .cpp with .o

OBJECTS := $(SOURCES:.cpp=.o)

# a recipe for making an object file from a .cpp file
# Note: this makes every header file a dependency of every object file,
# which is not ideal, but it is safe.

%.exe : %.cpp ${HEADERS}
	g++ -c $<

# explicitly write the rule for linking together the executable

Distribution: ${OBJECTS}
  g++ -o $@ ${OBJECTS}

unit_tests: Distribution
	./tests/ > /dev/null
	@if [ $$? -eq 0 ]; then echo "tests passed"; fi

clean:
	rm -f *.exe Distribution
