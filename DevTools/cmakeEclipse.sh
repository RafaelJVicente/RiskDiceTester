#!/bin/sh
foldName=build
cd ../..
rm -rf $foldName
mkdir $foldName
cd $foldName
cmake ../RiskDiceTester/ -G"Eclipse CDT4 - Unix Makefiles"
