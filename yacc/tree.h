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
