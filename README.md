# optarg 1.1.0

'optarg' is a library for easy argument handling in the 'main' function of the C language.

# Requirements

- headers
  - string.h
  - `getopt.h` (GNU extension)

# Items

- Definition
  - `OPT_END`
  - `DOCOPT_END`
  - DEFAULT_USAGE
  - DEFAULT_STYLE
- Structure
  - `struct option` ... *This is a structure attached to `getopt.h`*
  - `struct optarg`
  - `struct docoption`
  - `struct docstyle`
- Function
  - `getopt_once(...)`
  - `getopt_flex(...)`
  - `printHelp(...)`
  - `printVersion(...)`

# Reference

- Parsing arguments with `getopt_once()` (old: `optprocess()`)
  - [English](https://github.com/GrapeJuicer/optarg/blob/main/ref/ref_en_getopt_once.md)
  - [Japanese](https://github.com/GrapeJuicer/optarg/blob/main/ref/ref_ja_getopt_once.md)
- Parsing arguments with `getopt_flex()`
  - [English](https://github.com/GrapeJuicer/optarg/blob/main/ref/ref_en_getopt_flex.md) *WIP
  - [Japanese](https://github.com/GrapeJuicer/optarg/blob/main/ref/ref_ja_getopt_flex.md) *WIP

# Contact
| Contents | About                                         |
| :------- | :-------------------------------------------- |
| Name     | GrapeJuice                                    |
| Email    | Dev.Grape@outlook.jp                          |
| Twitter  | [@G__HaC](https://twitter.com/G__HaC)         |
| GitHub   | [GrapeJuicer](https://github.com/GrapeJuicer) |
