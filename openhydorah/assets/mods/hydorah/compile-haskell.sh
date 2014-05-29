#!/bin/bash
ghc -O2 -dynamic -shared -fPIC -optl '-g' -o libhydorah.so hsbracket.c $* -lHSrts-ghc7.6.3
