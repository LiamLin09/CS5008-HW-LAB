// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
//
//
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
// - You should not have any 'printf' statements in your DLL functions.
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
//   - (You may write helper functions to help you debug your code such as print_list etc)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H

#include <stdlib.h>
// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node{
    void* data;
    struct node* next;
    struct node* previous;
}node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL{
    int count;        // count keeps track of how many items are in the DLL.
    node_t* head;        // head points to the first node in our DLL.
    node_t * tail;          //tail points to the last node in our DLL.
}dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){
    // Modify the body of this function as needed.
    dll_t* myDLL= malloc(sizeof(dll_t));
    myDLL->count =0;
    myDLL->head = NULL;
    myDLL->tail = NULL;
    return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
// Returns -1 if the dll is NULL.
int dll_empty(dll_t* l){
	if (l == NULL) {  // 链表为空
		exit(0);
	}
	return l->count == 0;  // 返回链表节点数量是否为0
}

// push a new item to the front of the DLL ( before the first node in the list).
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// Returns -1 if DLL is NULL.
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, void* item){
	if (l == NULL) {  // 链表为空
		exit(0);
	}
	node_t* new_node = (node_t*)malloc(sizeof(node_t));  // 为新节点分配内存
	if (new_node == NULL) {  // 内存分配失败
		return 0;
	}
	new_node->data = item;  // 将数据存储到新节点中
	new_node->next = l->head;  // 将新节点的next指针指向链表头部
	new_node->previous = NULL;  // 将新节点的previous指针指向NULL
	if (l->head != NULL) {  // 如果链表不为空
		l->head->previous = new_node;  // 将链表头部节点的previous指针指向新节点
	} else {  // 如果链表为空
		l->tail = new_node;  // 将链表尾部指针指向新节点
	}
	l->head = new_node;  // 将链表头部指针指向新节点
	l->count++;  // 链表节点数量加1
	return 1;
}
// push a new item to the end of the DLL (after the last node in the list).
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// Returns -1 if DLL is NULL.
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, void* item){
	if (l == NULL) {  // 链表为空
		exit(0);
	}
	node_t* new_node = (node_t*)malloc(sizeof(node_t));  // 为新节点分配内存
	if (new_node == NULL) {  // 内存分配失败
		return 0;
	}
	new_node->data = item;  // 将数据存储到新节点中
	new_node->next = NULL;  // 将新节点的next指针指向NULL
	new_node->previous = l->tail;  // 将新节点的previous指针指向链表尾部
	if (l->tail != NULL) {  // 如果链表不为空
		l->tail->next = new_node;  // 将链表尾部节点的next指针指向新节点
	} else {  // 如果链表为空
		l->head = new_node;  // 将链表头部指针指向新节点
	}
	l->tail = new_node;  // 将链表尾部指针指向新节点
	l->count++;  // 链表节点数量加1
	return 1;
}

// Returns the first item in the DLL and also removes it from the list.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Returns a -1 if the DLL is NULL.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_front(dll_t* l){
	if (l == NULL || l->head == NULL) {  // 链表为空
		exit(0);
	}
	node_t* temp = l->head;  // 保存链表头部节点的指针
	void* data = temp->data;  // 保存链表头部节点的数据
	l->head = temp->next;  // 将链表头部指针指向下一个节点
	if (l->head != NULL) {  // 如果链表不为空
		l->head->previous = NULL;  // 将链表头部节点的previous指针指向NULL
	} else {  // 如果链表为空
		l->tail = NULL;  // 将链表尾部指针指向NULL
	}
	free(temp);  // 释放链表头部节点的内存
	l->count--;  // 链表节点数量减1
	return data;  // 返回链表头部节点的数据
}


// Returns the last item in the DLL, and also removes it from the list.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Returns a -1 if the DLL is NULL.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_back(dll_t* l){
	if (l == NULL || l->tail == NULL) {  // 链表为空
		exit(0);
	}
	node_t* temp = l->tail;  // 保存链表尾部节点的指针
	void* data = temp->data;  // 保存链表尾部节点的数据
	l->tail = temp->previous;  // 将链表尾部指针指向上一个节点
	if (l->tail != NULL) {  // 如果链表不为空
		l->tail->next = NULL;  // 将链表尾部节点的next指针指向NULL
	} else {  // 如果链表为空
		l->head = NULL;  // 将链表头部指针指向NULL
	}
	free(temp);  // 释放链表尾部节点的内存
	l->count--;  // 链表节点数量减1
	return data;  // 返回链表尾部节点的数据
}
// Inserts a new node before the node at the specified position.
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
// Returns -1 if the list is NULL
int dll_insert(dll_t* l, int pos, void* item){
	if (l == NULL) {  // 链表为空
		exit(0);
	}
	if (pos < 0 || pos > l->count) {  // 插入位置不合法
		return 0;
	}
	if (pos == 0) {  // 在链表头部插入新节点
		return dll_push_front(l, item);
	}
	if (pos == l->count) {  // 在链表尾部插入新节点
		return dll_push_back(l, item);
	}
	node_t* current = l->head;  // 从链表头部开始遍历
	for (int i = 0; i < pos; i++) {  // 遍历到指定位置
		current = current->next;
	}
	node_t* new_node = (node_t*)malloc(sizeof(node_t));  // 为新节点分配内存
	if (new_node == NULL) {  // 内存分配失败
		return 0;
	}
	new_node->data = item;  // 将数据存储到新节点中
	new_node->next = current;  // 将新节点的next指针指向当前节点
	new_node->previous = current->previous;  // 将新节点的previous指针指向当前节点的上一个节点
	current->previous->next = new_node;  // 将当前节点的上一个节点的next指针指向新节点
	current->previous = new_node;  // 将当前节点的previous指针指向新节点
	l->count++;  // 链表节点数量加1
	return 1;
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
//  (does not remove the item)
// Retruns 0 on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Returns -1 if the list is NULL
// Assume no negative numbers in the list or the number zero.
void* dll_get(dll_t* l, int pos){
	if (l == NULL) {  // 链表为空
		exit(0);
	}
	if (pos < 0 || pos >= l->count) {  // 获取位置不合法
		return 0;
	}
	node_t* current = l->head;  // 从链表头部开始遍历
	for (int i = 0; i < pos; i++) {  // 遍历到指定位置
		current = current->next;
	}
	return current->data;  // 返回当前节点的数据
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Retruns NULL on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Returns NULL if the list is NULL
// Assume no negative numbers in the list or the number zero.
void* dll_remove(dll_t* l, int pos){
	if (l == NULL) {  // 链表为空
		exit(0);
	}
	if (pos < 0 || pos >= l->count) {  // 删除位置不合法
		return 0;
	}
	if (pos == 0) {  // 删除链表头部节点
		return dll_pop_front(l);
	}
	if (pos == l->count - 1) {  // 删除链表尾部节点
		return dll_pop_back(l);
	}
	node_t* current = l->head;  // 从链表头部开始遍历
	for (int i = 0; i < pos; i++) {  // 遍历到指定位置
		current = current->next;
	}
	current->previous->next = current->next;  // 将当前节点的上一个节点的next指针指向当前节点的下一个节点
	current->next->previous = current->previous;  // 将当前节点的下一个节点的previous指针指向当前节点的上一个节点
	void* data = current->data;  // 保存当前节点的数据
	free(current);  // 释放当前节点的内存
	l->count--;  // 链表节点数量减1
	return data;  // 返回当前节点的数据
}

// DLL Size
// Queries the current size of a DLL
// Returns -1 if the DLL is NULL.
int dll_size(dll_t* l){
	if (l == NULL) {  // 链表为空
		exit(0);
	}
	return l->count;  // 返回链表节点数量
}

// Free DLL
// Removes a DLL and all of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t* l){
	if (l == NULL) {  // 链表为空
		return;
	}
	node_t* current = l->head;  // 从链表头部开始遍历
	while (current != NULL) {  // 遍历链表
		node_t* temp = current;  // 保存当前节点的指针
		current = current->next;  // 将当前节点的指针指向下一个节点
		free(temp);  // 释放当前节点的内存
	}
	free(l);  // 释放链表的内存
}



#endif

