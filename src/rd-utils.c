#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <rd/rd-utils.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>

static int verbose;

const char *
rd_home_dir(void) {
	const char *ret = getenv("HOME");
	if(!ret)
		ret = getpwuid(getuid())->pw_dir;
	return ret;
}

void
rd_set_verbose(int v) { verbose = v; }

int
rd_is_verbose(void) { return verbose; }

int
rd_verbose_printf(const char *pos, const char *fmt, ...) {
	int ret = 0;
	va_list ap;

	if (!rd_is_verbose()) return ret;
	if (pos) printf("%s", pos);

	va_start(ap, fmt);
	ret = vprintf(fmt, ap);
	va_end(ap);
	return ret;
}

char *
rd_string_printf(const char *fmt, ...) {
	char *p = NULL;
	va_list ap;
	int n = 0;
	size_t size = 30;

	p = malloc(size);
	RD_RETURN_VAL_IF_FAIL(p, NULL);

	while (1) {
		va_start(ap, fmt);
		n = vsnprintf(p, size, fmt, ap);
		va_end(ap);

		if (n > -1 && n < size)
			return p;

		if (n > -1)
			size = n + 1;
		else
			size *= 2;

		p = realloc(p, size);
		RD_RETURN_VAL_IF_FAIL(p, NULL);
	}

	return p;
}
