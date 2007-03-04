.SUFFIXES:	.cpp .o

include ../../config/makeConfig
include makeObjects

TESTDLLNAME=injectBeanImpl.so

.cpp.o:
	$(CXX) $(CXXFLAGS) -I../../include -c $<

$(TESTDLLNAME):$(OBJS)
	$(DLLMAKER) $(DLLLDFLAGS) -L../../lib -l$(DLLNAME) -o $@ $(OBJS)
	cp ./$(TESTDLLNAME) ../lib/
	cp ./Action.h ../include/

all:: $(TESTDLLNAME)

clean::
	rm -f *.o ./$(TESTDLLNAME)
	rm -f ../lib/$(TESTDLLNAME)
	rm -f ../include/Action.h

test::

include makeDepend
