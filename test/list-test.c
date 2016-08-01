#include <rd/rd-list.h>
#include <rd/rd-tap.h>
#include <string.h>

static int* alloc_num(int n) {
	int *r = malloc(sizeof(int));
	*r = n;
	return r;
}

static int as_num(void *n) {
	return *(int*)n;
}

int main() {
	rd_list_t *lst;
	rd_list_node_t *it;
	int i;

	rd_plan(14);

	lst = rd_list_init();
	rd_ok(rd_list_count(lst) == 0, "empty list");
	rd_ok(rd_list_first(lst) == NULL, "no first element");
	rd_ok(rd_list_last(lst) == NULL, "no last element");

	for(i = 0; i < 10; i++)
		rd_list_push_back(lst, alloc_num(i));

	rd_ok(rd_list_count(lst) == 10, "filled list");

	for(it = rd_list_first(lst), i = 0; it != rd_list_last(lst); it = it->next, i++)
		rd_ok(i == as_num(it->value), "compare elements in list");

	rd_list_clear(lst);

	rd_ok(rd_list_count(lst) == 0, "empty list");
	rd_ok(rd_list_first(lst) == NULL, "no first element");
	rd_ok(rd_list_last(lst) == NULL, "no last element");

	/* clear it multiple times */
	rd_list_clear(lst);
	rd_list_clear(lst);

	rd_ok(rd_list_count(lst) == 0, "empty list");
	rd_ok(rd_list_first(lst) == NULL, "no first element");
	rd_ok(rd_list_last(lst) == NULL, "no last element");

	/* manual insert; things are inserted in reverse order */
	it = rd_list_insert(lst, 0, alloc_num(10));
	it = rd_list_insert(lst, it, alloc_num(20));
	it = rd_list_insert(lst, it, alloc_num(30));

	it = rd_list_first(lst);
	rd_ok(30 == as_num(it->value), "first element in manual insert");

	it = it->next;
	rd_ok(20 == as_num(it->value), "second element in manual insert");

	it = it->next;
	rd_ok(10 == as_num(it->value), "third element in manual insert");
	rd_ok(rd_list_count(lst) == 3, "number of elements after manual insert");

	/* erase middle element */
	it = it->prev;
	it = rd_list_erase(lst, it);
	rd_ok(10 == as_num(it->value), "erasing returns iterator to next element");
	rd_ok(rd_list_count(lst) == 2, "number of elements after erasing middle element");

	rd_list_clear(lst);

	/* reverse iterating */
	rd_list_push_back(lst, alloc_num(10));
	rd_list_push_back(lst, alloc_num(20));
	rd_list_push_back(lst, alloc_num(30));

	it = rd_list_rfirst(lst);
	rd_ok(30 == as_num(it->value), "first element in reverse order");
	it = rd_list_rnext(it);
	rd_ok(20 == as_num(it->value), "second element in reverse order");
	it = rd_list_rnext(it);
	rd_ok(10 == as_num(it->value), "third element in reverse order");

	rd_list_fini(lst);
}
