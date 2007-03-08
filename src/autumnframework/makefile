.SUFFIXES:	.cpp .o

include ../config/makeConfig
include makeObjects

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

$(DLLLIBNAME):$(OBJS)
	$(DLLMAKER) $(DLLLDFLAGS) -o $@ $(OBJS)
	cp ./$(DLLLIBNAME) ../lib/
	cp ./BeanWrapperMacro.h ../include/
	cp ./IBasicType.h ../include/
	cp ./IBeanFactory.h ../include/
	cp ./IBeanWrapper.h ../include/

all:: $(DLLLIBNAME)

clean::
	rm -f *.o ./$(DLLLIBNAME)
	rm -f ../lib/$(DLLLIBNAME)
	rm -f ../include/BeanWrapperMacro.h
	rm -f ../include/IBasicType.h
	rm -f ../include/IBeanFactory.h
	rm -f ../include/IBeanWrapper.h

test::

include makeDepend

