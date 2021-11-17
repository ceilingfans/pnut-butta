#!/bin/sh

if ! command -v cmake > /dev/null
then
  echo "pnut-butta: install cmake before attempting to build"
  exit
fi

if ! command -v make > /dev/null
then
  echo "pnut-butta: install make before attempting to build"
  exit
fi

cmake .
make