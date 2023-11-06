COMPILER=g+++


build/%.o: src/%.cpp src/config.h
	$(COMPILER)-c $< -o $@
