#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

float calcSum(float D[][3], int n)
{
	float sum = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sum += D[i][j];
		}
	}
	return sum;
}


void meanFilter(float *A[], float *B[], float D[][3], int row, int col, int n)
{
	float divisor = calcSum(D, n);

	int i = 0, j = 0;
	if (i == 0)
	{
		B[i][i] = (A[i][j] * D[0][0] + A[i][j + 1] * D[0][1] + A[i][j + 2] * D[0][2] + A[i + 1][j] * D[1][0] + A[i + 1][j + 1] * D[1][1] + A[i + 1][j + 2] * D[1][2] + A[i + 2][j] * D[2][0] + A[i + 2][j + 1] * D[2][1] + A[i + 2][j + 2] * D[2][2]) / divisor;
	}

	j = 0;
	i = row - 1;
	if (i == row - 1)
	{
		B[i][i] = (A[i - 2][j] * D[0][0] + A[i - 2][j + 1] * D[0][1] + A[i - 2][j + 2] * D[0][2] + A[i - 1][j] * D[1][0] + A[i - 1][j + 1] * D[1][1] + A[i - 1][j + 2] * D[1][2] + A[i][j] * D[2][0] + A[i][j + 1] * D[2][1] + A[i][j + 2] * D[2][2]) / divisor;
	}

	i = 0;
	j = col - 1;
	if (i == 0)
	{
		B[i][j] = (A[i][j - 2] * D[0][0] + A[i][j - 1] * D[0][1] + A[i][j] * D[0][2] + A[i + 1][j - 2] * D[1][0] + A[i + 1][j - 1] * D[1][1] + A[i + 1][j] * D[1][2] + A[i + 2][j - 2] * D[2][0] + A[i + 2][j - 1] * D[2][1] + A[i + 2][j] * D[2][2]) / divisor;
	}

	i = row - 1;
	j = 0;
	if (i == row - 1)
	{
		B[i][j] = (A[i - 2][j] * D[0][0] + A[i - 2][j + 1] * D[0][1] + A[i - 2][j + 2] * D[0][2] + A[i - 1][j] * D[1][0] + A[i - 1][j + 1] * D[1][1] + A[i - 1][j + 2] * D[1][2] + A[i][j] * D[2][0] + A[i][j + 1] * D[2][1] + A[i][j + 2] * D[2][2]) / divisor;
	}

	i = 0;
	for (int j = 1; j < col - 1; j++)
	{
		B[i][j] = (A[i][j - 1] * D[0][0] + A[i][j] * D[0][1] + A[i][j + 1] * D[0][2] + A[i + 1][j - 1] * D[1][0] + A[i + 1][j] * D[1][1] + A[i + 1][j + 1] * D[1][2] + A[i + 2][j - 1] * D[2][0] + A[i + 2][j] * D[2][1] + A[i + 2][j + 1] * D[2][2]) / divisor;
	}

	i = row - 1;
	for (int j = 1; j < col - 1; j++)
	{
		B[i][j] = (A[i][j - 1] * D[0][0] + A[i][j] * D[0][1] + A[i][j + 1] * D[0][2] + A[i - 1][j - 1] * D[1][0] + A[i - 1][j] * D[1][1] + A[i - 1][j + 1] * D[1][2] + A[i - 2][j - 1] * D[2][0] + A[i - 2][j] * D[2][1] + A[i - 2][j + 1] * D[2][2]) / divisor;
	}

	j = 0;
	for (int i = 1; i < row - 1; i++)
	{
		B[i][j] = (A[i - 1][j] * D[0][0] + A[i - 1][j + 1] * D[0][1] + A[i - 1][j + 2] * D[0][2] + A[i][j] * D[1][0] + A[i][j + 1] * D[1][1] + A[i][j + 2] * D[1][2] + A[i + 1][j] * D[2][0] + A[i + 1][j + 1] * D[2][1] + A[i + 1][j + 2] * D[2][2]) / divisor;
	}

	j = col - 1;
	for (int i = 1; i < row - 1; i++)
	{
		B[i][j] = (A[i - 1][j - 2] * D[0][0] + A[i - 1][j - 1] * D[0][1] + A[i - 1][j] * D[0][2] + A[i][j - 2] * D[1][0] + A[i][j - 1] * D[1][1] + A[i][j] * D[1][2] + A[i + 1][j - 2] * D[2][0] + A[i + 1][j - 1] * D[2][1] + A[i + 1][j] * D[2][2]) / divisor;
	}

	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < col - 1; j++)
		{
			B[i][j] = (A[i - 1][j - 1] * D[0][0] + A[i - 1][j] * D[0][1] + A[i - 1][j + 1] * D[0][2] + A[i][j - 1] * D[1][0] + A[i][j] * D[1][1] + A[i][j + 1] * D[1][2] + A[i + 1][j - 1] * D[2][0] + A[i + 1][j] * D[2][1] + A[i + 1][j + 1] * D[2][2]) / divisor;
		}
	}
}

int main()
{
	Mat img = imread("Test.png",0);
	Mat dst;
	img.convertTo(dst, CV_32F);

	int row = dst.rows;
	int col = dst.cols;

	float **A = new float*[row];
	for (int i = 0; i < row; i++)
	{
		A[i] = new float[col];
	}
	
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			A[i][j] = dst.at<float>(i, j);
		}
	}

	float **B = new float*[row];
	for (int i = 0; i < row; i++)
	{
		B[i] = new float[col];
	}


	int n = 3;

	float *C = new float[row*col];

	float D[3][3] = { {0,1,0},{1,4,1},{0,1,0} };

	meanFilter(A, B, D, row, col, n);

	int m, o;
	for (o = 0; o < row; o++)
	{
		for (m = 0; m < col; m++)
		{
			C[o*col + m] = B[o][m];
		}
	}

	Mat E(row, col, CV_32F);
	memcpy(E.data, C, row * col * sizeof(CV_32F));

	imwrite("Test_05.png", E);
	imshow("image", img);

	Mat img_02 = imread("Test_05.png");
	imshow("Result", img_02);
	waitKey();


	return 0;
}