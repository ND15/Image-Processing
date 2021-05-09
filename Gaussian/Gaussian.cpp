
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#define PI 3.1415

using namespace cv;

using namespace std;


float calcGaussMatrix(int i, int j, float sigma)
{
	float exp = expf(-((i * i + j * j) / (2 * sigma * sigma)));
	float low = float(2 * PI * sigma * sigma);
	float right = 1 / low;
	float val = right * exp;
	return val * (i + j);
}


float sum_2d(float A[][7], int n)
{
	float sum = 0.0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sum += A[i][j];
		}
	}
	return sum;
}


float sum(float B[], int n)
{
	float sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum = sum + B[i];
	}
	return sum;
}

float GaussianFilter(float *A[], float B[], float C[][9], int n, int i, int j) //x -> neighbor matrix //i -> row, j->column
{
	int index = 0;
	int k = 0;
	for (int x = i - (n) / 2; x <= i + (n / 2); x++)
	{
		int l = 0;
		for (int y = j - (n) / 2; y <= j + (n / 2); y++)
		{
			B[index] = A[x][y] * C[k][l];
			index++;
			l++;
		}
		k++;
	}
	float GaussianSum = (sum(B, n*n));
	return GaussianSum;
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

	int n = 9;
	float sigma = 7;
	float GaussianValue = 0;
	float *B = new float[n * n];
	float *C = new float[x * y];
	float *D = new float[x * y];

	float Gauss[9][9];/*= { {0,0,1,2,1,0,0},
							{0,3,13,22,13,3,0},
							{1,13,59,97,59,13,1},
							{2,22,97,159,97,22,2},
							{1,13,59,97,59,13,1},
							{0,3,13,22,13,3,0},
							{0,0,1,2,1,0,0} };

	int sum = sum_2d(Gauss, 7);*/
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Gauss[i][j] = calcGaussMatrix(i, j, sigma);
		}
	}

	int count = 0;

	for (int i = (n) / 2; i <= (n) / 2 + (x - n); i++)
	{
		for (int j = (n) / 2; j <= (n) / 2 + (y - n); j++)
		{
			GaussianValue = GaussianFilter(A, B, Gauss, n, i, j);
			C[count] = GaussianValue;
			count++;
		}
	}

	count = 0;

	for (int i = (n) / 2; i <= (n) / 2 + (x - n); i++)
	{
		for (int j = (n) / 2; j <= (n) / 2 + (y - n); j++)
		{
			A[i][j] = C[count];
			count++;
		}
	}

	int m, o;
	for (o = 0; o < x; o++)
	{
		for (m = 0; m < y; m++)
		{
			D[o*y + m] = A[o][m];
		}
	}

	for (int i = 0; i < x*y; i++)
	{
		cout << D[i] << " ";
	}

	Mat E(x, y, CV_32F);
	memcpy(E.data, D, x * y * sizeof(CV_32F));

	imwrite("Test_09.png", E);
	imshow("image", img);
	waitKey();

	return 0;
}