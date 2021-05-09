// Copyright 2020 Vasilache Raluca
#include <stdio.h>
#include <stdlib.h>

// functie de hash
unsigned int hash_function_int(void *a) {
    /*
     * Credits: https://stackoverflow.com/a/12996028/7883884
     */
    unsigned int uint_a = *((unsigned int *)a);

    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = (uint_a >> 16u) ^ uint_a;
    return uint_a;
}
// functie care returneaza maximul dintre doua numere
int get_max(int a, int b)
{
	if(a > b)
	{
		return a;
	}
	return b;
}
// functie care calculeaza suma Z
double z_calc(int *M, int m)
{
	double s;
	double z = 0;
	for(int i = 1; i <= m; i++)
	{
		s = 1 << M[i];
		s = 1/s;
		z += s;
	}
	z = 1/z;
	return z;
}
// functie care citeste datele din fisier si
// completeaza vectorul M
void get_data(FILE *fin, int *M)
{
	int nr, j, zeros, i, x;
	unsigned int hash;
	while(fscanf(fin, "%d", &nr) != EOF)
	{
		// aplicarea functiei de hash
		hash = hash_function_int(&nr);
		j = hash >> (32-11);
		zeros = 0;
		// urmatoarele peratii se efectueaza
		// pe ultimii 21 de biti
		i = 32 - 11;
		while(i != 0)
		{
			// daca bitul este 0
			if( hash %2 == 0)
			{
				zeros++;
			}
			// daca bitul este 1
			// se reseteaza numarul de 0 gasiti
			else
			{
				zeros = 0;
			}
			hash = hash >> 1;
			i--;
		}

		// alegerea maximului si completarea lui M
		x = get_max(M[j], zeros);
		M[j] = x;
	}
}
int main(int argc, char** argv)
{
	// in linia de comanda trebuie introdusi doi parametri
	if(argc < 2)
	{
		printf("Introduceti numele fisierului!\n");
	}

	FILE *fin = fopen(argv[1], "r");

	// calculare m
	int m = 1<<11;
	// alocare si initializare M
	int *M = calloc(m+1, sizeof(int));
	if( M == NULL)
	{
		printf("Eroare la alocarea memoriei!\n");
	}
	// completare M
	get_data(fin, M);
	// calculare Z
	double Z = z_calc(M, m);
	// calculare alfa
	double alfa = 0.7213*(1+1.079/m);
	// calculare E
	int E = 2*alfa*m*m*Z;
	printf("%d\n", E);

	// eliberare memorie si inchidere fisier
	free(M);
	fclose(fin);
	return 0;
}
