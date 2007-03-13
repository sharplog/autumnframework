.SUFFIXES:	.cpp .o

include ../../config/makeConfig
include ../../config/make.rules
include $(OBJSFILE)

EXENAME=mainDemo

.cpp.o:
	$(CXX) $(CXXFLAGS) -I../../include -I../include -c $<

$(EXENAME): $(OBJS)
	 $(CXX) $(EXELDFLAGS) -L../../lib -l$(DLLNAME) -ldl -o $@ $(OBJS)

all:: $(EXENAME)

clean::
	$(RM) *.o ./$(EXENAME)

test:: 
	@$(LDLIBPATH)=$($(LDLIBPATH)):../../lib;   \
	export $(LDLIBPATH);    \
	sh ./runtest

depend::
	$(CXX) -I../../include -I../include -MM *.cpp >$(DEPENDFILE)
	@echo "OBJS= \\" >$(OBJSFILE)
	@ls *.cpp | sed -e 's/cpp$$/o \\/' >>$(OBJSFILE)
	@echo >>$(OBJSFILE)

include $(DEPENDFILE)

