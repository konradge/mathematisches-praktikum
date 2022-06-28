#!/bin/bash

COUNTER=0
TOTAL=0

play_game () {
    res=$(./build/bin/main 0.005 0.01 4 | grep "Ihr Programm hat gewonnen. Herzlichen Glueckwunsch!")
    let TOTAL++
    if [ -z "$res" ]
    then
        echo "Game lost"
    else
        echo "Game won"
        let COUNTER++
    fi
    echo "$COUNTER / $TOTAL games won"
    if (( $TOTAL < 30 )); then
        play_game & echo "\n\n\n\n\n\n\n"
    fi
}

play_game & echo "\n\n\n\n\n\n\n"