#!/usr/bin/env bash


sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update -y

#install g++
sudo apt-get install gcc-5 g++-5 -y
sudo update-alternatives --remove-all gcc
sudo update-alternatives --remove-all g++
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 20
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-5 20
sudo update-alternatives --config gcc
sudo update-alternatives --config g++

sudo apt-get install -y wget gunzip

cd scripts
chmod +x *.sh
./gen_all.sh

