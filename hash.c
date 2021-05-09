// Copyright 2020 Vasilache Raluca
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct hashtable
{
	char key[100];
	int value;
};

// functia de hash
unsigned int hash_function_string(void *a) {
    /*
     * Credits: http://www.cse.yorku.ca/~oz/hash.html
     */
    unsigned char *puchar_a = (unsigned char*) a;
    __int64_t hash = 5381;
    int c;

    while ((c = *puchar_a++))
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

    return hash;
}
// functia creeaza, inizializeaza si returneaza
// un array de structuri de tip hashtable
struct hashtable *create_ht(int size)
{
	// dimensiunea array-ului trebuie sa fie >= 1
	if(size  < 1)
	{
		return NULL;
	}
	// alocare array de structuri
	struct hashtable *ht = malloc(size*sizeof(struct hashtable));
	if(ht == NULL)
	{
		printf("Eroare la alocare!\n");
		return NULL;
	}
	return ht;
}
void init_ht(struct hashtable *ht, int size)
{
	// initializare variabile din fiecare structura
	for(int i = 0; i < size; i++)
	{
		ht[i].value = 0;
		snprintf(ht[i].key, strlen("\0") + 1, "%s", "\0");
	}
}
void insert_ht(struct hashtable *ht, char *key, int size)
{
	int index = hash_function_string(key)%size;

	// daca pe pozitia index a fost introdus deja string-ul
	if( ht[index].value == 0)
	{
		snprintf(ht[index].key, strlen(key) + 1 , "%s", key);
		ht[index].value++;
	}
	else if (strcmp(ht[index].key, key) == 0)
	{
		ht[index].value++;
	}
	// daca pozitia index este libera
	// daca se genereaza o coliziune
	else
	{
		int ok = 0;
		int pos = 0;
		// verificam daca string-ul nu a fost deja adaugat
		// pe o pozitie > index;
		// se retine in acelasi timp prima pozitie disponibila
		// pentru cazul in care string-ul nu se gaseste in hashtable
		for(int i = index; i < size; i++)
		{
			if(strcmp(ht[i].key, key) == 0)
			{
				ht[i].value++;
				ok = 1;
			}
			if(pos == 0)
			{
				if(ht[i].value == 0)
				{
					pos = i;
				}
			}
		}
		// verificam daca string-ul nu a fost deja adaugat
		// pe o pozitie < index
		if(ok == 0)
		{
			for(int i = 0; i < index; i++)
			{
				if(strcmp(ht[i].key, key) == 0)
				{
					ht[i].value++;
					ok = 1;
				}
				if(pos == 0)
				{
					if(ht[i].value == 0)
					{
						pos = i;
					}
				}
			}
		}

		// daca string-ul nu s-a gasit in hashtable
		// se adauga pe prima pozitie disponibila
		if(ok == 0)
		{
			snprintf(ht[pos].key, strlen(key) + 1 , "%s", key);
			ht[pos].value++;
		}
	}
}
int main()
{
	int size  = 0;
	char var[100];

	// aflare numar de intrari din fisier
	while(fscanf(stdin, "%s", var) != EOF)
	{
		size++;
	}
	// repozitionare cursor la inceputul fisierului
	fseek(stdin, 0, SEEK_SET);
	// creare hashtable
	struct hashtable *ht = create_ht(size);
	init_ht(ht, size);
	// citirea stringurilor si introducerea lor in hashtable
	while(fscanf(stdin, "%s", var) != EOF)
	{
		insert_ht(ht, var, size);
	}
	// afisare stringuri si frecventa lor de aparitie
	for(int i = 0 ; i < size; i++)
	{
		if(ht[i].value != 0)
		{
			printf("%s %d\n", ht[i].key, ht[i].value);
		}
	}
	// eliberare memorie hashtable
	free(ht);
}
