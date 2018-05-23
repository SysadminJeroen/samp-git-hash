#!/usr/bin/env make

################
# tool locations
################
#
SHELL= /bin/bash
CC= gcc
CFLAGS=
MINGW= x86_64-w64-mingw32-gcc
MINGWCFLAGS=-Os -g0 -fvisibility=hidden -fomit-frame-pointer -mno-accumulate-outgoing-args -finline-small-functions -fno-unwind-tables -fno-asynchronous-unwind-tables -maccumulate-outgoing-args -s

all: git-hash.c
		$(CC) $(CFLAGS) git-hash.c -o git-hash

mingw: git-hash.c
		$(MINGW) $(MINGWCFLAGS) git-hash.c -o git-hash

install: all
		@echo are you kidding'??'

clean:
		rm git-hash
