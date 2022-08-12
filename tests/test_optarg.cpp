//
//
//
#include <gtest/gtest.h>

extern "C" {
#include <optarg.h>
}

// 単一オプションのパース
TEST(OptionParseTests, ParseValidArgument) {
    // オプションの属性を定義
    const int option_type = 1;
    const struct docoption docopts[] = {
        {option_type, 'h', "help", no_argument, "the description of option"}};
    const size_t docopts_size = sizeof(docopts) / sizeof(struct docoption);

    // argc, argvを設定して
    const char *argv[] = {
        "(progname",
        "--help"};
    const int argc = 2;

    // パース
    struct optarg found_options[5];
    int parse_result = getopt_flex(argc, argv, docopts, docopts_size, found_options, 5);
    EXPECT_NE(parse_result, -1);

}
