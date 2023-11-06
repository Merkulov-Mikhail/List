COMPILER=g++


all: mkDir main.exe
	@echo "/--------\\"
	@echo "|  DONE  |"
	@echo "\\--------/"

mkDir:
ifeq (,$(wildcard ./$(BUILD_DIR)))
	mkdir $(BUILD_DIR)
endif
ifeq (,$(wildcard ./$(SOURCES_DIR)))
	mkdir $(SOURCES_DIR)
endif


main.exe: build/main.o build/list.o
	$(COMPILER) $^ -o $@

build/%.o: src/%.cpp src/list.h
	$(COMPILER) -c $< -o $@
