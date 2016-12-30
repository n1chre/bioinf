#!/usr/bin/env bash

ACTG='ACTG'
LINE_WIDTH=80

if [[ $# -lt 1 ]] || [[ $# -gt 2 ]]; then
    echo "usage: $0 length [line_width]"
    exit 1
fi

LENGTH=$1
if [[ $# -eq 2 ]]; then
    LINE_WIDTH=$2
fi;

ROWS=$(( ${LENGTH} / ${LINE_WIDTH} ))
REST=$(( ${LENGTH} % ${LINE_WIDTH} ))

echo ">EXAMPLE_LEN_${1}"

rand_char() {
    i=$(( RANDOM % 4 ))
    echo -n ${ACTG:${i}:1}
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


