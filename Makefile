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

main: source/main.cpp
	@echo "[compile] main"
	@$(CD) ./build && $(C) $(INC) -c ../source/main.cpp
	@$(L) build/*.o $(LIBS) -o main 
	@chmod +x main 

test: source/test.cpp
	@echo "[compile] test"
	@$(CD) ./build && $(C) $(INC) -c ../source/test.cpp
	@$(L) build/*.o $(LIBS) -o test
	@chmod +x test

