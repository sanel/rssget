#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <rd/rd-scheme.h>
#include <rd/rd-utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#if HAVE_MALLOC_USABLE_SIZE
# include <malloc.h>
#endif

#include "ts/scheme.h"
#include "ts/boot_ss.h"

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
	FILE *c = resolve_config_path(conf);

	RD_RETURN_VAL_IF_FAIL(c, NULL);

	s = malloc(sizeof(rd_scm_t));

	s->scm = scheme_init_new();
	if (!s->scm) {
		RD_WARNING("Not enough memory for scheme interpreter\n");
		fclose(c);
		free(s);
		return 0;
	}

#if HAVE_MALLOC_USABLE_SIZE
	RD_DEBUG("scheme init (scm: %ib, rd_scm_t: %ib)\n",
			 malloc_usable_size(s->scm),
			 malloc_usable_size(s));
#else
	RD_DEBUG("scheme init\n");
#endif

	scheme_set_input_port_file(s->scm, stdin);
	scheme_set_output_port_file(s->scm, stdout);

	/* boot stuff */
	scheme_load_string(s->scm, boot_ss_content);

	/* configuration */
	RD_DEBUG("loading configuration '%s'\n", conf);
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

	RD_DEBUG("scheme cleanup\n");
	scheme_deinit(s->scm);
	free(s);
}
