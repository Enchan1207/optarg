# optarg 1.1.0

日本語版は[こちら](https://github.com/GrapeJuicer/optarg/blob/main/README_ja.md)．

'optarg' is a library for easy argument handling in the 'main' function of the C language.

# Requirements

- headers
  - `string.h`
  - `getopt.h` (GNU extension)

# Items

- Definition
  - `OPT_END`
  - `DOCOPT_END`
  - `DEFAULT_USAGE`
  - `DEFAULT_STYLE`
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
  - [English](https://github.com/GrapeJuicer/optarg/blob/main/ref/ref_en_getopt_flex.md)
  - [Japanese](https://github.com/GrapeJuicer/optarg/blob/main/ref/ref_ja_getopt_flex.md)

# Versions

| Version | Highlight                                                                       |
| :-----: | :------------------------------------------------------------------------------ |
| v1.0.0  | First release.                                                                  |
| v1.1.0  | Add `getopt_flex()`, `printHelp()`.<br>Rename `optprocess()` to `getopt_once()` |


# Contact
| Contents | About                                         |
| :------- | :-------------------------------------------- |
| Name     | GrapeJuice                                    |
| Email    | Dev.Grape@outlook.jp                          |
| Twitter  | [@G__HaC](https://twitter.com/G__HaC)         |
| GitHub   | [GrapeJuicer](https://github.com/GrapeJuicer) |
