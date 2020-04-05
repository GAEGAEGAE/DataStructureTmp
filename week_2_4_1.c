/*******************************************************************************************************************************************
*  Class      : 자료구조 및 실습
*  Assignment : 2주차 4번째 과제(1)
*  Student    : 소프트웨어학과 201420485 문성훈
*
*  Description
*   배열의 이해를 위한 점수 계산 과제입니다.
*   모든 데이터를 int형 2차원 배열로 표현할 수 있긴하나 (예시. 이름을 유니코드로 저장) 너무 tricky한 방법은 쓰지않고 구현함
*   모든 데이터는 정상적으로 입력된다는 가정함(숫자가 입력되야하는 곳 숫자 입력, 문자가 입력되야하는 곳 문자 입력)
*   등수 계산마다 정렬(sorting)을 피하기 위한 추가적인 자료형을 둠 (출력형태1을 보면 입력된 순의 데이터가 유지되는 것으로 보여서 판단함)
*   문제의 조건을 충실하기 위해 코드를 작성하다보니 직관적이지 않은 코드가 존재합니다.
********************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_MAX 100

// 2.합계(SUM): 입력받은 값에 대해 합계를 계산하고 반환 
int sum_score(int n1, int n2, int n3) {
	return n1+n2+n3;
}

// 3.평균(AVE): 입력받은 값에 대해 평균을 계산하고 반환 
int aver_score(int sum) {
	return sum / 3;
}

// 4.등수(RANK): 입력받은 점수의 합계에 따라 오름차순으로 등수 계산하고 반환 
int get_rank(int sum, int length, int data[][2]) {
	for (int i = 0; i < length; i++) {
		if (sum == data[i][1]) {

			return i + 1;      // 등수반환 [기존에 생성된 데이터로 값을 비교하기에 '모든 제어 경로에서 값을 반환하지는 않습니다.' 걱정안해도 됨]
		}
	}

}

// 1. 입력(INPUT): 키보드로 값 입력 후 저장 후 반환 
int input_data(int index, char name[][10], int score[][6], int rank_info[][2]) {
	char answer;

	if (index >= STUDENT_MAX) {
		printf("[!] 더 이상의 데이터를 입력할 수 없습니다.\n");

		return -1;
	}

	rank_info[index][0] = index; 


	printf("이름: "); scanf("%10s", &name[index][0]);   // Buffer Over Flow 방지
	printf("국어: "); scanf("%d", &score[index][0]);
	printf("영어: "); scanf("%d", &score[index][1]);
	printf("수학: "); scanf("%d", &score[index][2]);

	score[index][3] = sum_score(score[index][0], score[index][1], score[index][2]);
	score[index][4] = aver_score(score[index][3]);

	rank_info[index][1] = score[index][3];

	getchar(); // for flush
	
	printf("더 많은 학생의 성적을 입력받으시겠습니까?(Y/N) ");
	scanf("%c", &answer);

	printf("\n");

	if (answer=='Y' || answer=='y') {
		
		//printf("1\n");
		return 1;
	}
	else {
		//printf("0\n");
		return 0;
	}

}

// 5. 출력(PRINT): 데이터가 입력이 완료되면 전체 출력(출력형태 1)
void print_all(int length, char name[][10], int score[][6], int rank[][2]) {
	printf("\n%-10s%-10s%-10s%-10s%-10s%-10s%-6s\n", "이름", "국어", "영어", "수학", "합계", "평균", "등수");
	printf("==================================================================\n");

	for (int i = 0; i < length; i++) {
		score[i][5] = get_rank(score[i][3], length, rank);

		// 출력양식을 문제의 주어진 조건과 같이 맞추다보니 포맷스트링으로 인해 지저분해짐 이해 부탁드립니다.
		printf("%-10s%3d%7s%3d%7s%3d%7s%3d%7s%3d%7s%3d%3s\n", &name[i][0], score[i][0], "", score[i][1], "", score[i][2], "", score[i][3], "", score[i][4], "", score[i][5], "");
	}
}

// 6. 검색(SEARCH)
int search(int length, char name[][10], int score[][6]) {
	char target[10];

	int result = 0;

	printf("검색하고자하는 사람의 이름: "); 
	scanf("%10s", target);

	for (int i = 0; i < length; i++) {
		if (!strcmp(target, &name[i][0])) {

			printf("이름: %s\n", target);
			printf("국어: %d점\n", score[i][0]);
			printf("영어: %d점\n", score[i][1]);
			printf("수학: %d점\n", score[i][2]);
			printf("합계: %d점\n", score[i][3]);
			printf("평균: %d점\n", score[i][4]);
			printf("등수: %d등\n\n", score[i][5]);

			result = 1;
		}
	}

	if (!result) {
		printf("검색하고자 하는 사람이 없습니다.\n");
	}

	return result;
}

// 소팅 저장
void sort(int length, int data[][2]) {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length - (i + 1); j++) {
			if (data[j][1] < data[j + 1][1]) {
				int t_student_id = data[j][0];
				int t_sum = data[j][1];

				data[j][0] = data[j + 1][0];
				data[j][1] = data[j + 1][1];

				data[j + 1][0] = t_student_id;
				data[j + 1][1] = t_sum;
			}
		}
	}

}


int main(void) {
	char name[STUDENT_MAX][10];  // 이름을 저장하는 2차원 배열
	int score[STUDENT_MAX][6];   // 점수(국어, 영어, 수학, 합계, 평균, 등수)을 저장하는 2차원 배열

	// index : 등수, sorted_sum[100][0] : 학생번호, sorted_sum[100][1]: 총합
	int sorted_sum[STUDENT_MAX][2]; // 학생의 합계에 따른 등수를 정렬해놓은 배열 [원본데이터를 유지해야 하기에 함수내부의 복사를 통한 탐색마다의 지속적인 소팅은 비효율적이라 판단되어 추가적인 자료구조 도입]


	int index = -1;
	int input_result;

	printf("[*] 성적 산출 프로그램\n\n");

	do {
		index = index + 1;

		input_result = input_data(index, name, score, sorted_sum);

		if (input_result == -1) {
			index = index - 1; // 이미 인덱스가 증가한 상태이기에 하나 감소시켜야함.
		}

	} while (input_result == 1);

	sort(index + 1, sorted_sum);
	print_all(index + 1, name, score, sorted_sum);

	input_result = 0;

	do {
		input_result = search(index + 1, name, score);

	} while (!input_result);

}
