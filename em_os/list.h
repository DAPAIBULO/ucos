#ifndef		_LIST_H
#define		_LIST_H


struct list_head
{
	struct list_head *prev;
	struct list_head *next;
};

#define offset(type, member)	((size_t)&(((type *)0)->member))


#define container_of(ptr, type, member)	({	\
		const typeof(((type *)0)->member) *__mptr = ptr;	\
		(type *)((char *)__mptr - offset(type, member)); })


#define list_entry(ptr, type, member)	\
	container_of(ptr, type, member)

#define list_for_each(pos, head)		\
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_entry(pos, head, member)	\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
			&pos->member != (head);	\
			pos = list_entry(pos->member.next, typeof(*pos), member))



#define LIST_HEAD_INIT(name)	{&(name), &(name)}
#define LIST_HEAD(name)	\
	struct list_head name = LIST_HEAD_INIT(name)


static inline void list_init(struct list_head *list)
{
	list->prev = list;
	list->next = list;
}


static inline void list_add(struct list_head *list, struct list_head *head)
{
	struct list_head *prev;
	struct list_head *next;

	prev = head;
	next = head->next;

	prev->next = list;
	list->prev = prev;

	list->next = next;
	next->prev = list;
}


static inline void list_del(struct list_head *entry)
{
	struct list_head *prev;
	struct list_head *next;

	prev = entry->prev;
	next = entry->next;

	prev->next = next;
	next->prev = prev;
}


static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->prev = list;
	list->next = list;
}


static inline void list_del_init(struct list_head *entry)
{
	list_del(entry);
	INIT_LIST_HEAD(entry);
}


static inline void list_move(struct list_head *entry, struct list_head *head)
{
	list_del_init(entry);
	list_add(entry, head);
}


static inline int list_empty(struct list_head *head)
{
	return (head->next == head);
}


#endif
