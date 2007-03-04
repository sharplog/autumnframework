.SUFFIXES:	.cpp .o

include ../config/makeConfig
include makeObjects

EXENAME=FrameworkTest
SUBDIRS=testDll

.cpp.o:
	$(CXX) $(CXXFLAGS) -I../include -I./include -c $<

$(EXENAME): $(OBJS)
	 $(CXX) $(EXELDFLAGS) -L../lib -l$(DLLNAME) -ldl -o $@ $(OBJS)

all test clean::
	@for subdir in $(SUBDIRS);	\
	do	\
		echo "making $@ in $$subdir"; \
		( cd $$subdir && $(MAKE) $@) || exit 1; \
	done

all:: $(EXENAME)

clean::
	rm -f *.o ./$(EXENAME)

test:: $(EXENAME)
	@./runtest

include makeDepend
