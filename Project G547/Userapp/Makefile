
USBFLAGS = `libusb-config --cflags`
USBLIBS = `libusb-config --libs`
EXE_SUFFIX =


CC		= gcc
CFLAGS	= $(USBFLAGS) -O -Wall
LIBS	= $(USBLIBS)

PROGRAM = GasAdc$(EXE_SUFFIX)


all: $(PROGRAM)

.c.o:
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): GasAdc.o
	$(CC) -o $(PROGRAM) GasAdc.o $(LIBS)

strip: $(PROGRAM)
	strip $(PROGRAM)

clean:
	rm -f *.o $(PROGRAM)
