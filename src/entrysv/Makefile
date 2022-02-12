SOURCES = entrysv.c
TARGET  = entrysv
OBJECTS = $(SOURCES:%.c=%.o)
CFLAGS  = $(shell printenv CFLAGS) -I../fml32 -I ../include

default: target

target: $(TARGET)

$(TARGET): $(OBJECTS)
	buildserver -o $@ $(LDFLAGS) -f $^ -sENTRY

clean:
	-rm $(TARGET)
	-rm *.o

