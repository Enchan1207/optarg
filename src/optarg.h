/*
optarg 2.0.0
Copyright (C) 2021, GrapeJuice.
GitHub: https://github.com/GrapeJuicer/optarg
*/

#pragma once

// include ---------------------------------------
#include <getopt.h>  // struct option, getopt_long(), opterr, optind
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // strchr()
#include <wctype.h>  // iswalnum()

// Definition -----------------------------------------------

// termination
#define OPT_END {0, 0, 0, 0}        // for 'struct option'
#define DOCOPT_END {-1, 0, 0, 0, 0} // for 'struct docoption'

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
#define DEFAULT_STYLE (struct docstyle) { .indent = "  ", .separator = " , ", .margin = "        ", .doc_width = 40 }

// Structure ---------------------------------------------

/**
 * @struct optarg
 * @brief コマンドラインオプションの種類および引数値を格納する構造体
 */
struct optarg {
    int opt; //! オプションを識別するための値
    char *arg; //! オプションがとる引数
};

/**
 * @struct docoption
 * @brief オプションに関する情報をまとめて格納する構造体
 */
struct docoption {
    const int val; //! オプションを識別するための値
    const int short_name; //! オプションを表す文字 (like 'h')
    const char *long_name; //! オプションを表す文字列 (like 'help')
    const int has_arg; //! オプションが引数をとるか(no_argument, required_argument, optional_argument)
    const char *help_msg; //! オプションの説明。 'printHelp()' 関数より参照されます。
};

/**
 * @struct docstyle
 * @brief ヘルプドキュメントのスタイルを定義する構造体
 */
struct docstyle {
    const char *indent; //! 字下げ (default: "  ")
    const char *separator; //! 区切り文字 (default: " , ")
    const char *margin; //! 余白 (default: "        ")
    int doc_width; //! 最大横幅 (default: 40)
};

// prototype -----------------------------------

// optarg.cpp

/**
 * @fn getopt_once
 * @brief 引数に渡された実行引数の配列をgetopt-likeにパースし、結果を返します。
 * 
 * @param argc 引数の数
 * @param argv 引数配列のポインタ
 * @param shortopts 短いオプションの配列
 * @param longopts 長いオプションの配列
 * @param findopts パースされたオプションの配列
 * @param len_findopts findoptsの長さ
 * @return int 成功した場合は0, 失敗した場合は-1が返ります。
 */
int getopt_once(int argc, char *argv[], const char *shortopts, const struct option *longopts, struct optarg findopts[], int len_findopts);

// getopt_flex.cpp

/**
 * @fn getopt_flex
 * @brief 引数に渡された実行引数の配列をgetoptライクにパースし、結果を返します。 getopt_onceよりも直感的に使用できます。
 * 
 * @param argc 引数の数
 * @param argv 引数配列のポインタ
 * @param docopts オプション配列
 * @param findopts パースされたオプションの配列
 * @param findopts_size findoptsの長さ
 * @return int 成功した場合は non-optional argument のインデックスが、失敗した場合は-1が返ります。
 */
int getopt_flex(int argc, char **argv, const struct docoption *docopts, struct optarg *findopts, size_t findopts_size);

int __initOpts(char **shortopts, size_t shortopts_size, struct option **longopts, size_t longopts_size);
void __flushOpts(char *shortopts, struct option *longopts);
int __optSize(const struct docoption *opts);
int __generateLongOption(const struct docoption *docopts, size_t docopts_size, struct option *longopts, size_t longopts_size);
int __generateShortOption(const struct docoption *docopts, size_t docopts_size, char *shortopts, size_t shortopts_size);
int __calShortOptsSize(const struct docoption *docopts, size_t docopts_size);
int __convertOption(const struct docoption *docopts, struct option **longopts, char **shortopts);
int __isEnd(const struct docoption opt);

// getopt_help.cpp

/**
 * @fn printHelp
 * @brief ヘルプメッセージを表示します。
 * 
 * @param docopts オプション配列
 * @param progname 名称
 * @param usage_arg 使用法に関する説明
 * @param style ヘルプメッセージのスタイル
 * @param header ヘッダ (optional)
 * @param footer フッタ (optional)
 * @return int 成功した場合は0, 失敗した場合は-1が返ります。
 */
int printHelp(const struct docoption *docopts, const char *progname, const char *usage_arg, const struct docstyle style, const char *header, const char *footer);

/**
 * @fn printVersion
 * @brief バージョン情報を表示します。
 * 
 * @param progname 名称
 * @param version バージョン
 * @param postscript 詳細情報
 */
void printVersion(const char *progname, const char *version, const char *postscript);

void __printUsage(const char *progname, const char *usage_arg);
int __shortOptionCommandLength(const struct docoption *docopts, int docopts_size);
size_t __longOptionCommandLength(const struct docoption *docopts, int docopts_size);
// int  __optionCommandLength      (const struct docoption *docopts, int docopts_size);
int __printOptionCommand(const struct docoption opt, size_t slen, size_t llen, struct docstyle style);
void __printOptionDocs(const char *docs, size_t indent, size_t min_line_size);
size_t __calIndentSize(size_t slen, size_t llen, const struct docstyle style);
