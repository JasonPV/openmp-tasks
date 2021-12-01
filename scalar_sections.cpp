#include <iostream>
#include <fstream>
#include <stdio.h>
#include <omp.h>


using namespace std;
#define threads 8


long long scalar(long long n, long long *array1, long long *array2, bool Parallel){
        long long result = 0;
        #pragma omp parallel for reduction(+:result) num_threads(threads-2) if(Parallel)
        for (int i = 0; i < n; ++i)
                result += (array1[i] * array2[i]);
        return result;
}


int main(){
srand(time(0));
long long n, m;
cout << "Input number of vectors and number of elements" << endl;
cin >> n >> m;
long long** array = new long long*[n];
for (int i = 0; i < n; i++)
        array[i] = new long long[m];
for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
                array[i][j] = rand() % 1000 + 1;

ofstream fout("arrays.txt", ios::out);
fout << n << " " << m << endl;
for (int i = 0; i < n; i++)
{
        for (int j = 0; j < m; j++)
                fout << array[i][j] << " ";
        fout << endl;
}
fout.close();

ifstream fin("arrays.txt", ios::in);
fin >> n >> m;
long long** array_in = new long long*[n];
long long* results = new long long[n/2];
for (int i = 0; i < n; i++)
        array_in[i] = new long long[m];

omp_set_num_threads(threads);
double start_time = omp_get_wtime();
#pragma omp parallel sections
{
#pragma omp section
{

        for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                        fin >> array_in[i][j];
}

#pragma omp section
{
        long long k = 0;
        while (k < n)
        {
        if (array_in[k] and array_in[k+1])
        {
                results[k/2] = scalar(m, array_in[k], array_in[k+1], true);
                k += 2;
        }

        }


}
}
double end_time = omp_get_wtime() - start_time;
fin.close();

//for (int i = 0; i < n/2 ; i++)
//      cout << i << ": " << results[i];
cout << " Num_threads: " << threads << endl;
cout << "Time: " << end_time << endl;

return 0;
}
