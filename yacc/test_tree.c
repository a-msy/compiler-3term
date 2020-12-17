#include <stdio.h>
#include "tree.h"

int
main(int argc, char *argv[]) {
    tree_t *p0 = make_var("x");
    tree_t *p1 = make_iconst(1);
    tree_t *p2 = make_binary(Add_Expr, p0, p1);
    tree_t *p3 = make_var("aaa");
    tree_t *p4 = make_binary(Mul_Expr, p2, p3);
    tree_t *p5 = make_var ("bbb");

    dump_tree();

    print_tree(p4);
}
