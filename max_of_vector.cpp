#include <iostream>
#include <omp.h>


using namespace std;
int get_max(long long* array, long long n , int Parallel, int num_threads=1){	
	int mx;
	if (Parallel == 1)
	{
		mx = array[0];
		omp_set_num_threads(num_threads);
		#pragma omp parallel for
		for (int i = 1; i < n; i++)
		{
			if (array[i] > mx)
				#pragma omp critical
				if (array[i] > mx)
					mx = array[i];
		}
	}
	if (Parallel == 2)
	{			
		mx = array[0];
		omp_set_num_threads(num_threads);
		#pragma omp parallel for reduction(max:mx)	
		for (int i = 1; i < num_threads; i++)
			if (array[i] > mx)
				mx = array[i];

	}

	else
	{	
		mx = array[0];
		for (int i = 1; i < n; i++)
			if (array[i] > mx)
				mx = array[i];

	}

	return mx;
}


int main(){

	long long* array;
	long long n;
	cout << "Input n: ";
	cin >> n;
	array = new long long[n];

	for (int i = 0; i < n; i++)
		array[i] = rand() % 1000 + 1;
	
	double start_time = omp_get_wtime();
	int result1 = get_max(array, n, 0);
	double time1 = omp_get_wtime() - start_time;
	cout << "result without omp: " << result1 << endl;
	cout << "time1: " << time1 << endl;

	int result2, result3;
	double time2, time3;
	for (int i = 2; i <= 16; i *= 2)
	{
		cout << "Number threads: " << i << endl;
		start_time = omp_get_wtime();
		result2 = get_max(array, n, 1, i);
		time2 = omp_get_wtime() - start_time;

		start_time = omp_get_wtime();
		result3 = get_max(array, n, 2, i);
		time3 = omp_get_wtime() - start_time;



		cout << "result with critical: " << result2 << endl;
		cout << "time: " << time2 << endl;

		cout << "result with reduction: " << result2 << endl;
		cout << "time: " << time3 << endl;
	}


	return 0;
}
