#!/bin/sh

rm *.deb
cd dropbear
fakeroot debian/rules clean
CROSS_TARGET=raspberry fakeroot debian/rules binary
cd ..
