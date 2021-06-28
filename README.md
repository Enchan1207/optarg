# optarg

'optarg' is a library for easy argument handling in the 'main' function of the C language.

# Requirements

- headers
  - string.h
  - `getopt.h` (GNU extension)

# Items

- Definition
  - `OPT_END`
- Variable
  - `struct option`
  - `struct optarg`
- Function
  - `optprocess(...)`

# Usage

For example:

| short option         | long option                              | argument |
| :------------------- | :--------------------------------------- | :------- |
| -h                   | --help                                   | none     |
| -v                   | --version                                | none     |
| -r=`<reqoption>`     | --req=`<reqoption>`, --req `<reqoption>` | require  |
| -a, -a=`<anyoption>` | --any, --any=`<anyoption>`               | optional |

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

Processes the arguments using the `optprocess` function:

```c
int folen = optprocess(argc, argv, shortopts, longopts, findopts, OPTSIZE);
```

`argc` and `argv` are the arguments of the `main` function and are written as follows:

```c
int main(int argc, char *argv[])
{
    ...
}
```

The return value of the function `optprocess` is the number of found options.

## Step. 5

The options obtained by the function `optprocess` are processed as follows:

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

# Contact
| Contents | About                                         |
| :------- | :-------------------------------------------- |
| Name     | GrapeJuice                                    |
| Email    | Dev.Grape@outlook.jp                          |
| Twitter  | [@G__HaC](https://twitter.com/G__HaC)         |
| GitHub   | [GrapeJuicer](https://github.com/GrapeJuicer) |
