//Part of ESE_3025 program

/*As described in class, write a C-language database sorting program using
 the stdlib qsort() function.*/

/*Recall that you are to read in your data from a text file, into a database 
 variable of 100 people, with a struct as described in class.*/
 
//2020.02.02

//Aim: To use more functions and better revise other aspects such as call by value and call by refernce etc. 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//static int cmpar(const void *a, const void *b);

typedef struct
{
    char lname[15];
    char fname[15];
    char city[15];    
}database;

database list[1000];

int cmpar(const void *a, const void *b)
{
    database *pa = (database *)a;
    database *pb = (database *)b;
    return (strcmp(pa->lname, pb->lname));
}

int cmpar1(const void *a, const void *b)
{
    database *pa = (database *)a;
    database *pb = (database *)b;
    return (strcmp(pa->fname, pb->fname));
}

int cmpar2(const void *a, const void *b)
{
    database *pa = (database *)a;
    database *pb = (database *)b;
    return (strcmp(pa->city, pb->city));
}

void print(int* ppcount)
{
    for(int i = 0; i < *ppcount; ++i)
    {
        printf("%s %s %s\n", list[i].lname, list[i].fname, list[i].city);
    }
}

void read(void *pfpr, int* pcount)
{
    int i = 0;
    while(!feof(pfpr))
    {
        
        fscanf(pfpr, "%12s %12s %12s", list[i].lname, list[i].fname, list[i].city);
        ++i;
        (*pcount)++;
    }
    print(pcount);
}

void sort(int* pcount)
{
    int x;
    printf("Enter:\n1 - if you want to sort by last name\n2 - if you want to sort it by first name\n3 - if you want to sort by city\n");
    scanf("%d", &x);

    switch(x)
    {
        case 1:
            qsort(list, *pcount, sizeof(database), cmpar);
            break;
        case 2:
            qsort(list, *pcount, sizeof(database), cmpar1);
            break;
        case 3:
            qsort(list, *pcount, sizeof(database), cmpar2);
            break;
    }
    
    print(pcount);
}

void write(void* pfpw, int* pcount)
{
    for(int i = 0; i < *pcount; ++i)
    {
        fprintf(pfpw, "%s %s %s\n", list[i].lname, list[i].fname, list[i].city);
    }
}

int main(int argc, char *argv[])
{
	if(argc!= 3) 
    {
        printf("usage: e_n <infile> <outfile>\n");
        return 0;
    }
    
    char* pinfile = argv[1];
    char* poutfile = argv[2];
	
    FILE* fpr = fopen(pinfile, "r");
    if(0 == fpr)
    {
        printf("Failed to open the file %s \n", pinfile);
        return 0;
    }
    int count = 0;

    read(fpr, &count);

    sort(&count);

    FILE *fpw = fopen(poutfile, "w");
    if(0 == fpw)
    {
        printf("Failed to create the file %s \n", poutfile);
        fclose(fpr);
        return 0;
    }
    write(fpw, &count);
    
    fclose(fpr);
    fclose(fpw);
    return 0;
}
