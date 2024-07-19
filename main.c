#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool is_end = false; // tell game loop is end
char winner; // tells who won
char move = 0; // counts moves to calculate which turn
int first; // tells which has first move 1=computer 0=human
int player_X, player_Y;
int computer_X, computer_Y;
char board[3][3] = {{2,2,2},{2,2,2},{2,2,2}};

void choice_who_first();
void game_loop();
void print_board();
void player_move();
void computer_move();
int randomize_number();
bool check_win();

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    choice_who_first();

    game_loop();

    return 0;
}

void choice_who_first() {
    do {
        printf("Kto zaczyna:\n");
        printf("[0] Gracz\n");
        printf("[1] Komputer\n");
        scanf("%d", &first);
        printf("Wybrano: %d\n", first);
    } while (first != 0 && first != 1);
}

void game_loop(){
    while (move < 9 && !check_win())
    {
        print_board();

        if(move % 2 == first){
            printf("ruch gracza \n");
            player_move();
        }else {
            printf("ruch komputera \n");
            computer_move();
        }
        //printf("%d, %d, %d \n", move, first, (move % 2));
        move++;
    }

    print_board();
    printf("GAME OVER!\n");
    switch (winner){
    case 1:
        printf("Player WON!\n");
        break;
    case 0:
        printf("Computer WON!\n");
        break;
    default:
        printf("DRAW!\n");
        break;
    }
}

void print_board(){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 2) { // empty square is 2
                printf(". ");
            } else if (board[i][j] == 0) { // computer is 0
                printf("O ");
            } else { // player is 1
                printf("X ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void player_move(){
    do{
        do{    
            printf("wybierz koordynat X, gdzie X < 3 oraz 0 >= X : ");
            scanf("%d", &player_X);
        } while (player_X >= 3 || player_X < 0);

        do{    
            printf("Wybierz koordynat Y, gdzie Y < 3 oraz 0 >= Y: ");
            scanf("%d", &player_Y);
        } while (player_Y >= 3 || player_Y < 0);
    } while (board[player_Y][player_X]!=2);
    
    board[player_Y][player_X] = 1; // player is 1
}

void computer_move(){
    do{
        computer_X = randomize_number(0, 3);
        computer_Y = randomize_number(0, 3);
    } while (board[computer_Y][computer_X] != 2);
    board[computer_Y][computer_X] = 0; // computer is 0 
}

int randomize_number(int min, int max){
    return rand() % (max - min + 1) + min;
}

bool check_win(){
    for (int i = 0; i < 3; i++)
    {
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i]){
            if(board[0][i] != 2){
                winner = board[0][i];
                return true;
            }
        }
    }
    
    for (int i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2]){
            if(board[i][0] != 2){
                winner = board[i][0];
                return true;
            }
        }
    }

    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]){
        if(board[1][1] != 2){
            winner = board[1][1];
            return true;
        }
    }


    if(board[0][2] == board[1][1] && board[1][1] == board[2][0]){
        if(board[1][1] != 2){
            winner = board[1][1];
            return true;
        }
    }
    return false;
}