all: a.out

a.out: y.tab.c lex.yy.c
	cc y.tab.c lex.yy.c -ly -lfl

y.tab.c: parser.y
	yacc -d $<

lex.yy.c: scanner.l
	lex $<

clean:
	rm -rf y.tab.h y.tab.c lex.yy.c *~

distclean:
	rm -rf y.tab.h a.out y.tab.c lex.yy.c *~

run1:
	echo "x*y+z*w" | ./a.out

run2:
	echo "x+y+" | ./a.out

kadai2:
	yacc -d kadai2.y
	flex kadai2.l
	cc y.tab.c lex.yy.c -ly -lfl
	./a.out





