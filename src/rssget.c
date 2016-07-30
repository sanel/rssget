#include <stdio.h>
#include <getopt.h>
#include <rd/rd-tap.h>

static void
help() {
	puts("Usage: rssget [OPTIONS]");
	puts("Fetch news feeds and deliver them.");
	puts("Options:");
	puts("  -h         show this help");
	puts("  -c CONF    use CONF as configuration. Default is ~/.rssgetrc");
}

int main(int argc, char **argv) {
	help();
	return 0;
}
