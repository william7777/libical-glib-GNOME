#!/bin/sh

export GI_TYPELIB_PATH="$1"
export LD_LIBRARY_PATH="$2":$LD_LIBRARY_PATH
