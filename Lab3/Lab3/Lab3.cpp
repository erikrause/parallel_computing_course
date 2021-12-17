#include <iostream>
#include <omp.h>
#include "windows.h"

omp_lock_t lock;

void barrier()
{
	int current_thread;
#pragma omp parallel private(current_thread)
	{
		current_thread = omp_get_thread_num();

		std::cout << "Сообщение 1\n";
		std::cout << "Сообщение 2\n";


#pragma omp barrier
		std::cout << "Сообщение 3\n";
	}
}

void barrier_via_lock()
{
	int current_thread;
	int num_threads;

	omp_init_lock(&lock);
	int lock_count = 0;


#pragma omp parallel private(current_thread, num_threads)
	{
		current_thread = omp_get_thread_num();
		num_threads = omp_get_num_threads();

		std::cout << "Сообщение 1\n";
		std::cout << "Сообщение 2\n";


		// Barrier:
		omp_set_lock(&lock);
		lock_count++;
		omp_unset_lock(&lock);

		while (lock_count < num_threads)
		{
			//std::cout << "Секция закрыта, поток №" << current_thread << "\n";
			Sleep(5);
		}

		std::cout << "Сообщение 3\n";
	}

	omp_destroy_lock(&lock);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	std::cout << "Original barrier:\n";
	barrier();

	std::cout << "\n\nBarrier implementation using lock:\n";
	barrier_via_lock();
}