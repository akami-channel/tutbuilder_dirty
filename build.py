#!/usr/bin/env python3
import fileinput
import sys
import re
import hashlib


with open("01_plain_svg.svg", 'r', encoding='utf-8') as file:
	contents = file.read()

lined_contents = contents.split("\n")