#ifndef __RD_SCHEME_H__
#define __RD_SCHEME_H__

/* tinyscheme fronted and helpers */

typedef struct _rd_scm_t rd_scm_t;

rd_scm_t *rd_scm_init(const char *conf, int repl);
void      rd_scm_fini(rd_scm_t *scm);


#endif
