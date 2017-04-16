/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Loris
 *
 * Created on April 12, 2017, 11:17 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cstdlib>

/*
 * 
 */
using namespace std;
float score;
float defaultScore = 10.0;
void menuProgram();
void choiceMenu();
void cashOut();
void save();

bool validNumber(char data) {
    if (data >= '0' && data <= '9') {
        return true;
    } else {
        return false;
    }
}

void checkFile() {
    FILE * fscore;
    fscore = fopen("score.txt", "r");
    if (fscore == NULL) {
        printf("Can not find score. Created file!\n");
        score = 10;
        fscore = fopen("score.txt", "wt");
        //fprintf(fscore, "%.2f", score);
    } else {
        fscanf(fscore, "%f", &score);
    }

    if (score < 0.25) {
        score = 10;
        fscore = fopen("score.txt", "wt");
        fprintf(fscore, "%.2f", score);
    }
    fclose(fscore);
}

int * randomArray() {
    int *randArray = (int *) malloc(3*sizeof(int));
    srand((unsigned) time(NULL));
    for (int i = 0; i < 3; i++) {
        randArray[i] = rand() % 10;
    }
    return randArray;
}

void showSlot() {
    int * randomResultK = randomArray();
    printf("The slot machine shows: ");
    for (int i = 0; i < 3; i++) {
        printf("%d", randomResultK[i]);
    }
}

float compare(int * randomResult) {
    int count = 0;
    float scoreResult = 0;
    int result[3];

    if (randomResult[0] == randomResult[1] || randomResult[0] == randomResult[2] || randomResult[1] == randomResult[2]) {
        scoreResult += 0.5;
    } else if (randomResult[0] == randomResult[1] && randomResult[0] == randomResult[2] && randomResult[1] == randomResult[2]) {
        scoreResult += 10;
    } else {
        scoreResult += 0;
    }
    return scoreResult;
}

void play() {
    int * randomResultK = randomArray();
    float compareResult = compare(randomResultK);
    showSlot();
    if (compareResult == 0) {
        printf("\nYou don't win anything.\n");
        score -= 0.25;
    } else if (compareResult == 0.5) {
        printf("\nYou win 50 cents\n");
        score += 0.5;
    } else if (compareResult == 10) {
        printf("\nYou win the big prize, $10.00!\n");
        score += 10;
    }

    printf("------------------------------------\n");
    if (score >= 0.25) {
        menuProgram();
        choiceMenu();
    } else {
        printf("Sorry, not enought money!");
    }
}

void cashOut() {
    printf("Thank you for playing! You end with $%.2f\n", score);
    FILE * fscore;
    score = 0;
    fscore = fopen("score.txt", "w+");
    fprintf(fscore, "%.2f", score);
    fclose(fscore);
    exit(0);
}

void exitProgram() {
    int check;
    if (score != defaultScore) {
        printf("Do you wnat to save your money(No enter 1 || Yes enter 2)? \n");
        printf("Your choice: ");
        do {
            scanf("%d", &check);
        } while (check == 1 && check == 2);

        if (check == 1) {
            FILE * fscore;
            score = 0;
            fscore = fopen("score.txt", "wt");
            fprintf(fscore, "%.2f", score);
            fclose(fscore);
            printf("Thank you for playing! Your money had not save!");
            exit(0);
        }

        if (check == 2) {
            FILE * fscore;
            fscore = fopen("score.txt", "wt");
            fprintf(fscore, "%.2f", score);
            fclose(fscore);
            printf("Thank you for playing! Your money had saved!");
            exit(0);
        }
    } else {
        save();
        printf("Thank you for playing!\n");
    }
}

void choiceMenu() {
    char value;
    printf("Your choice: ");
    scanf("%c", &value);
    if (validNumber(value)) {
        switch (value) {
            case '1':
            {
                play();
                break;
            }
            case '2':
            {
                save();
                choiceMenu();
                break;
            }
            case '3':
            {
                cashOut();
                break;
            }
            case '4':
            {
                exitProgram();
                break;
            }
            default:
            {
                printf("Please enter 1 or 2 or 3 or 4: \n");
                choiceMenu();
            }
        }
    } else {
        choiceMenu();
    }
}

void save() {
    FILE * fscore;
    fscore = fopen("score.txt", "w+");
    fprintf(fscore, "%.2f", score);
    fclose(fscore);
    printf("------------------------------------\n");
    printf("Your money had saved!\n");
}

void menuProgram() {
    printf("You have $%.2f\n", score);
    printf("Choose  one of following menu option: \n");
    printf("1) Play the slot machine\n");
    printf("2) Save game\n");
    printf("3) Cash out\n");
    printf("4) Exit program\n");
}

int main(int argc, char** argv) {
    checkFile();
    while (true) {
        menuProgram();
        choiceMenu();
    }
    return (EXIT_SUCCESS);
}
