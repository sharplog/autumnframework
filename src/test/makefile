.SUFFIXES:	.cpp .o

include ../config/makeConfig
include ../config/make.rules
include $(OBJSFILE)

EXENAME=FrameworkTest
SUBDIRS=testDll

.cpp.o:
	$(CXX) $(CXXFLAGS) -I../include -I./include -c $<

$(EXENAME): $(OBJS)
	 $(CXX) $(EXELDFLAGS) -L../lib -l$(DLLNAME) -ldl -o $@ $(OBJS)

all test clean depend::
	@for subdir in $(SUBDIRS);	\
	do	\
		echo "making $@ in $$subdir"; \
		( cd $$subdir && $(MAKE) $@) || exit 1; \
	done

all:: $(EXENAME)

clean::
	$(RM) *.o ./$(EXENAME)
	$(RM) AutumnFramework.log AutumnApp.log
	$(RM) lib/TestDll.dll lib/TestDll2.dll

test:: $(EXENAME)
	@$(LDLIBPATH)=$($(LDLIBPATH)):../lib;	\
	export $(LDLIBPATH);	\
	sh ./runtest

depend::
	$(CXX) -I../include -I./include $(DEPFLAGS) *.cpp >$(DEPENDFILE)
	@echo "OBJS= \\" >$(OBJSFILE)
	@ls *.cpp | sed -e 's/cpp$$/o \\/' >>$(OBJSFILE)
	@echo >>$(OBJSFILE)

include $(DEPENDFILE)
include $(WRAPPERDEP)
