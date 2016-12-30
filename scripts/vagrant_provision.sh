#!/usr/bin/env bash

sudo apt-get -y update
sudo apt-get -y upgrade
sudo apt-get -y install g++

cd scripts
chmod +x *.sh
./gen_all.sh

