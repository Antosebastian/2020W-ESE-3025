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
    int count = 0;
    int i = 0;
    while(!feof(fpr))
    {
        
        fscanf(fpr, "%12s %12s %12s", list[i].lname, list[i].fname, list[i].city);
        ++i;
        count++;
    }
    
    for(int i = 0; i < count; ++i)
    {
        printf("%s %s %s\n", list[i].lname, list[i].fname, list[i].city);
    }
    
    int x;
    printf("Enter:\n1 - if you to sort by last name\n2 - if you want to sort it by first name\n3 - if you want to sort by city\n");
    scanf("%d", &x);

    switch(x)
    {
        case 1:
            qsort(list, count, sizeof(database), cmpar);
            break;
        case 2:
            qsort(list, count, sizeof(database), cmpar1);
            break;
        case 3:
            qsort(list, count, sizeof(database), cmpar2);
            break;
    }
    
    for(int i = 0; i < count; ++i)
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
    for(int i = 0; i < count; ++i)
    {
        fprintf(fpw, "%s %s %s\n", list[i].lname, list[i].fname, list[i].city);
    }
    
    fclose(fpr);
    fclose(fpw);
    return 0;
}

