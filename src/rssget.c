#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <rd/rd-scheme.h>
#include <rd/rd-utils.h>
#include <rd/rd-list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void
help() {
	puts("Usage: rssget [OPTIONS]");
	puts("Fetch news feeds and deliver them.");
	puts("Options:");
	puts("   -h         show this help");
	puts("   -c CONF    use CONF as configuration. Default is ~/.rssgetrc");
	puts("   -r         run REPL. Useful for testing scheme code");
	puts("   -v         be verbose");
}

int
main(int argc, char **argv) {
	int c, repl = 0;
	char *config = 0;
	rd_scm_t *interp;

	opterr = 0;

	while ((c = getopt(argc, argv, "hrvc:")) != -1) {
		switch (c) {
			case 'h':
				help();
				return 0;
			case 'c':
				config = optarg;
				break;
			case 'r':
				repl = 1;
				break;
			case 'v':
				rd_set_verbose(1);
				break;
			default:
				printf("Unknown option '-%c'\n", optopt);
				return 1;
		}
	}

	rd_list_t *o = rd_list_init();
	rd_list_push_front(o, strdup("1"));
	rd_list_push_front(o, strdup("2"));
	rd_list_push_front(o, strdup("3"));
	rd_list_push_front(o, strdup("4"));

	puts(" === printing ===");
	for(rd_list_node_t *it = rd_list_first(o); it != rd_list_last(o); it = it->next)
		printf( "%s\n", (char *)it->value);

	//printf(" %i\n", rd_list_count(o));
	rd_list_fini(o);

	// interp = rd_scm_init(config, repl);
	// rd_scm_fini(interp);
	return 0;
}
