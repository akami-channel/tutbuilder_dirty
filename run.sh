#!/usr/bin/bash
./stuff/build.py
cd output/SDLGL_tuts_dirty/Tutorials/
find . -type f -exec md5sum {} \; | sort -k 2 | md5sum