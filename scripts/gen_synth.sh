#!/usr/bin/env bash

if [[ $# -lt 1 ]] || [[ $# -gt 3 ]]; then
    echo "usage: $0 length [alphabet=ACTG] [line_width=80]"
    exit 1
fi

# store parameters
LENGTH=$1

ALPHA='ACTG'
if [[ $# -eq 2 ]]; then
    ALPHA=$2
fi;

LINE_WIDTH=80
if [[ $# -eq 3 ]]; then
    LINE_WIDTH=$3
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
    for i in `seq 1 ${ROWS}`; do
        for j in `seq 1 ${LINE_WIDTH}`; do
            rand_char
        done;
        echo ''
done;
fi;

if [[ ${REST} -gt 0 ]]; then
    for j in `seq 1 ${REST}`; do
        rand_char
    done;
fi;
