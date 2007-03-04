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
	rm ../lib/$(DLLLIBNAME)
	rm ../include/BeanWrapperMacro.h
	rm ../include/IBasicType.h
	rm ../include/IBeanFactory.h
	rm ../include/IBeanWrapper.h

test::

include makeDepend

