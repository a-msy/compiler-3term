LIB=-lfl

all: rei1.out rei2.out rei3.out

rei1: rei1.out

rei1.out:
	flex scan.l
	cc -o rei1.out lex.yy.c $(LIB)

rei2: rei2.out
rei2.out:
	flex scan1.l
	cc -o rei2.out lex.yy.c $(LIB)

rei3: rei3.out
rei3.out:
	flex scan2.l
	cc -o rei3.out lex.yy.c $(LIB)

clean:
	rm -rf *~ lex.yy.c a.out rei1.out rei2.out rei3.out

