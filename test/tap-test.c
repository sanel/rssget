#include <rd/rd-tap.h>

int main() {
	rd_plan(3);

	rd_ok(1, "Sample 1");
	rd_ok(1, "Sample 2");
	rd_not_ok(2 == 3, "should 2 != 3");

	rd_todo("Should be skipped");
	rd_ok(0, "Failed TODO");
	rd_ok(1, "Sample 3");
	rd_is_str("foo", "foo", "foo == foo");
	rd_todo_end();

	return rd_done();
}
