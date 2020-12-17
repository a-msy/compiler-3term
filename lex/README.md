コンパイラ Lex 演習
-------------------

### 実験用サーバへのログイン
----------------------------

情報工学実験A（ハードウェア）のプロセッサ設計実験（1学期）で利用した実験用サーバ `jikken-a2.cs.okayama-u.ac.jp` へログインする

    ssh jikken-a2.cs.okayama-u.ac.jp



### ファイルの取得
------------------

適当な作業用ディレクトリに移動して，下記でファイル群を取得

    git clone http://jikken1.arc.cs.okayama-u.ac.jp/gitbucket/git/compiler/compiler-lex.git




### 【例1 教科書 p.51】
-------------------

`(a|b)*ab` が入力されたら `OK.` そうでない場合 `wrong.` を表示

(`scan.l`)

    %%
    [\t ]+ {}
    (a|b)*ab { printf("%s: OK.\n", yytext); }
    . { printf("%s: wrong.\n", yytext); }
    %%


#### (コンパイルと実行)

    % flex scan.l                   
    % cc lex.yy.c -lfl
    % ./a.out
    aabbab                   <<< 入力
    aabbab: OK.              
    aba                      <<< 入力
    ab: OK.                  
    a: wrong.                
    ^D                       <<< 入力
    %




### 【例2 教科書 p. 52】
---------------------

operator 5種, separator, identifier, number を切り出す例

(`scan1.l`)

    %%
    [\t ]+ {}
    "+"|"-"|"*"|"/"|"=" { printf("%s (operator) ", yytext); }
    ";"                 { printf("%s (separator) ", yytext); }
    [a-z][a-z0-9]*      { printf("%s (identifier) ", yytext); }
    [0-9\.]             { printf("%s (number) ", yytext); }
    .                   { printf("%s (don't know) ", yytext); }
    %%


#### (コンパイルと実行)

    % flex scal1.l
    % cc lex.yy.c -lfl
    % ./a.out
    abc = e * 3.14 + abc / e;      <<< 入力
    abc (identifier) = (operator) e (identifier) * (operator) 3.14 (number)
    + (operator) abc (identifier) / (operator) e (identifier) ; (separator)
    ^D                             <<< 入力
    %



### 【例3 プログラミング言語の字句解析】
----------------

字句要素の切り出しを行って，切り出したトークンを表示

(`scan2.l`)

    %%
    [\t ]+         {}
    "+"            { printf("PLUS "); }
    "*"            { printf("TIMES "); }
    "("            { printf("LPAR "); }
    ")"            { printf("RPAR "); }
    [a-z][a-z0-9]* { printf("IDENTIFIER(%s) ", yytext); }
    ";"            { printf("SEPARATOR(%s) ", yytext); }
    "\n"           { printf("NEWLINE\n"); }
    .              { printf("lexical error: '%c'\n", yytext[0]);
                     return 0; // stop lexical analysis
                   }



### (演習)
-----------

上記の `scan2.l` に次の字句要素に対応するように変更せよ．

(1) 下記の演算子に対応するように変更せよ．

- '`-`'  ===> `MINUS`
- '`/`'  ===> `DIVIDE`
- '`=`'  ===> `ASSIGN`
- '`==`' ===> `EQUAL`
- '`<`'  ===> `LT`
- ...

(2) 数値（整数 あるいは 固定小数点数)
   例えば '`123`' が切り出されたら「`NUMBER(123)`」と表示

(3) キーワード '`if`', '`for`', '`while`'
   例えば '`if`' が切り出されたら「`KEYWORD(if)`」と表示

上記の(1)〜(3)の機能追加を確認するテスト用の入力を与えて，動作を確認せよ．

演習を終えたら，変更箇所と動作確認に用いた入力および出力結果を報告書にまとめよ．
なお，(1)〜(3) の変更箇所は，配布したファイル（`scan2.l.orig`）との差分を次のコマンドにより表示することができる（ファイル`scan2.l`を変更した場合）．

  `diff -c scan2.l.orig scan2.l`



---

