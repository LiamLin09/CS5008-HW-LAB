# Run by typing in 'python compile.py' in the terminal.
# You do not have to use this file--but it may save you some time
# from typing everything out.
# Note: That 'make' which we previously learned about is a 
#       build system that has additional optimizations for compiling code.
#       This simple python script is primarily for convenience.
import os

os.system("clang tcpserver.c -o tcpserver")
os.system("clang tcpclient.c -o tcpclient")
