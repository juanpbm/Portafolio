#!/bin/bash

wget -O - http://www.mshah.io/comp/Fall18/Systems/Lab/2/baseballdata.csv | cut -d ',' -f 5 | tail -n +2 > data.txt
