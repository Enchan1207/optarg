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

// getopt_flex.cpp

/**
 * @fn getopt_flex
 * @brief 引数に渡された実行引数の配列をgetoptライクにパースし、結果を返します。 getopt_onceよりも直感的に使用できます。
 * 
 * @param argc 引数の数
 * @param argv 引数配列のポインタ
 * @param docopts オプション配列
 * @param docopts_size docoptsの長さ
 * @param findopts パースされたオプションの配列
 * @param findopts_size findoptsの長さ
 * @return int 成功した場合は non-optional argument のインデックスが、失敗した場合は-1が返ります。
 */
int getopt_flex(const int argc, const char **argv,
                const struct docoption *docopts, const size_t docopts_size,
                struct optarg *findopts, const size_t findopts_size);

// getopt_help.cpp

/**
 * @fn printHelp
 * @brief ヘルプメッセージを表示します。
 * 
 * @param docopts オプション配列
 * @param docopts_size docoptsの長さ
 * @param progname 名称
 * @param usage_arg 使用法に関する説明
 * @param style ヘルプメッセージのスタイル
 * @param header ヘッダ (optional)
 * @param footer フッタ (optional)
 * @return int 成功した場合は0, 失敗した場合は-1が返ります。
 */
int printHelp(const struct docoption *docopts, const size_t docopts_size,
              const char *progname, const char *usage_arg, const struct docstyle style, const char *header, const char *footer);

/**
 * @fn printVersion
 * @brief バージョン情報を表示します。
 * 
 * @param progname 名称
 * @param version バージョン
 * @param postscript 詳細情報
 */
void printVersion(const char *progname, const char *version, const char *postscript);
