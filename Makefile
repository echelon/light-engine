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

main: source/main.cpp build/etherdream/dac.o build/misc.o build/etherdream/find.o build/asset/circle.o build/gfx/streamer.o build/gfx/tracking.o build/game/entity.o
	@echo "[compile] main"
	@$(CD) ./build && $(C) $(INC) -c ../source/main.cpp
	@echo "[linking] main"
	@$(L) build/*.o build/etherdream/*.o build/asset/*.o \
		build/gfx/*.o build/game/*.o \
		$(LIBS) -o main 
	@chmod +x main 

build/etherdream/dac.o: source/etherdream/Dac.cpp
	@echo "[compile] etherdream/dac"
	@$(CD) ./build/etherdream && $(C) $(INC) \
		-c ../../source/etherdream/Dac.cpp

build/etherdream/find.o: source/etherdream/find.cpp
	@echo "[compile] etherdream/find"
	@$(CD) ./build/etherdream && $(C) $(INC) \
		-c ../../source/etherdream/find.cpp

build/asset/circle.o: source/asset/circle.cpp
	@echo "[compile] asset/circle"
	@$(CD) ./build/asset && $(C) $(INC) \
		-c ../../source/asset/circle.cpp

build/gfx/streamer.o: source/gfx/streamer.cpp
	@echo "[compile] gfx/streamer"
	@$(CD) ./build/gfx && $(C) $(INC) \
		-c ../../source/gfx/streamer.cpp

build/gfx/tracking.o: source/gfx/tracking.cpp
	@echo "[compile] gfx/tracking"
	@$(CD) ./build/gfx && $(C) $(INC) \
		-c ../../source/gfx/tracking.cpp

build/game/entity.o: source/game/entity.cpp
	@echo "[compile] game/entity"
	@$(CD) ./build/game && $(C) $(INC) \
		-c ../../source/game/entity.cpp

build/misc.o: source/misc.cpp
	@echo "[compile] misc"
	@$(CD) ./build && $(C) $(INC) -c ../source/misc.cpp

