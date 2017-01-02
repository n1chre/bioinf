#!/usr/bin/env bash

ALPHA='ACTG'

if [[ -d synth ]]; then
    rm -rf synth
fi
mkdir synth

if [[ -d cmds ]]; then
    rm -rf cmds
fi
mkdir cmds

len=10
while [[ ${len} -lt 1000000 ]]; do
    len=$((len*10))
    >&2 echo "Generating for length ${len}..."
    # create example
    ./gen_synth.sh ${len} ${ALPHA} > "./synth/example_${len}.in"
    # create cmds file for that example
    num_cmds=10
    while [[ ${num_cmds} -lt 1000000 ]]; do
        num_cmds=$((num_cmds*10))
        ./gen_cmd.sh ${len} ${num_cmds} ${ALPHA} > "./cmds/cmd_${len}_${num_cmds}.cmd"
    done;
done