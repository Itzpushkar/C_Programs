#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int random, guess, noOfGuess = 0;
    srand(time(NULL));
    printf("Welcome to Number Guessing Game\nDeveloped By: Kikani Pushkar\n");
    random = rand() % 100 + 1;

    do
    {
        printf("\nPlease guess the random number between 1 to 100:");
        scanf("%d", &guess);
        noOfGuess++;
        if (guess < random)
        {
            printf("\nPlease guess a bigger number");
        }
        else if (guess > random)
        {
            printf("\nPlease guess a smaller number");
        }
        else if (guess == random)
        {
            printf("\nCongratulations!!! You guess a correct number in %d attempts", noOfGuess);
        }

    } while (guess != random);
    printf("\nHave a great day ahead");
    return 0;
}