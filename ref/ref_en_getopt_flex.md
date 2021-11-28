# reference - getopt_flex()

*日本語版は[こちら](https://github.com/GrapeJuicer/optarg/blob/main/ref/ref_ja_getopt_flex.md).*

This is reference for 'getopt_flex()' function and objects associated with it.

# Summary

`getopt_flex()` is a function that can parse options from the arguments of the main function.

It is a wrapper function for the `getopt_long()` function in `getopt.h`.
It is essentially the same as `getopt_once()`, the structure to be used is different.
`getopt_flex()` uses `struct docoption`.

The difference between `getopt_flex()` and `getopt_once()` is as follows:

- `struct docoption` can hold both long and short option
- Remove the ability to store values in flags
- The structure array used by `getopt_flex()` can be used `printHelp()`.

# Reference

- `struct docoption`

    `struct docoption` is a structure to store a list of options to be defined.
    It can store information for a single option, so it usually needs to be declared as an array.

    It is defined as follows:

    ```c
    struct docoption
    {
        const int    val;        // option value = id
        const int    short_name; // option short name
        const char * long_name;  // option long name
        const int    has_arg;    // option has argument: no_argument, required_argument, optional_argument
        const char * help_msg;   // description for option. it is used when you use 'printHelp()'
    };
    ```

- `struct optarg`

    `struct optarg` is a structure to store the parsed results of the `getopt_flex()` function.
    It can store information for a single result, so it usually needs to be declared as an array.
    **The size of the array must be greater than or equal to the number of options.**

    It is defined as follows:

    ```c
    struct optarg
    {
        int opt;   // option value
        char *arg; // option's argument
    };
    ```

- `struct docstyle`

    `struct docstyle` is a structure used to show the help with `printHelp()`

    It is defined as follows:

    ```c
    struct docstyle
    {
        const char * indent;    // default: "  "
        const char * separator; // default: " , "
        const char * margin;    // default: "        "
        int          doc_width; // default: 40
    };
    ```

    Default style: `DEFAULT_STYLE` is defined as follows:

    ```c
    #define DEFAULT_STYLE (struct docstyle){ .indent = "  ", .separator = " , ", .margin = "        ", .doc_width = 40 }
    ```


    The relationship between each member and the help message is as follows:

    ![](img/2021-11-28-19-01-58.png)

- `getopt_flex(int argc, char **argv, const struct docoption *docopts, struct optarg *findopts, size_t findopts_size)`

    `getopt_flex()` is a function that can parse options from the arguments of the main function.

    It is defined as follows:

    ```c
    // return: Number of found options
    int getopt_flex(
        int argc,                        // number of arguments
        char **argv,                     // arguments
        const struct docoption *docopts, // options
        struct optarg *findopts,         // found options and arguments
        size_t findopts_size             // findopts array size
    );
    ```

- `printHelp(const struct docoption *docopts, const char *progname, const char *usage_arg, const struct docstyle style, const char *header, const char *footer)`

    Generate and show help based on the option information stored in the `struct docoption`.

  - `docopts` : An array of `struct docoption` containing the options.
  - `progname` : Prrogram name. Specify `argv[0]`.
  - `usage_arg` : Specify the format of the usage arguments: `xxx.exe {specify here}` / Specify `DEFAULT_USAGE` to use the default format (`"[OPTION] ..."`).
  - `style` : Specify the format of the options. Use `struct docstyle`. Specify `DEFAULT_STYLE` to use the default format.
  - `header` : Header information.
  - `footer` : Footer information.

    The relationship betweeb each argument and help message is as follows:

    ![](img/2021-11-28-19-13-38.png)

    This function has the following features:

    - Depending on the type of option, the position of the description is automatically adjusted.
    - Automatically break lines when the width specified by `doc_width` in `struct docstyle` is exceeded.
    - No line break in the middle of a word.
    - When a newline character (`'\n'`) is inserted manually, it will be automatically indented.
    - Not output spaces between words after automatic line break.
    - Output spaces following a line break character (`'\n'`) after a manual line break.

- `printVersion(const char *progname, const char *version, const char *postscript)`

    Show version.

  - `progname` : Program name. Specify `argv[0]`.
  - `version` : Version.
  - `postscript` : Postscript. ≈ Footer. Write Copyright etc.


# Usage

There is a sample program in [example_flex/](https://github.com/GrapeJuicer/optarg/blob/main/example_flex) .
In this section, I will explain the another example.

The specifications are as follows:

| short option                      | long option                              | argument |
| :-------------------------------- | :--------------------------------------- | :------- |
| -h                                | --help                                   | none     |
| -v                                | --version                                | none     |
| -r `<reqoption>`, -r`<reqoption>` | --req=`<reqoption>`, --req `<reqoption>` | require  |
| -a, -a`<anyoption>`               | --any, --any=`<anyoption>`               | optional |
| -s                                |                                          | none     |
|                                   | --long                                   | none     |

## Step. 1

Define IDs.
There should be as many IDs as option size.

```c
enum {
    opt_help,
    opt_version,
    opt_require,
    opt_optional,
    opt_short,
    opt_long,
};
```

## Step. 2

Declare a variable for the long option by using `struct docoption`:
Specify `DOCOPT_END` at the end of the array.

```c
struct docoption opts[] = {
    {opt_help    , 'h', "help"    , no_argument      , "This is help option."    },
    {opt_version , 'v', "version" , no_argument      , "This is version option." },
    {opt_require , 'r', "require" , required_argument, "This is required option."},
    {opt_optional, 'o', "optional", optional_argument, "This is optional option."},
    {opt_short   , 's', "short"   , no_argument      , "This is short option."   },
    {opt_long    , 'l', "long"    , no_argument      , "This is long option."    },
    DOCOPT_END
};
```

## Step. 3

Declare a variable for the found option by using `struct optarg`:

```c
struct optarg findopts[OPTSIZE];
```

`OPTSIZE` must be larger than or equal to the number of found options.

## Step. 4

Analyze the arguments using the `getopt_flex()` function:

```c
int folen = getopt_flex(argc, argv, opts, findopts, OPTSIZE);
```

`argc` and `argv` are the arguments of the `main` function and are written as follows:

```c
int main(int argc, char *argv[])
{
    ...
}
```

The return value of the function `getopt_flex()` (= folen) is the number of found options.

## Step. 5

The options obtained by the function `getopt_flex()` are processed as follows:

```c
int i;
for (i = 0; i < folen; i++) {
    switch (findopts[i].opt) {
    {
    case opt_help:
        ...
        break;
    case opt_version:
        ...
        break;
    case opt_require:
        ...
        break;
    case opt_optional:
        ...
        break;
    case opt_short:
        ...
        break;
    case opt_long:
        ...
        break;
    }
}
```

The option's arguments are stored in `findopts[i].arg`.

## Step. 6

The non-optional arguments of the main function are stored in `argv[optind] ~ argv[argc-1]`.

# Step. 7

It is recommended to use `printHelp()` and `printVersion()` when `help` and `version` are detected.

# Attention

- When this function is used, the order of `argv`, the argument of the `main` function, may be switched. Therefore, it is preferable to process the arguments at the beginning of the `main` function.
