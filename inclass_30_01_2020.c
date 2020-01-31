// Inclass work
//complete the programme to understand quick sort algorithm in C


#include<stdio.h>
#include<stdlib.h> 

int myarr[]={8, 32, -76, 4025, 0, 3, -329, 5412, 6};
int compar(const void *pa, const void *pb)
{	return(*(int*)pa-*(int*)pb);
}
int main()
{
	for(int i=0; i<8; i++)
	{	printf(" %d", myarr[i]);
	}
	printf("\n");

	qsort(myarr, 8, sizeof(int), compar);
	for(int i=0; i<8; i++)
        {        printf(" %d", myarr[i]);
	}
	printf("\n");
	return(0);
}
