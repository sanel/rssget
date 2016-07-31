#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <rd/rd-scheme.h>
#include <rd/rd-utils.h>
#include <stdio.h>
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

	interp = rd_scm_init(config, repl);
	rd_scm_fini(interp);
	return 0;
}
