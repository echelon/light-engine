### VARIABLES #############
C = g++ -std=c++0x -pthread -g -Wall
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
	build/main.o 
	@echo "[linking] main"
	@$(L) build/*.o build/etherdream/*.o build/asset/*.o \
		build/gfx/*.o build/game/*.o \
		$(LIBS) -o main 
	@chmod +x main 

build/main.o: source/main.cpp
	@echo "[compile] main"
	@$(CD) ./build && $(C) $(INC) -c ../source/main.cpp

asset: build/asset/square.o build/asset/circle.o
	@cd .

build/asset/square.o: source/asset/square.cpp
	@echo "[compile] asset/square"
	@$(CD) ./build/asset && $(C) $(INC) \
		-c ../../source/asset/square.cpp

build/asset/circle.o: source/asset/circle.cpp
	@echo "[compile] asset/circle"
	@$(CD) ./build/asset && $(C) $(INC) \
		-c ../../source/asset/circle.cpp

etherdream: build/etherdream/Dac.o build/etherdream/find.o
	@cd .

build/etherdream/Dac.o: source/etherdream/Dac.cpp
	@echo "[compile] etherdream/dac"
	@$(CD) ./build/etherdream && $(C) $(INC) \
		-c ../../source/etherdream/Dac.cpp

build/etherdream/find.o: source/etherdream/find.cpp
	@echo "[compile] etherdream/find"
	@$(CD) ./build/etherdream && $(C) $(INC) \
		-c ../../source/etherdream/find.cpp

gfx: build/gfx/streamer.o build/gfx/tracking.o build/gfx/transformation.o 
	@cd .


build/gfx/streamer.o: source/gfx/streamer.cpp
	@echo "[compile] gfx/streamer"
	@$(CD) ./build/gfx && $(C) $(INC) \
		-c ../../source/gfx/streamer.cpp

build/gfx/tracking.o: source/gfx/tracking.cpp
	@echo "[compile] gfx/tracking"
	@$(CD) ./build/gfx && $(C) $(INC) \
		-c ../../source/gfx/tracking.cpp

build/gfx/transformation.o: source/gfx/transformation.cpp
	@echo "[compile] gfx/transformation"
	@$(CD) ./build/gfx && $(C) $(INC) \
		-c ../../source/gfx/transformation.cpp

build/game/entity.o: source/game/entity.cpp
	@echo "[compile] game/entity"
	@$(CD) ./build/game && $(C) $(INC) \
		-c ../../source/game/entity.cpp

build/misc.o: source/misc.cpp
	@echo "[compile] misc"
	@$(CD) ./build && $(C) $(INC) -c ../source/misc.cpp

