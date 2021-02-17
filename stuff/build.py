#!/usr/bin/env python3
import fileinput
import sys
import re
import hashlib


# with open("01_plain_svg.svg", 'r', encoding='utf-8') as file:
# 	contents = file.read()

# lined_contents = contents.split("\n")


name1 = "test_file1"
name2 = "test_file2"
fin = open(name1, "r")
data2 = fin.read()
fin.close()
fout = open(name2, "a")
fout.write(data2)
fout.close()