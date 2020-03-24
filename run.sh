#!/bin/sh

TOPDIR=$(dirname $(readlink -f $0))

rm -rfv $TOPDIR/_build
mkdir $TOPDIR/_build
pushd $TOPDIR/_build
cmake .. -DWITH_SANITIZERS=ON
make -j4
popd
