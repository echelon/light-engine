### VARIABLES #############
C = g++ -std=c++0x -pthread -g -Wall
GCC = gcc -pthread -g -Wall 
EDFLAGS = -Wall -Wextra -ansi -pedantic -std=c99 -lm -lpthread
L = g++ -std=c++0x -pthread -g
RM = /bin/rm -f
CD = cd
INC = 
#LIBS = -lstdc++ -lrt -lzmq
LIBS = -lstdc++
.PHONY: clean
clean:
	@$(RM) main 
	@cd ./build && $(RM) *.o */*.o */*.so */*/*.o */*/*.so 


.PHONY: stats
stats:
	@wc -l -w -c -L */*.*pp */*/*.*pp 
	@echo " Lines\tWords\tBytes\tLine\t"

### MAIN BUILD TARGET #############

main: asset etherdream gfx build/misc.o build/game/entity.o \
	build/lib/etherdream.o build/main.o 
	@echo "[linking] main"
	@$(L) build/*.o build/etherdream/*.o build/asset/*.o \
		build/gfx/*.o build/game/*.o \
		build/lib/etherdream.o \
		$(LIBS) -lrt -lm -o main 
	@chmod +x main 

gfx2test: gfx2 build/gfx2/test.o
	@echo "[linking] gfx2test"
	@$(L) build/gfx2/*.o \
		$(LIBS) -lrt -lm -o gfx2test
	@chmod +x gfx2test

edtest: build/lib/etherdream.o build/lib/test.o
	@echo "[linking] edtest"
	$(GCC) $(CFLAGS) -g build/lib/*o -lrt -lm -o edtest
	@chmod +x edtest

build/main.o: source/main.cpp
	@echo "[compile] main"
	@$(CD) ./build && $(C) $(INC) -c ../source/main.cpp


gfx2: build/gfx2/geo.o build/gfx2/path.o
	@cd .

build/gfx2/geo.o: source/gfx2/geo.cpp source/gfx2/geo.hpp
	@echo "[compile] gfx2/geo"
	@mkdir -p ./build/gfx2
	@$(CD) ./build/gfx2 && $(C) $(INC) \
		-c ../../source/gfx2/geo.cpp

build/gfx2/path.o: source/gfx2/path.cpp
	@echo "[compile] gfx2/path"
	@mkdir -p ./build/gfx2
	@$(CD) ./build/gfx2 && $(C) $(INC) \
		-c ../../source/gfx2/path.cpp


build/gfx2/test.o: source/gfx2/test.cpp
	@echo "[compile] gfx2/test"
	@mkdir -p ./build/gfx2
	@$(CD) ./build/gfx2 && $(C) $(INC) \
		-c ../../source/gfx2/test.cpp

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

etherdream: build/etherdream/Dac.o build/etherdream/find.o
	@cd .

build/etherdream/Dac.o: source/etherdream/Dac.cpp source/etherdream/Dac.hpp
	@echo "[compile] etherdream/dac"
	@$(CD) ./build/etherdream && $(C) $(INC) \
		-c ../../source/etherdream/Dac.cpp

build/etherdream/find.o: source/etherdream/find.cpp source/etherdream/find.hpp
	@echo "[compile] etherdream/find"
	@$(CD) ./build/etherdream && $(C) $(INC) \
		-c ../../source/etherdream/find.cpp

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

