#!/bin/bash
if [ ! -f convertpk3-src/convertpk3 ]; then
    cd convertpk3-src
    make
    cd ..
fi

PK3NAME="KL_HornsBR_v8" #rename to later version
convertpk3-src/convertpk3 . $PK3NAME.pk3
