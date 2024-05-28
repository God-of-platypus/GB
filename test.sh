#!/bin/sh

cd build;
make -j 4 test && ./testsuite/test
make clean
