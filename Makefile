COMPILER=g++


all: mkDirs main.exe
	@echo "/--------\\"
	@echo "|  DONE  |"
	@echo "\\--------/"

mkDirs:
ifeq (,$(wildcard ./build))
	mkdir build
endif
ifeq (,$(wildcard ./src))
	mkdir src
endif


main.exe: build/main.o build/list.o
	$(COMPILER) $^ -o $@

build/%.o: src/%.cpp src/list.h
	$(COMPILER) -c $< -o $@
