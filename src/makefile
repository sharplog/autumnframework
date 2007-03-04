.SUFFIXES:	.cpp .o

include ./config/makeConfig

SUBDIRS=autumnframework demo test

all test clean::
	@for subdir in $(SUBDIRS);	\
	do	\
		echo "making $@ in $$subdir"; \
		( cd $$subdir && $(MAKE) $@) || exit 1; \
	done
