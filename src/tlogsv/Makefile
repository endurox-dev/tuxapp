SOURCES = tlogsv.c
TARGET  = tlogsv
OBJECTS = $(SOURCES:%.c=%.o)
CFLAGS	= $(shell printenv CFLAGS) -I../tuxfbuf -I ../include -I${ORACLE_HOME}/precomp/public

default: target

target: $(TARGET) tms

%.c: %.proc
	proc iname=$^ SQLCHECK=SYNTAX MODE=ANSI CODE=ANSI_C IRECLEN=255 ORECLEN=255 PARSE=PARTIAL INCLUDE=../include INCLUDE=${ORACLE_HOME}/precomp/public INCLUDE=${TUXDIR}/include INCLUDE=../tuxfbuf

$(TARGET): $(OBJECTS)
	buildserver -v -r Oracle_XA -o $@ $(LDFLAGS) -f $^ -sTLOG

tms:
	buildtms -rOracle_XA -o TMS_ORA1

clean:
	-rm $(TARGET)
	-rm *.o
	-rm TMS_ORA1

