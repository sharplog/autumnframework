.SUFFIXES:	.cpp .o

include ../../config/makeConfig
include makeObjects

TESTDLLNAME=TestDll.so

.cpp.o:
	$(CXX) $(CXXFLAGS) -I../../include -c $<

$(TESTDLLNAME):$(OBJS)
	$(DLLMAKER) $(DLLLDFLAGS) -L../../lib -l$(DLLNAME) -o $@ $(OBJS)
	cp ./$(TESTDLLNAME) ../lib/
	cp ./IBasicTypesBean.h ../include/

all test clean::
	@for subdir in $(SUBDIRS);  \
	do  \
	    echo "making $@ in $$subdir"; \
	    ( cd $$subdir && $(MAKE) $@) || exit 1; \
	done

all::$(TESTDLLNAME)

clean::
	rm -f *.o ./$(TESTDLLNAME)
	rm -f ../lib/$(TESTDLLNAME)
	rm -f ../include/IBasicTypesBean.h

test::

include makeDepend

