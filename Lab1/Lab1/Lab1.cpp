// Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <omp.h>

/// <summary>
/// Возвращает двумерный массив со случайными целыми числами в диапазоне [-10; 10].
/// </summary>
/// <param name="m"> Число строк </param>
/// <param name="n"> Число столбцов </param>
/// <returns> Указатель на массив </returns>
float** initRandom2DArray(int m, int n)
{
    float** arr = new float* [m];

    std::cout << "\nДвумерный массив:\n";

    for (int i = 0; i < m; i++) {
        arr[i] = new float[n];

        for (int j = 0; j < n; j++)
        {
            arr[i][j] = rand() % 21 - 10;
            std::cout << "  " << arr[i][j];
        }
        std::cout << "\n";
    }

    return arr;
}

/// <summary>
/// Возвращает вектор со случайными целыми числами в диапазоне [-10; 10].
/// </summary>
/// <param name="m"> Размерность вектора </param>
/// <returns> Указатель на вектор </returns>
float* initRandom(int m)
{
    float* vector = new float[m];

    std::cout << "\nВектор:\n";

    for (int i = 0; i < m; i++)
    {
        vector[i] = rand() % 21 - 10;
        std::cout << "  " << vector[i] << "\n";
    }

    return vector;
}

void printVector(float* vector, int m)
{
    for (int i = 0; i < m; i++)
    {
        std::cout << "  " << vector[i] << "\n";
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int m, n;
    std::cout << "Введите размерность матрицы (m x n).\n";
    std::cout << "m = ";
    std::cin >> m;
    std::cout << "n = ";
    std::cin >> n;
    std::cout << "Размерность вектора = m (m = " << m << " )\n";

    srand(time(0));
    float** arr = initRandom2DArray(m, n);
    float* vector = initRandom(m);
    float* resultVector = new float[m];

    double startTime = clock();

#pragma omp parallel for shared(arr, vector, resultVector, n, m) // попробовать firstprivate(n, m), согласно https://docs.oracle.com/cd/E19059-01/stud.10/819-0501/7_tuning.html
    for (int i = 0; i < m; i++)
    {
        resultVector[i] = 0;
        for (int j = 0; j < n; j++)
        {
            resultVector[i] += arr[i][j] * vector[j];
        }
    }

    double endTime = clock();
    double resultTime = (endTime - startTime) / CLOCKS_PER_SEC;


    std::cout << "Результат:\n";
    printVector(resultVector, m);
    std::cout << "Затраченное время: " << resultTime << " сек.";
    std::cin;
}