#pragma optimize( "", off)
#include <iostream>
#include <omp.h>
#define M_PI 3.14159265358979323846

double f(double x)
{
    return 4 / (1 + pow(x, 2));
}

int main()
{
    setlocale(LC_ALL, "Russian");
    long numSubdivisions;
    std::cout << "Введите количество разбиений отрезка [a; b]: ";
    std::cin >> numSubdivisions;
    std::cout << "\n";

    const double A = 0.;
    const double B = 1;
    double dx = (B - A) / (float)(numSubdivisions - 1);
    double sum = (f(A) + f(B)) / 2.;


    // SINGLE THREAD:
    double singleThreadStartTime = clock();

    for (int i = 1; i < numSubdivisions - 1; i++)
    {
        double x = A + dx * (float)i;
        double f_part = f(x);
        sum += f_part;
    }
    sum *= dx;

    double singleThreadEndTime = clock() - singleThreadStartTime;
    std::cout << "Single result = " << sum << "\n";
    std::cout << "Single thread time = " << singleThreadEndTime / CLOCKS_PER_SEC << "sec.\n\n\n";




    // MULTI THREAD:
    sum = (f(A) + f(B)) / 2.;
    double multiThreadStartTime = clock();

#pragma omp parallel for default(none), shared(A, dx, numSubdivisions), reduction(+:sum)
    for (int i = 1; i < numSubdivisions - 1; i++)
    {
        double x = A + dx * (float)i;
        double f_part = f(x);
        sum += f_part;
    }
    sum *= dx;

    double multiThreadEndTime = clock() - multiThreadStartTime;
    std::cout << "Multithread result = " << sum << "\n";
    std::cout << "Multi thread time = " << multiThreadEndTime / CLOCKS_PER_SEC << "sec.\n\n\n";
}

#pragma optimize( "", on )










// Составной метод:
//int main()
//{
//    setlocale(LC_ALL, "Russian");
//
//    double a = 0.0;
//    double b = 1.0;
//    int n_steps = 8000000;
//    double length = b - a;
//    double h = length / n_steps; // step length
//
//
//    // SINGLE THREAD:
//    double singleThreadStartTime = clock();
//
//    double result = 0;
//    for (int step = 0; step < n_steps - 1; step++)
//    {
//        double x = a + h * step;
//        double delta_x = a + h * (step + 1);
//        result += ((f(x) + f(delta_x)) / 2) * (delta_x - x);
//    }
//
//    double singleThreadEndTime = clock() - singleThreadStartTime;
//    std::cout << "Multithread result = " << result << "\n";
//    std::cout << "Single thread time = " << singleThreadEndTime / CLOCKS_PER_SEC << "sec.\n\n\n";
//
//
//
//    // MULTI THREAD:
//    double multiThreadStartTime = clock();
//
//    result = 0;
//#pragma omp parallel for  shared(n_steps, a, h) reduction(+ : result)
//    for (int step = 0; step < n_steps - 1; step++)
//    {
//        double x = a + h * step;
//        double delta_x = a + h * (step + 1);
//        double step_result = ((f(x) + f(delta_x)) / 2) * (delta_x - x);
//        result += step_result;
//    }
//
//    double multiThreadEndTime = clock() - multiThreadStartTime;
//    std::cout << "Multithread result = " << result << "\n";
//    std::cout << "Multithread thread time = " << multiThreadEndTime / CLOCKS_PER_SEC << "sec.\n\n\n";
//
//
//
//    // MULTI THREAD (NUMBER OF THREADS = n_threads):
//    double multiThreadStartTime2 = clock();
//
//    int n_threads = 4;
//    int thread_n_steps = n_steps / n_threads;
//    result = 0;
//#pragma omp parallel for// reduction(+ : result)
//    for (int thread_id = 0; thread_id < n_threads; thread_id++)
//    {
//        double thread_result = 0;
//
//        double local_a = a + h * thread_n_steps * thread_id;
//
//        for (int step = 0; step < thread_n_steps; step++)
//        {
//            double x = local_a + h * step;
//            double delta_x = local_a + h * (step + 1);
//            double step_result = ((f(x) + f(delta_x)) / 2) * (delta_x - x);
//            thread_result += step_result;
//        }
//
//        result += thread_result;
//    }
//    double multiThreadEndTime2 = clock() - multiThreadStartTime2;
//    std::cout << "Multithread2 result = " << result << "\n";
//    std::cout << "Multithread2 thread time = " << multiThreadEndTime2 / CLOCKS_PER_SEC << "sec.\n";
//}
