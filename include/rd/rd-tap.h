#ifndef __RD_TAP_H__
#define __RD_TAP_H__

/* TAP - test anything protocol */

void rd_plan(int n);
int  rd_done(void);

void rd_todo(const char *msg);
void rd_todo_end();

void rd_skip(int n, const char *msg);
void rd_skip_end();

int _rd_ok(int expr, const char *msg, const char *path, unsigned int line);
int _rd_is_str(const char *s1, const char *s2, const char *msg, const char *path, unsigned int line);

#define rd_ok(expr, str)        _rd_ok(expr, str, __FILE__, __LINE__)
#define rd_not_ok(expr, str)    _rd_ok(!(expr), str, __FILE__, __LINE__)
#define rd_is_str(s1, s2, str)  _rd_is_str(s1, s2, str, __FILE__, __LINE__)

#endif

#if 0
rd_plan(5);

rd_ok(1 == 1, "check if 1 eq 1");
rd_not_ok(1 == 2, "check 1 not 2");

rd_skip(rd_ok(1 == 1, 0), 2);
rd_ok(1 + 2, 0);
rd_ok(1 + 2, 0);
rd_ok(1 + 2, 0);
rd_ok(1 + 2, 0);
rd_skip_end();

rd_done();
#endif
