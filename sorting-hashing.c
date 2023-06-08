/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{ // 메뉴 형식으로 작동
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");
		printf("[--------------  [최상영]  	[2022041062]  --------------]\n");
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL) // 배열이 비어있지 않을 경우
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) { // 배열이 비어있는 경우
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // 인덱스 출력
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // 인덱스의 원소 출력
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++) // 끝까지 돌 때까지 반복
	{
		minindex = i; // 최솟값을 가진 인덱스를 i로 초기화
		min = a[i]; // 최솟값을 i의 원소로 초기화
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) // 해당 선택한 인덱스부터, 끝까지 돌 때까지 반복
		{
			if (min > a[j]) // 만약 현재 최솟값으로 저장된 값보다, 뒤쪽의 배열 중 j 인덱스의 원소가 작다면
			{
				min = a[j]; // 최솟값을 j의 원소로 변경
				minindex = j; // 최솟값을 가진 인덱스를 j로 변경
			}
		}
		// 정렬을 진행할 선택된 인덱스 i의 원소와, 아직 정렬되지 않은 뒷 배열 부분에서 찾은 최솟값을 가진 인덱스의 원소를 바꿈
		a[minindex] = a[i];
		a[i] = min; 
		// 이를 반복하며, 전체 배열 정렬.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++) // 끝까지 돌 때까지 반복
	{
		t = a[i]; // t는 정렬되지 않은 배열의 시작 부분 원소
		j = i; // j는 정렬되지 않은 배열의 시작 인덱스를 나타냄
		while (a[j-1] > t && j > 0) // 정렬된 부분, 즉 j보다 인덱스가 작은 부분의 원소 중, 현재 정렬되지 않은 배열의 시작 원소를 가르키는 t가 작은 것이 있다면, 
		// 정렬이 완료될 때까지 앞쪽으로 밀어준다. 만약 j가 0이 된 상태라면(더 작은 원소는 존재하지 않는 경우) 끝낸다.
		{ // 조건을 만족하면(해당 원소 t를 포함하여 적절한 위치까지 밀려서 정렬이 완료되었다면, while문을 끝내고 다음 정렬이 안된 원소로 넘어간다)
			a[j] = a[j-1]; // 조건을 만족해서 밀어줘야 하는 경우, j-1 공간의 원소를 j로 옮기어서 j-1 공간을 확보해주는 방식이다. 
			// (최종적으로 와일문을 빠져나오고 나면, j가 해당 공간의 인덱스 번호가 된다.)
			j--;
		}
		a[j] = t; // 최종적으로 while문을 빠져 나온 뒤, 확보해둔 공간에 t를 삽입한다.
		// 이를 반복하며, 전체 배열 정렬.
	} 

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++) // 끝까지 돌 때까지 반복
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++) // 끝까지 돌 때까지 반복
		{ // 기존에는 j가 0이였는데, 그렇게 되면 아래 문장에서 0-1, 즉 j[-1]에도 접근하게 되므로, 오류를 막기 위해 1부터로 바꾸었습니다. 그렇게 해도 모든 원소를 비교하므로, 문제는 없습니다.
			if (a[j-1] > a[j]) // 순차적으로 계속 확인하면서, 만약 배열에서 앞의 원소가 뒤의 원소보다 크다면, 해당 원소를 뒤의 원소 위치와 바꾼다.
			{ // 그를 계속 반복하면서, 내부의 j로 컨트롤되는 for문을 한번 돌 때마다, 뒤쪽으로 쌓여가며 원소가 정렬될 것이다.
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a) 
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // h가 간격을 의미함. 최초 시작은 배열 사이즈의 절반인 13/2 = 6(내림)부터이며,
	// 순서대로 돌수록 6, 3, 1, 0가 될 것임.
	{
		for (i = 0; i < h; i++) // h 간격만큼 벌어진 대상과 비교를 진행할 건데, i는 시작하는 부분의 인덱스임
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // j는 i와 h간격만큼 벌어진 원소의 인덱스임. 이를 이용해 비교할 것.
			{ // 더이상 갈 수 없을 때까지, 뒤쪽으로 간격만큼 이동하며 순서대로 비교.
				v = a[j]; // 현재의 j 인덱스의 원소를 v에 넣음
				k = j; // 현재의 j 인덱스를 k에 넣음
				while (k > h-1 && a[k-h] > v) // 간격만큼 앞에 있는 원소가 존재하고, 그 앞의 이전 원소가 더 크다면 진행
				{
					a[k] = a[k-h]; // 간격만큼 떨어진 앞쪽의 원소는 뒷쪽의 공간으로 넣고, 
					k -= h; // 인덱스는 간격 단위로 더 앞으로 감
				} // 이 과정을 반복하며, 더 작은 원소가 나올 때까지, 밀어주듯 앞쪽의 큰 원소들을 뒤로 빼줌
				a[k] = v; // 더이상 큰 게 없거나, 앞으로 갈 수 없을 때, 저장해두었던 v를 그곳에 넣음
			}
		}	// 해당 과정을 반복하며, 점점 간격을 줄여나가고, 정렬을 완료함
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n) // n은 데이터의 사이즈를 나타냄. 동시에, 명령문에서 데이터의 마지막 인덱스를 구할때도 사용함.
{
	int v, t;
	int i, j;

	if (n > 1) // 데이터가 1개 보다 많을 때만 진행. 오류를 방지하기 위해서, 그리고 재귀 시에 잘리고 잘려서 1개짜리가 들어왔을 대를 위해서 진행
	{
		v = a[n-1]; // v는 배열의 마지막 인덱스 원소 (피벗이 될 것임)
		i = -1; // i는 -1(가장 왼쪽보다 한칸 밖, 밑에서 실행문에서 오류를 없게 하기 위함)
		j = n - 1; // j는 배열의 마지막 인덱스(오른쪽) (피벗의 인덱스가 될 것임)

		while(1) // 무한 반복
		{
			while(a[++i] < v); // v보다 큰 원소를 찾을때까지 오른쪽으로 이동
			while(a[--j] > v); // v보다 작은 원소를 찾을때까지 왼쪽으로 이동

			if (i >= j) break; // 모든 원소를 한차례 탐색 더 비교할 필요가 없을 경우(와일문 밖으로 탈출)
			// 각각의 바꿔야 하는 한 쌍의 원소들을 찾았을 때, 즉 v를 기준으로 정상 위치가 아닌 두 원소들
			// (피벗보다 크지만 왼쪽에 있는 원소, 피벗보다 작지만 오른쪽에 있는 원소. 즉, 위의 if문에서 걸러지지 않은 경우)을 찾았을 때, i 인덱스의 원소와, j 인덱스의 원소를 교환함
			t = a[i]; 
			a[i] = a[j];
			a[j] = t;
		} // 이를 반복하며, v를 중심으로 왼쪽에는 작은 것들이 오도록, 오른쪽에는 큰 것들이 오도록 정렬함.
		// 마지막으로, 현재 i 인덱스의 원소와, 피벗(v)를 바꾸어 줌으로써, 왼쪽에는 v보다 작은 것, 오른쪽에는 큰 것이 오도록 정렬함
		// i는 피벗보다 큰 걸 가르키므로, 피벗과 교환하게 되면, 최종적으로 윗줄의 조건을 만족하게 됨.
		t = a[i]; 
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i); // 왼쪽의 것들을 다시 퀵소트에 넣어 반복
		quickSort(a+i+1, n-i-1); // 오른쪽의 것들을 다시 퀵소트에 넣어 반복
	} // 이 재귀를 반복함으로써, 모든 데이터를 정렬함


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; // MAX_HASH_tABLE_SIZE로 나눈 나머지, 즉 배열 사이즈인 13으로 나눈 나머지를 주소로 갖는다.
} // 해당 방식은, 제산 함수 방식이다.

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) // 해시 테이블의 모든 데이터를 -1로 초기화
		hashtable[i] = -1;

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i]; // 키는 배열의 원소들
		hashcode = hashCode(key); // 원소들의 인덱스는 별도의 해시 코드 함수를 통해 구함.

		if (hashtable[hashcode] == -1) // 해당 공간이 비어있다면
		{
			hashtable[hashcode] = key; // 키를 넣는다
		} else 	{ // 비어있지 않는 경우에는,

			index = hashcode; // 이미 구한 인덱스를 인덱스 변수에 넣고,

			while(hashtable[index] != -1) // 해당 인덱스가 가르키는 공간이 비어있을 때까지
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; // 해당 인덱스를 계속 증가시킨다. 해당 방식은 선형 조사법 방식이다.
			} // 뒤의 % 연산은 인덱스가 마지막 12까지 도달 후, 해시 테이블의 사이즈를 넘어서는 13이 되면 앞으로 돌아오도록 하기 위한 연산이다.
			hashtable[index] = key; // 빈 공간을 찾으면, 그곳에 키를 넣는다
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); // 해시 코드 함수를 통해 해당 찾는 원소의 인덱스를 구함

	if(ht[index] == key) // 바로 찾았다면, 해당 인덱스를 바로 리턴
		return index;

	int try = 1; // 위에서 한개를 탐색한 셈이므로, 1부터 시작한다
	while(try != MAX_HASH_TABLE_SIZE) // 바로 찾지 못했다면, 선형 조사법 방식을 사용했으므로, 순차적으로 탐색해가며 해당 원소를 찾는다
	{ // 찾아본 원소의 개수가 해쉬 테이블의 사이즈와 동일할 때(모든 원소를 탐색했을때) 와일문이 종료된다.
		index++;
		index = index % MAX_HASH_TABLE_SIZE; // 만약 끝까지 도달했으면 앞으로 다시 이동하도록 한다
		if (ht[index] == key)
		{
			return index;  // 찾고 나면 해당 인덱스를 리턴한다
		} 
		// 못찾았으면 try 횟수만 늘린다.
		try++;

	
	} // 찾을 때까지 돌린다. 단, 원래 코드의 경우, 만약 없는 원소를 탐색하는 경우에는, 무한 반복할 수 있는 오류의 여지가 있다. 또한, index를 ++index로 하고 검사 뒤에 나머지연산을 수행하면
	// 검사 시에는 이미 해쉬 테이블의 사이즈를 넘어선 채로 검사할 수 있다. 그래서 코드를 수정했다.
	return -1;
}



