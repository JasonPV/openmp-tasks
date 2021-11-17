#include <omp.h>
#include <iostream>
#include <cmath>


using namespace std;

double f(double x){
return sin(x)* cos(x);
}


double integral(double a, double b, int N, bool Parallel, int num_threads = 1){
double res = 0.0;
double h = (b-a)/N;
	omp_set_num_threads(num_threads);
	#pragma parallel for reduction(+:res) if(Parallel)
	for(int i = 0; i < N; i++)
	      res += f(a + i*h)*h;
	
return res;
}


double test_reduction(double a, double b, int N){
	double res;
	double h = (b-a)/N;
	for (int i = 2; i < 16; i *= 2){
		cout << "Threads num: " << i << endl;
		omp_set_num_threads(i);
		
		res = 0.0;
		double start_time = omp_get_wtime();
		#pragma parallel for reduction(+:res)
		for(int i = 0; i < N; i++)
      			res += f(a + i*h)*h;
		double end_time = omp_get_wtime() - start_time;
		cout << "Result with reduction: " << res << endl;
		cout << "Time with reduciton: " << end_time << endl << endl;

		res = 0.0;
		start_time = omp_get_wtime();
		#pragma omp parallel for shared(res)
		for(int i = 0; i < N; i++)
		{
			#pragma omp critical
      			res += f(a + i*h)*h;
		}
		end_time = omp_get_wtime() - start_time;
		cout << "Result with critical: " << res << endl;
		cout << "Time with critical: " << end_time << endl << endl;
		
		res = 0.0;
		start_time = omp_get_wtime();
		#pragma omp parallel for shared(res)
			for(int i = 0; i < N; i++)
			{
				#pragma omp atomic
      				res += f(a + i*h)*h;
			}
		end_time = omp_get_wtime() - start_time;
		cout << "Result with atomic: " << res << endl;
		cout << "Time with atomic: " << end_time << endl << endl;
		
		omp_lock_t lock;
		omp_init_lock(&lock);
		res = 0.0;
		start_time = omp_get_wtime();
		#pragma omp parallel for shared(res)
			for(int i = 0; i < N; i++)
			{
				omp_set_lock(&lock);
      				res += f(a + i*h)*h;
				omp_unset_lock(&lock);
			}
		end_time = omp_get_wtime() - start_time;
		cout << "Result with lock: " << res << endl;
		cout << "Time with lock: " << end_time << endl << endl;


}


}


int main(){
double a, b;
int N;
cout << "Input a and b: ";
cin >> a >> b;
cout << "Input n: ";
cin >> N;

double start_time = omp_get_wtime();
double result = integral(a, b, N, false);
double time = omp_get_wtime() - start_time;
cout << "result without omp: " << result << endl;
cout << "time: " << time << endl;

for (int i = 2; i <= 16; i *= 2)
{
	cout << "Number threads: " << i << endl;
	start_time = omp_get_wtime();
	result = integral(a, b, N, true, i);
	time = omp_get_wtime() - start_time;
	cout << "result with omp: " << result << endl;
	cout << "time: " << time << endl;

//test_reduction(a, b, N);
return 0;
}
