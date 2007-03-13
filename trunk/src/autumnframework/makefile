.SUFFIXES:	.cpp .o

include ../config/makeConfig
include ../config/make.rules
include $(OBJSFILE)

.cpp.o:
	$(CXX) $(CXXFLAGS) -I../include -c $<

$(DLLLIBNAME):$(OBJS)
	$(DLLMAKER) $(DLLLDFLAGS) -o $@ $(OBJS)
	$(CP) ./$(DLLLIBNAME) ../lib/

all:: $(DLLLIBNAME)

clean::
	$(RM) *.o ./$(DLLLIBNAME)
	$(RM) ../lib/$(DLLLIBNAME)

test::

depend::
	$(CXX) -I../include -MM *.cpp >$(DEPENDFILE)
	@echo "OBJS= \\" >$(OBJSFILE)
	@ls *.cpp | sed -e 's/cpp$$/o \\/' >>$(OBJSFILE)

include $(DEPENDFILE)

