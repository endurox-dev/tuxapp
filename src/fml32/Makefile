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

.DEFAULT_GOAL: $(OUTPUT)
LDFLAGS=

$(OUTPUT): $(SOURCES)
	mkfldhdr32


.PHONY: clean
clean:
	- rm *.h
