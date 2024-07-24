#include<stdio.h>
#include<stdlib.h>

//双向链表节点结构体
typedef struct Node//表示双向链表的节点，每个节点包含三个成员
{
	int data;//存储节点的数据
	struct Node* prev;//指向前一个节点的指针
	struct Node* next;//指向下一个节点的指针
}Node;

//双向链表结构体
typedef struct DoublyLinkedList//表示双链表，包含两个成员
{
	Node* head;//指向链表头节点的指针
	int count;//存储链表中的节点数量
}DoublyLinkedList;   

//初始化链表
void initList(DoublyLinkedList* list)
{
	list->head = NULL;//将链表的head成员初始化为NULL
	list->count = 0;//将链表的count成员初始化为0
}

//创建新节点
Node* createNode(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));//使用malloc函数为新节点分配内存
	newNode->data = data;//将打他赋值给新节点的data成员
	newNode->prev = NULL;//将prev初始化为NULL
	newNode->next = NULL;//将next初始化为NULL
	return newNode;//返回新创建的节点
}

//在链表头部插入节点
void insertAtHead(DoublyLinkedList* list, int data)
{
	Node* newNode = createNode(data);//调用函数创建一个新节点
	if (list->head != NULL)//判断链表是否为空
	{
		list->head->prev = newNode;//如果链表不为空，将头节点的prev指针指向新节点
		newNode->next = list->head;//并将开年新节点的next指针指向当前节点
	}
	list->head = newNode;//将链表的head指针指向新节点，使其成为新的头节点
	list->count++;//链表节点计数count加一
}

//在链表尾部插入节点
void insertAtTail(DoublyLinkedList* list, int data)
{
	Node* newNode = createNode(data);//调用函数创建一个新节点
	if (list->head == NULL)//判断链表是否为空
	{
		list->head = newNode;//如果链表为空，将链表的head指针指向新节点
	}
	else//否则
	{
		Node* temp = list->head;
		while (temp->next != NULL)//遍历链表，找到最后一个节点
		{
			temp = temp->next;
		}
		temp->next = newNode;//将next指针指向新节点
		newNode->prev = temp;//并将新节点的prev指针指向该节点
	}
	list->count++;//链表节点计数count加一
}

//在指定的位置插入节点
void insertAtPosition(DoublyLinkedList* list, int data, int position)
{
	if (position<0 || position>list->count)//如果插入位置无效(小于0或大于链表长度)
	{
		printf("插入位置无效\n");//打印错误信息
		return;//返回
	}
	if (position == 0)//如果插入位置为0
	{
		insertAtHead(list, data);//调用函数在头部插入新节点
		return;//返回
	}
	if (position == list->count)//如果擦汗如的位置等于链表长度
	{
		insertAtHead(list, data);//条用函数在链表的尾部插入新节点
		return;//返回
	}
	Node* newNode = createNode(data);//否则调用函数，创建一个新节点
	Node* temp = list->head;

	for (int i = 0; i < position - 1; i++)//遍历链表，找到插入位置的前一个节点
	{
		temp = temp->next;
	}
	newNode->next = temp->next;//将新节点插入到指定位置，并调整相邻节点的指针
	newNode->prev = temp;
	temp->next->prev = newNode;
	temp->next = newNode;
	list->count++;//链表节点计数count加一
}

//正向遍历链表
void printList(DoublyLinkedList* list)
{
	Node* temp = list->head;
	while (temp != NULL)//遍历链表
	{
		printf("%d ", temp->data);//打印每个节点的数据，直到链表结束
		temp = temp->next;
	}
	printf("\n");//打印完毕后，换行
}

//反向遍历链表
void reversePrintList(DoublyLinkedList* list)
{
	Node* temp = list->head;//初始化一个临时指针temp，指向链表的头指针
	if (temp == NULL)//判断链表是否为空
	{
		return;//如果为空，直接返回
	}
	while (temp->next != NULL)//通过循环遍历，扎到链表的尾节点(temp->next为NULL的节点)
	{
		temp = temp->next;
	}
	while (temp != NULL)//从尾节点开始，反向遍历链表，直到到达头节点(temp为NULL)
	{
		printf("%d ", temp->data);//并打印每个节点的数据
		temp = temp->prev;
	}
	printf("\n");//遍历结束，打印换行符
}

//查找节点
Node* searchNode(DoublyLinkedList* list, int key)
{
	Node* temp = list->head;
	while (temp != NULL)//遍历链表
	{
		if (temp->data == key)//如果找到包含key数据的节点
		{
			return temp;//返回该节点
		}
		temp = temp->next;
	}
	return NULL;//如果未找到，返回NULL
}

//删除节点
void deleteNode(DoublyLinkedList* list, Node* delNode)
{
	if (list->head == NULL || delNode == NULL)//如果链表为空或要删除的节点为空
	{
		return;//直接返回
	}
	if (list->head == delNode)//如果删除的节点是头节点
	{
		list->head = delNode->next;//将链表的head指针指向下一个节点
	}
	if (delNode->next != NULL)//调整要删除节点的下一个节点，使其绕过要删除的节点
	{
		delNode->next->prev = delNode->prev;
	}
	if (delNode->prev != NULL)//调整要删除的前一个节点，使其绕过要删除的节点
	{
		delNode->prev->next = delNode->next;
	}
	free(delNode);//释放要删除节点的内存
	list->count--;//链表节点计数count减一
}

//合并两个链表
void mergeLists(DoublyLinkedList* list1, DoublyLinkedList* list2)
{
	if (list1->head == NULL)//检查list1是否为空
	{
		list1->head = list2->head;//如果list1为空，将list1的头指针指向list2的头指针
		list1->count = list2->count;//并更新list1的节点计数为list2的节点计数
		return;//返回
	}
	if (list2->head == NULL)//检查list2是否为空
	{
		return;//如果list2为空，直接返回，没有节点需要合并
	}
	Node* temp = list1->head;
	while (temp->next != NULL)//遍历list1找到最后一个节点
	{
		temp = temp->next;
	}
	temp->next = list2->head;//将list1的最后一个节点的next指针指向list2的头节点
	list2->head->prev = temp;//并将list2头节点的prev指针指向list1的最后一个节点
	list1->count += list2->count;//更新list1的节点计数
}

//链表排序
void sortList(DoublyLinkedList* list)
{
	if (list->head == NULL || list->head->next == NULL)//检查链表是否能为空或只有一个节点
	{
		return;//直接返回，因为已经是有序的
	}
	Node* sorted = NULL;//初始化一个指针sorted为NULL，用于指向已经排序的部分
	Node* current = list->head;//初始化一个指针current，指向链表的头节点
	while (current != NULL)//遍历链表，将每个节点插入到已经排序部分的合适位置
	{
		Node* next = current->next;//保存当前节点的下一个节点指针
		current->prev = current->next = NULL;//清空当前节点的前后指针，准备插入到已排序部分
		if (sorted == NULL)//如果已排序部分为空
		{
			sorted = current;//将当前节点设为已排序部分的头节点
		}
		else if (sorted->data >= current->data)//如果当前节点的数据小于等于已排序部分的头节点数据
		{
			current->next = sorted;//将当前节点的next指针指向已排序部分的头节点
			sorted->prev = current;//将已排序部分头节点的prev指针指向当前节点
			sorted = current;//更新已排序部分的头节点为当前节点
		}
		else
		{
			Node* temp = sorted;//初始化一个指针temp，指向已排序部分的头节点
			while (temp->next != NULL && temp->next->data < current->data)//通过循环遍历已排序部分，找到第一个数据大于或等于当前节点数据的位置
			{	//确保位置不会越界			//继续移动，直到找到合适的位置
				temp = temp->next;
			}
			current->next = temp->next;//将当前节点的next指针指向temp的下一个节点
			if (temp->next != NULL)//如果temp的下一个节点不为空
			{
				temp->next->prev = current;//jiangprev指针指向当前节点
			}
			temp->next = current;//将temp的next指针指向当前节点
			current->prev = temp;//将当前节点的prev指针指向temp

		}
		current = next;//移到下一个节点
	}
	list->head = sorted;//将list->head指针指向已排序部分的头节点
}

void freeList(DoublyLinkedList* list)
{
	Node* temp;
	while (list->head != NULL)//遍历链表，逐个释放每个节点的内存
	{
		temp = list->head;
		list->head = list->head->next;
		free(temp);
	}
	list->count = 0;//清空链表头指针，并将节点计数count设为0
}

//主函数
int main()
{
	DoublyLinkedList list1;
	DoublyLinkedList list2;
	initList(&list1);//初始化链表list1
	initList(&list2);//初始化链表list2

	insertAtHead(&list1, 1);//在头部插入1
	insertAtHead(&list1, 2);//在头部插入2
	insertAtTail(&list1, 3);//在尾部插入3
	insertAtTail(&list1, 4);//在尾部插入4
	insertAtPosition(&list1, 5, 2);//在位置2插入5

	printf("List 1 正向遍历：");
	printList(&list1);//正向遍历并打印

	printf("List 1 反向遍历：");
	reversePrintList(&list1);//反向遍历并打印

	Node* node = searchNode(&list1, 3);//查找数据为3的节点并打印结果
	if (node != NULL)
	{
		printf("找到节点：%d\n", node->data);
	}
	else
	{
		printf("节点未找到\n");
	}

	deleteNode(&list1, list1.head->next);//删除list1的第二个节点
	printf("删除第二个节点后的 List 1：");
	printList(&list1);//打印

	insertAtHead(&list2, 10);//在list2中插入节点头部插入10
	insertAtTail(&list2, 20);//尾部插入20
	printf("List 2 正向遍历：");
	printList(&list2);//正向遍历并打印

	mergeLists(&list1, &list2);//合并list1和list2
	printf("合并后 List 1:");
	printList(&list1);//打印

	sortList(&list1);//对list1进行排序
	printf("排序后 List 1 :");
	printList(&list1);//打印

	freeList(&list1);//释放list1的所有节点内存
	return 0;
}