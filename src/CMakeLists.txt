cmake_minimum_required(VERSION 3.21)

add_library(optarg STATIC
    optarg.h
    optarg.c
    getopt_flex.c
    getopt_help.c
)
