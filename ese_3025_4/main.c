#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void sorting(void *array, unsigned n);
static int cmpar(const void *a, const void *b);


int main(int argc, char *argv[])
{
	if(argc!= 3) 
    {
        printf("usage: ese_3025_4 <infile> <outfile>\n");
        return 0;
    }
    
    char* pinfile = argv[1];
    char* poutfile = argv[2];
    char *list[1000];
    char l[1024];
    int i = 0;
    int j = 0;
    
    FILE *fpr = fopen(pinfile, "r");
    if(0 == fpr)
    {
        printf("Failed to open the file %s \n", pinfile);
        return 0;
    }
    
    if (fpr != NULL)
    {
        while (fgets(l, sizeof l, fpr) != NULL)
        {
            if (i < sizeof list / sizeof *list)
            {
                list[i++] = strdup(l);
            }
            else
            {
                break;
            }
        }
        
        sorting(list, i);
        
        
        for (j = 0; j < i; j++)
        {
        printf("%s", list[j]);
        
        }
        
        FILE *fpw = fopen(poutfile, "w");
        if(0 == fpw)
        {
            printf("Failed to create the file %s \n", poutfile);
            fclose(fpr);
            return 0;
        }
        
        for (j = 0; j < i; j++)
        {
            fprintf(fpw, "%s", list[j]);
//            fwrite(list[j], 4, 1, fpw);
            
        }
        fclose(fpw);
    }
    
    fclose(fpr);
//    fclose(fpw);
    return 0;
}
int cmpar(const void *a, const void *b)
{
    return (strcmp(*(char **)a, *(char **)b));
}
void sorting(void *array, unsigned n)
{
    qsort(array, n, sizeof(const char *), cmpar);
}