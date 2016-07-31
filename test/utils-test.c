#include <rd/rd-tap.h>
#include <rd/rd-utils.h>

int main() {
	rd_plan(2);

	rd_ok(rd_is_verbose() == 0, "default verbosity is 0");
	rd_set_verbose(1);
	rd_ok(rd_is_verbose() == 1, "verbosity is 1 now");
	rd_set_verbose(0);

	return rd_done();
}
