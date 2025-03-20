#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
    //Treasure: A = +1; B= +2; C= +3
    //Trap: T = 0; Monster: M = -1
    char array[] = "ABCTM";
    char floor;
    int lives = 3;
    int scores = 0;
    int choice = 1; //player choice

    //random seed
    srand(time(NULL));

    do{
        floor = array[rand() % 5];

        if(floor == 'A') {
            printf("You found a treasure, your scores + 1. \n");
            scores += 1;
        }
        else if (floor == 'B') {
            printf("You found a treasure, your scores + 2. \n");
            scores += 2;
        }
        else if (floor == 'C') {
            printf("You found a treasure, your scores + 3. \n");
            scores += 3;
        }
        else if (floor == 'T') {
            printf("It is a trap! But you avoid it with your skills. \n");
        }
        else {
            printf("A monster appeared! You fight it and lose 1 life. \n");
            lives -= 1;

            if(lives == 0){
                scores = 0;
                break;
            }
        }

        printf("Your scores is %d and you life is %d. \n", scores, lives);
        printf("Do you want to continue or quit? 1:continue 2:quit   ");
        scanf("%d", &choice);
    }while(choice == 1);

    printf("Your final score is %d. \n", scores);
}