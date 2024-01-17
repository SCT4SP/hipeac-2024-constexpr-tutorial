#!/bin/bash

$CXX -O3 -std=c++20 echo_n_words.cpp -o echo_n_words

NUM_WORDS=20
./echo_n_words ${NUM_WORDS} > ${NUM_WORDS}-words.txt
NUM_WORDS=1000
./echo_n_words ${NUM_WORDS} > ${NUM_WORDS}-words.txt
NUM_WORDS=10000
./echo_n_words ${NUM_WORDS} > ${NUM_WORDS}-words.txt
NUM_WORDS=100000
./echo_n_words ${NUM_WORDS} > ${NUM_WORDS}-words.txt
