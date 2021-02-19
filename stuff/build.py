#!/usr/bin/env python3
import fileinput
import sys
import re
import hashlib


# with open("01_plain_svg.svg", 'r', encoding='utf-8') as file:
# 	contents = file.read()

# lined_contents = contents.split("\n")


name1 = "sources/main.cpp"
name2 = "output/main.cpp"
fin = open(name1, "r")
data2 = fin.read()
fin.close()
fout = open(name2, "w")
fout.write(data2)
fout.close()