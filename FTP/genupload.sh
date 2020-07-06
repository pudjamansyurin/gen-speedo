#!/bin/sh

SRC_BIN_FILE="../HMI-APP/Debug/HMI-APP.bin"
APP_BIN_FILE="APP.bin"
APP_CRC_FILE="APP.crc"

echo "Files preparing..."
rm -rf $APP_BIN_FILE $APP_CRC_FILE
cp $SRC_BIN_FILE $APP_BIN_FILE
#objcopy -I binary -O binary --reverse-bytes=4 $SRC_BIN_FILE "tmp.bin"

echo "Checksum calculating..."
java -jar ./jacksum.jar -a crc32_mpeg2 -X -F "#CHECKSUM" -O $APP_CRC_FILE $APP_BIN_FILE

echo "FTP binary uploading..."
curl -T $APP_BIN_FILE ftp://ftp.genmotorcycles.com/hmi/ --user 'fota@genmotorcycles.com:@Garda313'
echo "FTP checksum uploading..."
curl -T $APP_CRC_FILE ftp://ftp.genmotorcycles.com/hmi/ --user 'fota@genmotorcycles.com:@Garda313'

echo "Done, ready for FOTA."
