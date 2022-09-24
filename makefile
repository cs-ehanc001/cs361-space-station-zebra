PROJNAME=Space_Station_Zebra
STD=-std=c++17
OPT=-O0
WARN=-Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wredundant-decls -Wconversion -Wnon-virtual-dtor -Wunused -Wdouble-promotion -Wformat=2 -Wnull-dereference -Wimplicit-fallthrough -Wuninitialized -Wstrict-overflow=4 -Wold-style-cast -Wfloat-equal -Wundef -Wshadow -Wfree-nonheap-object -Wsign-conversion -Wno-multichar -Woverloaded-virtual -Wctor-dtor-privacy -Wsign-promo -Wmisleading-indentation -Wzero-as-null-pointer-constant -Wsuggest-override -Weffc++ -Wno-error=effc++ -fsanitize=address -fsanitize=leak -fsanitize=undefined -Werror
CXX=g++
ADDFLAGS=
CXXFLAGS=$(STD) $(OPT) $(ADDFLAGS) $(WARN)
TSTARGS=
EXE=bin/$(PROJNAME)

.PHONY: default
default: tags exe test

.PHONY: exe
exe: tst/obj bin obj $(EXE)

.PHONY: test
test: tst/bin/test
	@echo ; echo
	@printf "\033[1;32mTest Results:\033[1;0m\n\n"
	@./run_tests $(TSTARGS)

.PHONY: tags
tags:
	@printf "\033[1;32mGenerating ctags\033[1;0m\n"
	@ctags -R src inc tst >/dev/null 2>&1

.PHONY: doc
doc:
	@printf "\033[1;32mGenerating docs\033[1;0m\n"
	@doxygen >/dev/null 2>&1

.PHONY: docopen
docopen: doc
	@firefox -new-window doc/html/index.html >/dev/null 2>&1

.PHONY: all
all: tags exe assembly preprocess doc test

.PHONY: assembly
assembly: asm asm/ship.s asm/main.s

.PHONY: preprocess
preprocess: pre pre/ship.ii pre/main.ii

asm:
	@mkdir -p asm

pre:
	@mkdir -p pre

bin:
	@mkdir -p bin

obj:
	@mkdir -p obj

tst/bin:
	@mkdir -p tst/bin

tst/obj:
	@mkdir -p tst/obj

.PHONY: clean
clean:
	@printf "\n\t\033[1;32mCLEAN\033[1;0m\n"
	@rm -f obj/* bin/* tst/obj/* tst/bin/*
	@rm -rf asm pre doc/html

$(EXE): obj/ship.o obj/main.o
	@printf "\033[1;32mLinking\t\t $(EXE)\033[1;0m\n"
	@$(CXX) -o $@ $^ $(CXXFLAGS)
	@ln -sf $(EXE) ./run

tst/bin/test: tst/bin tst/obj tst/obj/maintest.o tst/obj/test_ship.o tst/obj/test_random.o obj/ship.o obj/main.o
	@printf "\033[1;32mLinking\t\t tst/bin/test\033[1;0m\n"
	@rm -f tst/obj/main.o
	@$(CXX) -o $@ tst/obj/*.o $(CXXFLAGS)
	@ln -sf tst/bin/test ./run_tests

obj/ship.o: src/ship.cpp inc/utils/algorithm.hpp inc/random.hpp inc/constants.h inc/ship.h inc/ship.h
	@printf "\033[1;32mBuilding object\t $@\033[1;0m\n"
	@$(CXX) -c -o $@ $< -Iinc $(CXXFLAGS)
	@ln -sf ../../obj/ship.o tst/obj/ship.o

asm/ship.s: src/ship.cpp inc/utils/algorithm.hpp inc/random.hpp inc/constants.h inc/ship.h inc/ship.h
	@printf "\033[1;32mGenerating\t $@\033[1;0m\n"
	@$(CXX) -S -o $@ $< -Iinc $(CXXFLAGS)

pre/ship.ii: src/ship.cpp inc/utils/algorithm.hpp inc/random.hpp inc/constants.h inc/ship.h inc/ship.h
	@printf "\033[1;32mPreprocessing\t $@\033[1;0m\n"
	@$(CXX) -E -o $@ $< -Iinc $(CXXFLAGS)

obj/main.o: src/main.cpp inc/constants.h
	@printf "\033[1;32mBuilding object\t $@\033[1;0m\n"
	@$(CXX) -c -o $@ $< -Iinc $(CXXFLAGS)
	@ln -sf ../../obj/main.o tst/obj/main.o

asm/main.s: src/main.cpp inc/constants.h
	@printf "\033[1;32mGenerating\t $@\033[1;0m\n"
	@$(CXX) -S -o $@ $< -Iinc $(CXXFLAGS)

pre/main.ii: src/main.cpp inc/constants.h
	@printf "\033[1;32mPreprocessing\t $@\033[1;0m\n"
	@$(CXX) -E -o $@ $< -Iinc $(CXXFLAGS)

tst/obj/maintest.o: tst/src/maintest.cpp tst/inc/test_utils.hpp inc/utils/etc.hpp inc/utils/algorithm.hpp inc/utils/metaprogramming.hpp inc/utils/term_colors.h tst/inc/test_random.h inc/random.hpp inc/constants.h inc/ship.h tst/inc/test_ship.h inc/ship.h
	@printf "\033[1;32mBuilding object\t $@\033[1;0m\n"
	@$(CXX) -c -o $@ $< -Iinc -Itst/inc $(CXXFLAGS)

tst/obj/test_ship.o: tst/src/test_ship.cpp inc/utils/algorithm.hpp inc/utils/etc.hpp inc/utils/metaprogramming.hpp tst/inc/test_ship.h inc/ship.h inc/constants.h tst/inc/test_utils.hpp inc/utils/term_colors.h
	@printf "\033[1;32mBuilding object\t $@\033[1;0m\n"
	@$(CXX) -c -o $@ $< -Iinc -Itst/inc $(CXXFLAGS)

tst/obj/test_random.o: tst/src/test_random.cpp inc/utils/etc.hpp inc/utils/algorithm.hpp inc/utils/metaprogramming.hpp inc/constants.h tst/inc/test_random.h inc/random.hpp inc/constants.h inc/ship.h tst/inc/test_utils.hpp inc/utils/term_colors.h
	@printf "\033[1;32mBuilding object\t $@\033[1;0m\n"
	@$(CXX) -c -o $@ $< -Iinc -Itst/inc $(CXXFLAGS)
