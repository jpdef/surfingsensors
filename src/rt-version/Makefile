include  ../../Makefile.variables
SRCS      = $(wildcard *.cpp)
OBJS      = $(patsubst %.cpp,$(TOP)$(BUILDDIR)imu/%.o,$(SRCS))
test : idm-rt 
	mkdir -p $(TOP)$(BUILDDIR)rt

idm-rt  : $(OBJS) 
	$(TOP)$(CC) -o  $(TOP)$(BINDIR)idm-rt  $^ $(LIBS)

$(TOP)$(BUILDDIR)imu/%.o : %.cpp 
	$(TOP)$(CC)  -c $< -o $@ $(CFLAGS)
