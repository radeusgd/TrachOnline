#!/bin/bash
./cardscript $1 $2
mv "$2.hpp" ../../cards/
mv "$2.cpp" ../../cards/

