#include "optarg.h"

/* case 1
  -a      , --alpha         This is an option with an argument.
  -b [ARG], --beta [ARG]    This is another option with an argument.
  -c      , --charlie       This is a third option with an argument.
            --delta         This is a fourth option with an argument.
  -e                        This is a fifth option with an argument.
*/
/* case 2
  --alpha           This is an option with an argument.
  --beta [ARG]      This is another option with an argument.
  --charlie ARG     This is a third option with an argument.
  --delta           This is a fourth option with an argument.
  --echo            This is a fifth option with an argument.
*/
/* case 1
  -a          This is an option with an argument.
  -b [ARG]    This is another option with an argument.
  -c          This is a third option with an argument.
  -d ARG      This is a fourth option with an argument.
  -e          This is a fifth option with an argument.
*/

/*
  2(  ) + 1(-) + 1(sopts) + 6([=ARG]) + 2(, ) + 2(--) + n(lopts) + 6([=ARG])
= 20 + n ... option list width

*/

// summary:
//      print help message.
// arg:
//      docopts: option list
//      progname: program name = argv[0]
//      usage_arg: Format of command arguments to be displayed in USAGE.
//          If NULL, the default format is "[OPTION] ...".
//          else, write it like following: "[OPTION] ... source_file target_file" (note: Don't write prog name)
//          ex: "[OPTION] ... source_file target_file" --> "Usage: {executable} [OPTION] ... source_file target_file\n"
int printHelp(const struct docoption *docopts, const char *progname, const char *usage_arg, struct docstyle style, char *postscript)
{
    int docopts_size = __optSize(docopts);
    int slen = __shortOptionCommandLength(docopts, docopts_size);
    int llen = __longOptionCommandLength(docopts, docopts_size);
    int doc_indent = __calIndentSize(slen, llen, style);

    if (slen < 0 || llen < 0)
    {
        return -1;
    }

    // print header
    __printHeader(progname, usage_arg);

    printf("Options:\n");

    // loop for each option
    for (int i = 0; i < docopts_size; i++)
    {
        // print option command
        if (__printOptionCommand(docopts[i], slen, llen, style) == -1)
        {
            return -1;
        }

        // print option description
        __printOptionDocs(docopts[i].help_msg, doc_indent, style.doc_width);
    }

    if (postscript != NULL)
    {
        printf("\n%s\n", postscript);
    }

    return 0;
}

int __calIndentSize(int slen, int llen, const struct docstyle style)
{
    return strlen(style.indent) + slen + strlen(style.separator) + llen + strlen(style.margin);
}

void __printHeader(const char *progname, const char *usage_arg)
{
    printf("Usage: %s %s\n", progname, usage_arg);
    printf("\n");
}

int __shortOptionCommandLength(const struct docoption *docopts, int docopts_size)
{
    int i;
    int slen = 0;
    int tmp;

    // short opts length
    for (i = 0; i < docopts_size; i++)
    {
        if (docopts[i].short_name != 0)
        {
            switch (docopts[i].has_arg)
            {
            case no_argument:
                tmp = 2; // -a
                break;
            case required_argument:
                tmp = 6; // -a ARG
                break;
            case optional_argument:
                tmp = 8; // -a [ARG]
                break;
            default:
                return -1;
            }

            // save larger one
            if (tmp > slen)
            {
                slen = tmp;
            }
        }
    }

    return slen;
}

int __longOptionCommandLength(const struct docoption *docopts, int docopts_size)
{
    int i;
    int llen = 0;
    int tmp;

    // long opts length
    for (i = 0; i < docopts_size; i++)
    {
        if (docopts[i].long_name != 0)
        {
            // long opts length
            tmp = strlen(docopts[i].long_name);

            switch (docopts[i].has_arg)
            {
            case no_argument:
                tmp += 2; // --alpha
                break;
            case required_argument:
                tmp += 6; // --alpha ARG
                break;
            case optional_argument:
                tmp += 8; // --alpha [ARG]
                break;
            default:
                return -1;
            }

            // save larger one
            if (tmp > llen)
            {
                llen = tmp;
            }
        }
    }

    return llen;
}

// print only 1 command
int __printOptionCommand(const struct docoption opt, unsigned int slen, unsigned int llen, struct docstyle style)
{
    if (slen == -1 || llen == -1)
    {
        return -1;
    }

    // print indent
    printf("%s", style.indent);

    // print short option
    if (opt.short_name != 0)
    {
        switch (opt.has_arg)
        {
        case no_argument:
            printf("-%-*c", slen - 1, opt.short_name);
            break;
        case required_argument:
            printf("-%c ARG", opt.short_name);
            printf("%*s", slen - 6, ""); // space * (slen - 6)
            break;
        case optional_argument:
            printf("-%c [ARG]", opt.short_name);
            printf("%*s", slen - 8, ""); // space * (slen - 8)
            break;
        default:
            break;
        }
    }
    else
    {
        printf("%*s", slen, ""); // space * slen
    }

    // print separator
    if (opt.short_name != 0 && opt.long_name != 0)
    {
        printf("%s", style.separator);
    }
    else
    {
        printf("%*s", (int)strlen(style.separator), ""); // space * strlen(sep)
    }

    // print long option
    if (opt.long_name != 0)
    {
        switch (opt.has_arg)
        {
        case no_argument:
            printf("--%-*s", llen - 2, opt.long_name);
            break;
        case required_argument:
            printf("--%s ARG", opt.long_name);
            printf("%*s", llen - 6 - (int)strlen(opt.long_name), "");
            break;
        case optional_argument:
            printf("--%s [ARG]", opt.long_name);
            printf("%*s", llen - 8 - (int)strlen(opt.long_name), "");
            break;
        default:
            return -1;
        }
    }
    else
    {
        printf("%*s", llen, ""); // space * llen
    }

    // print margin
    printf("%s", style.margin);

    return 0;
}

// note: indent will not be applied to the first line
void __printOptionDocs(char *docs, unsigned int indent, unsigned int min_line_size)
{
    // int line = 20; // line-1文字を最低とした単語で区切る
    char *p = docs;
    bool is_first = true;
    bool contain_return = false;
    bool contain_null = false;

    while (p[0] != '\0')
    {
        // initialize
        int cnt = 0;

        // count
        // proceed until it reaches '\0' or '\n' or ' '
        while (p[cnt] != '\0' && p[cnt] != '\n' && (p[cnt] != ' ' || cnt < min_line_size - 1))
        {
            // print cnt
            cnt++;
        }

        // chck contain '\n' or '\0'
        switch (p[cnt])
        {
        case '\n':
            contain_return = true;
            break;
        case '\0':
            contain_null = true;
            break;
        default:
            break;
        }

        // if string is not ended
        if (!contain_null && !contain_return)
        {
            int peak = 0;
            // proceed until it reaches '\0' or '\n' or 'a-zA-Z0-9'
            while (p[cnt + peak] != '\0' && p[cnt + peak] != '\n' && iswalnum(p[cnt + peak]) == 0)
            {
                peak++;
            }

            if (p[cnt + peak] == '\n')
            {
                contain_return = true;
            }
            cnt += peak;
        }

        // print help msg
        printf("%*.*s\n", cnt + (is_first ? 0 : indent) /*don't indent only at the beginning*/, cnt, p);
        is_first = false;

        // update p
        p += (contain_return ? cnt + 1 : cnt);
    }
}

void printVersion(const char *progname, const char *version, const char *postscript)
{
    printf("%s %s\n", progname, version);
    if (postscript != NULL)
    {
        printf("%s\n", postscript);
    }
}
