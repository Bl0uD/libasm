#!/bin/bash

#docker build --platform linux/amd64 -t libasm-env .
docker run --platform linux/amd64 -v "$PWD":/libasm -w /libasm -it --rm libasm-env bash -c "make test && ./test"