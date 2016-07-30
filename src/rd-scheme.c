#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <rd/rd-scheme.h>
#include "ts/scheme.h"

struct _rd_scm_t {
	int a;
};

rd_scm_t *
rd_scm_init(const char *conf, int repl) {
	return 0;
}

void
rd_scm_fini(rd_scm_t *scm) {
	if (!scm) return;
}



