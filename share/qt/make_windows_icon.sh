#!/bin/bash
# create multiresolution windows icon
#mainnet
ICON_SRC=../../src/qt/res/icons/spescoin.png
ICON_DST=../../src/qt/res/icons/spescoin.ico
convert ${ICON_SRC} -resize 16x16 spescoin-16.png
convert ${ICON_SRC} -resize 32x32 spescoin-32.png
convert ${ICON_SRC} -resize 48x48 spescoin-48.png
convert spescoin-16.png spescoin-32.png spescoin-48.png ${ICON_DST}
#testnet
ICON_SRC=../../src/qt/res/icons/spescoin_testnet.png
ICON_DST=../../src/qt/res/icons/spescoin_testnet.ico
convert ${ICON_SRC} -resize 16x16 spescoin-16.png
convert ${ICON_SRC} -resize 32x32 spescoin-32.png
convert ${ICON_SRC} -resize 48x48 spescoin-48.png
convert spescoin-16.png spescoin-32.png spescoin-48.png ${ICON_DST}
rm spescoin-16.png spescoin-32.png spescoin-48.png
