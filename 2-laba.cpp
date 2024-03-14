#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <time.h>

// 1 вариант
// ступенчатая инт

using namespace std;

void print_array(int *A, int N);
void FillRand(int *A, int N, int min, int max, int K);
void FillUp(int *A, int N, int min, int max, int K);
void FillDown(int *A, int N, int min, int max, int K);
void FillStep(int *A, int N, int min, int max, int K);
int CheckSort(int *A, int N); // Функция проверки сортировки
void InsertionSort(int *A, int N); // 11 - сортировка вставками
void InsertionSortKey(int *A, int N); // 12 - Модифицированная сортировка вставками 1
void CountingSort(int *A, int N); // 22 - Сортировка подсчётом
int partition(int *A, int start, int end); // 9 - Модифицированная быстрая сортировака 2
void quicksort(int *A, int start, int end); 
int Less(int A, int B);

long long Cmp;
int compare(const void *value, const void *value2){
	int a = *(int*)value;
	int b = *(int*)value2;
	Cmp++;
	if(a > b) return 1;
	if(a < b) return -1;
	return 0;
}


int main() {
	
	
	int max = 100000, min=0;
	int N = max;
	int s = 5;
	double t;
	int count = 0;
	int Nmax = 5000000;
	int *A;
	A = new int[Nmax];
	cout << endl;
	srand(time(NULL));
	
	for(N = Nmax/10; N <= Nmax; N+=Nmax/10){
		Cmp = 0;	
		FillRand(A, N, 0, 100, s);
		t = GetTickCount();
		quicksort(A, 0, N);
		cout << GetTickCount() - t << " "<< Cmp << endl;
	}
	cout << endl;
	cout << endl;
	for(N = Nmax/10; N <= Nmax; N+=Nmax/10){
		Cmp = 0;	
		FillUp(A, N, 0, 100, s);
		t = GetTickCount();
		quicksort(A, 0, N);
		cout << GetTickCount() - t << " "<< Cmp << endl;
	}
	cout << endl;
	cout << endl;
	for(N = Nmax/10; N <= Nmax; N+=Nmax/10){
		Cmp = 0;	
		FillDown(A, N, 0, 100, s);
		t = GetTickCount();
		quicksort(A, 0, N);
		cout << GetTickCount() - t << " "<< Cmp << endl;
	}
	cout << endl;
	cout << endl;
	for(N = Nmax/10; N <= Nmax; N+=Nmax/10){
		Cmp = 0;	
		FillStep(A, N, 0, 100, s);
		t = GetTickCount();
		quicksort(A, 0, N);
		cout << GetTickCount() - t << " "<< Cmp << endl;
	}
	cout << endl;
	cout << endl;
	
	delete[] A;
	
	return 0;
}

void print_array(int *A, int N){
	for(int i = 0; i < N; i++){
		cout << A[i] << ' ';
	}
	cout << endl;
}

void FillRand(int *A, int N, int min, int max, int K){
	for(int i = 0; i < N; i++){
		A[i] = ((rand() << 15) | rand()) % (max - min) + min;
	}
}

void FillUp(int *A, int N, int min, int max, int K){
//	for(int i = 0; i < N; i++){
//		A[i] = (max-min)*i/N+min;
//	}
	double delta = ((double)(max - min))/N;
	for(int i = 0; i < N; i++){
		A[i] = delta*i+min;
	}
}

void FillDown(int *A, int N, int min, int max, int K){
	double delta = ((double)(max - min))/N;
	for(int i = N-1, j = 0; i >=0; i--, j++){
		A[j] = delta*i+min;
	}
}

void FillStep(int *A, int N, int min, int max, int K){ // Ступенчатая
	int step = N/K;
	int stepbegin = 0;
	int mins = min;
	int maxs = max/K;
	for(int j = 0; j < K; j++){
		
		for(int i = stepbegin; i < stepbegin+step; i++){
			A[i] = rand() % (maxs - mins) + mins;
		}
		mins = maxs;
		maxs += max/K;
		stepbegin += step;
	}
}

// Функция проверки сортировки

int CheckSort(int *A, int N){
	for(int i = 1; i < N; i++){
		if(A[i] < A[i-1]){
			return 1;
		}
	}
	return 0;
}

// 11 - сортировка вставками

int Less(int A, int B) {
	Cmp++;
	return A < B;
}

void InsertionSort(int *A, int N){
	int  V;
	int j;
	for(int i = 1; i < N; i++){
		V = A[i];
//		for(j = i; j > 0 && V < A[j-1]; j--){
		for(j = i; j > 0 && Less(V, A[j-1]); j--){
			A[j] = A[j-1];
		}	
		A[j] = V;
	}
}

// 12 - Модифицированная сортировка вставками 1 (С использованием сигнального ключа)

void InsertionSortKey(int *A, int N){
	int  V;
	int j;
	for(int i = N-1; i > 0; i--){
//		if(A[i-1] > A[i])
		if(Less(A[i], A[i-1]))
			swap(A[i], A[i-1]);
	}
	for(int i = 2; i < N; i++){
		V = A[i];
		for(j = i; Less(V, A[j-1]); j--){
			A[j] = A[j-1];
		}	
		A[j] = V;
	}
}

// 22 - Сортировка подсчётом

void CountingSort(int *A, int N){
//	int count = 0;
//	
	int *Cnt, *AH, D = 101;
	AH = new int[N];
	Cnt = new int[D];
	for(int i = 0; i < D; i++) Cnt[i] = 0;
	for(int i = 0; i < N; i++) Cnt[A[i]+1]++;
	for(int i = 1; i < D; i++) Cnt[i] += Cnt[i-1];
	for(int i = 0; i < N; i++) AH[Cnt[A[i]]++] = A[i];
	for(int i = 0; i < N; i++) A[i] = AH[i]; 
	free(AH);
	free(Cnt);
//	int max = 101;
//	int *output = new int[N];
//	int count[101];//] = new int[max];
////	int max = A[0];
//	
////	for(int i = 1; i <= N; i++) {
//////		if(A[i] > max)
////		if(Less(max, A[i]))
////			max = A[i];
////	}
//	for(int i = 0; i <= max; ++i){
//		count[i] = 0;
//	}
//	for(int i = 0; i < N; i++){
//		count[A[i]]++;
//	}
//	for(int i = 1; i <= max; i++){
//		count[i] += count[i-1];
//	}
//	for(int i = N-1; i >=0; i--){
//		output[count[A[i]]--] = A[i];
//		count[A[i]]--;
//	}
//	for(int i = 0; i < N; i++){
//		A[i] = output[i];
//	}
	
}

// 9 - Модифицированная быстрая сортировака 2 (Выбор разделяющего элемента с помощью медианы)

int partition(int *A, int start, int end)
{
    int V = A[end];
    int i = start-1;
    int j = end;
    for(;;){
//    	while(V> A[++i]);
    	while(Less(A[++i], V));
    	while(Less(V, A[--j])) if(j==start) break;
    	if(i >=j) break;
    	swap(A[i], A[j]);
	}
	swap(A[end], A[i]);
	return i;
}
 
void quicksort(int *A, int start, int end)
{
    int P;
    if (end - start <= 0) return;
    
    swap(A[(start+end)/2], A[end-1]);
//    if(A[start] > A[end-1]) swap(A[start], A[end-1]);
    if(Less(A[end-1], A[start])) swap(A[start], A[end-1]);
//    if(A[start] > A[end]) swap(A[start], A[end]);
    if(Less(A[end], A[start])) swap(A[start], A[end]);
//    if(A[end-1] > A[end]) swap(A[end-1], A[end]);
	if(Less(A[end], A[end-1])) swap(A[end-1], A[end]);	
    
    P = partition(A, start, end);
    quicksort(A, start, P-1);
    quicksort(A, P+1, end);
}








