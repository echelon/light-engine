# ==================== VARIABLES ======================
RM := /bin/rm -f
C  := g++ -std=c++0x -pthread -g -Wall -Wextra -pedantic
L  := g++ -std=c++0x -pthread -g -Wall -Wextra -pedantic

PROJECT_DIR := $(shell pwd)
SOURCE_DIR  := "$(PROJECT_DIR)/source"
BUILD_DIR   := "$(PROJECT_DIR)/build"

INC_ALL  := 
INC_MAIN := $(INC_ALL)
INC_TEST := $(INC_ALL) -I$(PWD)/source

LIB_ALL  := -lstdc++ -lrt -lm
LIB_MAIN := $(LIB_ALL)
LIB_TEST := $(LIB_ALL) -lpthread -lgtest

# =====================================================

# Compile a source file and output to the build dir.
# $(call compile_, rel/path/to/file, file.cpp, includes)

compile_ =                                            \
	mkdir -p "$(BUILD_DIR)/$(1)" ;                    \
	$(C) $(3) -c "$(1)/$(2)" -o                       \
		"$(BUILD_DIR)/$(1)/$(patsubst %.cpp,%.o,$(2))"

compile_main = $(call compile_,$(1),$(2),$(INC_MAIN))
compile_test = $(call compile_,$(1),$(2),$(INC_TEST))

# =====================================================

.PHONY: clean
clean:
	@cd $(PROJECT_DIR) && \
		$(RM) main &&     \
		$(RM) test
	@cd $(BUILD_DIR) &&            \
		$(RM) *.o */*.o */*/*.o && \
		$(RM) *.so */*.so */*/*.so

# =====================================================

.PHONY: stats
stats:
	@wc -l -w -c -L */*.*pp */*/*.*pp */*/*/*pp
	@echo " Lines\tWords\tBytes\tLine\t"

# =====================================================

main: \
	main_modules \
	build/source/main.o 
	@echo "[linking] main"
	@$(L) \
		build/source/main.o \
		build/source/*/*.o \
		$(LIB_MAIN) -lrt -lm -o main 
	@chmod +x main 

main_modules: \
	etherdream \
	network \
	pipeline \
	tools
	@cd .

build/source/main.o: source/main.cpp
	@echo "[compile] main"
	@$(call compile_main,source,main.cpp)

# =====================================================

test: \
	main_modules \
	test_modules \
	build/testing/test.o
	@echo "[compile test]"
	@$(L) \
		build/testing/test.o \
		build/testing/*/*.o \
		build/source/*/*.o \
		$(LIB_TEST) -lrt -lm -o test
	@chmod +x test

test_modules: \
	test_etherdream
	@cd .

build/testing/test.o: testing/test.cpp
	@echo "[compile] testing/test.cpp"
	@$(call compile_test,testing,test.cpp)

# =====================================================

pipeline: \
	build/source/pipeline/Frame.o \
	build/source/pipeline/SimpleTracking.o \
	build/source/pipeline/Geometry.o \
	build/source/pipeline/MatrixStack.o \
	build/source/pipeline/FourMatrix.o \
	build/source/pipeline/FrameBuffers.o
	@cd .

build/source/pipeline/%.o : \
	source/pipeline/%.cpp \
	source/pipeline/%.hpp
	@echo "[compile $(<D)] $(*F)"
	@$(call compile_main,$(<D),$(<F))

# =====================================================

etherdream: \
	build/source/etherdream/Dac.o \
	build/source/etherdream/StreamingPointBuffer.o \
	build/source/etherdream/get_flags.o
	@cd .

build/source/etherdream/%.o : \
	source/etherdream/%.cpp \
	source/etherdream/%.hpp
	@echo "[compile $(<D)] $(*F)"
	@$(call compile_main,$(<D),$(<F))

# =====================================================

network: \
	build/source/network/mac_address.o \
	build/source/network/ip_address.o
	@cd .

build/source/network/%.o : \
	source/network/%.cpp \
	source/network/%.hpp
	@echo "[compile $(<D)] $(*F)"
	@$(call compile_main,$(<D),$(<F))

# =====================================================

tools: \
	build/source/tools/BounceAnimation.o

build/source/tools/%.o : \
	source/tools/%.cpp \
	source/tools/%.hpp
	@echo "[compile $(<D)] $(*F)"
	@$(call compile_main,$(<D),$(<F))

# =====================================================

test_etherdream: \
	build/testing/etherdream/StreamingPointBufferTest.o
	@cd .

build/testing/etherdream/%.o : \
	source/testing/etherdream/%.cpp \
	source/testing/etherdream/%.hpp
	@echo "[compile $(<D)] $(*F)"
	@$(call compile_test,$(<D),$(<F))

