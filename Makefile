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

main: source/main.cpp source/dac.o source/misc.o source/find.o
	@echo "[compile] main"
	@$(CD) ./build && $(C) $(INC) -c ../source/main.cpp
	@$(L) build/*.o $(LIBS) -o main 
	@chmod +x main 

source/dac.o: source/Dac.hpp
	@echo "[compile] dac"
	@$(CD) ./build && $(C) $(INC) -c ../source/Dac.cpp

source/find.o: source/find.hpp
	@echo "[compile] find"
	@$(CD) ./build && $(C) $(INC) -c ../source/find.cpp

source/misc.o: source/misc.hpp
	@echo "[compile] misc"
	@$(CD) ./build && $(C) $(INC) -c ../source/misc.cpp

