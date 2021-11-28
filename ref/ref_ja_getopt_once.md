# リファレンス - getopt_once()

*English version is [here](https://github.com/GrapeJuicer/optarg/blob/main/ref/ref_en_getopt_once.md).*

こちらは，'getopt_once()' 関数とそれに関連する要素のリファレンスになります．

*注: 2021/11/4に `getopt_once()` 関数は  `optprocess()` から改名されました*

# 概要

`getopt_once()` は，`main` 関数の引数からオプションを解析する関数です．
これは，`getopt.h` の `getopt_long()` 関数のラッパー関数です．
通常，`getopt()` や `getopt_long()` は1つのオプションしか解析できないので，繰り返し呼び出す必要があります．
対して，`getopt_once()`では一度の呼び出しですべてのオプションの解析が可能です．
解析結果は `struct optarg` 構造体に格納されます．

# リファレンス
- `struct option`
    `struct option` は、定義するオプションのリストを格納するための構造体です．この構造体では1つのオプションの情報しか格納できないため，通常は配列として宣言する必要があります．`struct option` は以下のように定義されています．
    ```c
    struct option
    {
        const char *name; /* option name, without leading hyphens */
        int has_arg;      /* does it take an argument?		*/
        int *flag;        /* where to save its status, or NULL	*/
        int val;          /* its associated status value		*/
    };
    ```
    *注：この構造は `getopt.h` で定義されています。*

- `struct optarg`

    `struct optarg` は， `getopt_once()` 関数で解析された結果を格納するための構造体です．この構造体では1つの結果の情報しか格納できないため，通常は配列として宣言する必要があります．**この配列の大きさは、オプションの数以上である必要があります．**
    `struct optarg` は以下のように定義されています．
    ```c
    struct optarg
    {
        int opt;   // オプションの値
        char *arg; // オプションの引数
    };
    ```

- `getopt_once(int argc, char *argv[], const char *shortopts, const struct option *longopts, struct optarg findopts[], int len_findopts)`

    `getopt_once()` は，`main` 関数の引数からオプションを解析することができる関数です．
    `getopt_once()` は，以下のように定義されています。
    ```c
    // 戻り値: 見つかったオプションの数
    int getopt_once(
        int argc,                      // 引数の数
        char *argv[],                  // 引数
        const char *shortopts,         // オプション(短)
        const struct option *longopts, // オプション(長)
        struct optarg findopts[],      // 見つかったオプションの情報
        int len_findopts               // findopts の配列の大きさ
    );
    ```


# 使用方法

[example/](https://github.com/GrapeJuicer/optarg/blob/main/example) にサンプルプログラムがあります．
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

検出されたオプションの情報の格納先を `struct optarg` 型の変数で宣言します．

```c
struct optarg findopts[OPTSIZE];
```

`OPTSIZE` は，検出され得るオプションの最大数以上の値である必要があります．

## ステップ. 4

`getopt_once()` 関数を用いて `main` 関数の引数を解析します．

```c
int folen = getopt_once(argc, argv, shortopts, longopts, findopts, OPTSIZE);
```

`argc` と `argv` は， `main` 関数の引数であり，次のように記述します．

```c
int main(int argc, char *argv[])
{
    ...
}
```

関数 `getopt_once()` の戻り値は，見つかったオプションの数です．

## ステップ. 5

関数 `getopt_once()` で取得したオプションは，以下のように処理します．

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