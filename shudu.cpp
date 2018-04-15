#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<malloc.h>
using namespace std;

struct Grid
{
	int col, row;
}grid[81];

FILE *a;
FILE *b;
int cout = 0;
int flag = 0;
int n = 0;
int judge = 0;
int limit = 0;

int arr[9][9];
int base[9][9];
int Judge[6][3] = { { 0,1,2 },{ 0,2,1 },{ 1,0,2 },{ 1,2,0 },{ 2,1,0 },{ 2,0,1 } };
int model[9][9] =
{
{ '3','9','4','5','7','1','6','2','8' },
{ '2','6','8','4','3','9','7','5','1' },
{ '7','5','1','8','6','2','3','9','4' },
{ '5','8','3','1','2','6','9','4','7' },
{ '9','4','7','3','5','8','1','6','2' },
{ '6','1','2','7','9','4','8','3','5' },
{ '1','3','5','9','4','7','2','8','6' },
{ '4','7','6','2','8','3','5','1','9' },
{ '8','2','9','6','1','5','4','7','3' },
};



void exchage(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

int juge(int col, int row)
{
	int temp[10];
	int row9 = row / 3 * 3;
	int col9 = col / 3 * 3;
	memset(temp, 0, sizeof(temp));
	for (int i = 0; i<9; i++)
	{
		temp[base[col][i]]++;
	}
	for (int i = 0; i<10; i++)
	{
		if (temp[i]>1)
			return 0;
	}
	memset(temp, 0, sizeof(temp));
	for (int i = 0; i<9; i++)
	{
		temp[base[i][row]]++;
	}
	for (int i = 0; i<10; i++)
	{
		if (temp[i]>1)
			return 0;
	}
	memset(temp, 0, sizeof(temp));
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			temp[base[i + col9][j + row9]]++;
		}
	}
	for (int i = 0; i<10; i++)
	{
		if (temp[i]>1)
			return 0;
	}
	return 1;
}
void Solve(int x)
{
	if (x >= limit)
	{
		judge = 1;
		return;
	}
	for (int i = 1; i <= 9 && !judge; i++)
	{
		base[grid[x].col][grid[x].row] = i;
		if (juge(grid[x].col, grid[x].row))
		{
			Solve(x + 1);
		}
	}
}
int main(int argc,char* argv[])
{
	if (strcmp(argv[1], "-c") == 0)
	{
		int len = strlen(argv[2]);
		a = fopen("shuduku.txt", "w");
		for (int i = 0; i < len; i++)
		{
			if (argv[2][i] >= '0'&&argv[2][i] <= '9')
				continue;
			else
			{
				printf("Wrong\n");
				return 0;
			}
		}
		for (int i = 0; i < len; i++)
		{
			n *= 10;
			n += argv[2][i] - '0';
		}
		int modelarr[8] = { '1','2','4','5','6','7','8','9', };
		int start = 7, cur = 0, changeads;
		while (start != 0 && !flag)
		{
			cur = start;
			start--;
			if (modelarr[cur] >modelarr[start])
			{
				changeads = 7;
				while (modelarr[start] >= modelarr[changeads])
					changeads--;
				exchage(modelarr[start], modelarr[changeads]);
				for (int i = start + 1, j = 7; i < j; i++, j--)
				{
					exchage(modelarr[i], modelarr[j]);
				}
				start = 7;
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						int temp = model[i][j]-'0';
						if (temp == 3)
						{
							model[i][j] = '3';
							arr[i][j] = '3';
							continue;
						}
						else if (temp>3)
						{
							model[i][j] = modelarr[temp - 2];
							arr[i][j] = modelarr[temp - 2];
						}
						else
						{
							model[i][j] = modelarr[temp - 1];
							arr[i][j] = modelarr[temp - 1];
						}
					}
				}
				for (int i = 0; i < 6 && !flag; i++)
				{
					for (int i = 0; i < 9; i++)
	              {
		             arr[3][i] = model[Judge[i][0]+ 3][i];
		             arr[3 + 1][i] = model[Judge[i][1] + 3][i];
		             arr[3 + 2][i] = model[Judge[i][2] + 3][i];
	              }
					for (int j = 0; j < 6 && !flag; j++)
					{
						for (int i = 0; i < 9; i++)
	                  {
		                arr[6][i] = model[Judge[j][0] + 6][i];
		                arr[6 + 1][i] = model[Judge[j][1] + 6][i];
		                arr[6 + 2][i] = model[Judge[j][2] + 6][i];
	                  }
						for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j <8)
			{
				fputc(arr[i][j] , a);
				fputc(' ', a);
			}
			else
			{
				fputc(arr[i][j], a);
				fputc('\n', a);
			}
		}
	}
	cout++;
	if (cout<n)
	{
		fputc('\n', a);
	}
	else
	{
		flag = 1;
	}
					}
				}
			}
			if (start == 0 && !flag)
				break;
		}
		fclose(a);
		return 0;
	}
	else if (strcmp(argv[1], "-s") == 0)
	{
		a = fopen("shuduku.txt", "w");
		b = fopen(argv[2], "r");
		int temp;
		int num = 0, t = 0;
		while (~fscanf(b, "%d", &temp))
		{
			int x = num / 9;
			int y = num % 9;
			num++;
			base[x][y] = temp;
			if (temp == 0)
			{
				grid[limit].col = x;
				grid[limit].row = y;
				limit++;
			}
			if (num == 81)
			{
				num = 0;
				Solve(0);
				limit = 0;
				judge = 0;
				if (t != 0)
				{
					fprintf(a, "\n");
				}
				t++;
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						if (j <8)
						{
							fprintf(a, "%d ", base[i][j]);
						}
						else
						{
							fprintf(a, "%d\n", base[i][j]);
						}
					}
				}
			}
		}
		fclose(a);
		fclose(b);
		return 0;
	}
}
