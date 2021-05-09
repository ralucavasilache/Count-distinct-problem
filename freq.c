// Copyright 2020 Vasilache Raluca
#include <stdio.h>
#include <stdlib.h>
#define NMAX 2000001

int main()
{
	// alocare array initializat cu 0
	int *freq_arr = calloc(NMAX, sizeof(int));
	int var;

	// cat timp se poate citi un numar x
	// creste numarul de aparitii a lui x
	while(fscanf(stdin, "%d", &var) != EOF)
	{
		freq_arr[var]++;
	}

	// afisare numere citite si frecventa lor de aparitie
	for(int i = 0; i < NMAX; i++)
	{
		if(freq_arr[i] != 0)
		{
			fprintf(stdout, "%d %d\n", i, freq_arr[i]);
		}
	}
	// eliberare memorie array
	free(freq_arr);
}
