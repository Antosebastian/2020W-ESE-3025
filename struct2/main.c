#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static int cmpar(const void *a, const void *b);

typedef struct
{
    char lname[15];
    char fname[15];
    char city[15];    
}database;

int cmpar(const void *a, const void *b)
{
    database *pa = (database *)a;
    database *pb = (database *)b;
    return (strcmp(pa->lname, pb->lname));
}


database list[1000];

int main(int argc, char *argv[])
{
	if(argc!= 3) 
    {
        printf("usage: struct_ <infile> <outfile>\n");
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
    int i = 0;
    while(!feof(fpr))
    {
        
        fscanf(fpr, "%12s %12s %12s", list[i].lname, list[i].fname, list[i].city);
        ++i;
    }
    for(int i = 0; i < 8; ++i)
    {
        printf("%s %s %s\n", list[i].lname, list[i].fname, list[i].city);
    }
    qsort(list, 8, sizeof(database), cmpar);

    for(int i = 0; i < 8; ++i)
    {
        printf("%s %s %s\n", list[i].lname, list[i].fname, list[i].city);
    }
    
    FILE *fpw = fopen(poutfile, "w");
    if(0 == fpw)
    {
        printf("Failed to create the file %s \n", poutfile);
        fclose(fpr);
        return 0;
    }
    for(int i = 0; i < 8; ++i)
    {
        fprintf(fpw, "%s %s %s\n", list[i].lname, list[i].fname, list[i].city);
    }
    
    return 0;
}

