.SUFFIXES:	.cpp .o

include ../../config/makeConfig
include makeObjects

EXENAME=mainDemo

.cpp.o:
	$(CXX) $(CXXFLAGS) -I../../include -I../include -c $<

$(EXENAME): $(OBJS)
	 $(CXX) $(EXELDFLAGS) -L../../lib -l$(DLLNAME) -ldl -o $@ $(OBJS)

all:: $(EXENAME)

clean::
	rm -f *.o ./$(EXENAME)

test:: 
	@sh ./runtest
