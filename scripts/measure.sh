#!/usr/bin/env bash

if [[ -d measures ]]; then
    echo "Already measured, exiting..."
    exit 1
fi
mkdir measures

if [[ ! -d synth ]]; then
    scripts/dl_bacteria.sh
    scripts/gen_all.sh
fi;

# measure on synthetic files

echo "Measuring synthetic files..."

echo "length;num_cmds;vector;rbtree;create_time;cmd_time;memory_kb" > measures/examples.txt

for input_file in `ls synth/*`; do
    len=`echo ${input_file} | cut -d_ -f2 | cut -d. -f1`

    for cmd_file in `ls cmds/cmd_${len}_*`; do
        num_cmds=`echo ${cmd_file} | cut -d_ -f3 | cut -d. -f1`

        for opt1 in -v x; do
            [[ ${opt1} = "-v" ]]
            is_vector=$?
            optb=${opt1}
            [[ ${optb} != "x" ]] || optb=""

            for opt2 in -t x; do
                [[ ${opt2} = "-t" ]]
                is_rbtree=$?
                optt=${opt2}
                [[ ${optt} != "x" ]] || optt=""

                out=`./bioinf ${optb} ${optt} -o /dev/null -c ${cmd_file} -s ${input_file} 2>&1`

                node_time=`echo ${out} | sed -nE "s/.*Creating nodes took: ([0-9]+) .*/\1/p"`
                tree_time=`echo ${out} | sed -nE "s/.*Creating tree took: ([0-9]+) .*/\1/p"`
                create_time=$(( node_time+tree_time ))
                cmd_time=`echo ${out} | sed -nE "s/.*commands took: ([0-9]+) .*/\1/p"`
                memory_used=`echo ${out} | sed -nE "s/.*Memory used: ([0-9]+) .*/\1/p"`



                row="${len};${num_cmds};${is_vector};${is_rbtree};${create_time};${cmd_time};${memory_used}"
                echo ${row} >> measures/examples.txt

            done
        done

    done
done

# measure bacteria

echo "Measuring bacterias..."

echo "name;num_cmds;vector;rbtree;create_time;cmd_time;memory_kb" > measures/bacterias.txt

for input_file in `ls bacterias/*`; do
    name=`echo ${input_file} | cut -d/ -f2 | cut -d. -f1 | cut -d_ -f1,2`

    # length = 1000000
    for cmd_file in `ls cmds/cmd_1000000_*`; do
        num_cmds=`echo ${cmd_file} | cut -d_ -f3 | cut -d. -f1`

        for opt1 in -v x; do
            [[ ${opt1} = "-v" ]]
            is_vector=$?
            optb=${opt1}
            [[ ${optb} != "x" ]] || optb=""

            for opt2 in -t x; do
                [[ ${opt2} = "-t" ]]
                is_rbtree=$?
                optt=${opt2}
                [[ ${optt} != "x" ]] || optt=""

                out=`./bioinf ${optb} ${optt} -o /dev/null -c ${cmd_file} -s ${input_file} 2>&1`

                node_time=`echo ${out} | sed -nE "s/.*Creating nodes took: ([0-9]+) .*/\1/p"`
                tree_time=`echo ${out} | sed -nE "s/.*Creating tree took: ([0-9]+) .*/\1/p"`
                create_time=$(( node_time+tree_time ))
                cmd_time=`echo ${out} | sed -nE "s/.*commands took: ([0-9]+) .*/\1/p"`
                memory_used=`echo ${out} | sed -nE "s/.*Memory used: ([0-9]+) .*/\1/p"`

                row="${name};${num_cmds};${is_vector};${is_rbtree};${create_time};${cmd_time};${memory_used}"
                echo ${row} >> measures/bacterias.txt

            done
        done

    done
done