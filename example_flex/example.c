#include <stdio.h>
#include "../optarg.h"

#define VERSION "1.0.0"
#define COPYRIGHT "Copyright (C) 2021, GrapeJuice."
#define OPTSIZE 10

enum
{
    opt_help,
    opt_version,
    opt_require,
    opt_optional,
    opt_short,
    opt_long,
};

int main(int argc, char *argv[])
{
    // option list
    struct docoption opts[] = {
        {opt_help    , 'h', "help"    , no_argument      , "This is help option."    },
        {opt_version , 'v', "version" , no_argument      , "This is version option." },
        {opt_require , 'r', "require" , required_argument, "This is required option."},
        {opt_optional, 'o', "optional", optional_argument, "This is optional option."},
        {opt_short   , 's', 0         , no_argument      , "This is short option."   },
        {opt_long    , 0  , "long"    , no_argument      , "This is long option."    },
        DOCOPT_END
    };

    // found options
    struct optarg findopts[OPTSIZE];

    // analyze
    int folen = getopt_flex(argc, argv, opts, findopts, OPTSIZE);

    // process found options
    int i;
    for (i = 0; i < folen; i++)
    {
        switch (findopts[i].opt)
        {
            {
            case opt_help:
                printf("help option is selected.\n");
                printHelp(opts, argv[0], DEFAULT_USAGE, DEFAULT_STYLE, "This is header -----", "This is footer -----");
                break;
            case opt_version:
                printf("version option is selected.\n");
                printVersion(argv[0], VERSION, "Copyright (C) 2021, Grape Juice.\nRepository: https://github.com/GrapeJuicer/optarg");
                break;
            case opt_require:
                printf("require option is selected. arg=%s\n", findopts[i].arg);
                break;
            case opt_optional:
                printf("optional option is selected. arg=%s\n", findopts[i].arg == NULL ? "None" : findopts[i].arg);
                break;
            case opt_short:
                printf("short option is selected.\n");
                break;
            case opt_long:
                printf("long option is selected.\n");
                break;
            }
        }
    }

    printf("remain arguments ---\n");

    for (i = optind; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    return 0;
}
