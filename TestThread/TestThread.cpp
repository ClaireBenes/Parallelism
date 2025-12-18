#include <iostream>
#include <thread>

#include <exception>
#include <memory>
#include <mutex>

using std::cout;
using std::endl;

std::mutex m;

void sayHello() 
{
	cout << "Hello world\n" << endl;
}

void toString(float mat[4])
{
	printf("(X = %.0f), (Y = %.0f), (Z = %.0f), (W = %.0f)\n", mat[0], mat[1], mat[2], mat[3]);
}

void ComputeMatriceValue(float& out, float val1, float val2, float val3, float val4) 
{
	out = val1 * val2 + val3 * val4;
	return;
}

float* multMatrices(float mat1[4], float mat2[4])
{
	float newMat[4];
	newMat[0] = mat1[0] * mat2[0] + mat1[1] * mat2[2];
	newMat[1] = mat1[0] * mat2[1] + mat1[1] * mat2[3];
	newMat[2] = mat1[2] * mat2[0] + mat1[3] * mat2[2];
	newMat[3] = mat1[1] * mat2[2] + mat1[3] * mat2[3];

	toString(newMat);
	return newMat;
}

void printEven(int& number)
{
	while (true)
	{
		m.lock();

		if (number > 1000)
		{
			m.unlock();
			break;
		}

		if (number % 2 == 0)
		{
			printf("Even: %d\n", number);
			++number;
		}

		m.unlock();
		std::this_thread::yield(); 
	}
}

void printOdd(int& number)
{
	while (true)
	{
		m.lock();

		if (number > 1000)
		{
			m.unlock();
			break;
		}

		if (number % 2 != 0)
		{
			printf("Odd: %d\n", number);
			++number;
		}

		m.unlock();
		std::this_thread::yield();
	}
}

int main() 
{
	// *************** PRINT HELLO WORD ***************
	//std::thread t1(sayHello);
	//std::thread t2(sayHello);

	//t1.join();
	//t2.join();

	//float mat1[4] = { 1, 1, 2, 2 };
	//float mat2[4] = { 2, 2, 1, 1 };
	//float mat3[4];

	//float* newMatrice = multMatrices(mat1, mat2);
	// *************** PRINT HELLO WORD ***************

	// *************** MULTIPLY MATRICES ***************
	//float mat1[4] = { 1, 1, 2, 2 };
	//float mat2[4] = { 2, 2, 1, 1 };
	//float mat3[4];

	//std::thread Val1([&]()
	//	{
	//		(ComputeMatriceValue(mat3[0], mat1[0], mat2[0], mat1[1], mat2[2]));
	//	}		
	//);
	//std::thread Val2([&]()
	//	{
	//		(ComputeMatriceValue(mat3[1], mat1[0], mat2[1], mat1[1], mat2[3]));
	//	}
	//);
	//std::thread Val3([&]()
	//	{
	//		(ComputeMatriceValue(mat3[2], mat1[2], mat2[0], mat1[3], mat2[2]));
	//	}
	//);
	//std::thread Val4([&]()
	//	{
	//		(ComputeMatriceValue(mat3[3], mat1[1], mat2[2], mat1[3], mat2[3]));
	//	}
	//);

	//Val1.join();
	//Val2.join();
	//Val3.join();
	//Val4.join();

	//
	//float mat[4] = { mat3[0], mat3[1], mat3[2], mat3[3] };
	//toString(mat);
	// *************** MULTIPLY MATRICES ***************

	int number = 0; 
	std::thread t1([&]() 
		{ 
			printEven(number); 
			printf("Even : %i\n", number);
		}
	); 
	
	std::thread t2([&]() 
		{ 
			printOdd(number);
			printf("Odd : %i\n", number); 
		}
	); 
	
	t1.join();
	t2.join();


	//while (number < 100) 
	//{
	//	t1.join();
	//	t2.join();
	//}

	return 0;
}

