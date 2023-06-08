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

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{ // �޴� �������� �۵�
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");
		printf("[--------------  [�ֻ�]  	[2022041062]  --------------]\n");
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

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a;

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL) // �迭�� ������� ���� ���
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) { // �迭�� ����ִ� ���
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // �ε��� ���
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // �ε����� ���� ���
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

	for (i = 0; i < MAX_ARRAY_SIZE; i++) // ������ �� ������ �ݺ�
	{
		minindex = i; // �ּڰ��� ���� �ε����� i�� �ʱ�ȭ
		min = a[i]; // �ּڰ��� i�� ���ҷ� �ʱ�ȭ
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) // �ش� ������ �ε�������, ������ �� ������ �ݺ�
		{
			if (min > a[j]) // ���� ���� �ּڰ����� ����� ������, ������ �迭 �� j �ε����� ���Ұ� �۴ٸ�
			{
				min = a[j]; // �ּڰ��� j�� ���ҷ� ����
				minindex = j; // �ּڰ��� ���� �ε����� j�� ����
			}
		}
		// ������ ������ ���õ� �ε��� i�� ���ҿ�, ���� ���ĵ��� ���� �� �迭 �κп��� ã�� �ּڰ��� ���� �ε����� ���Ҹ� �ٲ�
		a[minindex] = a[i];
		a[i] = min; 
		// �̸� �ݺ��ϸ�, ��ü �迭 ����.
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

	for(i = 1; i < MAX_ARRAY_SIZE; i++) // ������ �� ������ �ݺ�
	{
		t = a[i]; // t�� ���ĵ��� ���� �迭�� ���� �κ� ����
		j = i; // j�� ���ĵ��� ���� �迭�� ���� �ε����� ��Ÿ��
		while (a[j-1] > t && j > 0) // ���ĵ� �κ�, �� j���� �ε����� ���� �κ��� ���� ��, ���� ���ĵ��� ���� �迭�� ���� ���Ҹ� ����Ű�� t�� ���� ���� �ִٸ�, 
		// ������ �Ϸ�� ������ �������� �о��ش�. ���� j�� 0�� �� ���¶��(�� ���� ���Ҵ� �������� �ʴ� ���) ������.
		{ // ������ �����ϸ�(�ش� ���� t�� �����Ͽ� ������ ��ġ���� �з��� ������ �Ϸ�Ǿ��ٸ�, while���� ������ ���� ������ �ȵ� ���ҷ� �Ѿ��)
			a[j] = a[j-1]; // ������ �����ؼ� �о���� �ϴ� ���, j-1 ������ ���Ҹ� j�� �ű� j-1 ������ Ȯ�����ִ� ����̴�. 
			// (���������� ���Ϲ��� ���������� ����, j�� �ش� ������ �ε��� ��ȣ�� �ȴ�.)
			j--;
		}
		a[j] = t; // ���������� while���� ���� ���� ��, Ȯ���ص� ������ t�� �����Ѵ�.
		// �̸� �ݺ��ϸ�, ��ü �迭 ����.
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

	for(i = 0; i < MAX_ARRAY_SIZE; i++) // ������ �� ������ �ݺ�
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++) // ������ �� ������ �ݺ�
		{ // �������� j�� 0�̿��µ�, �׷��� �Ǹ� �Ʒ� ���忡�� 0-1, �� j[-1]���� �����ϰ� �ǹǷ�, ������ ���� ���� 1���ͷ� �ٲپ����ϴ�. �׷��� �ص� ��� ���Ҹ� ���ϹǷ�, ������ �����ϴ�.
			if (a[j-1] > a[j]) // ���������� ��� Ȯ���ϸ鼭, ���� �迭���� ���� ���Ұ� ���� ���Һ��� ũ�ٸ�, �ش� ���Ҹ� ���� ���� ��ġ�� �ٲ۴�.
			{ // �׸� ��� �ݺ��ϸ鼭, ������ j�� ��Ʈ�ѵǴ� for���� �ѹ� �� ������, �������� �׿����� ���Ұ� ���ĵ� ���̴�.
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

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // h�� ������ �ǹ���. ���� ������ �迭 �������� ������ 13/2 = 6(����)�����̸�,
	// ������� ������ 6, 3, 1, 0�� �� ����.
	{
		for (i = 0; i < h; i++) // h ���ݸ�ŭ ������ ���� �񱳸� ������ �ǵ�, i�� �����ϴ� �κ��� �ε�����
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // j�� i�� h���ݸ�ŭ ������ ������ �ε�����. �̸� �̿��� ���� ��.
			{ // ���̻� �� �� ���� ������, �������� ���ݸ�ŭ �̵��ϸ� ������� ��.
				v = a[j]; // ������ j �ε����� ���Ҹ� v�� ����
				k = j; // ������ j �ε����� k�� ����
				while (k > h-1 && a[k-h] > v) // ���ݸ�ŭ �տ� �ִ� ���Ұ� �����ϰ�, �� ���� ���� ���Ұ� �� ũ�ٸ� ����
				{
					a[k] = a[k-h]; // ���ݸ�ŭ ������ ������ ���Ҵ� ������ �������� �ְ�, 
					k -= h; // �ε����� ���� ������ �� ������ ��
				} // �� ������ �ݺ��ϸ�, �� ���� ���Ұ� ���� ������, �о��ֵ� ������ ū ���ҵ��� �ڷ� ����
				a[k] = v; // ���̻� ū �� ���ų�, ������ �� �� ���� ��, �����صξ��� v�� �װ��� ����
			}
		}	// �ش� ������ �ݺ��ϸ�, ���� ������ �ٿ�������, ������ �Ϸ���
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n) // n�� �������� ����� ��Ÿ��. ���ÿ�, ��ɹ����� �������� ������ �ε����� ���Ҷ��� �����.
{
	int v, t;
	int i, j;

	if (n > 1) // �����Ͱ� 1�� ���� ���� ���� ����. ������ �����ϱ� ���ؼ�, �׸��� ��� �ÿ� �߸��� �߷��� 1��¥���� ������ �븦 ���ؼ� ����
	{
		v = a[n-1]; // v�� �迭�� ������ �ε��� ���� (�ǹ��� �� ����)
		i = -1; // i�� -1(���� ���ʺ��� ��ĭ ��, �ؿ��� ���๮���� ������ ���� �ϱ� ����)
		j = n - 1; // j�� �迭�� ������ �ε���(������) (�ǹ��� �ε����� �� ����)

		while(1) // ���� �ݺ�
		{
			while(a[++i] < v); // v���� ū ���Ҹ� ã�������� ���������� �̵�
			while(a[--j] > v); // v���� ���� ���Ҹ� ã�������� �������� �̵�

			if (i >= j) break; // ��� ���Ҹ� ������ Ž�� �� ���� �ʿ䰡 ���� ���(���Ϲ� ������ Ż��)
			// ������ �ٲ�� �ϴ� �� ���� ���ҵ��� ã���� ��, �� v�� �������� ���� ��ġ�� �ƴ� �� ���ҵ�
			// (�ǹ����� ũ���� ���ʿ� �ִ� ����, �ǹ����� ������ �����ʿ� �ִ� ����. ��, ���� if������ �ɷ����� ���� ���)�� ã���� ��, i �ε����� ���ҿ�, j �ε����� ���Ҹ� ��ȯ��
			t = a[i]; 
			a[i] = a[j];
			a[j] = t;
		} // �̸� �ݺ��ϸ�, v�� �߽����� ���ʿ��� ���� �͵��� ������, �����ʿ��� ū �͵��� ������ ������.
		// ����������, ���� i �ε����� ���ҿ�, �ǹ�(v)�� �ٲپ� �����ν�, ���ʿ��� v���� ���� ��, �����ʿ��� ū ���� ������ ������
		// i�� �ǹ����� ū �� ����Ű�Ƿ�, �ǹ��� ��ȯ�ϰ� �Ǹ�, ���������� ������ ������ �����ϰ� ��.
		t = a[i]; 
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i); // ������ �͵��� �ٽ� ����Ʈ�� �־� �ݺ�
		quickSort(a+i+1, n-i-1); // �������� �͵��� �ٽ� ����Ʈ�� �־� �ݺ�
	} // �� ��͸� �ݺ������ν�, ��� �����͸� ������


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; // MAX_HASH_tABLE_SIZE�� ���� ������, �� �迭 �������� 13���� ���� �������� �ּҷ� ���´�.
} // �ش� �����, ���� �Լ� ����̴�.

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) // �ؽ� ���̺��� ��� �����͸� -1�� �ʱ�ȭ
		hashtable[i] = -1;

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i]; // Ű�� �迭�� ���ҵ�
		hashcode = hashCode(key); // ���ҵ��� �ε����� ������ �ؽ� �ڵ� �Լ��� ���� ����.

		if (hashtable[hashcode] == -1) // �ش� ������ ����ִٸ�
		{
			hashtable[hashcode] = key; // Ű�� �ִ´�
		} else 	{ // ������� �ʴ� ��쿡��,

			index = hashcode; // �̹� ���� �ε����� �ε��� ������ �ְ�,

			while(hashtable[index] != -1) // �ش� �ε����� ����Ű�� ������ ������� ������
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; // �ش� �ε����� ��� ������Ų��. �ش� ����� ���� ����� ����̴�.
			} // ���� % ������ �ε����� ������ 12���� ���� ��, �ؽ� ���̺��� ����� �Ѿ�� 13�� �Ǹ� ������ ���ƿ����� �ϱ� ���� �����̴�.
			hashtable[index] = key; // �� ������ ã����, �װ��� Ű�� �ִ´�
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); // �ؽ� �ڵ� �Լ��� ���� �ش� ã�� ������ �ε����� ����

	if(ht[index] == key) // �ٷ� ã�Ҵٸ�, �ش� �ε����� �ٷ� ����
		return index;

	int try = 1; // ������ �Ѱ��� Ž���� ���̹Ƿ�, 1���� �����Ѵ�
	while(try != MAX_HASH_TABLE_SIZE) // �ٷ� ã�� ���ߴٸ�, ���� ����� ����� ��������Ƿ�, ���������� Ž���ذ��� �ش� ���Ҹ� ã�´�
	{ // ã�ƺ� ������ ������ �ؽ� ���̺��� ������� ������ ��(��� ���Ҹ� Ž��������) ���Ϲ��� ����ȴ�.
		index++;
		index = index % MAX_HASH_TABLE_SIZE; // ���� ������ ���������� ������ �ٽ� �̵��ϵ��� �Ѵ�
		if (ht[index] == key)
		{
			return index;  // ã�� ���� �ش� �ε����� �����Ѵ�
		} 
		// ��ã������ try Ƚ���� �ø���.
		try++;

	
	} // ã�� ������ ������. ��, ���� �ڵ��� ���, ���� ���� ���Ҹ� Ž���ϴ� ��쿡��, ���� �ݺ��� �� �ִ� ������ ������ �ִ�. ����, index�� ++index�� �ϰ� �˻� �ڿ� ������������ �����ϸ�
	// �˻� �ÿ��� �̹� �ؽ� ���̺��� ����� �Ѿ ä�� �˻��� �� �ִ�. �׷��� �ڵ带 �����ߴ�.
	return -1;
}



