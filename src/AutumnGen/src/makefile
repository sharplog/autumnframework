.SUFFIXES:	.cpp .o

include ../../config/makeConfig
include ../../config/make.rules
include $(OBJSFILE)

EXENAME=AutumnGen

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

$(EXENAME): $(OBJS)
	$(CXX) $(EXELDFLAGS) -o $@ $(OBJS)
	$(CP) $@ ../../bin/

all:: $(EXENAME)

clean::
	$(RM) *.o ./$(EXENAME)
	$(RM) ../../bin/$(EXENAME)

test:: 

depend::
	$(CXX) -I../../include $(DEPFLAGS) *.cpp >$(DEPENDFILE)
	@echo "OBJS= \\" >$(OBJSFILE)
	@ls *.cpp | sed -e 's/cpp$$/o \\/' >>$(OBJSFILE)
	@echo >>$(OBJSFILE)

include $(DEPENDFILE)

