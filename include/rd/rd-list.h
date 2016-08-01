#ifndef __RD_LIST_H__
#define __RD_LIST_H__

#include <stdlib.h>
#include <rd/rd-utils.h>

typedef struct _rd_list_node_t {
	void *value;
	struct _rd_list_node_t *next;
	struct _rd_list_node_t *prev;
} rd_list_node_t;

typedef struct _rd_list_t {
	unsigned int count;
	rd_list_node_t *tail;
} rd_list_t;

rd_list_t *
rd_list_init(void);

void
rd_list_fini(rd_list_t *o);

void
rd_list_clear(rd_list_t *o);

rd_list_node_t *
rd_list_insert(rd_list_t *lst, rd_list_node_t *it, void *value);

rd_list_node_t *
rd_list_erase(rd_list_t *lst, rd_list_node_t *it);

static inline rd_list_node_t *
rd_list_first(rd_list_t *o) { return o->tail ? o->tail->next : NULL; }

/*
 * NOTE: it will return last element in list, which is tail. It is not last
 * actual element - you should obtain it with rd_list_last(o)->prev;
 */
static inline rd_list_node_t *
rd_list_last(rd_list_t *o) { return o->tail ? o->tail : NULL; }

static inline rd_list_node_t *
rd_list_rfirst(rd_list_t *o) { return o->tail ? o->tail->prev: NULL; }

static inline rd_list_node_t *
rd_list_push_back(rd_list_t *o, void *value) {
	return rd_list_insert(o, rd_list_last(o), value);
}

static inline rd_list_node_t *
rd_list_push_front(rd_list_t *o, void *value) {
	return rd_list_insert(o, rd_list_first(o), value);
}

static inline unsigned int
rd_list_count(rd_list_t *o) { return o->count; }

/* forward/backward iterator emulation */
#define rd_list_next(it) (it)->next
#define rd_list_prev(it) (it)->prev
#define rd_list_rnext(it) (it)->prev
#define rd_list_rprev(it) (it)->next

#endif
