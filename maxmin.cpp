#include <iostream>
#include <omp.h>


using namespace std;


int get_min(int* line, int m, int Parallel=false)
{
        if (Parallel)
                omp_set_nested(true);
        int min = line[0];
        #pragma parallel for if(Parallel)
        for (int i = 0; i < m; i++)
        {
                if (line[i] < min)
                        min = line[i];
        }
        return min;
}


int get_max(int** array, int n, int  m, int Parallel){
        int mx;
        int* min_of_lines = new int [n];
        omp_set_num_threads(Parallel);
        #pragma omp parallel if(Parallel)
        {
                #pragma omp for
                for (int i = 0; i < n; i++)
                        min_of_lines[i] = get_min(array[i], m);
                mx = min_of_lines[0];
                #pragma omp for reduction(max:mx)
                for (int i = 1; i < n; i++)
                        if (min_of_lines[i] > mx)
                                mx = min_of_lines[i];
        }
        return mx;
}



int main(){
        int** array;
        int n, m;
        cout << "Input n and m: ";
        cin >> n >> m;
        array = new int*[n];

        for (int i = 0; i < n; i++)
                array[i] = new int[m];

        for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                        array[i][j] = rand() % 1000 + 1;


        for (int i = 1; i <= 16; i *= 2)
        {
              double start_time = omp_get_wtime();
              int result = get_max(array, n, m, i);
              double time = omp_get_wtime() - start_time;
              cout << "Num threads: " << i << endl;
              cout << "Time: " << time << endl;
              cout << "Result: " << result << endl;
        }


        return 0;
}
      
