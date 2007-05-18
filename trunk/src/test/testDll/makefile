.SUFFIXES:	.cpp .o

include ../../config/makeConfig
include ../../config/make.rules
include $(OBJSFILE)

TESTDLLNAME=TestDll.so

.cpp.o:
	$(CXX) $(CXXFLAGS) -I../../include -I../include -c $<

$(TESTDLLNAME):$(OBJS)
	$(DLLMAKER) $(DLLLDFLAGS) -L../../lib -l$(DLLNAME) -o $@ $(OBJS)
	$(CP) ./$(TESTDLLNAME) ../lib/

all::$(TESTDLLNAME)

clean::
	$(RM) *.o ./$(TESTDLLNAME)
	$(RM) ../lib/$(TESTDLLNAME)

test::

depend::
	$(CXX) -I../../include -I../include $(DEPFLAGS) *.cpp >$(DEPENDFILE)
	@echo "OBJS= \\" >$(OBJSFILE)
	@ls *.cpp | sed -e 's/cpp$$/o \\/' >>$(OBJSFILE)
	@echo >>$(OBJSFILE)

include $(DEPENDFILE)
include $(WRAPPERDEP)

