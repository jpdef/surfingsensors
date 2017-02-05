include  ../../Makefile.variables
SRCS      = $(wildcard *.cpp)
OBJS      = $(patsubst %.cpp,$(TOP)$(BUILDDIR)imu/%.o,$(SRCS))
test : idm 
	mkdir -p $(TOP)$(BUILDDIR)imu

idm  : $(OBJS) 
	$(TOP)$(CC) -o  $(TOP)$(BINDIR)idm  $^ $(LIBS)

$(TOP)$(BUILDDIR)imu/%.o : %.cpp 
	$(TOP)$(CC)  -c $< -o $@ $(CFLAGS)
