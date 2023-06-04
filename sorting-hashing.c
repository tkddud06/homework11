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
		for (j = 0; j < MAX_ARRAY_SIZE; j++) // 끝까지 돌 때까지 반복
		{ /////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 0-1이 되지 않나? 에러 xx??
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

int shellSort(int *a) ///////////////////////////////////////////////// 해야됨
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n) /////////////////////////////////////////////////////////// 해야됨
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; // MAX_HASH_tABLE_SIZE로 나눈 나머지, 즉 배열 사이즈인 13으로 나눈 나머지를 주소로 갖는다.
} ////////////////////////////////////////////////////////////////////////////////////////////////// 해당 방식은, ~~~~~~~~~~~~~ 방식이다.

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
		hashcode = hashCode(key); // 원소들의 주소(해쉬테이블에서의 인덱스)는 별도의 해쉬 코드 함수를 통해 구함.

		if (hashtable[hashcode] == -1) // 해당 공간이 비어있다면
		{
			hashtable[hashcode] = key; // 키를 넣는다
		} else 	{ // 비어있지 않는 경우에는,

			index = hashcode; // 이미 구한 주소를 인덱스 변수에 넣고,

			while(hashtable[index] != -1) // 해당 인덱스가 가르키는 공간이 비어있을 때까지
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //////////////////////////////// 해당 인덱스를 계속 증가시킨다. 해당 방식은 ~~~~~~~~~~~~~~~~~~~~(순차~) 방식이다.
			} // 뒤의 % 연산은 인덱스가 마지막 12까지 도달 후, 해시 테이블의 사이즈를 넘어서는 13이 되면 앞으로 돌아오도록 하기 위한 연산이다.
			hashtable[index] = key; // 빈 공간을 찾으면, 그곳에 키를 넣는다
		}
	}

	return 0;
}

int search(int *ht, int key) ///////////////////////////////// 해야됨
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



