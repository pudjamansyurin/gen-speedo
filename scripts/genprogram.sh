#!/bin/bash
source .env
source "./gencrc.sh"

$PROG -c port=SWD -r32 $UNIQID_ADDR 0x04
printf "UNIQID (above) readed from flash.\n"

printf "Replace UNIQID (Decimal) [or let empty to use old] : "
read UNIQID_INPUT

if [ -z $UNIQID_INPUT ]
then
      $PROG -c port=SWD --read $UNIQID_ADDR 0x04 $UNIQID_BIN_FILE
      printf "Use in-flash UNIQID, backed up to $UNIQID_BIN_FILE\n"
else
      printf "Use new UNIQID (Decimal) = $UNIQID_INPUT\n"
fi
sleep 2

$PROG -c port=SWD --erase all
printf "Flash erased.\n"
sleep 2
 
$PROG -c port=SWD --skipErase --write $BL_BIN_FILE $BL_START_ADDR 
printf "Bootloader downloaded.\n"
sleep 2

$PROG -c port=SWD --skipErase --write $APP_BIN_FILE $APP_START_ADDR 
printf "Application downloaded.\n"
sleep 2
 
$PROG -c port=SWD --skipErase --write $CRC_BIN_FILE $APP_CRC_ADDR 
printf "Application:CRC inserted.\n"
sleep 2

APP_SIZE=$(printf "0x%08x" `stat -c %s "$APP_BIN_FILE"`)
$PROG -c port=SWD --skipErase -w32 $APP_SIZE_ADDR $APP_SIZE
printf "Application:Size inserted.\n"
sleep 2

if [ -z $UNIQID_INPUT ]
then
      $PROG -c port=SWD --skipErase --write $UNIQID_BIN_FILE $UNIQID_ADDR 
      printf "Bootloader:Old UNIQID inserted.\n"
else
      UNIQID_HEX=$(printf "0x%08x" $UNIQID_INPUT)
      $PROG -c port=SWD --skipErase -w32 $UNIQID_ADDR $UNIQID_HEX
      printf "Bootloader:New UNIQID inserted.\n"
fi
sleep 2

read -p "Do you wish swv tracing [y/n]? " yn
case $yn in
      [Yy]* ) $PROG -c port=SWD -swv freq=$SYS_FREQ_MHZ portnumber=0 $SWV_LOG;;
      * ) $PROG -c port=SWD --go $BL_START_ADDR;;
esac
