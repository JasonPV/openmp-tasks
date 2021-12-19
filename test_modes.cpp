#include <iostream>
#include <omp.h>


using namespace std;

void test(char c, int n, int threads){
        int buf;
        srand(time(0));
        if (c == 's')
        {
                omp_set_num_threads(threads);
                #pragma omp parallel for schedule(static)
                for (int i = 0; i < n; i++)
                {
                        if (i % 3 == 0)
                        {
                                buf = rand()%100000 + rand()%10000 + rand()%1000 + rand()%100 + rand()%10 + 1;
                        }
                        else
                                buf = rand()%1000;
                }
        }
        else if(c == 'g')
        {
                omp_set_num_threads(threads);
                #pragma omp parallel for schedule(guided)
                for (int i = 0; i < n; i++)
                {
                        if (i % 3 == 0)
                        {
                                buf = rand()%100000 + rand()%10000 + rand()%1000 + rand()%100 + rand()%10 + 1;
                        }
                        else
                                buf = rand()%1000;
                }
        }

        else if (c == 'd')
        {
                omp_set_num_threads(threads);
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < n; i++)
                {
                        if (i % 3 == 0)
                        {
                                buf = rand()%100000 + rand()%10000 + rand()%1000 + rand()%100 + rand()%10 + 1;
                        }
                        else
                                buf = rand()%1000;
                }
        }


}


int main(){
        int n = 100000000;
        double start_time, time;
        for (int j = 1; j <=8; j *=2)
        {
                cout << "******************" <<  "NUM THREADS: " << j << "*****************" << endl;

                //for (int i = 1; i < 16 ; i*=2)
                //{
                //      cout << "-------------------" << i << "---------------------" << endl;
                        start_time = omp_get_wtime();
                        test('s', n, j);
                        time = omp_get_wtime() - start_time;
                        cout << "Static: " << time << endl;
                        cout << endl;

                        start_time = omp_get_wtime();
                        test('d', n, j);
                        time = omp_get_wtime() - start_time;
                        cout << "Dynamic: " << time << endl;
                        cout << endl;

                        start_time = omp_get_wtime();
                        test('g', n, j);
                        time = omp_get_wtime() - start_time;
                        cout << "Guided: " << time << endl;
                        cout << endl;

        //}
}

        return 0;
}
