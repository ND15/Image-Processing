#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void BubbleSort(int n, int A[])
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (A[j] > A[j + 1])
			{
				swap(&A[j], &A[j + 1]);
			}
		}
	}
}


int updateElments(int *A[], int B[], int x, int i, int j)
{
	int o = 0;
	for (int a = i - (x) / 2; a <= i + (x) / 2; a++)
	{
		for (int b = j - (x) / 2; b <= j + (x) / 2; b++)
		{
			B[o] = A[a][b];
			o++;
		}
	}
	BubbleSort(x*x, B);
	return B[(x*x) / 2];
}



int main()
{
	Mat dst;
	Mat img = imread("noise_test.png", 0);
	img.convertTo(dst, CV_32S);
	//cout << img;

	int x = dst.rows;
	int y = dst.cols;

	int **arrOut = new int*[x];

	for (int i = 0; i < x; i++)
	{
		arrOut[i] = new int[y];
	}

	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			arrOut[i][j] = dst.at<int>(i, j);
		}
	}


	int z = 11;
	int median;
	int count = 0;

	int *B = new int[z*z];
	int *C = new int[x*y];
	int *D = new int[x*y];



	for (int i = (z) / 2; i <= ((z) / 2) + (x - z); i++)
	{
		for (int j = (z) / 2; j <= ((z) / 2) + (y - z); j++)
		{
			median = updateElments(arrOut, B, z, i, j);
			C[count] = median;
			count++;
		}
	}
	count = 0;

	for (int i = (z) / 2; i <= ((z) / 2) + (x - z); i++)
	{
		for (int j = (z) / 2; j <= ((z) / 2) + (y - z); j++)
		{
			arrOut[i][j] = C[count];
			count++;
		}
	}

	int n, m;

	for (n = 0; n < x; n++)
	{
		for (m = 0; m < y; m++)
		{
			D[n*y + m] = arrOut[n][m];
		}
	}

	//for (int i = 0; i < x*y; i++)
	//{
	//	cout << D[i] << " ";
	//}

	Mat E(x, y, CV_32S);
	memcpy(E.data, D, x * y * sizeof(CV_32S));

	imwrite("noise_result.png", E);
	imshow("image", img);
	Mat img_02 = imread("noise_result.png");
	imshow("image_01", img_02);
	waitKey();

	for (int i = 0; i < x; i++) {
		delete[] arrOut[i];
	}
	delete[] arrOut;

	delete[] B;
	delete[] C;
	delete[] D;

	return 0;
}
