//Game between threads to find the number first.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int x = 0;
int y = 0;
int z = 0;

int guess()
{
    printf("Enter a number between 0 and 1000\n");
    return scanf("%d", &x);
    if((x <= 0) && (x >= 1000))
    {
        printf("WARNING: Out of bounds\n");
        EXIT_FAILURE;
    }
}

void* incremental_search(void* is_param)
{
    int i = 0;
    for(i = 0; i <= 1000;i++)
    {
        if(x == i)
            return 0;
        y++;
        usleep(1000);
    }
    return y;
}

void* binary_search(void* is_param)
{
    int a = 0;
    int b = 1000;
    int half = ((a+b)/2);
    while(x != half)
    {
        if((x > half) && (x < b))
        {
            a = half;
        }
        else if((x>a) && (x < half))
        { 
            b = half;
        }
        half = ((a+b)/2);
        z++;
        usleep(1000);
    }
}

int main()
{
    guess(x);
    pthread_t player_1;//incrimental search -> player
    pthread_t player_2;//binary search -> player
    if (pthread_create (&player_1, NULL, &incremental_search, NULL) != 0)
    {
      printf ("Failed to create the thread\n");
      return 1;
    }
    if (pthread_create (&player_2, NULL, &binary_search, NULL) != 0)
    {
      printf ("Failed to create the thread\n");
      return 1;
    }
    pthread_join (player_1, NULL);
    pthread_join (player_2, NULL);
    if(y > z)
        printf("\nplayer_2 is the winner with the binary search technique");
    else if(z > y)
        printf("\nplayer_1 is the winner with the incrimental search technique");
    else
        printf("Failed to establish the winner\n");
    printf("\nNumber of turns taken by each player\nplayer 1 = %d\nplayer 2 = %d", y, z);
    return 0;
}
