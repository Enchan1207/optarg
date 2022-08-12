cmake_minimum_required(VERSION 3.21)

add_library(optarg STATIC
    optarg.h
    getopt_flex.c
    getopt_help.c
)
