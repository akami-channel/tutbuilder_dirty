#!/usr/bin/env python3
import fileinput
import sys
import re
import hashlib
import os
from distutils.dir_util import copy_tree
import subprocess

# with open("01_plain_svg.svg", 'r', encoding='utf-8') as file:
# 	contents = file.read()

# lined_contents = contents.split("\n")

def make_dir(directory_to_make):
	try:
		os.mkdir(directory_to_make) 
	except OSError as error:
		pass
		# print(error)

make_dir("output/SDLGL_tuts_dirty")
make_dir("output/SDLGL_tuts_dirty/Libraries")
copy_tree("sources/Libraries", "output/SDLGL_tuts_dirty/Libraries")
copy_tree("sources/Tutorials", "output/SDLGL_tuts_dirty/Tutorials")

# make_dir("output/SDLGL_tuts_dirty/Tutorials")
# make_dir("output/SDLGL_tuts_dirty/Tutorials/01_create_window")
# make_dir("output/SDLGL_tuts_dirty/Tutorials/02_quad")
# make_dir("output/SDLGL_tuts_dirty/Tutorials/03_separate_shader_files")
# make_dir("output/SDLGL_tuts_dirty/Tutorials/04_textures")
# make_dir("output/SDLGL_tuts_dirty/Tutorials/05_uniforms")
# make_dir("output/SDLGL_tuts_dirty/Tutorials/06_frag_shader_basics")
# make_dir("output/SDLGL_tuts_dirty/Tutorials/07_user_input")


# exec("do_checksums.sh")
subprocess.call("stuff/do_checksums.sh")
# # this bash command thing does not like you cd'ing somewhere else; use cwd argument below
# bashCommand = 'find . -type f -exec md5sum {} \; | sort -k 2 | md5sum'
# # bashCommand = "pwd"

# process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE, cwd='output/SDLGL_tuts_dirty/Tutorials')
# output, error = process.communicate()
# output_string = str(output, 'utf-8')
# # print(output.splice(0,output.length()))
# print(output_string)






# name1 = "sources/main.cpp"
# name2 = "output/main.cpp"
# fin = open(name1, "r")
# data2 = fin.read()
# fin.close()
# fout = open(name2, "w")
# fout.write(data2)
# fout.close()



