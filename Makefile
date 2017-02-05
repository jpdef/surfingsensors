.PHONY: depend clean print
include Makefile.variables

all : 
	$(MAKE) -C src test

clean:
	$(RM) $(BUILDDIR)*.o *~ $(BINDIR)*

depend: $(SRCS)
	makedepend $(INCLUDES) $^

print-%  : 
	@echo $* = $($*)

