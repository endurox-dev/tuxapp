#
# Master build project
#

# Silent debug for Enduro/X (in case of building for)
export NDRX_DEBUG_CONF=

all:
	make -C tuxfbuf
	make -C txgencl
	make -C entrysv
	make -C tlogsv

clean:
	make -C tuxfbuf clean
	make -C txgencl clean
	make -C entrysv clean
	make -C tlogsv clean

.PHONY: clean all

