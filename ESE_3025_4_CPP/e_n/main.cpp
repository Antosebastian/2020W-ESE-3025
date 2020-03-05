#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct database
{
    char lname[15];
    char fname[15];
    char city[15];    
};

database list[1000];

int cmpar(const void *a, const void *b)
{
    database *pa = (database *)a;
    database *pb = (database *)b;
    return strcmp(pa->lname, pb->lname);
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
        cout<<list[i].lname<<" "<<list[i].fname<<" "<<list[i].city<<"\n";
    }
    return;
}

void read(char* file, int count)
{
    int i = 0;
    fstream read_file;
    read_file.open(file, ios::in);
    if(!read_file)
    {
        cerr<<"Failed to open the file "<<file<<"\n";
    }
    while(file != 0)
    {       
        read_file>>list[i].lname>>list[i].fname>>list[i].city;
        ++i;
        (count)++;
    }
    print(&count);
    read_file.close();
    return;
}

void sort(int* pcount)
{
    int x;
    cout<<"Enter:\n1 - if you want to sort by last name"<<"\n"<<"2 - if you want to sort it by first name"<<"\n"<<"3 - if you want to sort by city"<<"\n";
    cin>>x;

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
    return;
}

void write(char* file, int* pcount)
{
    fstream write_file;
    write_file.open(file, ios::out);
    if(!file)
    {
        cerr<<"Failed to create the file "<<file<<"\n";
        write_file.close();
    }
    for(int i = 0; i < *pcount; ++i)
    {
        write_file<<list[i].lname<<" "<<list[i].fname<<" "<<list[i].city<<"\n";
    }
    write_file.close();
    return;
}

int main(int argc, char *argv[])
{
	if(argc!= 3) 
    {
        cout<<"usage: struct_ <infile> <outfile>"<<"\n";
        return 0;
    }
    int count = 0;
    read(argv[1], count);
    sort(&count);
    write((char*) argv[2], &count); 
    return 0;
}