#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

float maxElement(float B[], int n)
{
	float max = B[0];
	for (int i = 1; i < n; i++)
	{
		if (B[i] > max)
		{
			max = B[i];
		}
	}
	return max;
}

float conservativeSmoothiing(float *A[], float B[], int n, int i, int j)
{
	int index = 0;
	for (int x = i - n / 2; x <= i + n / 2; x++)
	{
		for (int y = j - n / 2; y <= j + n / 2; y++)
		{
			if (x == i && y == j)
			{
				continue;
			}
			B[index] = A[x][y];
			index++;
		}
	}
	float val = maxElement(B, n*n);
	return val;
}

int main()
{
	Mat dst;
	Mat img = imread("Test.png", 0);
	img.convertTo(dst, CV_32F);

	int x = dst.rows;
	int y = dst.cols;

	float **A = new float*[x];

	for (int i = 0; i < x; i++)
	{
		A[i] = new float[y];
	}

	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			A[i][j] = dst.at<float>(i, j);
		}
	}

	//Neighbour matrix size
	int n = 7;
	float *B = new float[n*n];
	float *C = new float[x*y];
	float *D = new float[x*y];

	float cons = 0;
	int count = 0;
	for (int i = n / 2; i <= n / 2 + (x - n); i++)
	{
		for (int j = n / 2; j <= n / 2 + (y - n); j++)
		{
			cons = conservativeSmoothiing(A, B, n, i, j);
			C[count] = cons;
			count++;
		}
	}

	count = 0;
	for (int i = n / 2; i <= n / 2 + (x - n); i++)
	{
		for (int j = n / 2; j <= n / 2 + (y - n); j++)
		{
			A[i][j] = C[count++];
		}
	}

	//test matrix
	/*int A[5][5] = { {1, 2, 3, 4, 8},
					{5, 6, 7, 8, 9},
					{9, 10, 11, 12, 10},
					{5, 6, 7, 8, 9},
					{1, 2, 3, 4, 8} };*/

	int o, m;

	for (o = 0; o < x; o++)
	{
		for (m = 0; m < y; m++)
		{
			D[o*y + m] = A[o][m];
		}
	}

	//for (int i = 0; i < x*y; i++)
	//{
	//	cout << D[i] << " ";
	//}

	Mat E(x, y, CV_32F);
	memcpy(E.data, D, x * y * sizeof(CV_32F));

	imwrite("noise_result_02.png", E);
	imshow("image", img);
	Mat img_02 = imread("noise_result_02.png");
	imshow("image_01", img_02);
	waitKey();

	for (int i = 0; i < x; i++) {
		delete[] A[i];
	}
	delete[] A;

	delete[] B;
	delete[] C;
	delete[] D;

	return 0;
}