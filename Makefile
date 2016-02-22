#!/usr/bin/env make

################
# tool locations
################
#
SHELL= /bin/bash
CC= gcc
CFLAGS=

all: git-hash.c
        $(CC) $(CFLAGS) git-hash.c -o git-hash

install: all
        @echo are you kidding'??'

clean:
        rm git-hash