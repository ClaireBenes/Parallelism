#include <iostream>
#include <thread>

#include <mutex>
#include <vector>

using std::cout;
using std::endl;

// *************** PRINT HELLO WORD ***************
void sayHello() 
{
	cout << "Hello world\n" << endl;
}
// *************** PRINT HELLO WORD ***************

// *************** MULTIPLY MATRICES ***************
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
// *************** MULTIPLY MATRICES ***************

// *************** PRINT EVEN AND ODD LIST ***************
std::mutex m;
std::condition_variable cv;

void printEven(int& number)
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(m);

		cv.wait(lock, [&number] { return number % 2 == 0 || number > 1000; });

		if (number > 1000)
			break;

		printf("Even: %d\n", number);
		++number;

		cv.notify_one();
	}
}

void printOdd(int& number)
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(m);

		cv.wait(lock, [&number] { return number % 2 != 0 || number > 1000; });

		if (number > 1000)
			break;

		printf("Odd: %d\n", number);
		++number;

		cv.notify_one();
	}
}
// *************** PRINT EVEN AND ODD LIST ***************

float SumSequential(std::vector<float> elements)
{
	float sum = 0;
	for (auto el : elements) 
	{
		sum += el;
	}

	return sum;
}

float SumThreadLocal(const std::vector<float>& elements, int m)
{
	std::vector<std::thread> threads;
	std::vector<float> localSums(m, 0.0f);

	int chunkSize = elements.size() / m;

	for (int i = 0; i < m; ++i)
	{
		int start = i * chunkSize;
		int end = (i == m - 1) ? elements.size() : start + chunkSize;

		threads.emplace_back([&, i, start, end]()
			{
				float localSum = 0.0f;
				for (int j = start; j < end; ++j)
					localSum += elements[j];

				localSums[i] = localSum;
			});
	}

	for (auto& t : threads)
		t.join();

	float totalSum = 0.0f;
	for (float s : localSums)
		totalSum += s;

	return totalSum;
}

float globalSum = 0.0f;
std::mutex sumMutex;

void SumWithMutexWorker(const std::vector<float>& elements, int start, int end)
{
	for (int i = start; i < end; ++i)
	{
		std::lock_guard<std::mutex> lock(sumMutex);
		globalSum += elements[i];
	}
}

float SumWithMutex(const std::vector<float>& elements, int m)
{
	globalSum = 0.0f;

	std::vector<std::thread> threads;
	int chunkSize = elements.size() / m;

	for (int i = 0; i < m; ++i)
	{
		int start = i * chunkSize;
		int end = (i == m - 1) ? elements.size() : start + chunkSize;

		threads.emplace_back(SumWithMutexWorker,
			std::cref(elements), start, end);
	}

	for (auto& t : threads)
		t.join();

	return globalSum;
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


	// *************** PRINT EVEN AND ODD LIST ***************
	//int number = 0;

	//std::thread t1{ printEven , std::ref(number) };
	//std::thread t2{ printOdd , std::ref(number) };

	//t1.join();
	//t2.join();
	// *************** PRINT EVEN AND ODD LIST ***************
	

	std::vector<float> theList(1000);
	for (int i = 0; i < theList.size(); ++i) 
	{
		theList[i] = 1.0f;
	}

	int subTables = 4;

	printf("Sequential sum: %.1f\n", SumSequential(theList));
	printf("Thread-local sum: %.1f\n", SumThreadLocal(theList, subTables));
	printf("Mutex sum: %.1f\n", SumWithMutex(theList, subTables));


	return 0;
}

