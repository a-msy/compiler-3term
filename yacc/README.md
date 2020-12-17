コンパイラ Yacc 演習
-------------------

### 実験用サーバへのログイン
----------------------------

情報工学実験A（ハードウェア）のプロセッサ設計実験（1学期）で利用した
実験用サーバ `jikken-a2.cs.okayama-u.ac.jp` へログインする．

    ssh jikken-a2.cs.okayama-u.ac.jp



### ファイルの取得
------------------

下記で取得

    git clone http://jikken1.arc.cs.okayama-u.ac.jp/gitbucket/git/compiler/compiler-yacc.git




### 【 教科書 4.4 p.118〜】
-------------------

簡単な式の構文解析
テキスト 文法G1

（注意）
テキストのコードは，32ビットの実行環境を前提に書かれている．
本演習では，64ビットの実行環境を用いるため，テキストで32ビット整数 (int)
となっている箇所を，long 型に変更している．
long 型は，ポインタ型と同じ幅の型である．
32ビット実行環境では32ビット，64ビット実行環境では64ビットとなるため，
双方の実行環境でも同様に扱える．
コード中に，char へのポインタ型を整数型に変換して利用している箇所があり，
上記の変更を行わないと，コンパイル時に警告（64ビットのポインタ型を
32ビット整数型へ変換している箇所）がでることへの対応である．


(`parser.y`)

    %{
    #include <stdio.h>
    %}
    %token PLUS TIMES LPAR RPAR IDENTIFIER
    %%
    E: E PLUS T { $$ = make_tuple("+", $1, $3); }
     | T        { $$ = $1; }
    T: T TIMES F { $$ = make_tuple("*", $1, $3); }
     | F        { $$ = $1; }
    F: LPAR E RPAR { $$ = $2; }
     | IDENTIFIER  { $$ = $1; }
    %%
    long prev_tuple = 0;
    long make_tuple(char *op, long arg1, long arg2) {
        printf("T%d: (%s, ", ++prev_tuple, op);
        if (arg1 > 0) 
            printf("%s, ", arg1);
        else
            printf("T%d, ", -arg1);
        if (arg2 > 0) 
            printf("%s", arg2);
        else
            printf("T%d", -arg2);
        printf(")\n");
        return -prev_tuple;
    }



(`scanner.l`)

    %{
    #include "y.tab.h"
    extern long yylval; /* long型へ変更 (LP32/LP64対応) */
    long copy_lexeme(); /* 関数 copy_lexeme のプロトタイプ宣言 */
    %}
    %%
    [\t ]+ {}
    "+" { return PLUS; }
    "*" { return TIMES; }
    "(" { return LPAR; }
    ")" { return RPAR; }
    [a-z][a-z0-9]* { yylval = copy_lexeme(); return IDENTIFIER; }
    \n { return 0; }
    . { printf("lexical error: '%c'\n", yytext[0]); }
    %%
    char StringTable[1000];
    char *STp = StringTable;
    long copy_lexeme() {
        long p = (long) STp;
        strcpy(STp, yytext);
        STp += strlen(yytext) + 1;
        return p;
    }




#### (コンパイルと実行)

    % yacc -d parser.y
    % flex scanner.l
    % cc y.tab.c lex.yy.c -ly -lfl
    % ./a.out
    x*y+z*w                  <<< 入力
    T1: (*, x, y)
    T2: (*, z, w)
    T3: (+, T1, T2)

    % ./a.out
    x+y+                     <<< 入力
    T1: (+, x, y)
    syntax error
    %


下記のようにファイルで入力を与えて実行することもできる．

    % ./a.out < test1.txt
    T1: (*, x, y)
    T2: (*, z, w)
    T3: (+, T1, T2)
    % ./a.out < test2.txt
    T1: (+, x, y)
    syntax error
    %


ここで`test1.txt` と `test2.txt` は次の内容である．

(`test1.txt`)

    x*y+z*w

(`test2.txt`)

    x+y+



### (演習1)
-----------

上記のコードでは，入力として数値を含む式（例えば，`a + 10`）には対応していない．
数値を含む式に対応するように改変し，動作を確認せよ．



### (演習2)
-----------

テキスト p.135 演習問題 4.6 のコードの動作を述べよ．
またコードを記述し，実際に動作させて確認せよ．


### 追加
--------

余力のある人は，下記も参照せよ．

[構文木オブジェクトを作成する例](http://jikken1.arc.cs.okayama-u.ac.jp/gitbucket/compiler/compiler-yacc/blob/master/README2.md)

---
