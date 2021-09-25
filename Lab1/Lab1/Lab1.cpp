// Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <omp.h>


void printArray(float const *const *const arr, int const m, int const n)
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
        {
            std::cout << "  " << arr[i][j];
        }
        std::cout << "\n";
    }
}

void printVector(float const *const vector, int const m)
{
    for (int i = 0; i < m; i++)
    {
        std::cout << "  " << vector[i] << "\n";
    }
}


/// <summary>
/// Возвращает двумерный массив со случайными целыми числами в диапазоне [-10; 10].
/// </summary>
/// <param name="m"> Число строк </param>
/// <param name="n"> Число столбцов </param>
/// <returns> Указатель на массив </returns>
float** initRandom2DArray(int const m, int const n)
{
    float** arr = new float* [m];

    for (int i = 0; i < m; i++) {
        arr[i] = new float[n];

        for (int j = 0; j < n; j++)
        {
            arr[i][j] = rand() % 21 - 10;
        }
    }

    return arr;
}

/// <summary>
/// Возвращает вектор со случайными целыми числами в диапазоне [-10; 10].
/// </summary>
/// <param name="m"> Размерность вектора </param>
/// <returns> Указатель на вектор </returns>
float* initRandom(int const m)
{
    float* vector = new float[m];

    for (int i = 0; i < m; i++)
    {
        vector[i] = rand() % 21 - 10;
    }

    return vector;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int m, n;
    bool isPrintData = true;
    
    std::cout << "Введите размерность матрицы (m x n).\n";
    std::cout << "m = ";
    std::cin >> m;
    std::cout << "n = ";
    std::cin >> n;
    std::cout << "Размерность вектора = n (n = " << n << " )\n";
    std::cout << "Заполнение массива случайными числами...\n";

#pragma region Arrays initialization

    srand(time(0));
    float** arr = initRandom2DArray(m, n);
    float* vector = initRandom(n);
    float* resultVector = new float[m];

#pragma endregion


#pragma region Matrix product

    double singleThreadStartTime = clock();

    // Умножение в одном потоке.
    for (int i = 0; i < m; i++)
    {
        resultVector[i] = 0;
        for (int j = 0; j < n; j++)
        {
            resultVector[i] += arr[i][j] * vector[j];
        }
    }

    double singleThreadEndTime = clock() - singleThreadStartTime;
    double multiThreadStartTime = clock();

    // Умножение в m потоках openMP.
#pragma omp parallel for shared(arr, vector, resultVector, m, n)
    for (int i = 0; i < m; i++)
    {
        resultVector[i] = 0;
        for (int j = 0; j < n; j++)
        {
            resultVector[i] += arr[i][j] * vector[j];
        }
    }

    double multiThreadEndTime = clock() - multiThreadStartTime;
    double multiThreadStartTime2 = clock();

    // Умножение в m потоках openMP с директивой firstprivate для констант (оптимизация предложена в https://docs.oracle.com/cd/E19059-01/stud.10/819-0501/7_tuning.html).
#pragma omp parallel for shared(arr, vector, resultVector) firstprivate(m, n)
    for (int i = 0; i < m; i++)
    {
        resultVector[i] = 0;
        for (int j = 0; j < n; j++)
        {
            resultVector[i] += arr[i][j] * vector[j];
        }
    }

    double multiThreadEndTime2 = clock() - multiThreadStartTime2;

#pragma endregion


    std::cout << "Single-thread, затраченное время: " << singleThreadEndTime / CLOCKS_PER_SEC << " сек.\n";
    std::cout << "Multi-thread, затраченное время: " << multiThreadEndTime / CLOCKS_PER_SEC << " сек.\n";
    std::cout << "Multi-thread + firstprivate(m, n), затраченное время: " << multiThreadEndTime2 / CLOCKS_PER_SEC << " сек.\n";

    
    std::cout << "Показать данные? (1 - да, 0 - нет)\n";
    std::cin >> isPrintData;
    if (isPrintData)
    {
        std::cout << "\nДвумерный массив:\n";
        printArray(arr, m, n);
        std::cout << "\nВектор:\n";
        printVector(vector, n);
        std::cout << "Результат умножения:\n";
        printVector(resultVector, m);
    }
    
    std::cin;
}