#!/usr/bin/env bash

if [[ $# -lt 1 ]] || [[ $# -gt 3 ]]; then
    echo "usage: $0 length [line_width=80] [alphabet=ACTG]"
    exit 1
fi

# store parameters
LENGTH=$1

LINE_WIDTH=80
if [[ $# -eq 2 ]]; then
    LINE_WIDTH=$2
fi;

ALPHA='ACTG'
if [[ $# -eq 3 ]]; then
    ALPHA=$3
fi;

ROWS=$(( ${LENGTH} / ${LINE_WIDTH} ))
REST=$(( ${LENGTH} % ${LINE_WIDTH} ))

# create output
echo ">EXAMPLE_LEN_${1}"

rand_char() {
    i=$(( RANDOM % ${#ALPHA} ))
    echo -n ${ALPHA:${i}:1}
}

if [[ ${ROWS} -gt 0 ]]; then
    for i in `seq 0 ${ROWS}`; do
        for j in `seq ${LINE_WIDTH}`; do
            rand_char
        done;
        echo ''
done;
fi;

if [[ ${REST} -gt 0 ]]; then
    for j in `seq 0 ${REST}`; do
        rand_char
    done;
fi;


