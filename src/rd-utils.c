#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <rd/rd-utils.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>

const char *
rd_home_dir(void) {
	const char *ret = getenv("HOME");
	if(!ret)
		ret = getpwuid(getuid())->pw_dir;
	return ret;
}
