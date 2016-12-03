.PHONY: depend clean print
#CC        =  arm-linux-gnueabihf-g++
CC         =  ../tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++

CFLAGS    = -Wall -std=c++11 
LIBS      = -lm -lrt
SRCS      = $(wildcard src/*.cpp)
HDRS      = $(patsubst src/%.cpp,src/%.h,$(SRCS))
OBJS      = $(patsubst src/%.cpp,build/%.o,$(SRCS))
BIN       = idm
SRCDIR    = src/
BUILDDIR  = build/
BINDIR    = bin/
all : $(BIN) 

$(BIN) : $(OBJS) 
	$(CC) -o  $(BINDIR)$(BIN)  $^ $(LIBS)

$(BUILDDIR)%.o : $(SRCDIR)%.cpp 
	$(CC)  -c $< -o $@ $(CFLAGS)

clean:
	$(RM) $(BUILDDIR)*.o *~ $(BINDIR)*

depend: $(SRCS)
	makedepend $(INCLUDES) $^

print-%  : 
	@echo $* = $($*)

