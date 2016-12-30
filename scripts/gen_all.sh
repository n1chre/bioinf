#!/usr/bin/env bash

if [[ -d synth ]]; then
    rm -rf synth
fi

mkdir synth

len=10
while [[ $len -lt 1000000 ]]; do
    len=$((len*10))
    ./gen_synth.sh ${len} > "./synth/example_${len}.in"
done