/*
*	LinuxList.h:	��ֲLinux4.9��˫��ѭ������/include/linux/list.h������g++/gcc��������
*	
*	�ӿں�����
*			list_head: 						����ڵ㣬ͨ����Ƕ���������ݽṹʹ�á���ͷ�ڵ��������δʹ�ã�
*
*			INIT_LIST_HEAD��					��ʼ������ͷ��������ͷ��next,prevָ�붼ָ���Լ�����״̬��ʾ����Ϊ��
*			list_add��						����ͷ�ڵ�͵ڶ����ڵ��м����
*			list_add_tail:      			����ͷ�ڵ��β�ڵ��м����
*			list_del:						ɾ���ڵ㣬ɾ����ǰ����Ľڵ�
*			list_empty:						�����Ƿ�Ϊ�գ�ͷ�ڵ��next��prevָ��ָ���Լ���Ϊ�ա�
*			list_for_each_entry:			ͷ�ڵ㿪ʼ�������������
*			list_for_each_entry_reverse:	ͷ�ڵ㿪ʼ�������������
*
*			contain_of		ͨ���ṹ���Աָ�룬�ṹ���Ա�����ṹ�����ͻ�ȡ �ṹ���׵�ַ
*			list_entry		ͨ�������ṹ�����Ƕ��Աlist_head�ĳ�Աָ�룬��Ա�����ṹ�����ͻ�ȡ �����ṹ����׵�ַ
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
*			list_head  ͷ�������ݽṹ������ڵ�
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
*			entry  ��Ƕ���������ݽṹ������ڵ�
*			head   ͷ�������ݽṹ�е�����ڵ�
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
*			Ҫɾ���������ݽṹ�е�����ͷ
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

#ifdef __cplusplus  // C����û��bool����
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

#ifdef __cplusplus  // C++���ͼ��ҪǿһЩ
#define __container_of(ptr, sample, member)	 container_of((ptr), typeof(*(sample)), member)
#else
#define __container_of(ptr, sample, member)	 (void *)container_of((ptr), typeof(*(sample)), member)
#endif

/*	params: 
*			pos  	�����α�ĸ������ݽṹ
*			head	ͷ�������ݽṹ������ڵ㣨����ͷ��
*			member	�������ݽṹ�ж����list_head�ı�����
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
	Node *m_slider = NULL;   // �α�
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
