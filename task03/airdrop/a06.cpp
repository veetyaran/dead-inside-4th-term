#include <stdio.h>
#include <time.h>
#include "zapr.h"

int main(int argc, char *argv[])
{
	char* s = nullptr, *t = nullptr;
	char* ina = nullptr, *oub = nullptr;
	int task = 6;
	double time = 0.0;
	int res = 0;
	if(argc!= 5)
	{
		printf("Usage: %s infile outfile s t\n", argv[0]);
		return 0;
	}
	ina = argv[1];
	oub = argv[2];
	s = argv[3];
	t = argv[4];

	FILE* in = fopen(ina, "rt");
	if(!in)
	{
		printf("ERROR: Cannot open file\n");
		return 0;
	}

	FILE* out = fopen(oub, "wt");
	if(!out)
	{
		fclose(in);
		printf("ERROR: Cannot open file\n");
		return 0;
	}

	zapr A;

	A.kraft(task, s, t);
	time = clock();
	res = A.real(in, out);
	time = (clock() - time)/CLOCKS_PER_SEC;
	fclose(in);
	fclose(out);
	printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, time);

	return 0;
}
