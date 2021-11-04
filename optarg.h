#pragma once

// インクルード ---------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h> // struct option, getopt_long(), opterr, optind
#include <string.h> // strchr()

// 定義 -----------------------------------------------

#define OPT_END {0, 0, 0, 0}
#define DOCOPT_END {-1, 0, 0, 0, 0, 0}

#define SFREE(ptr) { free(ptr); ptr = NULL; }


// 構造体 ---------------------------------------------

struct optarg
{
    int opt;
    char *arg;
};

struct docoption
{
    int val;
    int short_name;
    char *long_name;
    int has_arg;
    int *flag;
    char *help_msg;
};
// プロトタイプ宣言 -----------------------------------

int optprocess(
    int argc,                      // 引数の個数
    char *argv[],                  // 引数の内容
    const char *shortopts,         // オプション群(短)
    const struct option *longopts, // オプション群(長)
    struct optarg findopts[],      // 見つかったオプションと引数の情報を格納する場所
    int len_findopts               // findoptsの配列の長さ
);

// prototype
int getopt_flex(int argc, char **argv, const struct docoption *docopts, struct optarg *findopts, size_t findopts_size);
int __optSize(const struct docoption *opts);
int __isEnd(struct docoption opt);
int __initOpts(char **shortopts, size_t longopts_size, struct option **longopts, size_t shortopts_size);
void __flushOpts(char *shortopts, struct option *longopts);
int __generateLongOption(const struct docoption *docopts, size_t docopts_size, struct option *longopts, size_t longopts_size);
int __generateShortOption(const struct docoption *docopts, size_t docopts_size, char *shortopts, size_t shortopts_size);
int __calShortOptsLength(const struct docoption *docopts, size_t docopts_size);
int __convertOption(const struct docoption *docopts, struct option **longopts, char **shortopts);

