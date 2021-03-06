# Simple shell script to compile an AVR C program, and if successful, download
#  it to the STK500 board
#
# To use, type ./avrcmd file
#
#  Don't include the .c in the file name
#

avr-gcc -o $1  -mmcu=atmega32 $1.c

if (( $? != 0 ));      # '$?' is the shell variable that hold last command status 
  then
    exit 1
fi

echo Compilation Successful

avr-objcopy -v -S -O ihex $1 $1.hex

avrdude -v -y -p atmega32  -P /dev/ttyS0 -c stk500v2 -U flash:w:$1.hex:i 

# The following line will set the clock speed. Values for lfuse are:
#   0xE1 - 1 MHz
#   0xE2 - 2 MHz
#   0xE3 - 4 MHz
#   0xE4 - 8 MHz
# avrdude -v -y -p atmega32  -P /dev/ttyS0 -c stk500v2 -U lfuse:w:0xE1:m 
