#!/usr/bin/env bash

# downloads bacteria fasta files

BASE_URL="ftp://ftp.ensemblgenomes.org/pub/bacteria/release-34/fasta/bacteria_0_collection"
BACTERIA="anaplasma_phagocytophilum_str_hz/dna/Anaplasma_phagocytophilum_str_hz.ASM1312v1.dna.toplevel.fa.gz
escherichia_coli_str_k_12_substr_mg1655/dna/Escherichia_coli_str_k_12_substr_mg1655.ASM584v2.dna.toplevel.fa.gz
mycobacterium_tuberculosis_h37rv/dna/Mycobacterium_tuberculosis_h37rv.ASM19595v2.dna.toplevel.fa.gz
salmonella_enterica_subsp_enterica_serovar_typhimurium_str_lt2/dna/Salmonella_enterica_subsp_enterica_serovar_typhimurium_str_lt2.ASM694v2.dna.toplevel.fa.gz"

if [[ -d bacterias ]]; then
    echo "Bacterias already downloaded into folder bacterias"
    read -p "Do you want to download again? [y/N] " confirm && [[ ${confirm} == [yY] || ${confirm} == [yY][eE][sS] ]] || exit 1
    rm -rf bacterias
fi

mkdir bacterias

for bacteria in ${BACTERIA}; do
    URL=${BASE_URL}/${bacteria}
    wget -P bacterias ${URL}
done

gunzip bacterias/*


