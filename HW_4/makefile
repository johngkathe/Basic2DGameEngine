#Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++11  #Add more flags as you see fit!
LDFLAGS = `sdl2-config --libs --clags` -ggdb3 -O0 -Wall -lSDL2_image -lm 

#Executable name.
#NOTE: If you change the name to include a filepath, it will put the executable
#      at that location. Use that to get the executable in the right position
#      for finding any other files like images!
EXEC = my_game

#Function for finding source code. Touch at your own risk!
glob = $(foreach d, $(wildcard $(1:=/*)), $(call glob, $d, $2) $(filter $(subst *, %, $2), $d))

#Automatically constructed file lists
SRCS := $(wildcard *.cpp)
SRCS += $(call glob, *, *.cpp)

HDRS := $(wildcard *.h)
HDRS += $(call glob, *, *.h)

OBJS := $(patsubst %.cpp, bin/%.o, $(SRCS))


#Build targets
bin/%.o: %.cpp $(HDRS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build: $(EXEC) #Remove update if you want to stop automatically checking git repo

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

#Execution commands
run: build
	./$(EXEC)

clean:
	rm -rf bin
	rm $(EXEC)


#Update to most recent git state.
#update:
#	@git config credentials.helper cache
#	@git pull


#Print the file lists
print_s: 
	@echo $(SRCS) | tr " " "\n"
print_h: 
	@echo $(HDRS) | tr " " "\n"
print_o:
	@echo $(OBJS) | tr " " "\n"
