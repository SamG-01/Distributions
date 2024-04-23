# by default, make will try to build the first target it encounters.
# here we make up a dummy name "ALL" (note: this is not a special make
# name, it is just commonly used).

ALL: testing
# explicitly write the rule for linking together the executable

tests/Tests.exe: include/Distribution.h include/RandomDistribution.h
	g++ -o tests/Tests.exe tests/Tests.cpp

testing: tests/Tests.exe
	$(shell ./tests/Tests.exe > out)
	@if [ ${.SHELLSTATUS} = 0 ]; then echo "all tests passed"; exit 0; else exit 1; fi
