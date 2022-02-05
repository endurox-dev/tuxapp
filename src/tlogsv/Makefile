SOURCES = tlogsv.c
TARGET  = tlogsv
OBJECTS = $(SOURCES:%.c=%.o)
CFLAGS	= -I../tuxfbuf -I ../include

default: target

target: $(TARGET) tms

%.o: %.proc
	proc iname=$^ SQLCHECK=SYNTAX MODE=ANSI CODE=ANSI_C IRECLEN=255 ORECLEN=255 PARSE=PARTIAL INCLUDE=../include INCLUDE=${ORACLE_HOME}/precomp/public

$(TARGET): $(OBJECTS)
	buildserver -o $@ $(LDFLAGS) -f $^ -sTLOG -rOracle_XA

tms:
	buildtms -rOracle_XA -o ORA_TMS

clean:
	-rm $(TARGET)
	-rm *.o

