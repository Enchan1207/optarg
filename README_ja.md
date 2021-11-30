# optarg 1.1.0

English version is [here](https://github.com/GrapeJuicer/optarg/blob/main/README.md).

optarg は，C言語の `main` 関数で引数を簡単に処理するためのライブラリです．

## 要求事項

- ヘッダ
  - `string.h`
  - `getopt.h` (GNU拡張)

## 宣言/定義

- 定義
  - `OPT_END`
  - `DOCOPT_END`
  - `DEFAULT_USAGE`
  - `DEFAULT_STYLE`
- 構造体
  - `struct option` ... *This is a structure attached to `getopt.h`*
  - `struct optarg`
  - `struct docoption`
  - `struct docstyle`
- 関数
  - `getopt_once(...)`
  - `getopt_flex(...)`
  - `printHelp(...)`
  - `printVersion(...)`

## リファレンス

- `getopt_once()` (旧: `optprocess()`) による引数の解析
  - [English](https://github.com/GrapeJuicer/optarg/blob/main/ref/ref_en_getopt_once.md)
  - [Japanese](https://github.com/GrapeJuicer/optarg/blob/main/ref/ref_ja_getopt_once.md)
- `getopt_flex()` による引数の解析
  - [English](https://github.com/GrapeJuicer/optarg/blob/main/ref/ref_en_getopt_flex.md)
  - [Japanese](https://github.com/GrapeJuicer/optarg/blob/main/ref/ref_ja_getopt_flex.md)

## バージョン情報

| バージョン | ハイライト                                                                                   |
| :--------: | :------------------------------------------------------------------------------------------- |
|   v1.0.0   | 初回リリース．                                                                               |
|   v1.1.0   | 次の関数を追加: `getopt_flex()`, `printHelp()`<br>`optprocess()` を `getopt_once()` に変更． |

## ライセンス

本リポジトリはMITライセンスの下で公開されています。詳細については、[ライセンス](https://github.com/GrapeJuicer/optarg/edit/main/LICENSE)を参照してください。

## 問い合わせ
| 項目    | 内容                                          |
| :------ | :-------------------------------------------- |
| Name    | GrapeJuice                                    |
| Email   | Dev.Grape@outlook.jp                          |
| Twitter | [@G__HaC](https://twitter.com/G__HaC)         |
| GitHub  | [GrapeJuicer](https://github.com/GrapeJuicer) |
