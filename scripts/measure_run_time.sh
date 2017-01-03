#!/usr/bin/env bash

PREFIX='cmake-build-debug'
[[ `uname -s` = 'Darwin' ]] || PREFIX='.'

echo "length;num_cmds;vector;rbtree;create_time;cmd_time;memory_kb" > measures/run_time.txt

for input_file in `ls synth/*`; do
    len=`echo ${input_file} | cut -d_ -f2 | cut -d. -f1`
    echo "measuring length ${len}"

    for cmd_file in `ls cmds/cmd_${len}_*`; do
        num_cmds=`echo ${cmd_file} | cut -d_ -f3 | cut -d. -f1`
        echo -e "\tmeasuring numcmds ${num_cmds}"

        for i in `seq 1 5`; do
            echo -e "\t\t${i}"

            for opt1 in -v x; do
                [[ ${opt1} != "-v" ]]
                is_vector=$?
                optb=${opt1}
                [[ ${optb} != "x" ]] || optb=""

                for opt2 in -t x; do
                    [[ ${opt2} != "-t" ]]
                    is_rbtree=$?
                    optt=${opt2}
                    [[ ${optt} != "x" ]] || optt=""

                        out=`${PREFIX}/bioinf ${optb} ${optt} -o /dev/null -c ${cmd_file} -s ${input_file} 2>&1`

                        node_time=`echo ${out} | sed -nE "s/.*Creating nodes took: ([0-9]+) .*/\1/p"`
                        tree_time=`echo ${out} | sed -nE "s/.*Creating tree took: ([0-9]+) .*/\1/p"`
                        create_time=$(( node_time+tree_time ))
                        cmd_time=`echo ${out} | sed -nE "s/.*commands took: ([0-9]+) .*/\1/p"`
                        memory_used=`echo ${out} | sed -nE "s/.*Memory used: ([0-9]+) .*/\1/p"`

                        row="${len};${num_cmds};${is_vector};${is_rbtree};${create_time};${cmd_time};${memory_used}"
                        echo ${row} >> measures/run_time.txt

                        sleep 0.333

                done
            done
        done
    done
done