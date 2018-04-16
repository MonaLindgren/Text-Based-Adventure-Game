#makefile for Lab 3
#tecken:
# $< - väljer den första
# 
# File names
CXXFLAGS = -std=c++11 -Wall -g 
CXX = g++
OBJ = ./build
EXEC = catgame
EXEC_PATH = ./bin
SRC_PATH = ./src
SRCS = $(wildcard $(SRC_PATH)/*.cpp) 


# Main target
$(EXEC_PATH)/$(EXEC): main.o $(OBJ)/game.o $(OBJ)/actor.o $(OBJ)/cat.o $(OBJ)/enemy.o $(OBJ)/environment.o $(OBJ)/room.o $(OBJ)/object.o $(OBJ)/food.o $(OBJ)/weapon.o $(OBJ)/container.o $(OBJ)/observer.o $(OBJ)/catgameobserver.o $(OBJ)/inputoutput.o $(OBJ)/kitchen.o
	@echo New executable
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o : main.cpp $(SRC_PATH)/game.hpp $(SRC_PATH)/game.cpp 
	@echo New object main file
	$(COMPILE.cpp) $< -o $@
#$(EXEC_PATH)/$(EXEC): main.cpp $(OBJ)/a.o 
#	@echo $^
#	$(CXX) $(CXXFLAGS) $< -o $@

##dependencies, härifrån
DEPDIR = ./d
$(shell mkdir -p $(DEPDIR) >/dev/null)	#skapar en underkatalog i current path och discardar output från stdout
#kompilatorflaggor för att GCC ska skapa en dependency file:
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td	
# DEPFLAGS kommer att bli som en funktion typ. 
#nedan definieras regler för kompilering.. typ
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.cpp = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

#overrida inbyggd rule så att objektfilen byggs med egendefinierad rule nedan istället
%.o : %.cpp
$(OBJ)/%.o : $(SRC_PATH)/%.cpp $(DEPDIR)/%.d
	@echo New object file from $<
	$(COMPILE.cpp) $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))

run: bin/$(EXEC)
	./$<

valgrind: bin/$(EXEC)
	valgrind --leak-check=full -v ./$<
clean: 
	$(RM) bin/$(EXEC) $(wildcard d/*.d) $(wildcard build/*.o) main.o *~