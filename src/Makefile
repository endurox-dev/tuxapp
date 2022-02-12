#
# Master build project
#

all:
	make -C fml32
	make -C txgencl
	make -C entrysv
	make -C txlogsv

clean:
	make -C fml32 clean
	make -C txgencl clean
	make -C entrysv clean
	make -C txlogsv clean

.PHONY: clean all

