/*
*	LinuxList.h:	移植Linux4.9的双向循环链表/include/linux/list.h，兼容g++/gcc编译器。
*	
*	接口函数：
*			list_head: 						链表节点，通过内嵌到其他数据结构使用。（头节点的数据域并未使用）
*
*			INIT_LIST_HEAD：					初始化链表头，将链表头的next,prev指针都指向自己，此状态表示链表为空
*			list_add：						链表头节点和第二个节点中间插入
*			list_add_tail:      			链表头节点和尾节点中间插入
*			list_del:						删除节点，删除当前传入的节点
*			list_empty:						链表是否为空，头节点的next和prev指针指向自己则为空。
*			list_for_each_entry:			头节点开始，正向遍历链表
*			list_for_each_entry_reverse:	头节点开始，逆向遍历链表
*
*			contain_of		通过结构体成员指针，结构体成员名，结构体类型获取 结构体首地址
*			list_entry		通过父级结构体的内嵌成员list_head的成员指针，成员名，结构体类型获取 父级结构体的首地址
*/

#ifndef LINUXLIST_H
#define LINUXLIST_H

struct list_head 
{
    struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) (struct list_head name = LIST_HEAD_INIT(name))

/*	params: 
*			list_head  头父级数据结构的链表节点
*/
static  void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list->prev = list;
}

static  void __list_add(struct list_head *entry, struct list_head *prev, struct list_head *next)
{
    next->prev = entry;
    entry->next = next;
    entry->prev = prev;
    prev->next = entry;
}

/*	params: 
*			entry  内嵌到父级数据结构的链表节点
*			head   头父级数据结构中的链表节点
*/
static void list_add(struct list_head *entry, struct list_head *head)
{
    __list_add(entry, head, head->next);
}

static void list_add_tail(struct list_head *entry, struct list_head *head)
{
    __list_add(entry, head->prev, head);
}

static void __list_del(struct list_head *prev, struct list_head *next)
{
    next->prev = prev;
    prev->next = next;
}

/*	params: 
*			要删除父级数据结构中的链表头
*/
static void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
}

static void list_del_init(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    INIT_LIST_HEAD(entry);
}

static void list_move_tail(struct list_head *list,
				  struct list_head *head)
{
	__list_del(list->prev, list->next);
	list_add_tail(list, head);
}

#ifdef __cplusplus  // C语言没有bool类型
static bool list_empty(struct list_head *head)
{
    return head->next == head;
}
#else
static int list_empty(struct list_head *head)
{
    return head->next == head;
}
#endif

#ifndef container_of
#define container_of(ptr, type, member) (type *)((char *)(ptr) - (char *)&((type *)0)->member)
#endif

#define list_entry(ptr, type, member)  container_of(ptr, type, member)

#define list_first_entry(ptr, type, member)  list_entry((ptr)->next, type, member)

#define list_last_entry(ptr, type, member)  list_entry((ptr)->prev, type, member)

#ifdef __cplusplus  // C++类型检查要强一些
#define __container_of(ptr, sample, member)	 container_of((ptr), typeof(*(sample)), member)
#else
#define __container_of(ptr, sample, member)	 (void *)container_of((ptr), typeof(*(sample)), member)
#endif

/*	params: 
*			pos  	用作游标的父级数据结构
*			head	头父级数据结构的链表节点（链表头）
*			member	父级数据结构中定义的list_head的变量名
*/
#define list_for_each_entry(pos, head, member)				\
    for (pos = __container_of((head)->next, pos, member);		\
	 &pos->member != (head);					\
	 pos = __container_of(pos->member.next, pos, member))

#define list_for_each_entry_safe(pos, tmp, head, member)		\
    for (pos = __container_of((head)->next, pos, member),		\
	 tmp = __container_of(pos->member.next, pos, member);		\
	 &pos->member != (head);					\
	 pos = tmp, tmp = __container_of(pos->member.next, tmp, member))

#define list_for_each_entry_reverse(pos, head, member)			\
	for (pos = __container_of((head)->prev, pos, member);		\
	     &pos->member != (head);					\
	     pos = __container_of(pos->member.prev, pos, member))

#define list_for_each_entry_continue(pos, head, member)			\
	for (pos = __container_of(pos->member.next, pos, member);	\
	     &pos->member != (head);					\
	     pos = __container_of(pos->member.next, pos, member))

#define list_for_each_entry_continue_reverse(pos, head, member)		\
	for (pos = __container_of(pos->member.prev, pos, member);	\
	     &pos->member != (head);					\
	     pos = __container_of(pos->member.prev, pos, member))

#define list_for_each_entry_from(pos, head, member)			\
	for (;								\
	     &pos->member != (head);					\
	     pos = __container_of(pos->member.next, pos, member))

#endif

/* TEST

main.cpp:
#include<iostream>
#include"LinuxList.h"
#include<cstdio>

using namespace std;  

int main(void)
{
	struct Node
	{
		int value; 
		struct list_head head;
	};

	Node *m_list = (Node *)malloc(sizeof(Node));
	struct list_head *m_head = &m_list->head;
	Node *m_slider = NULL;   // 游标
	INIT_LIST_HEAD(m_head);

	for(int i=0; i<10; i++)
	{
		Node *temp_node = (Node *)malloc(sizeof(Node));
		temp_node->value = i;
		list_add_tail(&temp_node->head, m_head);
		cout << temp_node->value << endl;
	} 

	list_for_each_entry(m_slider, m_head, head)
	{
		int i = m_slider->value;
		cout << i << endl;
	}
	return 0;
} 

*/
