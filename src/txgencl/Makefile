SOURCES = txgencl.c
TARGET  = txgencl
OBJECTS = $(SOURCES:%.c=%.o)
CFLAGS	= $(shell printenv CFLAGS) -I../tuxfbuf -I ../include

default: target

target: $(TARGET)

$(TARGET): $(OBJECTS)
	buildclient -o $@ $(LDFLAGS) -f $^

clean:
	-rm *.o
	-rm $(TARGET)

