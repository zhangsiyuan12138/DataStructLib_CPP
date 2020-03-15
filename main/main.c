#include<stdio.h>
#include<malloc.h>
#include"LinuxList.h"

int main(void)
{
	typedef struct 
	{
		int value; 
		struct list_head head;
	}Node;

	Node *m_list = (Node *)malloc(sizeof(Node));
	struct list_head *m_head = &m_list->head;
	Node *m_slider = NULL;   // �α�
	INIT_LIST_HEAD(m_head);
	
	((Node *)list_entry(m_head, Node, head))->value = 999;  // ����ͷ�ڵ�������Ϊ 999
	
	for(int i=0; i<10; i++)
	{
		Node *temp_node = (Node *)malloc(sizeof(Node));
		temp_node->value = i;
		list_add_tail(&temp_node->head, m_head);
		printf("%d \n",temp_node->value); 
	}

	list_for_each_entry(m_slider, m_head, head)
	{
		int i = m_slider->value;
		printf("%d \n",i); 
	}

	printf("list_head data = %d",((Node *)list_entry(m_head, Node, head))->value); // print 999 ---> ͷ�ڵ��������δʹ��
	
	return 0;
} 