#
# Master build project
#

#
# Silent debug for Enduro/X
#
export NDRX_DEBUG_CONF=

all:
	make -C tuxfbuf
	make -C txgencl
	make -C entrysv

clean:
	make -C tuxfbuf clean
	make -C txgencl clean
	make -C entrysv clean

.PHONY: clean all

