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
#LIBS = -lstdc++ -lrt -lzmq
LIBS = -lstdc++
#LIB_TEST = /usr/src/gtest/libgtest.a \
#		   /usr/src/gtest/libgtest_main.a -lpthread
LIB_TEST = -lpthread -lgtest -lgtest_main

.PHONY: clean
clean:
	@$(RM) main 
	@cd ./build && $(RM) *.o */*.o */*.so */*/*.o */*/*.so 


.PHONY: stats
stats:
	@wc -l -w -c -L */*.*pp */*/*.*pp 
	@echo " Lines\tWords\tBytes\tLine\t"

### MAIN BUILD TARGET #############

main: asset etherdream gfx network pipeline build/misc.o \
	build/game/entity.o \
	build/lib/etherdream.o build/main.o 
	@echo "[linking] main"
	@$(L) build/*.o build/etherdream/*.o build/asset/*.o \
		build/gfx/*.o \
		build/game/*.o \
		build/network/*.o \
		build/pipeline/*.o \
		build/lib/etherdream.o \
		$(LIBS) -lrt -lm -o main 
	@chmod +x main 

test: testing/test.o pipeline etherdream gfx network asset \
	build/game/entity.o \
	build/lib/etherdream.o
	@echo "[TESTING]"
	@$(L) build/etherdream/*.o build/asset/*.o \
		build/gfx/*.o \
		build/game/*.o \
		build/network/*.o \
		build/pipeline/*.o \
		build/lib/etherdream.o \
		$(LIBS) -lrt -lm -o test $(LIB_TEST)
	@chmod +x test

dac_report: asset etherdream gfx build/misc.o build/game/entity.o \
	build/lib/etherdream.o build/dac_report.o 
	@echo "[linking] dac_report"
	@$(L) build/*.o build/etherdream/*.o build/asset/*.o \
		build/gfx/*.o build/game/*.o \
		build/lib/etherdream.o \
		$(LIBS) -lrt -lm -o dac_report
	@chmod +x dac_report


edtest: build/lib/etherdream.o build/lib/test.o
	@echo "[linking] edtest"
	$(GCC) $(CFLAGS) -g build/lib/*o -lrt -lm -o edtest
	@chmod +x edtest

build/main.o: source/main.cpp
	@echo "[compile] main"
	@$(CD) ./build && $(C) $(INC) -c ../source/main.cpp

build/dac_report.o: source/dac_report.cpp
	@echo "[compile] dac_report"
	@$(CD) ./build && $(C) $(INC) -c ../source/dac_report.cpp

build/network_test.o: source/network_test.cpp
	@echo "[compile] network_test"
	@$(CD) ./build && $(C) $(INC) -c ../source/network_test.cpp


# =====================================================

testing/test.o: testing/test.cpp
	@echo "[compile] testing/test.cpp"
	@$(CD) ./build && $(C) $(INC) $(INC_TEST) -c ../testing/test.cpp

#pipeline_test: test/pipeline/StreamingPointBufferTest.o
#	@cd .
#
#test/pipeline/StreamingPointBufferTest.o: test/pipeline/#StreamingPointBufferTest.hpp
#	@echo "[compile] test/pipeline/StreamingPointBufferTest"
#	@$(CD) ./build/pipeline && $(C) $(INC) $(INC_TEST) \
#		-c ../../test/pipeline/StreamingPointBufferTest.cpp

# =====================================================

pipeline: build/pipeline/Frame.o build/pipeline/Tracking.o build/pipeline/Geometry.o build/pipeline/MatrixStack.o build/pipeline/FourMatrix.o build/pipeline/FrameBuffers.o build/pipeline/StreamingPointBuffer.o
	@cd .

build/pipeline/StreamingPointBuffer.o: source/pipeline/StreamingPointBuffer.hpp source/pipeline/StreamingPointBuffer.cpp
	@echo "[compile] pipeline/StreamingPointBuffer"
	@$(CD) ./build/pipeline && $(C) $(INC) \
		-c ../../source/pipeline/StreamingPointBuffer.cpp

build/pipeline/Tracking.o: source/pipeline/Tracking.hpp source/pipeline/Tracking.cpp
	@echo "[compile] pipeline/Tracking"
	@$(CD) ./build/pipeline && $(C) $(INC) \
		-c ../../source/pipeline/Tracking.cpp

build/pipeline/Frame.o: source/pipeline/Frame.hpp source/pipeline/Frame.cpp
	@echo "[compile] pipeline/Frame"
	@$(CD) ./build/pipeline && $(C) $(INC) \
		-c ../../source/pipeline/Frame.cpp

build/pipeline/FrameBuffers.o: source/pipeline/FrameBuffers.hpp source/pipeline/FrameBuffers.cpp
	@echo "[compile] pipeline/FrameBuffers"
	@$(CD) ./build/pipeline && $(C) $(INC) \
		-c ../../source/pipeline/FrameBuffers.cpp

build/pipeline/FourMatrix.o: source/pipeline/FourMatrix.hpp source/pipeline/FourMatrix.cpp
	@echo "[compile] pipeline/FourMatrix"
	@$(CD) ./build/pipeline && $(C) $(INC) \
		-c ../../source/pipeline/FourMatrix.cpp

build/pipeline/Geometry.o: source/pipeline/Geometry.hpp source/pipeline/Geometry.cpp
	@echo "[compile] pipeline/Geometry"
	@$(CD) ./build/pipeline && $(C) $(INC) \
		-c ../../source/pipeline/Geometry.cpp

build/pipeline/MatrixStack.o: source/pipeline/MatrixStack.hpp source/pipeline/MatrixStack.cpp
	@echo "[compile] pipeline/MatrixStack"
	@$(CD) ./build/pipeline && $(C) $(INC) \
		-c ../../source/pipeline/MatrixStack.cpp

#asset: build/asset/square.o build/asset/circle.o build/asset/rectangle.o
asset: build/asset/circle.o build/asset/rectangle.o
	@cd .

build/asset/rectangle.o: source/asset/rectangle.cpp source/asset/rectangle.hpp
	@echo "[compile] asset/rectangle"
	@$(CD) ./build/asset && $(C) $(INC) \
		-c ../../source/asset/rectangle.cpp

build/asset/square.o: source/asset/square.cpp source/asset/square.hpp
	@echo "[compile] asset/square"
	@$(CD) ./build/asset && $(C) $(INC) \
		-c ../../source/asset/square.cpp

build/asset/circle.o: source/asset/circle.cpp source/asset/circle.hpp
	@echo "[compile] asset/circle"
	@$(CD) ./build/asset && $(C) $(INC) \
		-c ../../source/asset/circle.cpp

etherdream: build/etherdream/Dac.o
	@cd .

build/etherdream/Dac.o: source/etherdream/Dac.cpp source/etherdream/Dac.hpp
	@echo "[compile] etherdream/dac"
	@$(CD) ./build/etherdream && $(C) $(INC) \
		-c ../../source/etherdream/Dac.cpp

network: build/network/mac_address.o build/network/ip_address.o
	@cd .

build/network/ip_address.o: source/network/ip_address.cpp source/network/ip_address.hpp
	@echo "[compile] network/ip_address"
	@$(CD) ./build/network && $(C) $(INC) \
		-c ../../source/network/ip_address.cpp

build/network/mac_address.o: source/network/mac_address.cpp source/network/mac_address.hpp
	@echo "[compile] network/mac_address"
	@$(CD) ./build/network && $(C) $(INC) \
		-c ../../source/network/mac_address.cpp

gfx: build/gfx/streamer.o build/gfx/tracking.o build/gfx/transformation.o 
	@cd .

build/gfx/streamer.o: source/gfx/streamer.cpp source/gfx/streamer.hpp
	@echo "[compile] gfx/streamer"
	@$(CD) ./build/gfx && $(C) $(INC) \
		-c ../../source/gfx/streamer.cpp

build/gfx/tracking.o: source/gfx/tracking.cpp source/gfx/tracking.hpp
	@echo "[compile] gfx/tracking"
	@$(CD) ./build/gfx && $(C) $(INC) \
		-c ../../source/gfx/tracking.cpp

build/gfx/transformation.o: source/gfx/transformation.cpp source/gfx/transformation.hpp
	@echo "[compile] gfx/transformation"
	@$(CD) ./build/gfx && $(C) $(INC) \
		-c ../../source/gfx/transformation.cpp

build/game/entity.o: source/game/entity.cpp source/game/entity.hpp
	@echo "[compile] game/entity"
	@$(CD) ./build/game && $(C) $(INC) \
		-c ../../source/game/entity.cpp

build/misc.o: source/misc.cpp source/misc.hpp
	@echo "[compile] misc"
	@$(CD) ./build && $(C) $(INC) -c ../source/misc.cpp

build/lib/etherdream.o: source/lib/etherdream.c \
		source/lib/etherdream.h
	@echo "[compile] lib/etherdream"
	@$(CD) ./build/lib && $(GCC) $(EDFLAGS) $(INC) \
		-c ../../source/lib/etherdream.c

build/lib/test.o: source/lib/test.c
	@echo "[compile] lib/test"
	@$(CD) ./build/lib && $(GCC) $(EDFLAGS) $(INC) \
		-c ../../source/lib/test.c

