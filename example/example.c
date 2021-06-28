#include <stdio.h>
#include "../optarg.h"

#define OPTSIZE 10 // >= 4
int main(int argc, char *argv[])
{
    // int flags[4] = {0};

    // step 1
    char *shortopts = "hvr:a::";

    // step 2
    struct option longopts[] = {
        {"help"   , no_argument      , NULL /*&flags[0]*/ , 'h'},
        {"version", no_argument      , NULL /*&flags[1]*/ , 'v'},
        {"req"    , required_argument, NULL /*&flags[2]*/ , 'r'},
        {"any"    , optional_argument, NULL /*&flags[3]*/ , 'a'},
        OPT_END};

    // step 3
    struct optarg findopts[OPTSIZE];

    // step 4
    int folen = optprocess(argc, argv, shortopts, longopts, findopts, OPTSIZE);

    // step 5
    int i;
    for (i = 0; i < folen; i++)
    {
        switch (findopts[i].opt)
        {
        case 'h': // help
            printf("\'help\' option enabled.\n");
            break;
        case 'v': // version
            printf("\'version\' option enabled.\n");
            break;
        case 'r': // req
            printf("\'req\' option enabled. arg = %s\n", findopts[i].arg);
            break;
        case 'a': // any
            printf("\'any\' option enabled. arg = %s\n", findopts[i].arg);
            break;
        default:
            break;
        }
    }

    printf("remain arguments ---\n");
    for (i = optind; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    // printf("option flag ---\n");
    // for (i = 0; i < 4; i++)
    // {
    //     printf("flag[%d]: %d\n", i, flags[i]);
    // }
    
    return 0;
}