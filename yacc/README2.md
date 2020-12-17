

### 構文木オブジェクトを作成する例
----------------------------------

教科書の p.118 4.4 にある例では，構文解析で還元の際に構文木を作成せずに
作成される木を表示するだけであった．
ここでは，実際に構文木を作成する例を示す．

テキストにある簡単な式の文法G1（一部，整数値に対応するように拡張）の構文解析プログラムを生成する yacc の記述を
以下に示す．

(`parser2.y`)

    %{
    #include <stdlib.h>
    #include "tree.h"
    %}
    %union {
        char   *name;
        tree_t *tree;
    }
    %token PLUS TIMES LPAR RPAR 
    %token <name> IDENTIFIER
    %token <name> NUMBER
    %type <tree> E T F
    %%
    Expr: E        { print_tree($1); }
    E: E PLUS T    { $$ = make_binary(Add_Expr, $1, $3); }
     | T           { $$ = $1; }
    T: T TIMES F   { $$ = make_binary(Mul_Expr, $1, $3); }
     | F           { $$ = $1; }
    F: LPAR E RPAR { $$ = $2; }
     | IDENTIFIER  { $$ = make_var($1); }
     | NUMBER      { $$ = make_iconst(atoi($1)); }
    %%


冒頭にある

    %{
    #include <stdlib.h>
    #include "tree.h"
    %}

の部分では，動作を記述するC言語コードで用いる宣言等を記述しており，
ASCII文字列から整数への変換を行う atoi 関数のプロトタイプ宣言を含む
標準ライブラリのヘッダファイル `stdlib.h` をインクルードしている．
さらに，構文木のデータ構造の型の定義，構文木の生成や表示関数の
プロトタイプ宣言を含むヘッダファイル `tree.h` をインクルードしている．
後者については後述する．

次の

    %union {
        char   *name;
        tree_t *tree;
    }

の記述は，還元時に返す値の型の定義である．
省略時は int型の値を返すが，ここでは文字へのポインタ（`char *`）あるいは
構文木を表す型 `tree_t` へのポインタ（`tree_t *`）のいずれかの値を返すように
記述している．
還元する際に使用する生成規則によって返す値が異なる場合，このように記述する．

次にある

    %token PLUS TIMES LPAR RPAR 
    %token <name> IDENTIFIER
    %token <name> NUMBER
    %type <tree> E T F

では，トークンの種類と型，構文解析の還元時に返す値の型を宣言している．
トークンの IDENTIFIER と NUMBER は，文字へのポインタ型（`char *`）の
値を，非終端記号 `E`, `T`, `F` を左辺とする各生成規則では還元時に
構文木を表す型 `tree_t` へのポインタ型（`tree_t *`）の値をそれぞれ
返すことを記述している．

最後の

    %%
    Expr: E        { print_tree($1); }
    E: E PLUS T    { $$ = make_binary(Add_Expr, $1, $3); }
     | T           { $$ = $1; }
    T: T TIMES F   { $$ = make_binary(Mul_Expr, $1, $3); }
     | F           { $$ = $1; }
    F: LPAR E RPAR { $$ = $2; }
     | IDENTIFIER  { $$ = make_var($1); }
     | NUMBER      { $$ = make_iconst(atoi($1)); }
    %%

の部分では，文法の生成規則と還元時の動作が記述されている．
テキスト p.119 の記述例とほぼ同じ記述であるが，構文木を作成する
関数が `make_tuple` から変更している．
加算および乗算の各算術式では，`make_binary(...)` という関数を用いて
構文木を作成する．
この関数の第一引数では，演算の種類を表す値を与え，第二引数と第三引数では
演算のオペランドに対応する構文木へのポインタを与える．
ここで与える演算の種類は，厳密には構文木のノードの種類でありヘッダファイル
`tree.h` に enum 型で定義している．

識別子に対しては，関数 `make_var` を用いて構文木を作成する．
トークン `IDENTIFIER` は文字へのポインタを返すため，
その値をそのまま関数 `make_var` へ与えて構文木を作成する．

整数値に対しては，関数 `make_iconst` を用いて構文木を作成する．
トークン `NUMBER` も文字へのポインタを返す．
関数 `make_iconst` は，int型 の値を引数としてとるように定義されているため，
文字へのポインタを int 型へ変換する標準ライブラリ関数の `atoi` を用いて
変換している．


lexの記述を下記に示す．

(`scanner2.l`)

    %{
    #include "tree.h"
    #include "y.tab.h"
    char *copy_lexeme();
    %}
    %%
    [\t ]+         {}
    "+"            { return PLUS; }
    "*"            { return TIMES; }
    "("            { return LPAR; }
    ")"            { return RPAR; }
    [a-z][a-z0-9]* { yylval.name = copy_lexeme(); return IDENTIFIER; }
    0|[1-9][0-9]*  { yylval.name = copy_lexeme(); return NUMBER; }
    \n             { return 0; }
    .              { printf("lexical error: '%c'\n", yytext[0]); }
    %%
    char StringTable[1000];
    char *STp = StringTable;
    char *copy_lexeme() {
        char *p = STp;
        strcpy(STp, yytext);
        STp += strlen(yytext) + 1;
        return p;
    }

こちらは，教科書 p.120〜p.121 にある lex コードの記述とほぼ同様であるが，
下記の点が変更されている．

* ヘッダファイル `tree.h` をインクルード
* 関数`copy_lexeme` のプロトタイプ宣言を追加
* 整数値への対応
* 関数`copy_lexeme` の定義の変更

教科書では，関数 `copy_lexeme` は int 型の値を返す関数として定義されているが，
ここでは，char へのポインタ（`char *`）を返す関数に変更している．


構文木を表すデータ型や構文木作成，表示のための関数プロトタイプ宣言を記述しているヘッダファイルを以下に示す．

(`tree.h`)

    #if !defined(_TREE_H)
    #define _TREE_H
      
    /* Tree の種類を表す型 */
    typedef enum tree_type {
        /* 二項演算式 */
        Add_Expr,    /* + */
        Sub_Expr,    /* - */
        Mul_Expr,    /* * */
        Div_Expr,    /* / */
        /* リーフ */
        Var,         /* 識別子 */
        IConst       /* 整数値 */
    } tree_type_t;
        
    /*
     * 木のノード構造体の型
     */
    typedef struct node {
        int n_children;         /* number of children */
        struct tree *child[1];  /* メモリ確保時は，子ノードの数を含めて確保 */
    } node_t;
      
    /*
     * Tree 構造体
     */
    typedef struct tree {
        struct tree *chain;   /* 確保したノードをつなげておく chain */
        int serial;           /* シリアル番号 */
        tree_type_t kind;     /* ノードの種類 */
        union {               /* 共用体 */
            int int_value;      /* 整数値  （ノードがIConst のとき） */
            char *var_name;     /* 名前の綴（ノードが Var のとき） */
            struct node node;   /* ノード構造体（ノードが葉でないとき） */
        } u;
    } tree_t;
        
    /*
     * Prototypes - プロトタイプ宣言
     */
    /* Tree の生成 */
    tree_t *make_var(char *name);  
    tree_t *make_iconst(int n);
    tree_t *make_binary(tree_type_t kind, tree_t *left, tree_t *right);
        
    /* Tree の表示 */
    void dump_tree(void);        /* 生成した木のノードをすべて表示 */
    void print_tree(tree_t *p);
        
    #endif
    /* End of file (tree.h) */


構文木の生成や表示の関数等を定義しているプログラムを以下に示す．

(`tree.c`)

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include "tree.h"
        
    /* Tree構造体ノードのシリアル番号 */
    static int node_serial = 1000;
        
    /* Tree構造体のチェイン */
    static tree_t *tree_chain = NULL;
        
    /* Tree構造体のメモリ確保 */
    static tree_t *
    new_tree_n(int n) {
        tree_t *p = (tree_t *)malloc(sizeof(tree_t) + sizeof(tree_t *) * n);
        if (p == NULL) {
            fprintf(stderr, "cannot allocate memory for tree node\n");
            exit(1);
        }
        p->serial = node_serial++;
        p->chain = tree_chain;
        tree_chain = p;
        return p;
    }
        
    /* 識別子ノードオブジェクトの作成 */
    tree_t *
    make_var(char *name) {
        tree_t *p = new_tree_n(1);
        p->kind = Var;
        p->u.var_name = name;
        return p;
    }
        
    /* 整数値ノードオブジェクトの作成 */
    tree_t *
    make_iconst(int n) {
        tree_t *p = new_tree_n(1);
        p->kind = IConst;
        p->u.int_value = n;
        return p;
    }
        
    /* 二項演算式ノードオブジェクトの作成 */
    tree_t *
    make_binary(tree_type_t kind, tree_t *left, tree_t *right) {
        tree_t *p = new_tree_n(2);
        p->kind = kind;
        p->u.node.child[0] = left;
        p->u.node.child[1] = right;
        return p;
    }
        
        
    /*
     * 木の表示
     */
        
    void
    print_node(tree_t *p) {
        printf("T%d: ", p->serial);
        switch (p->kind) {
        case Var: 
            printf("(Var %s)", p->u.var_name);
            break;
        case IConst:
            printf("(IConst %d)", p->u.int_value);
            break;
        case Add_Expr:
            printf("(Add_Expr T%d T%d)", p->u.node.child[0]->serial, 
                                         p->u.node.child[1]->serial);
            break;
        case Mul_Expr:
            printf("(Mul_Expr T%d T%d)", p->u.node.child[0]->serial, 
                                         p->u.node.child[1]->serial);
            break;
        default:
            printf("(??? ...)");
        }
    }
        
    /* 生成した木ノードを表示 */
    static void 
    dump_tree1(tree_t *p) { 
        /* chainされているノードを逆順に表示するために，chain先のノードを
           表示した後に p のノードを表示 */
        tree_t *p1 = p->chain;
        if (p->chain != NULL) {
            dump_tree1(p->chain);
        } 
        print_node(p); /* 木ノードの表示 */
        printf("\n");
    }
    void
    dump_tree(void) {
        tree_t *p = tree_chain;
        
        printf("--- dump_tree ---\n");
        if (p != NULL) {
            dump_tree1(p);
        }
        printf("-----------------\n");
    }
            
    /* 改行とインデント */
    void
    print_newline(int n) {
        printf("\n");
        while (n-- > 0) printf(" "); /* 行頭に n 個のスペース */
    }
        
    /* 木の表示 */
    void
    print_tree1(int n, tree_t *p) {
        int n0 = n;
        
        switch (p->kind) {
        case Var: 
            printf("(Var %s)", p->u.var_name);
            break;
        case IConst:
            printf("(IConst %d)", p->u.int_value);
            break;
        case Add_Expr:
            printf("(Add_Expr ");
            print_tree1(n + 10, p->u.node.child[0]);
            print_newline(n + 10);
            print_tree1(n + 10, p->u.node.child[1]);
            printf(")");
            break;
        case Mul_Expr:
            printf("(Mul_Expr ");
            print_tree1(n + 10, p->u.node.child[0]);
            print_newline(n + 10);
            print_tree1(n + 10, p->u.node.child[1]);
            printf(")");
            break;
        default:
            printf("(??? ...)");
        }
    }
        
    /* 木の表示 */
    void
    print_tree(tree_t *p) {
        print_tree1(0, p);
        printf("\n");
    }
        
    /* End of file (tree.c) */



#### (コンパイルと実行)

    % yacc -d parser2.y
    % flex scanner2.l
    % cc y.tab.c lex.yy.c tree.c -ly -lfl
    % ./a.out
    aaa * b + 123 * xyz                    <<< 入力
    (Add_Expr (Mul_Expr (Var aaa)
                        (Var b))
              (Mul_Expr (IConst 123)
                        (Var xyz)))
    %

### (演習3)
-----------

減算（`-`）や除算（`/`）に対応するように修正せよ．

---








