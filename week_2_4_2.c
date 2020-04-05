/*******************************************************************************************************************************************
*  Class      : 자료구조 및 실습
*  Assignment : 2주차 4번째 과제(1)
*  Student    : 소프트웨어학과 201420485 문성훈
*
*  Description
*   구조체의 이해를 위한 점수 계산 과제입니다.
*   구조체의 특성(장점)을 활용하기 위하여 평균점수는 실수형 자료형 double로 나타내었습니다.
*   모든 데이터는 정상적으로 입력된다는 가정함(숫자가 입력되야하는 곳 숫자 입력, 문자가 입력되야하는 곳 문자 입력)
*   등수 계산마다 정렬(sorting)을 피하기 위한 추가적인 자료형을 둠 (출력형태1을 보면 입력된 순의 데이터가 유지되는 것으로 보여서 판단함)
*   문제의 조건을 충실하기 위해 코드를 작성하다보니 직관적이지 않은 코드가 존재합니다.
********************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_MAX 100


struct studentInfo {
	char name[10];
	
	int score_kor;
	int score_eng;
	int score_math;
	
	int score_sum;
	double score_aver;

	int rank;
};

typedef struct studentInfo STUDENT_INFO;

int sum(int a_kor, int a_eng, int a_math) {
	return a_kor + a_eng + a_math;
}

double ave(int a_sum) {
	return a_sum / 3.0;
}

int input(STUDENT_INFO * s, int * sorted_sum) {
	char answer;

	// STEP1. Input
	printf("이름: "); scanf("%10s", &(s->name));   // Buffer Over Flow 방지
	printf("국어: "); scanf("%d", &(s->score_kor));
	printf("영어: "); scanf("%d", &(s->score_eng));
	printf("수학: "); scanf("%d", &(s->score_math));

	// STEP2. Calculate
	s->score_sum = sum(s->score_kor, s->score_eng, s->score_math);
	*sorted_sum = s->score_sum;

	s->score_aver = ave(s->score_sum);

	getchar(); // for flush


	// STEP3. Ask more data
	printf("더 많은 학생의 성적을 입력받으시겠습니까?(Y/N) ");
	scanf("%c", &answer);
	printf("\n");

	if (answer == 'Y' || answer == 'y') {
		return 1;
	}
	else {
		return 0;
	}
}

int rank(int a_sum, int length, int sorted_sum[]) {
	for (int i = 0; i < length; i++) {
		if (sorted_sum[i] == a_sum) {

			return i + 1;

		}
	}
}

void print(STUDENT_INFO * s[], int sorted_sum[], int length) {
	printf("\n%-10s%-10s%-10s%-10s%-10s%-10s%-6s\n", "이름", "국어", "영어", "수학", "합계", "평균", "등수");
	printf("==================================================================\n");


	for (int i = 0; i < length; i++) {
		s[i]->rank = rank(s[i]->score_sum, length, sorted_sum);

		printf("%-10s%3d%7s%3d%7s%3d%7s%3d%7s%2.1lf%7s%3d%3s\n", 
			&(s[i]->name), 
			s[i]->score_kor, "", s[i]->score_eng, "", s[i]->score_math, "",
			s[i]->score_sum, "", s[i]->score_aver, "",
			s[i]->rank, "");
	}

}


void sort(int length, int sorted_sum[]) {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length - (i + 1); j++) {
			if (sorted_sum[j] < sorted_sum[j + 1]) {
				int tmp = sorted_sum[j];

				sorted_sum[j] = sorted_sum[j + 1];
				
				sorted_sum[j + 1] = tmp;
			}
		}
	}

}

// 6. 검색(SEARCH)
int search(int length, STUDENT_INFO * s[]) {
	char target[10];

	int result = 0;

	printf("\n검색하고자하는 사람의 이름: ");
	scanf("%10s", target);

	for (int i = 0; i < length; i++) {
		if (!strcmp(target, &(s[i]->name))) {

			printf("이름: %s\n", target);
			printf("국어: %d점\n", s[i]->score_kor);
			printf("영어: %d점\n", s[i]->score_eng);
			printf("수학: %d점\n", s[i]->score_math);
			printf("합계: %d점\n", s[i]->score_sum);
			printf("평균: %2.1lf점\n", s[i]->score_aver);
			printf("등수: %d등\n\n", s[i]->rank);

			result = 1;
		}
	}

	if (!result) {
		printf("검색하고자 하는 사람이 없습니다.\n");
	}

	return result;
}

int main(void) {
	STUDENT_INFO * info[STUDENT_MAX] = { 0, };
	int sorted_sum[STUDENT_MAX] = { 0, };

	int input_result = 0;
	int index = 0;
	printf("[*] 성적 산출 프로그램\n\n");

	do {
		info[index] = (STUDENT_INFO *)malloc(sizeof(STUDENT_INFO));

		//printf("%08x\n", info[index]);

		input_result = input(info[index], &sorted_sum[index]);

		index = index + 1;

		if (index >= 100) {
			printf("[!] 더 이상의 데이터를 입력할 수 없습니다.\n");

			break;
		}
		
	} while (input_result);

	//
	sort(index, sorted_sum);
	print(info, sorted_sum, index);

	input_result = 0;

	do {
		input_result = search(index, info);
	} while (!input_result);

	// Free all heap memory!
	for (int i = 0; i < index; i++) {
		free(info[i]);
	}


}
