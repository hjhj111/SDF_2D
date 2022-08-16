#include"SDF_2D.h"

int main()
{
	int I = 20;
	int J = 20;
	vector<vector<double>> test = vector<vector<double>>(I, vector<double>(J, -1));
	vector<vector<vec2>> test_targets = vector<vector<vec2>>(I, vector<vec2>(J, { -1,-1 }));
	test[5][5] = 0;
	test[5][4] = 0;
	DiscreteSDF2D(test, I, J,test_targets);

	for (int i = 0; i < I; i++)
	{
		printf("\n");
		for (int j = 0; j < J; j++)
		{
			printf("%f  ", test[i][j]);
		}
	}
	printf("\n");
	for (int i = 0; i < I; i++)
	{
		printf("\n");
		for (int j = 0; j < J; j++)
		{
			printf("%d, %d   ", test_targets[i][j].x, test_targets[i][j].y);
		}
	}
	return 0;
}