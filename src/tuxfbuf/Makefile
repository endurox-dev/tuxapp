#
# Demo field table
#
SOURCEDIR=.
SOURCES := $(shell find $(SOURCEDIR) -name '*.fd')

OUTPUT = $(addsuffix .h, $(SOURCES))

comma:= ,
empty:=
space:= $(empty) $(empty)

export FIELDTBLS=$(subst $(space),$(comma),$(SOURCES))
export FLDTBLDIR=$(shell pwd)
unexport NDRX_CCONFIG

#$(info $$SOURCES is [${SOURCES}])
#$(info $$OUTPUT is [${OUTPUT}])
#$(info $$FIELDTBLS is [${FIELDTBLS}])

PACKAGE=ubftab

.DEFAULT_GOAL: $(OUTPUT)
LDFLAGS=

$(OUTPUT): $(SOURCES)
	mkfldhdr32 -m0 -p${PACKAGE}


.PHONY: clean
clean:
	- rm *.h
