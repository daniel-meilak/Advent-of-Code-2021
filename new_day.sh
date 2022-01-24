#!/bin/bash

#-------------------------------------------------------
# script for making new day folder and including files
#-------------------------------------------------------

# argument must be passed to script
if [[ -z ${1+x} ]]; then
    echo "A day number is required"
    exit 1
fi


# determine week
if   (( ${1} >= 1  && ${1} <= 7  )); then
    week="week_1"
elif (( ${1} >= 8  && ${1} <= 14 )); then
    week="week_2"
elif (( ${1} >= 15 && ${1} <= 21 )); then
    week="week_3"
else 
    week="week_4"
fi

# create day folder (and week if necessary)
mkdir -p ${week}/day_${1}

# create template c++ file
echo "#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include\"utils.h\"

int main(){

    // read input into vector of strings.
    // std::vector<std::string> delimiters = {};
    // std::vector<std::string> input = read_input(\"input\", delimiters);

    // read input into vector of vector of strings.
    // std::vector<std::string> delimiters = {};
    // std::vector<std::vector<std::string>> input = read_input_2D(\"input\", delimiters);

    std::cout << \"Answer (part 1): \" << std::endl;
    std::cout << \"Answer (part 2): \" << std::endl;

    return 0;
}" >> ${week}/day_${1}/day_${1}.cpp

# create template c++ test file 
echo "#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include\"utils.h\"

int main(){

    return 0;
}" >> ${week}/day_${1}/test.cpp

# create README.md for each day
echo "## Day ${1}" >> ${week}/day_${1}/README.md

