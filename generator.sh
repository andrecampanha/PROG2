#!/bin/bash
FOLDER=$1"/prob"$2

if [ ! -d "$FOLDER" ]; then
    echo "GENERATING" $FOLDER
    mkdir -p $FOLDER
    cp .template/main.c $FOLDER
    cp .template/Makefile $FOLDER
    cd $FOLDER
    exec bash
else
    echo "EXERCISE" $FOLDER "ALREADY EXISTS"
fi