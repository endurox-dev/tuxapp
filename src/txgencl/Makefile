
SOURCES = txgencl.c
TARGET  = txgencl
OBJECTS = $(SOURCES:%.c=%.o)
CFLAGS	= -I../tuxfbuf -I ../include
#LIBS = -latmiclt -latmi -lubf -lnstd -lpthread -lrt -ldl -lm

default: target

target: $(TARGET)

$(TARGET): $(OBJECTS)
	buildclient -o $@ $(LDFLAGS) -f $^

clean:
	-rm *.o
	-rm $(TARGET)

