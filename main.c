#include<stdio.h>
#include<stdlib.h>

//˫������ڵ�ṹ��
typedef struct Node//��ʾ˫������Ľڵ㣬ÿ���ڵ����������Ա
{
	int data;//�洢�ڵ������
	struct Node* prev;//ָ��ǰһ���ڵ��ָ��
	struct Node* next;//ָ����һ���ڵ��ָ��
}Node;

//˫������ṹ��
typedef struct DoublyLinkedList//��ʾ˫��������������Ա
{
	Node* head;//ָ������ͷ�ڵ��ָ��
	int count;//�洢�����еĽڵ�����
}DoublyLinkedList;   

//��ʼ������
void initList(DoublyLinkedList* list)
{
	list->head = NULL;//�������head��Ա��ʼ��ΪNULL
	list->count = 0;//�������count��Ա��ʼ��Ϊ0
}

//�����½ڵ�
Node* createNode(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));//ʹ��malloc����Ϊ�½ڵ�����ڴ�
	newNode->data = data;//��������ֵ���½ڵ��data��Ա
	newNode->prev = NULL;//��prev��ʼ��ΪNULL
	newNode->next = NULL;//��next��ʼ��ΪNULL
	return newNode;//�����´����Ľڵ�
}

//������ͷ������ڵ�
void insertAtHead(DoublyLinkedList* list, int data)
{
	Node* newNode = createNode(data);//���ú�������һ���½ڵ�
	if (list->head != NULL)//�ж������Ƿ�Ϊ��
	{
		list->head->prev = newNode;//�������Ϊ�գ���ͷ�ڵ��prevָ��ָ���½ڵ�
		newNode->next = list->head;//���������½ڵ��nextָ��ָ��ǰ�ڵ�
	}
	list->head = newNode;//�������headָ��ָ���½ڵ㣬ʹ���Ϊ�µ�ͷ�ڵ�
	list->count++;//����ڵ����count��һ
}

//������β������ڵ�
void insertAtTail(DoublyLinkedList* list, int data)
{
	Node* newNode = createNode(data);//���ú�������һ���½ڵ�
	if (list->head == NULL)//�ж������Ƿ�Ϊ��
	{
		list->head = newNode;//�������Ϊ�գ��������headָ��ָ���½ڵ�
	}
	else//����
	{
		Node* temp = list->head;
		while (temp->next != NULL)//���������ҵ����һ���ڵ�
		{
			temp = temp->next;
		}
		temp->next = newNode;//��nextָ��ָ���½ڵ�
		newNode->prev = temp;//�����½ڵ��prevָ��ָ��ýڵ�
	}
	list->count++;//����ڵ����count��һ
}

//��ָ����λ�ò���ڵ�
void insertAtPosition(DoublyLinkedList* list, int data, int position)
{
	if (position<0 || position>list->count)//�������λ����Ч(С��0�����������)
	{
		printf("����λ����Ч\n");//��ӡ������Ϣ
		return;//����
	}
	if (position == 0)//�������λ��Ϊ0
	{
		insertAtHead(list, data);//���ú�����ͷ�������½ڵ�
		return;//����
	}
	if (position == list->count)//����������λ�õ���������
	{
		insertAtHead(list, data);//���ú����������β�������½ڵ�
		return;//����
	}
	Node* newNode = createNode(data);//������ú���������һ���½ڵ�
	Node* temp = list->head;

	for (int i = 0; i < position - 1; i++)//���������ҵ�����λ�õ�ǰһ���ڵ�
	{
		temp = temp->next;
	}
	newNode->next = temp->next;//���½ڵ���뵽ָ��λ�ã����������ڽڵ��ָ��
	newNode->prev = temp;
	temp->next->prev = newNode;
	temp->next = newNode;
	list->count++;//����ڵ����count��һ
}

//�����������
void printList(DoublyLinkedList* list)
{
	Node* temp = list->head;
	while (temp != NULL)//��������
	{
		printf("%d ", temp->data);//��ӡÿ���ڵ�����ݣ�ֱ���������
		temp = temp->next;
	}
	printf("\n");//��ӡ��Ϻ󣬻���
}

//�����������
void reversePrintList(DoublyLinkedList* list)
{
	Node* temp = list->head;//��ʼ��һ����ʱָ��temp��ָ�������ͷָ��
	if (temp == NULL)//�ж������Ƿ�Ϊ��
	{
		return;//���Ϊ�գ�ֱ�ӷ���
	}
	while (temp->next != NULL)//ͨ��ѭ�����������������β�ڵ�(temp->nextΪNULL�Ľڵ�)
	{
		temp = temp->next;
	}
	while (temp != NULL)//��β�ڵ㿪ʼ�������������ֱ������ͷ�ڵ�(tempΪNULL)
	{
		printf("%d ", temp->data);//����ӡÿ���ڵ������
		temp = temp->prev;
	}
	printf("\n");//������������ӡ���з�
}

//���ҽڵ�
Node* searchNode(DoublyLinkedList* list, int key)
{
	Node* temp = list->head;
	while (temp != NULL)//��������
	{
		if (temp->data == key)//����ҵ�����key���ݵĽڵ�
		{
			return temp;//���ظýڵ�
		}
		temp = temp->next;
	}
	return NULL;//���δ�ҵ�������NULL
}

//ɾ���ڵ�
void deleteNode(DoublyLinkedList* list, Node* delNode)
{
	if (list->head == NULL || delNode == NULL)//�������Ϊ�ջ�Ҫɾ���Ľڵ�Ϊ��
	{
		return;//ֱ�ӷ���
	}
	if (list->head == delNode)//���ɾ���Ľڵ���ͷ�ڵ�
	{
		list->head = delNode->next;//�������headָ��ָ����һ���ڵ�
	}
	if (delNode->next != NULL)//����Ҫɾ���ڵ����һ���ڵ㣬ʹ���ƹ�Ҫɾ���Ľڵ�
	{
		delNode->next->prev = delNode->prev;
	}
	if (delNode->prev != NULL)//����Ҫɾ����ǰһ���ڵ㣬ʹ���ƹ�Ҫɾ���Ľڵ�
	{
		delNode->prev->next = delNode->next;
	}
	free(delNode);//�ͷ�Ҫɾ���ڵ���ڴ�
	list->count--;//����ڵ����count��һ
}

//�ϲ���������
void mergeLists(DoublyLinkedList* list1, DoublyLinkedList* list2)
{
	if (list1->head == NULL)//���list1�Ƿ�Ϊ��
	{
		list1->head = list2->head;//���list1Ϊ�գ���list1��ͷָ��ָ��list2��ͷָ��
		list1->count = list2->count;//������list1�Ľڵ����Ϊlist2�Ľڵ����
		return;//����
	}
	if (list2->head == NULL)//���list2�Ƿ�Ϊ��
	{
		return;//���list2Ϊ�գ�ֱ�ӷ��أ�û�нڵ���Ҫ�ϲ�
	}
	Node* temp = list1->head;
	while (temp->next != NULL)//����list1�ҵ����һ���ڵ�
	{
		temp = temp->next;
	}
	temp->next = list2->head;//��list1�����һ���ڵ��nextָ��ָ��list2��ͷ�ڵ�
	list2->head->prev = temp;//����list2ͷ�ڵ��prevָ��ָ��list1�����һ���ڵ�
	list1->count += list2->count;//����list1�Ľڵ����
}

//��������
void sortList(DoublyLinkedList* list)
{
	if (list->head == NULL || list->head->next == NULL)//��������Ƿ���Ϊ�ջ�ֻ��һ���ڵ�
	{
		return;//ֱ�ӷ��أ���Ϊ�Ѿ��������
	}
	Node* sorted = NULL;//��ʼ��һ��ָ��sortedΪNULL������ָ���Ѿ�����Ĳ���
	Node* current = list->head;//��ʼ��һ��ָ��current��ָ�������ͷ�ڵ�
	while (current != NULL)//����������ÿ���ڵ���뵽�Ѿ����򲿷ֵĺ���λ��
	{
		Node* next = current->next;//���浱ǰ�ڵ����һ���ڵ�ָ��
		current->prev = current->next = NULL;//��յ�ǰ�ڵ��ǰ��ָ�룬׼�����뵽�����򲿷�
		if (sorted == NULL)//��������򲿷�Ϊ��
		{
			sorted = current;//����ǰ�ڵ���Ϊ�����򲿷ֵ�ͷ�ڵ�
		}
		else if (sorted->data >= current->data)//�����ǰ�ڵ������С�ڵ��������򲿷ֵ�ͷ�ڵ�����
		{
			current->next = sorted;//����ǰ�ڵ��nextָ��ָ�������򲿷ֵ�ͷ�ڵ�
			sorted->prev = current;//�������򲿷�ͷ�ڵ��prevָ��ָ��ǰ�ڵ�
			sorted = current;//���������򲿷ֵ�ͷ�ڵ�Ϊ��ǰ�ڵ�
		}
		else
		{
			Node* temp = sorted;//��ʼ��һ��ָ��temp��ָ�������򲿷ֵ�ͷ�ڵ�
			while (temp->next != NULL && temp->next->data < current->data)//ͨ��ѭ�����������򲿷֣��ҵ���һ�����ݴ��ڻ���ڵ�ǰ�ڵ����ݵ�λ��
			{	//ȷ��λ�ò���Խ��			//�����ƶ���ֱ���ҵ����ʵ�λ��
				temp = temp->next;
			}
			current->next = temp->next;//����ǰ�ڵ��nextָ��ָ��temp����һ���ڵ�
			if (temp->next != NULL)//���temp����һ���ڵ㲻Ϊ��
			{
				temp->next->prev = current;//jiangprevָ��ָ��ǰ�ڵ�
			}
			temp->next = current;//��temp��nextָ��ָ��ǰ�ڵ�
			current->prev = temp;//����ǰ�ڵ��prevָ��ָ��temp

		}
		current = next;//�Ƶ���һ���ڵ�
	}
	list->head = sorted;//��list->headָ��ָ�������򲿷ֵ�ͷ�ڵ�
}

void freeList(DoublyLinkedList* list)
{
	Node* temp;
	while (list->head != NULL)//������������ͷ�ÿ���ڵ���ڴ�
	{
		temp = list->head;
		list->head = list->head->next;
		free(temp);
	}
	list->count = 0;//�������ͷָ�룬�����ڵ����count��Ϊ0
}

//������
int main()
{
	DoublyLinkedList list1;
	DoublyLinkedList list2;
	initList(&list1);//��ʼ������list1
	initList(&list2);//��ʼ������list2

	insertAtHead(&list1, 1);//��ͷ������1
	insertAtHead(&list1, 2);//��ͷ������2
	insertAtTail(&list1, 3);//��β������3
	insertAtTail(&list1, 4);//��β������4
	insertAtPosition(&list1, 5, 2);//��λ��2����5

	printf("List 1 ���������");
	printList(&list1);//�����������ӡ

	printf("List 1 ���������");
	reversePrintList(&list1);//�����������ӡ

	Node* node = searchNode(&list1, 3);//��������Ϊ3�Ľڵ㲢��ӡ���
	if (node != NULL)
	{
		printf("�ҵ��ڵ㣺%d\n", node->data);
	}
	else
	{
		printf("�ڵ�δ�ҵ�\n");
	}

	deleteNode(&list1, list1.head->next);//ɾ��list1�ĵڶ����ڵ�
	printf("ɾ���ڶ����ڵ��� List 1��");
	printList(&list1);//��ӡ

	insertAtHead(&list2, 10);//��list2�в���ڵ�ͷ������10
	insertAtTail(&list2, 20);//β������20
	printf("List 2 ���������");
	printList(&list2);//�����������ӡ

	mergeLists(&list1, &list2);//�ϲ�list1��list2
	printf("�ϲ��� List 1:");
	printList(&list1);//��ӡ

	sortList(&list1);//��list1��������
	printf("����� List 1 :");
	printList(&list1);//��ӡ

	freeList(&list1);//�ͷ�list1�����нڵ��ڴ�
	return 0;
}