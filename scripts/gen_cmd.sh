#!/usr/bin/env bash

if [[ $# -lt 1 ]] || [[ $# -gt 3 ]]; then
    echo "usage: $0 length [num_cmds=64] [alphabet=ACTG]"
    exit 1
fi

# store parameters
LENGTH=$1

NUM_CMDS=64
if [[ $# -ge 2 ]]; then
    NUM_CMDS=$2
fi;

ALPHA='ACTG'
if [[ $# -ge 3 ]]; then
    ALPHA=$3
fi;

rand_char() {
    i=$(( RANDOM % ${#ALPHA} ))
    echo -n ${ALPHA:${i}:1}
}

if [[ ${NUM_CMDS} -gt 0 ]]; then
    for i in `seq 1 ${NUM_CMDS}`; do
        if [[ $((RANDOM%2)) -eq 0 ]]; then
            OPERATION='r'
        else
            OPERATION='s'
        fi
        echo -n ${OPERATION} ' '
        rand_char
        echo ' ' $((RANDOM%${LENGTH}))
    done
fi

