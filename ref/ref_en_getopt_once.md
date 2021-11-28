# reference - getopt_once()

*日本語版は[こちら](https://github.com/GrapeJuicer/optarg/blob/main/ref/ref_ja_getopt_once.md).*

This is reference for 'getopt_once()' function and objects associated with it.

*Note: `getopt_once()` is renamed from `optprocess()`  on Nov. 4, 2021.*

# Summary

`getopt_once()` is a function that can parse options from the arguments of the main function.
It is a wrapper function for the `getopt_long()` function in `getopt.h`.
Normally, `getopt()` and `getopt_long()` can only parse one argument, so they need to be called repeatedly.
`getopt_once()` only needs to be called once, and the result of the analysis will be stored in the `struct optarg` structure.

# Reference
- `struct option`

    `struct option` is a structure to store a list of options to be defined. It can store information for a single option, so it usually needs to be declared as an array. It is defined as follows:
    ```c
    struct option		/* specification for a long form option...	*/
    {
        const char *name; /* option name, without leading hyphens */
        int has_arg;      /* does it take an argument?		*/
        int *flag;        /* where to save its status, or NULL	*/
        int val;          /* its associated status value		*/
    };
    ```
    *Note: this structure defined in `getopt.h`*

- `struct optarg`

    `struct optarg` is a structure to store the parsed results of the `getopt_once()` function. It can store information for a single result, so it usually needs to be declared as an array. **The size of the array must be greater than or equal to the number of options.**
    It is defined as follows:
    ```c
    struct optarg
    {
        int opt;   // option value
        char *arg; // option's argument
    };
    ```

- `getopt_once(int argc, char *argv[], const char *shortopts, const struct option *longopts, struct optarg findopts[], int len_findopts)`

    `getopt_once()` is a function that can parse options from the arguments of the main function.
    It is defined as follows:
    ```c
    // return: Number of found options
    int getopt_once(
        int argc,                      // Number of arguments
        char *argv[],                  // Arguments
        const char *shortopts,         // short options
        const struct option *longopts, // long options
        struct optarg findopts[],      // Found options with their args
        int len_findopts               // Length of the findopts array
    );
    ```

# Usage

There is a sample program in [example/](https://github.com/GrapeJuicer/optarg/blob/main/example) .
In this section, I will explain the another example. The specifications are as follows:

| short option                      | long option                              | argument |
| :-------------------------------- | :--------------------------------------- | :------- |
| -h                                | --help                                   | none     |
| -v                                | --version                                | none     |
| -r `<reqoption>`, -r`<reqoption>` | --req=`<reqoption>`, --req `<reqoption>` | require  |
| -a, -a`<anyoption>`               | --any, --any=`<anyoption>`               | optional |

## Step. 1

Declare a variable for the short option by using `char *`:

```c
char *shortopts = "hvr:a::"; // help, version, req + require_arg, any + optional_arg
```

- `<character>` means **no require** argument.
- `<character>:` means **require** argument. You can write option like: `-c=argument`, `-c argument`.
- `<character>::` means**optional** argument. You can write option or not, like: `-c`, `-c=argument`. But you can't write it by `-c argument`.

## Step. 2

Declare a variable for the long option by using `struct option`:

```c
struct option longopts[] = {
    {"help"   , no_argument      , NULL, 'h'},
    {"version", no_argument      , NULL, 'v'},
    {"req"    , required_argument, NULL, 'r'},
    {"any"    , optional_argument, NULL, 'a'},
    OPT_END // It means the end of this array.
};
```

For more details about the `option` structure, click [here(jp)](http://linuxjm.osdn.jp/html/LDP_man-pages/man3/getopt.3.html) or search for "man page of getopt".

## Step. 3

Declare a variable for the found option by using `struct optarg`:

```c
struct optarg findopts[OPTSIZE];
```

`OPTSIZE` must be larger than or equal to the number of found options.

## Step. 4

Analyze the arguments using the `getopt_once()` function:

```c
int folen = getopt_once(argc, argv, shortopts, longopts, findopts, OPTSIZE);
```

`argc` and `argv` are the arguments of the `main` function and are written as follows:

```c
int main(int argc, char *argv[])
{
    ...
}
```

The return value of the function `getopt_once()` is the number of found options.

## Step. 5

The options obtained by the function `getopt_once()` are processed as follows:

```c
int i;
for (i = 0; i < folen; i++)
{
    switch (findopts[i].opt)
    {
    case 'h': // help
        ...
        break;
    case 'v': // version
        ...
        break;
    case 'r': // req
        ...
        break;
    case 'a': // any
        ...
        break;
    default:
        break;
    }
}
```

The option's arguments are stored in `findopts[i].arg`.

## Step. 6

The non-optional arguments of the main function are stored in `argv[optind] ~ argv[argc-1]`.

# Attention

- When this function is used, the order of `argv`, the argument of the `main` function, may be switched. Therefore, it is preferable to process the arguments at the beginning of the `main` function.
