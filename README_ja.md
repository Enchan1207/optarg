# optarg

optarg は，C言語の `main` 関数で引数を簡単に処理するためのライブラリです．

# 要求事項

- ヘッダ
  - string.h
  - `getopt.h` (GNU拡張)

# 宣言/定義

- 定義
  - `OPT_END`
- 型
  - `struct option`
  - `struct optarg`
- 関数
  - `optprocess(...)`

# 使用方法

[example/](https://github.com/GrapeJuicer/optarg/blob/main/example/example.c) にサンプルプログラムがあります．
ここでは，別の例を説明します．仕様は以下の通りです．

| short option         | long option                              | argument |
| :------------------- | :--------------------------------------- | :------- |
| -h                   | --help                                   | none     |
| -v                   | --version                                | none     |
| -r=`<reqoption>`     | --req=`<reqoption>`, --req `<reqoption>` | require  |
| -a, -a=`<anyoption>` | --any, --any=`<anyoption>`               | optional |

## ステップ. 1

short option の内容を `char *` 型の変数で宣言します．

```c
char *shortopts = "hvr:a::"; // help, version, req + require_arg, any + optional_arg
```

- `<文字>` は**引数を必要としない**ことを意味します．
- `<文字>:` は**引数を必要とする**ことを意味し，次のように記述できます: `-c=argument`, `-c argument`.
- `<文字>::` **引数の有無を問わない**ことを意味し，次のように記述できます: `-c`, `-c=argument`. ただし，次の記述はできません: `-c argument`.

## ステップ. 2

long option の内容を `struct option` 型の変数で宣言します．

```c
struct option longopts[] = {
    {"help"   , no_argument      , NULL, 'h'},
    {"version", no_argument      , NULL, 'v'},
    {"req"    , required_argument, NULL, 'r'},
    {"any"    , optional_argument, NULL, 'a'},
    OPT_END // It means the end of this array.
};
```

option 構造体に関する詳細は[こちら](http://linuxjm.osdn.jp/html/LDP_man-pages/man3/getopt.3.html)を参照してください．

## ステップ. 3

検出されたオプションの情報を格納先を `struct optarg` 型の変数で宣言します．

```c
struct optarg findopts[OPTSIZE];
```

`OPTSIZE` は，検出され得るオプションの最大数以上の値である必要があります．

## ステップ. 4

`optprocess` 関数を用いて `main` 関数の引数を処理します．

```c
int folen = optprocess(argc, argv, shortopts, longopts, findopts, OPTSIZE);
```

`argc` と `argv` は， `main` 関数の引数であり，次のように記述します．

```c
int main(int argc, char *argv[])
{
    ...
}
```

関数 `optprocess` の戻り値は，見つかったオプションの数です．

## ステップ. 5

関数 `optprocess` で取得したオプションは，以下のように処理します．

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

オプションの引数は `findopts[i].arg` に格納されます．

## ステップ. 6

`main` 関数の引数のうち，オプションでないものは `argv[optind] ~ argv[argc-1]` に格納されます．

# 注意事項

- この関数を使用すると，`main` 関数の引数である `argv` の順序が入れ替わることがあります．そのため，`main` 関数の最初で引数を処理することが推奨されます．

# 問い合わせ
| 項目    | 内容                                          |
| :------ | :-------------------------------------------- |
| Name    | GrapeJuice                                    |
| Email   | Dev.Grape@outlook.jp                          |
| Twitter | [@G__HaC](https://twitter.com/G__HaC)         |
| GitHub  | [GrapeJuicer](https://github.com/GrapeJuicer) |
