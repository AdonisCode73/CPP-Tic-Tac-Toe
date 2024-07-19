#include <iostream>
#include <ctime>


// print out the board visually, inputting spaces for player/computer entry
void drawBoard(char *spaces){

    std::cout << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << "  " << spaces[0] << "  |  " << spaces[1] << "  |  " << spaces[2] << "  " << "\n";
    std::cout << "_____|_____|_____" << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << "  " << spaces[3] << "  |  " << spaces[4] << "  |  " << spaces[5] << "  " << "\n";
    std::cout << "_____|_____|_____" << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << "  " << spaces[6] << "  |  " << spaces[7] << "  |  " << spaces[8] << "  " << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << "\n";
}

// player picks position for X, if player or computer has already played in this square, try again
void playerMove(char *spaces, char player){

    int number;
    
    std::cout << "Enter your move, position (1 - 9): ";
    std::cin >> number;

    while (spaces[number - 1] != ' '){
        std::cout << "Space occupied. Pick another number (1-9): ";
        std::cin >> number;
    }

    spaces[number - 1] = player;
}

// computer randomly picks a square and checks if its available, if not it rolls again until a free square
void computerMove(char *spaces, char computer){

    srand(time(NULL));

    int number = (rand() % 9);

    while (spaces[number] != ' '){
        number = (rand() % 9);
    }

    spaces[number] = computer;

}

// 2D array of winning combinations, for each array checks if all 3 elements match, if not loops through, if none found return false
bool checkWinner(char *spaces, char player, char computer){

    int winCombos[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

    int lengthWinCombos = sizeof(winCombos)/sizeof(winCombos[0]);

    for (int i = 0; i < lengthWinCombos; i++) {
        if (spaces[winCombos[i][0]] == player && spaces[winCombos[i][1]] == player && spaces[winCombos[i][2]] == player){
            return true;
        }
    }

    for (int i = 0; i < lengthWinCombos; ++i) {
        if (spaces[winCombos[i][0]] == computer && spaces[winCombos[i][1]] == computer && spaces[winCombos[i][2]] == computer){
            return true;
        }
    }

    return false;
}

// loop through spaces array to check if any open spaces are available, if not, its a tie and returns true, else false
bool checkTie(char *spaces){

    int length = sizeof(spaces)/sizeof(spaces[0]);

    for (int i = 0; i < length; i++){
        if (spaces[i] == ' '){
            return false;
        }
    }

    return true;
}



int main(){

    char spaces[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

    char player = 'X';
    char computer = 'O';

    bool running = true;

    srand(time(NULL));

    int firstMove = (rand() % 2);

    drawBoard(spaces);

    while (running){

        // switch cases to contain the possibility of player or computer moving first
        switch(firstMove){
        case 0:
            playerMove(spaces, player);
            drawBoard(spaces);
            if (checkWinner(spaces, player, computer)){
                std::cout << "The player has won the game.";
                running = false;
                break;
            }

            // check for possible tie
            if (checkTie(spaces)){
                std::cout << "The game has ended in a tie.";
                running = false;
                break;
            }

            computerMove(spaces, computer);
            drawBoard(spaces);
            if (checkWinner(spaces, player, computer)){
                std::cout << "The computer has won the game.";
                running = false;
                break;
            }
            break;

        // if firstmove is 1 then computer moves first
        case 1:
            computerMove(spaces, computer);
            drawBoard(spaces);
            if (checkWinner(spaces, player, computer)){
                std::cout << "The computer has won the game.";
                running = false;
                break;
            }

            // check for possible tie
            if (checkTie(spaces)){
                std::cout << "The game has ended in a tie.";
                running = false;
                break;
            }

            playerMove(spaces, player);
            drawBoard(spaces);
            if (checkWinner(spaces, player, computer)){
                std::cout << "The player has won the game.";
                running = false;
                break;
            }
            break;
        }
    }

    return 0;
}