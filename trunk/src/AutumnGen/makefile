.SUFFIXES:	.cpp .o

include ../config/makeConfig
include ../config/make.rules

SUBDIRS=src

all test clean depend::
	@for subdir in $(SUBDIRS);	\
	do	\
		echo "making $@ in $$subdir"; \
		( cd $$subdir && $(MAKE) $@) || exit 1; \
	done
