#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <rd/rd-scheme.h>
#include <rd/rd-utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "ts/scheme.h"

struct _rd_scm_t {
	scheme *scm;
};

static FILE *
resolve_config_path(const char *conf) {
	FILE *fd = 0;

	if (!conf) {
		char path[PATH_MAX];
		const char *home = rd_home_dir();
	    RD_RETURN_VAL_IF_FAIL(home, NULL);

		snprintf(path, sizeof(path), "%s/rssgetrc", home);
		fd = fopen(path, "r");
		if (!fd) {
			RD_WARNING("Failed to open '%s'\n", path);
			return 0;
		}
	} else {
		fd = fopen(conf, "r");

		if (!fd) {
			RD_WARNING("Failed to open '%s'\n", conf);
			return 0;
		}
	}

	return fd;
}

rd_scm_t *
rd_scm_init(const char *conf, int repl) {
	rd_scm_t *s;
	FILE *b, *c = resolve_config_path(conf);

	RD_RETURN_VAL_IF_FAIL(c, NULL);

	s = malloc(sizeof(rd_scm_t));
	s->scm = scheme_init_new();
	if (!s->scm) {
		RD_WARNING("Not enough memory for scheme interpreter\n");
		fclose(c);
		return 0;
	}

	scheme_set_input_port_file(s->scm, stdin);
	scheme_set_output_port_file(s->scm, stdout);

	b = fopen("src/ts/boot.ss", "r");
	scheme_load_file(s->scm, b);
	fclose(b);

	scheme_load_file(s->scm, c);
	fclose(c);
	if (repl) {
		printf("rssget REPL. Type (quit) to exit.");
		scheme_load_file(s->scm, stdin);
	}
	return s;
}

void
rd_scm_fini(rd_scm_t *s) {
	if (!s) return;

	scheme_deinit(s->scm);
	free(s);
}



