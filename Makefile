### VARIABLES #############
C = g++ -std=c++0x -pthread -g -Wall
GCC = gcc -pthread -g -Wall 
EDFLAGS = -Wall -Wextra -ansi -pedantic -std=c99 -lm -lpthread
L = g++ -std=c++0x -pthread -g
RM = /bin/rm -f
CD = cd
INC = 
PWD = $(shell pwd)
INC_TEST= -I$(PWD)/source
LIBS = -lstdc++
LIB_TEST = -lpthread -lgtest

# =====================================================

.PHONY: clean
clean:
	@$(RM) main 
	@$(RM) test
	@cd ./build && $(RM) *.o */*.o */*.so */*/*.o */*/*.so 


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
		$(LIBS) -lrt -lm -o main 
	@chmod +x main 

main_modules: \
	asset \
	etherdream \
	game \
	gfx \
	network \
	pipeline
	@cd .

build/source/main.o: source/main.cpp
	@echo "[compile] main"
	@$(CD) ./build/source && $(C) $(INC) -c ../../source/main.cpp

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
		$(LIBS) -lrt -lm -o test $(LIB_TEST)
	@chmod +x test

test_modules: \
	test_etherdream
	@cd .

build/testing/test.o: testing/test.cpp
	@echo "[compile] testing/test.cpp"
	@$(CD) ./build/testing && $(C) $(INC) $(INC_TEST) -c ../../testing/test.cpp


# =====================================================

pipeline: \
	build/source/pipeline/Frame.o \
	build/source/pipeline/SimpleTracking.o \
	build/source/pipeline/Geometry.o \
	build/source/pipeline/MatrixStack.o \
	build/source/pipeline/FourMatrix.o \
	build/source/pipeline/FrameBuffers.o
	@cd .

build/source/pipeline/SimpleTracking.o: \
	source/pipeline/SimpleTracking.hpp \
	source/pipeline/SimpleTracking.cpp
	@echo "[compile] source/pipeline/SimpleTracking"
	@$(CD) ./build/source/pipeline && $(C) $(INC) \
		-c ../../../source/pipeline/SimpleTracking.cpp

build/source/pipeline/Frame.o: \
	source/pipeline/Frame.hpp \
	source/pipeline/Frame.cpp
	@echo "[compile] source/pipeline/Frame"
	@$(CD) ./build/source/pipeline && $(C) $(INC) \
		-c ../../../source/pipeline/Frame.cpp

build/source/pipeline/FrameBuffers.o: \
	source/pipeline/FrameBuffers.hpp \
	source/pipeline/FrameBuffers.cpp
	@echo "[compile] source/pipeline/FrameBuffers"
	@$(CD) ./build/source/pipeline && $(C) $(INC) \
		-c ../../../source/pipeline/FrameBuffers.cpp

build/source/pipeline/FourMatrix.o: \
	source/pipeline/FourMatrix.hpp \
	source/pipeline/FourMatrix.cpp
	@echo "[compile] source/pipeline/FourMatrix"
	@$(CD) ./build/source/pipeline && $(C) $(INC) \
		-c ../../../source/pipeline/FourMatrix.cpp

build/source/pipeline/Geometry.o: \
	source/pipeline/Geometry.hpp \
	source/pipeline/Geometry.cpp
	@echo "[compile] source/pipeline/Geometry"
	@$(CD) ./build/source/pipeline && $(C) $(INC) \
		-c ../../../source/pipeline/Geometry.cpp

build/source/pipeline/MatrixStack.o: \
	source/pipeline/MatrixStack.hpp \
	source/pipeline/MatrixStack.cpp
	@echo "[compile] source/pipeline/MatrixStack"
	@$(CD) ./build/source/pipeline && $(C) $(INC) \
		-c ../../../source/pipeline/MatrixStack.cpp

# =====================================================

asset: \
	build/source/asset/circle.o \
	build/source/asset/rectangle.o
	@cd .

build/source/asset/rectangle.o: \
	source/asset/rectangle.cpp \
	source/asset/rectangle.hpp
	@echo "[compile] source/asset/rectangle"
	@$(CD) ./build/source/asset && $(C) $(INC) \
		-c ../../../source/asset/rectangle.cpp

build/source/asset/square.o: \
	source/asset/square.cpp \
	source/asset/square.hpp
	@echo "[compile] source/asset/square"
	@$(CD) ./build/source/asset && $(C) $(INC) \
		-c ../../../source/asset/square.cpp

build/source/asset/circle.o: \
	source/asset/circle.cpp \
	source/asset/circle.hpp
	@echo "[compile] source/asset/circle"
	@$(CD) ./build/source/asset && $(C) $(INC) \
		-c ../../../source/asset/circle.cpp

# =====================================================

etherdream: \
	build/source/etherdream/Dac.o \
	build/source/etherdream/StreamingPointBuffer.o
	@cd .

build/source/etherdream/StreamingPointBuffer.o: \
	source/etherdream/StreamingPointBuffer.hpp \
	source/etherdream/StreamingPointBuffer.cpp
	@echo "[compile] source/etherdream/StreamingPointBuffer"
	@$(CD) ./build/source/etherdream && $(C) $(INC) \
		-c ../../../source/etherdream/StreamingPointBuffer.cpp

build/source/etherdream/Dac.o: \
	source/etherdream/Dac.cpp \
	source/etherdream/Dac.hpp
	@echo "[compile] source/etherdream/dac"
	@$(CD) ./build/source/etherdream && $(C) $(INC) \
		-c ../../../source/etherdream/Dac.cpp

# =====================================================

network: \
	build/source/network/mac_address.o \
	build/source/network/ip_address.o
	@cd .

build/source/network/ip_address.o: \
	source/network/ip_address.cpp \
	source/network/ip_address.hpp
	@echo "[compile] source/network/ip_address"
	@$(CD) ./build/source/network && $(C) $(INC) \
		-c ../../../source/network/ip_address.cpp

build/source/network/mac_address.o: \
	source/network/mac_address.cpp \
	source/network/mac_address.hpp
	@echo "[compile] source/network/mac_address"
	@$(CD) ./build/source/network && $(C) $(INC) \
		-c ../../../source/network/mac_address.cpp

# =====================================================

gfx: \
	build/source/gfx/streamer.o \
	build/source/gfx/tracking.o \
	build/source/gfx/transformation.o 
	@cd .

build/source/gfx/streamer.o: \
	source/gfx/streamer.cpp \
	source/gfx/streamer.hpp
	@echo "[compile] source/gfx/streamer"
	@$(CD) ./build/source/gfx && $(C) $(INC) \
		-c ../../../source/gfx/streamer.cpp

build/source/gfx/tracking.o: \
	source/gfx/tracking.cpp \
	source/gfx/tracking.hpp
	@echo "[compile] source/gfx/tracking"
	@$(CD) ./build/source/gfx && $(C) $(INC) \
		-c ../../../source/gfx/tracking.cpp

build/source/gfx/transformation.o: \
	source/gfx/transformation.cpp \
	source/gfx/transformation.hpp
	@echo "[compile] source/gfx/transformation"
	@$(CD) ./build/source/gfx && $(C) $(INC) \
		-c ../../../source/gfx/transformation.cpp

# =====================================================

game: \
	build/source/game/entity.o

build/source/game/entity.o: \
	source/game/entity.cpp \
	source/game/entity.hpp
	@echo "[compile] source/game/entity"
	@$(CD) ./build/source/game && $(C) $(INC) \
		-c ../../../source/game/entity.cpp

# =====================================================

test_etherdream: \
	build/testing/etherdream/StreamingPointBufferTest.o
	@cd .

build/testing/etherdream/StreamingPointBufferTest.o: \
	testing/etherdream/StreamingPointBufferTest.hpp \
	testing/etherdream/StreamingPointBufferTest.cpp
	@echo "[compile] testing/etherdream/StreamingPointBufferTest"
	@$(CD) ./build/testing/etherdream && $(C) $(INC) $(INC_TEST) \
		-c ../../../testing/etherdream/StreamingPointBufferTest.cpp

