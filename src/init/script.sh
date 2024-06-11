#!/bin/bash

if [ -e "main" ]; then
	rm main
fi

gcc main.c -o main
./main
