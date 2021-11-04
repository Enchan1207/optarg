#pragma once

// include ---------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h> // struct option, getopt_long(), opterr, optind
#include <string.h> // strchr()
#include <stdbool.h>
#include <wctype.h> // iswalnum()

// Definition -----------------------------------------------

// termination
#define OPT_END {0, 0, 0, 0}        // for 'struct option'
#define DOCOPT_END {-1, 0, 0, 0, 0} // for 'struct docoption

// safe free macro
#define SFREE(ptr) { free(ptr); ptr = NULL; }

// for argument 'usage_arg' in printHelp()
#define DEFAULT_USAGE "[OPTION] ..."

/*
struct docstyle style = {
    .indent     = "  ",
    .separator  = " , ",
    .margin     = "        ",
    .doc_width  = 40
};
*/

// for argument 'style' in printHelp()
#define DEFAULT_STYLE (struct docstyle){ .indent = "  ", .separator = " , ", .margin = "        ", .doc_width = 40 }

// Structure ---------------------------------------------

struct optarg
{
    int opt;   // option value
    char *arg; // option's argument
};

struct docoption
{
    int val;         // option value (like id)
    int short_name;  // option short name (like 'h')
    char *long_name; // option long name (like 'help')
    int has_arg;     // option has argument: no_argument, required_argument, optional_argument
    char *help_msg;  // description for option. it is used when you use 'printHelp()'
};

struct docstyle
{
    char *indent;    // default: "  "
    char *separator; // default: " , "
    char *margin;    // default: "        "
    int doc_width;   // default: 40
};

// prototype -----------------------------------

int getopt_once(
    int argc,                      // number of arguments
    char *argv[],                  // arguments
    const char *shortopts,         // short options
    const struct option *longopts, // long options
    struct optarg findopts[],      // found options
    int len_findopts               // findopts array size
);

int getopt_flex(
    int argc,                       // number of arguments
    char **argv,                    // arguments
    const struct docoption *docopts,// options
    struct optarg *findopts,        // found options and arguments
    size_t findopts_size            // findopts array size
);

int __optSize(const struct docoption *opts);
int __isEnd(struct docoption opt);
int __initOpts(char **shortopts, size_t longopts_size, struct option **longopts, size_t shortopts_size);
void __flushOpts(char *shortopts, struct option *longopts);
int __generateLongOption(const struct docoption *docopts, size_t docopts_size, struct option *longopts, size_t longopts_size);
int __generateShortOption(const struct docoption *docopts, size_t docopts_size, char *shortopts, size_t shortopts_size);
int __calShortOptsLength(const struct docoption *docopts, size_t docopts_size);
int __convertOption(const struct docoption *docopts, struct option **longopts, char **shortopts);

int printHelp(
    const struct docoption *docopts, // options
    const char *progname,            // program name. normally, argv[0]
    const char *usage_arg,           // usage argument. normally, "[OPTION] ..."
    struct docstyle style,           // help message style
    char *postscript                 // postscript. ex: "Copyright (C) 2021 GrapeJuice."
);

void printVersion(
    const char *progname,  // program name. normally, argv[0]
    const char *version,   // version. ex: "1.0.0"
    const char *postscript // postscript. ex: "Copyright (C) 2020 GrapeJuice."
);

void __printHeader(const char *progname, const char *usage_arg);
int __shortOptionCommandLength(const struct docoption *docopts, int docopts_size);
int __longOptionCommandLength(const struct docoption *docopts, int docopts_size);
void __printOptionDocs(char *docs, unsigned int indent, unsigned int min_line_size);
int __optionCommandLength(const struct docoption *docopts, int docopts_size);
int __calIndentSize(int slen, int llen, const struct docstyle style);
int __printOptionCommand(const struct docoption opt, unsigned int slen, unsigned int llen, struct docstyle style);
