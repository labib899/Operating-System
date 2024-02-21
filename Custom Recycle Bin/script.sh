#! /bin/bash

BIN_DIR="$HOME/Desktop/OS/Trash"
RESTORE_DIR="$HOME/Desktop/OS/restore_info"
if [ ! -d $BIN_DIR ]; then
    mkdir $BIN_DIR
fi

if [ ! -d $RESTORE_DIR ]; then
    mkdir $RESTORE_DIR
fi


remv() 
{
    for file in $@; 
    do
        if [ -e $file ]; then
            original_path=$(realpath $file)
            mv $file $BIN_DIR
            echo "rm -rf $BIN_DIR/$file" | at now +30 hours
            echo "Moved '$file' to the Trash"
            file_name=$(basename $file)
            #file_name=${file_name%.*}
            echo $original_path > $RESTORE_DIR/$file_name
            echo "rm -rf $RESTORE_DIR/$file" | at now +30 hours
        else 
            echo "'$file' not found"
        fi
    done
}

restore() 
{
    for file in $@; 
    do  
        restore_path=$RESTORE_DIR/$file
        if [ -e $restore_path ]; then
            echo "Do you want to restore to the original path? (y/n)"
            read choice
            if [ $choice == "y" ]; then
                original_path=$(cat $restore_path)
                mv $BIN_DIR/$file $original_path
                echo "Restored '$file' from the Trash"
                rm $restore_path
            else 
                echo "Enter your desired path: "
                read path
                if [ -e $path ]; then
                    mv $BIN_DIR/$file $path
                    echo "Restored '$file' from the Trash"
                    if [ -e $restore_path ]; then
                        rm $restore_path
                    fi
                else
                    echo "Path not found"
                fi
            fi
        else 
            echo "'$file' can not be removed from Trash"
        fi
    done
}

remvp() 
{
    for file in $@; 
    do
        if [ -e $BIN_DIR/$file ]; then
            rm -rf $BIN_DIR/$file
            echo "Permanently removed '$file' from the Trash"
            if [ -e $RESTORE_DIR/$file ]; then 
                rm -rf $RESTORE_DIR/$file
            fi
        else
            echo "'$file' not found in the Trash"
        fi
    done
}



case $1 in
    remv) remv ${@:2} ;;
    restore) restore ${@:2} ;;
    remvp) remvp ${@:2} ;;
esac