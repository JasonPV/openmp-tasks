#include <iostream>
#include <stdio.h>
#include <omp.h>


using namespace std;


long long scalar(long long n, long long *array1, long long *array2, bool Parallel, int num_threads=1){
long long result = 0;
	omp_set_num_threads(num_threads);
	#pragma omp parallel for reduction(+:result) if(Parallel)
	for (int i = 0; i < n; ++i)
        	result += (array1[i] * array2[i]);
	cout << omp_get_num_threads() << endl;
return result;
}


int main(){
long long *array1;
long long *array2;
long long n;

cout << "Input n: ";
cin >> n;
array1 = new long long[n];
array2 = new long long[n];

for (int i=0; i<n; i++)
{
	array1[i] = rand() % 1000 + 1;
	array2[i] = rand() % 1000 + 1;
}

double start_time = omp_get_wtime();
long long result = scalar(n, array1, array2, false);
double time = omp_get_wtime() - start_time;
cout << "result: " << result << endl;
cout << "time: " << time << endl;


for (int i = 2; i <= 16; i *= 2)
{

	start_time = omp_get_wtime();
	result = scalar(n, array1, array2, true, i);
	time = omp_get_wtime() - start_time;
	cout << "result with omp: " << result << endl;
	cout << "time: " << time << endl;
}

return 0;
}
