SOURCES = entrysv.c
TARGET  = entrysv
OBJECTS = $(SOURCES:%.c=%.o)
CFLAGS	= -I../tuxfbuf -I ../include
#LIBS = -latmisrvinteg -latmi -lubf -lnstd -lpthread -lrt -ldl -lm

default: target

target: $(TARGET)

$(TARGET): $(OBJECTS)
	buildserver -o $@ $(LDFLAGS) -f $^ -sENTRY

clean:
	-rm $(TARGET)
	-rm *.o

