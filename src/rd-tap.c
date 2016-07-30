#include <rd/rd-tap.h>
#include <stdio.h>
#include <string.h>

static int texpected;
static int tfailed;
static int tcurr;
static const char *todo_msg;

void rd_plan(int n) {
	texpected = n;
	printf("1..%i\n", n);
}

int rd_done(void) {
	int ret = 0;

	if (texpected > tcurr)  {
		printf("# Looks like you have planned %i but executed %i tests\n", texpected, tcurr);
		ret = 1;
	}

	if (tfailed) {
		printf("# Looks like you have failed %i tests out of %i run and %i planned\n",
			   tfailed, tcurr, texpected);
		ret = 1;
	}

	return ret;
}

int _rd_ok(int expr, const char *name, const char *path, unsigned int line) {
	if (!expr) printf("not ");
	printf("ok %i", ++tcurr);
	if (name) printf(" - %s", name);
	if (todo_msg) printf(" # TODO %s", todo_msg);

	printf("\n");

	if (!expr) {
		printf("#   Failed");
		if (todo_msg) printf("(TODO) ");
		printf("test ");
		if (name) printf("'%s'\n#   ", name);
		printf("at %s line %i.\n", path, line);
		if(!todo_msg)
			tfailed++;
	}

	return expr;
}

int _rd_is_str(const char *s1, const char *s2, const char *msg, const char *path, unsigned int line) {
	return _rd_ok(strcmp(s1, s2) == 0, msg, path, line);
}

void rd_todo(const char *msg) {
	todo_msg = msg;
}

void rd_todo_end(void) {
	todo_msg = 0;
}
