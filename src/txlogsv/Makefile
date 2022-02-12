SOURCES = txlogsv.c
TARGET  = txlogsv
OBJECTS = $(SOURCES:%.c=%.o)
CFLAGS	= $(shell printenv CFLAGS) -I../fml32 -I ../include -I${ORACLE_HOME}/precomp/public

default: target

target: $(TARGET) TMS_ORA1

%.c: %.proc
	proc iname=$^ SQLCHECK=SYNTAX MODE=ANSI CODE=ANSI_C IRECLEN=255 ORECLEN=255 PARSE=PARTIAL INCLUDE=../include INCLUDE=${ORACLE_HOME}/precomp/public INCLUDE=${TUXAPP_ADDINC} INCLUDE=../fml32

$(TARGET): $(OBJECTS)
	buildserver -v -r Oracle_XA -o $@ $(LDFLAGS) -f $^ -sTXLOG

TMS_ORA1:
	buildtms -rOracle_XA -o TMS_ORA1

clean:
	-rm $(TARGET)
	-rm *.o
	-rm TMS_ORA1

