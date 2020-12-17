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
