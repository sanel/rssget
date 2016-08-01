#include <rd/rd-utils.h>
#include <rd/rd-list.h>
#include <stdio.h>

rd_list_t *
rd_list_init(void) {
	rd_list_t *ret = malloc(sizeof(rd_list_t));
	RD_RETURN_VAL_IF_FAIL(ret != NULL, NULL);

	ret->count = 0;
	ret->tail  = NULL;
	return ret;
}

void
rd_list_fini(rd_list_t *o) {
	RD_RETURN_IF_FAIL(o != NULL);
	rd_list_clear(o);
	free(o);
}

void
rd_list_clear(rd_list_t *o) {
	RD_RETURN_IF_FAIL(o != NULL);
	rd_list_node_t *tail, *p, *t;

	if (RD_UNLIKELY(rd_list_count(o) == 0))
		return;

	tail = o->tail;
	p = tail->next;
	while (p != tail) {
		t = p->next;
		if (p->value) free(p->value);
		free(p);
		p = t;
	}

	free(o->tail);
	o->tail = NULL;
	o->count = 0;
}

rd_list_node_t *
rd_list_insert(rd_list_t *lst, rd_list_node_t *it, void *value) {
	rd_list_node_t *tmp = malloc(sizeof(rd_list_node_t));
	tmp->value = value;
	tmp->next = tmp->prev = 0;

	if (!lst->tail) {
		/* dummy node if not present */
		rd_list_node_t *t = malloc(sizeof(rd_list_node_t));
		RD_ASSERT(it == NULL);

		t->value = NULL;
		t->next = t->prev = tmp;
		tmp->next = tmp->prev = t;
		lst->tail = t;
	} else {
		tmp->next = it;
		tmp->prev = it->prev;
		if (it->prev) it->prev->next = tmp;
		it->prev = tmp;
	}

	lst->count++;
	return tmp;
}

rd_list_node_t *
rd_list_erase(rd_list_t *lst, rd_list_node_t *it) {
	RD_ASSERT(it != lst->tail && "Bad code! You are erasing tail");
	rd_list_node_t *ret;

	it->prev->next = it->next;
	it->next->prev = it->prev;
	ret = it->next;

	free(it->value);
	free(it);
	lst->count--;

	/* returns next element */
	return ret;
}

