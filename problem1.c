#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
	element data;
	struct ListNote * link;
} ListNode;

// Single List List의 노드 추가 함수
ListNode* insert_first(ListNode * head, int value) {
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;

	return head;
}

// Single List Chain의 data를 탐색하여 이를 합산한 뒤 반환하는 함수
int sum_List(ListNode * head) {
	ListNode * t_pointer = head;
	int sum = 0;

	// 예외처리
	if (t_pointer == NULL) {
		printf("[!] 리스트에 어떠한 데이터도 존재하지 않아 프로그램을 종료합니다.\n");
		exit(0);
	}

	while (1) {
		if (t_pointer == NULL) {
			break;
		}
		sum += t_pointer->data;
		t_pointer = t_pointer->link;
	}

	return sum;
}

// Single List Chain의 모든 할당된 Node를 해제하는 함수
ListNode* free_ListNode(ListNode * head) {
	//printf("[*] free_ListNode()\n");

	ListNode * t_pointer = NULL;

	while (1) {
		t_pointer = head;

		if (head == NULL) {
			break;
		}

		head = head->link;

		free(t_pointer);
		//printf("FREE %08x\n", t_pointer);

	}

	return NULL;

}

int main(void) {
	ListNode * head = NULL;

	int length = 0;

	printf("노드의 개수: ");
	scanf("%d", &length);

	for (int i = 0; i < length; i++) {
		int value = 0;

		printf("노드 #%d 데이터: ", i + 1);
		scanf("%d", &value);

		head = insert_first(head, value);
		//printf("%08x\n", head);
	}

	printf("연결 리스트의 데이터 합: %d\n", sum_List(head));
	head = free_ListNode(head);

	return 0;
}
