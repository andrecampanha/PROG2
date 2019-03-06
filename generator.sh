FOLDER=$1"/prob"$2

if [ ! -d "$FOLDER" ]; then
    echo "GENERATING" $FOLDER
    mkdir -p $FOLDER
    cp .template/main.c $FOLDER
    cp .template/Makefile $FOLDER
else
    echo "EXERCISE" $FOLDER "ALREADY EXISTS"
fi