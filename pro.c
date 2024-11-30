#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include<ctype.h>
/*
-------------------------------------------------------------------------------
                                  DECLARATIONS
-------------------------------------------------------------------------------
*/

#define SIZE 9
// ANSI color escape codes
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_ORANGE  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"


//***************Bingo*****************
struct BingoCard {
    int numbers[25];
};
struct BingoCard createBingoCard();
int generateRandomNumber(int min, int max);
struct BingoCard createRandomBingoCard();
void drawNumberAndMark(struct BingoCard* card, int number);
int hasBingo(struct BingoCard card);
void displayCard(struct BingoCard card);


//******************Find the rat************
void findrat();


//******************Pacman*************
#define WIDTH 40
#define HEIGHT 20
#define PACMAN 'C'
#define WALL '#'
#define FOOD '.'
#define EMPTY ' '
#define DEMON 'X'

// Global Variables are
// Declared here
int res = 0;
int score = 0;
int pacman_x, pacman_y;
char board[HEIGHT][WIDTH];
int food = 0;
int curr = 0;
void initialize();
void draw();
void move(int move_x, int move_y);
int pacman();


// ****************Maze Runner*****************
#define r 3
#define c 3
int maze_x=0,maze_y=0;
int maze[r][c];
bool ismovevalid(int x, int y);
void displaymaze(int x1, int y1);
void maze_move(int move_x, int move_y);


//**********Rock Paper Scissors************
int rock_generateRandomNumber(int n);
int greater(char char1, char char2);
int RockPaperScissors();
bool isSolved(int grid[SIZE][SIZE]);


//***************Tic Tac Toe****************
char tboard[3][3];// The Tic-Tac-Toe board
void init_board();
void print_board();
char check_win();
void play_game();

//***************Hangman****************
int hangman();

//***************Mines****************

int mines_game();

/*






-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
                                                     MAIN FUNCTION
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------


*/

int main(){

    while(1){
        char *games_left[] = {
            ANSI_COLOR_GREEN   "Bingo"   ANSI_COLOR_RESET,
            ANSI_COLOR_ORANGE  "Find the rat"   ANSI_COLOR_RESET,
            ANSI_COLOR_RED     "Pacman"   ANSI_COLOR_RESET,
            ANSI_COLOR_BLUE    "Pathfinder"   ANSI_COLOR_RESET
           
        };
        char *games_right[] = {
            ANSI_COLOR_GREEN   "Rock Paper Scissors"   ANSI_COLOR_RESET,
            ANSI_COLOR_ORANGE  "Hangman"   ANSI_COLOR_RESET,
            ANSI_COLOR_RED     "Tic Tac Toe"   ANSI_COLOR_RESET,
            ANSI_COLOR_BLUE    "Mines"     ANSI_COLOR_RESET
            
        };
        int num_games_left = sizeof(games_left) / sizeof(games_left[0]);
        int num_games_right = sizeof(games_right) / sizeof(games_right[0]);
        int max_game_length_left = 0;
        int max_game_length_right = 0;
    
        // Find the length of the longest game name on the left
        for (int i = 0; i < num_games_left; i++) {
            int length = strlen(games_left[i]);
            if (length > max_game_length_left) {
                max_game_length_left = length;
            }
        }
    
        // Find the length of the longest game name on the right
        for (int i = 0; i < num_games_right; i++) {
            int length = strlen(games_right[i]);
            if (length > max_game_length_right) {
                max_game_length_right = length;
            }
        }
    
        // ANSI color codes for header and numbers
        char *header_color = ANSI_COLOR_ORANGE;
        char *number_color = ANSI_COLOR_RED;
    
        printf("         %sGAME ZONE%s\n", header_color, ANSI_COLOR_RESET);
        for (int i = 0; i < num_games_left; i++) {
            printf("%s%-2d. %-*s%s     ", number_color, i + 1, max_game_length_left, games_left[i], ANSI_COLOR_RESET);
            printf("%s%-2d. %-*s%s\n", number_color, i + 5, max_game_length_right, games_right[i], ANSI_COLOR_RESET);
        }
    
        int selection;
        printf("Enter the number of the game you want to play: ");
        scanf("%d", &selection);
        if ((selection >= 1 && selection <= num_games_left) || (selection >= 5 && selection <= 4 + num_games_right)) {
        switch (selection) {
            case 1:
                printf("Welcome to Bingo!\n");

                // Create Bingo cards for both players
                printf("Player 1, create your Bingo card:\n");
                struct BingoCard player1Card = createBingoCard();
                printf("Player 2's Bingo card (Computer Generated):\n");
                struct BingoCard player2Card = createRandomBingoCard();

                // Tracks the current player
                int currentPlayer = 1;

                // Display only player 1's card initially
                printf("Player 1's Card:\n");
                displayCard(player1Card);

                // Main game loop
                while (1) {
                    // Get the current player's card
                    struct BingoCard currentCard = (currentPlayer == 1) ? player1Card : player2Card;

                    // Get the drawn number from the current player
                    int drawnNumber;
                    if (currentPlayer == 1) {
                        printf("Player %d, enter the drawn number (1-25): ", currentPlayer);
                        scanf("%d", &drawnNumber);
                    } else {
                        // Generate a random number for Player 2
                        drawnNumber = generateRandomNumber(1, 25);
                        // Check if the number is already marked
                        while (currentCard.numbers[drawnNumber - 1] == 0) {
                            drawnNumber = generateRandomNumber(1, 25);
                        }
                        printf("Player %d (Computer) - Drawn Number: %d\n", currentPlayer, drawnNumber);
                    }

                    // Mark the drawn number on both player's cards
                    drawNumberAndMark(&player1Card, drawnNumber);
                    drawNumberAndMark(&player2Card, drawnNumber);

                    // Display only player 1's card after each input and number strike
                    printf("Player 1's Card:\n");
                    displayCard(player1Card);

                    // Check if the current player has achieved Bingo
                    if (hasBingo(currentCard)) {
                        // Exit the game loop
                        printf("\nPlayer %d has achieved Bingo! Congratulations!\n", currentPlayer);
                        break;
                    }

                    // Switch to the other player for the next round
                    currentPlayer = (currentPlayer == 1) ? 2 : 1;
                }

                // Display both players' cards after Bingo is achieved
                printf("Player 1's Card:\n");
                displayCard(player1Card);
                printf("--------------------------\n");
                printf("Player 2's Card:\n");
                displayCard(player2Card);
                printf("--------------------------\n");
                break;

            case 2:
                findrat();
                break;

            case 3:
                pacman();
                break;

            case 4:
                printf("Enter maze for 3*3 in 0 and 1");
                for(int i=0;i<r;i++){
                    for(int j=0;j<c;j++){
                        scanf("%d",&maze[i][j]);
                    }
                }

                printf("\n Right:d \n Left:a \n Up:w \n Down:s \n");
                printf("You've got %d moves to reach the end. All zeroes are treated as blocks.\n Currently at (0,0)\n",r*c);
    
                for(int i=0; i<r*c; i++){
                    if(maze_x==r-1 && maze_y==c-1){
                        printf("You won!!\n");
                        break;
                    }
                    int t=i+1;
                    char ch;
                    printf("Enter Move %d:",t);
                    fflush(stdin);
                    scanf("%c",&ch);

                    switch (ch){
                        case 'a':
                            maze_move(0,-1);
                            break;
                        case 'd':
                            maze_move(0,1);
                            break;
                        case 'w':
                            maze_move(-1,0);
                            break;
                        case 's':
                            maze_move(1,0);
                            break;
                        case 'q':
                            printf("exiting..");
                        return 0;
                    }
        
                }
                if(maze_x!=r-1 && maze_y!=c-1){
                        printf("You lost!!\n");
                        break;
                }
                                
                break;

            case 5:
                RockPaperScissors();
                break;

            case 6:
                  hangman();
                break;
            case 7:
                play_game();
                break;

            case 8:
                mines_game();
                break;
            
          

            default:
                printf("Invalid choice");
        }

        } 

    }
    

}


/*
-----------------------------------------------------------------------------------------------------------------------
                                                FUNCTION DECLARATIONS
-----------------------------------------------------------------------------------------------------------------------
*/



//**************************************************** Bingo *********************************************************


// Function to create a new Bingo card and shuffle the numbers
struct BingoCard createBingoCard() {
    struct BingoCard card;
    printf("Enter 25 unique numbers for the Bingo card:\n");
    for (int i = 0; i < 25; ++i) {
        scanf("%d", &card.numbers[i]);
    }
    return card;
}

// Function to generate a random number between min and max (inclusive)
int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Function to create a random Bingo card for the computer (Player 2)
struct BingoCard createRandomBingoCard() {
    struct BingoCard card;
    int numbers[25];
    // Initialize array with numbers 1 to 25
    for (int i = 0; i < 25; ++i) {
        numbers[i] = i + 1;
    }
    // Shuffle the numbers array
    for (int i = 0; i < 25; ++i) {
        int j = rand() % 25;
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }
    // Copy the shuffled numbers to the card
    for (int i = 0; i < 25; ++i) {
        card.numbers[i] = numbers[i];
    }
    return card;
}

// Function to mark the drawn number on a Bingo card
void drawNumberAndMark(struct BingoCard* card, int number) {
    for (int i = 0; i < 25; ++i) {
        if (card->numbers[i] == number) {
            card->numbers[i] = 0;
        }
    }
}

// Function to check if a Bingo card has achieved Bingo
int hasBingo(struct BingoCard card) {
    // Check rows for Bingo
    int rows[5] = {0};
    for (int i = 0; i < 5; ++i) {
        int count = 0;
        for (int j = 0; j < 5; ++j) {
            if (card.numbers[i * 5 + j] == 0) {
                count++;
            }
        }
        if (count == 5) {
            rows[i] = 1;
        }
    }

    // Check columns for Bingo
    int cols[5] = {0};
    for (int i = 0; i < 5; ++i) {
        int count = 0;
        for (int j = 0; j < 5; ++j) {
            if (card.numbers[j * 5 + i] == 0) {
                count++;
            }
        }
        if (count == 5) {
            cols[i] = 1;
        }
    }

    // Check main diagonal for Bingo
    int main_diag = 0;
    for (int i = 0; i < 5; ++i) {
        if (card.numbers[i * 5 + i] == 0) {
            main_diag = 1;
            break;
        }
    }

    // Check secondary diagonal for Bingo
    int sec_diag = 0;
    for (int i = 0; i < 5; ++i) {
        if (card.numbers[i * 5 + (4 - i)] == 0) {
            sec_diag = 1;
            break;
        }
    }

    // Count the number of complete lines
    int complete_lines = 0;
    for (int i = 0; i < 5; ++i) {
        complete_lines += rows[i];
        complete_lines += cols[i];
    }
    complete_lines += main_diag;
    complete_lines += sec_diag;

    // Return 1 if five different complete lines are crossed out
    return (complete_lines >= 5);
}

// Function to display the Bingo card
void displayCard(struct BingoCard card) {
    for (int i = 0; i < 25; ++i) {
        // Display numbers or 'X' for drawn numbers
        if (card.numbers[i] != 0) {
            printf("%d\t", card.numbers[i]);
        } else {
            printf("X\t");
        }

        // Move to the next line after every 5 numbers
        if ((i + 1) % 5 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}




//**************************************************Find the rat****************************************************************
void findrat(){
    srand(time(NULL));
    int a = rand()%50 + 1;
    printf("Hello there welcome to the guessing rats hole game \n In this game a rat has 50 holes to escape from you. \n you can have a maximum of 10 tries to catch the rat \n Right now he's in hole %d and now is on the run.\n",a);
    
    for (int i = 0; i < 10; i++) {
       int a = rand()%50 + 1;
       int b;
       printf("\n Guess the hole rat is in it's an integer between 1 and 50 \n");
       scanf("%d",&b);
       if(a==b){
           printf("you've catched the rat.");
           break;
       }
       else {printf("he has escaped. try again \n He's right now in hole %d \n",a);
       }

    }
    printf("     END    ");
}





//****************************************************Pacman***********************************************************
void initialize() {

    // Putting Walls as boundary in the Game
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || j == WIDTH - 1 || j == 0 || i == HEIGHT - 1) {
                board[i][j] = WALL;
            } else
                board[i][j] = EMPTY;
        }
    }

    // Putting Walls inside the Game

    int count = 50;
    while (count != 0) {
        int i = (rand() % (HEIGHT + 1));
        int j = (rand() % (WIDTH + 1));

        if (board[i][j] != WALL && board[i][j] != PACMAN) {
            board[i][j] = WALL;
            count--;
        }
    }

    int val = 5;
    while (val--) {
        int row = (rand() % (HEIGHT + 1));
        for (int j = 3; j < WIDTH - 3; j++) {
            if (board[row][j] != WALL && board[row][j] != PACMAN) {
                board[row][j] = WALL;
            }
        }
    }

    // Putting Demons in the Game
    count = 10;
    while (count != 0) {
        int i = (rand() % (HEIGHT + 1));
        int j = (rand() % (WIDTH + 1));

        if (board[i][j] != WALL && board[i][j] != PACMAN) {
            board[i][j] = DEMON;
            count--;
        }
    }

    // Cursor at Center
    pacman_x = WIDTH / 2;
    pacman_y = HEIGHT / 2;
    board[pacman_y][pacman_x] = PACMAN;

    // Points Placed
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i % 2 == 0 && j % 2 == 0 && board[i][j] != WALL && board[i][j] != DEMON && board[i][j] != PACMAN) {

                board[i][j] = FOOD;
                food++;
            }
        }
    }
}

void draw() {
    // Clear screen
    system("cls");

    // Drawing All the elements in the screen
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void move(int move_x, int move_y) {
    int x = pacman_x + move_x;
    int y = pacman_y + move_y;

    if (board[y][x] != WALL) {
        if (board[y][x] == FOOD) {
            score++;
            food--;
            curr++;
            if (food == 0) {
                res = 2;
                return;
            }
        } else if (board[y][x] == DEMON) {
            res = 1;
        }

        board[pacman_y][pacman_x] = EMPTY;
        pacman_x = x;
        pacman_y = y;
        board[pacman_y][pacman_x] = PACMAN;
    }
}

// Main function for the game
int pacman() {
    initialize();
    char ch;
    food -= 35;
    int totalFood = food;

    // Instructions to Play
    printf(" Use buttons for w(up), a(left), d(right) and s(down)\nAlso, Press q for quit\n");
    printf("Enter Y to continue: \n");

    ch = getch();
    if (ch != 'Y' && ch != 'y') {
        printf("Exit Game! ");
        return 1;
    }

    while (1) {
        draw();
        printf("Total Food count: %d\n", totalFood);
        printf("Total Food eaten: %d\n", curr);

        if (res == 1) {
            // Clear screen
            system("cls");
            printf("Game Over! Dead by Demon\n Your Score: %d\n", score);
            return 1;
        }

        if (res == 2) {
            // Clear screen
            system("cls");
            printf("You Win! \n Your Score: %d\n", score);
            return 1;
        }

        // Taking the Input from the user
        ch = getch();

        // Moving According to the
        // input character
        switch (ch) {
            case 'w':
                move(0, -1);
                break;
            case 's':
                move(0, 1);
                break;
            case 'a':
                move(-1, 0);
                break;
            case 'd':
                move(1, 0);
                break;
            case 'q':
                printf("Game Over! Your Score: %d\n", score);
                return 0;
        }

    }

    return 0;
}




//*************************************************Maze Runner*********************************************************************

bool ismovevalid(int x, int y){
    if (x >= 0 && x < r && y >= 0 && y < c && maze[x][y] == 1){
        return 1;
    }else{
        return 0;
    }
}

void displaymaze(int x1, int y1){
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(i==x1 && j==y1){printf("X ");}
            else{printf("%d ",maze[i][j]);}
        }
        printf("\n");
    }
}

void maze_move(int move_x, int move_y){
    int x1=maze_x+move_x; int y1=maze_y+move_y;
    if(ismovevalid(x1,y1)){
        displaymaze(x1,y1);
        maze_x=x1;
        maze_y=y1;
    }else{
        printf("blocked!!\n");
    }
}




//**************************************************Rock Paper Scissors*******************************************************
int rock_generateRandomNumber(int n){
    srand(time(NULL));
    return rand() % n;
}

int greater(char char1, char char2){
    if(char1 == char2){
        return -1;
    }
    else if((char1 == 'r')&&(char2 == 's'))
    {
        return 1;
    }
    else if ((char1 == 's')&&(char2 == 'r'))
    {
        return 0;
    }
    else if((char1 == 'p')&&(char2 == 'r'))
    {
        return 1;
    }
    else if((char1 == 'p')&&(char2 == 's'))
    {
        return 0;
    }
    else if((char1 == 's')&&(char2 == 'p'))
    {
        return 1;
    }
    else if((char1 == 'p')&&(char2 == 's'))
    {
        return 0;
    }
}

int RockPaperScissors()
{
    int playerScore = 0, compScore = 0, temp;
    char compChar, playerChar; 
    char dict[]= {'r', 'p', 's'};

    printf("Welcome to Rock, Paper, Scissors.\n");
    
    for( int i=0; i<3; i++){
        printf("Player 1's turn\n");
        printf("Choose 1 for Rock, Choose 2 for Paper and Choose 3 for Scissors\n");
        scanf("%d", &temp);
        playerChar = dict[temp-1];
        printf("You chose %c\n", playerChar);

        printf("Computer's turn\n");
        printf("Choose 1 for Rock, Choose 2 for Paper and Choose 3 for Scissors\n");
        temp = rock_generateRandomNumber(3)+1;
        compChar = dict[temp-1];
        printf("CPU chose %c\n", compChar);

        if(greater(compChar, playerChar) == 1)
        {
            printf("CPU got it!\n");
            compScore += 1;
        }
        else if (greater(compChar, playerChar) == -1)
        {
            compScore += 1;
            playerScore += 1;
            printf("Its a draw!\n"); 
        }
        else
        {
            playerScore += 1;
            printf("You got it!\n");
        }
        printf("You: %d\nCPU: %d\n\n", playerScore, compScore);
    }

    if(playerScore > compScore)
    {
        printf("You win the game\n");
    }
    else if(playerScore < compScore)
    {
        printf("CPU win the game\n");
    }
    else{
        printf("Game is a draw!\n");
    }

return 0;
}




//******************************************************Tic Tac Toe**************************************************
// Function to initialize the board
void init_board() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            tboard[i][j] = ' ';
}

// Function to print the board
void print_board() {
    printf(" %c | %c | %c\n", tboard[0][0], tboard[0][1], tboard[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", tboard[1][0], tboard[1][1], tboard[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", tboard[2][0], tboard[2][1], tboard[2][2]);
}

// Function to check if the game is over
char check_win() {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (tboard[i][0] == tboard[i][1] && tboard[i][1] == tboard[i][2] && tboard[i][0] != ' ')
            return tboard[i][0];
    }
    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (tboard[0][i] == tboard[1][i] && tboard[1][i] == tboard[2][i] && tboard[0][i] != ' ')
            return tboard[0][i];
    }
    // Check diagonals
    if (tboard[0][0] == tboard[1][1] && tboard[1][1] == tboard[2][2] && tboard[0][0] != ' ')
        return tboard[0][0];
    if (tboard[0][2] == tboard[1][1] && tboard[1][1] == tboard[2][0] && tboard[0][2] != ' ')
        return tboard[0][2];
    // Check for draw
    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (tboard[i][j] == ' ')
                return ' ';
    return 'D'; // Draw
}

// Function to play the game
void play_game() {
    int row, col;
    char player = 'X';
    char winner = ' ';

    init_board();

    printf("Tic Tac Toe\n");
    printf("Player 1 (X)  -  Player 2 (O)\n");
    printf("Enter row and column (1-3) to place your move\n");

    // Game loop
    do {
        print_board();
        printf("Player %c, enter your move: ", player);
        scanf("%d %d", &row, &col);
        row--; // Adjust to 0-based indexing
        col--; // Adjust to 0-based indexing
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && tboard[row][col] == ' ') {
            tboard[row][col] = player;
            winner = check_win();
            if (winner == ' ')
                player = (player == 'X') ? 'O' : 'X'; // Switch player
        } else {
            printf("Invalid move. Please try again.\n");
            getch(); // Wait for a key press
        }
    } while (winner == ' ');

    // Game over
    print_board();
    if (winner == 'D')
        printf("It's a draw!\n");
    else
        printf("Player %c wins!\n", winner);
}



//****************************************************************************************
//hangman

#define MAX_TRIES 6
#define WORDS_COUNT 10
#define MAX_WORD_LENGTH 20

char* words[] = {"programming", "hangman", "computer", "keyboard", "algorithm", "variable", "function", "language", "compiler", "software"};

// Function to randomly select a word from the list
char* selectRandomWord() {
    return words[rand() % WORDS_COUNT];
}

// Function to check if the guessed character is in the word
int checkGuess(char guess, char* word, char* guessed) {
    int i, found = 0;
    for (i = 0; word[i] != '\0'; i++) {
        if (tolower(word[i]) == tolower(guess)) {
            guessed[i] = word[i];
            found = 1;
        }
    }
    return found;
}

// Function to display the hangman figure
void drawHangman(int tries) {
    printf("\n");
    switch (tries) {
        case 1:
            printf("   +---+\n");
            printf("   |   |\n");
            printf("       |\n");
            printf("       |\n");
            printf("       |\n");
            printf("       |\n");
            printf("=========\n");
            break;
        case 2:
            printf("   +---+\n");
            printf("   |   |\n");
            printf("   O   |\n");
            printf("       |\n");
            printf("       |\n");
            printf("       |\n");
            printf("=========\n");
            break;
        case 3:
            printf("   +---+\n");
            printf("   |   |\n");
            printf("   O   |\n");
            printf("   |   |\n");
            printf("       |\n");
            printf("       |\n");
            printf("=========\n");
            break;
        case 4:
            printf("   +---+\n");
            printf("   |   |\n");
            printf("   O   |\n");
            printf("  /|   |\n");
            printf("       |\n");
            printf("       |\n");
            printf("=========\n");
            break;
        case 5:
            printf("   +---+\n");
            printf("   |   |\n");
            printf("   O   |\n");
            printf("  /|\\  |\n");
            printf("       |\n");
            printf("       |\n");
            printf("=========\n");
            break;
        case 6:
            printf("   +---+\n");
            printf("   |   |\n");
            printf("   O   |\n");
            printf("  /|\\  |\n");
            printf("  /    |\n");
            printf("       |\n");
            printf("=========\n");
            break;
        case 7:
            printf("   +---+\n");
            printf("   |   |\n");
            printf("   O   |\n");
            printf("  /|\\  |\n");
            printf("  / \\  |\n");
            printf("       |\n");
            printf("=========\n");
            break;
    }
}

int hangman() {
    srand(time(NULL));

    char* word = selectRandomWord();
    char guessed[MAX_WORD_LENGTH];
    int tries = 0;
    int i;
    int y1=0;

    // Initialize guessed array with underscores
    for (i = 0; word[i] != '\0'; i++) {
        guessed[i] = '_';
    }
    guessed[i] = '\0'; // Null terminate the string

    printf("\nWelcome to Hangman!\n");


    printf("\nThe rules of hangman are as follows:\n");


    printf("The computer is the executioner here.\n");
    


    printf("You shall guess a letter.\n");


    printf("If that letter is in the word(s) then write the letter will be displayed everywhere it would appear,"
    " an cross out that letter in the alphabet.\n");


    printf("If the letter isn't in the word then add a body part to the gallows "
    "(head, body, left arm, right arm, left leg, right leg).\n");


    printf("The player will continue guessing letters until they can either solve"
    " the word (or phrase) or all six body parts are on the gallows.\n");


    printf("The executioner wins if the full body is hanging from the gallows.\n");


    printf("The guesser(s) wins if they guess the word before the person is hung.\n\n");


    printf("Try to guess the word.\n");


    printf("You have 7 tries.\n");


    // Main game loop
    while (tries <= MAX_TRIES) {
        printf("\nWord: %s\n", guessed);
        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);

        // Check if the guessed letter is in the word
        if (checkGuess(guess, word, guessed)) {
            printf("Correct guess!\n");
        } else {
            printf("Incorrect guess!\n");
            tries++;
            drawHangman(tries);
        }

        // Check if the word has been completely guessed
        if (strcmp(word, guessed) == 0) {
            printf("\nCongratulations! You guessed the word: %s\n", word);
            y1=1;
            break;
        }
    }

    // If the player has used all tries
    if (tries > MAX_TRIES) {
        printf("\nSorry, you ran out of tries. The word was: %s\n", word);
        y1=0;
    }

    return y1;
}
//************************************************************************************

//*****************************************************************************************
//mines

#define BOARD_SIZE 5

char board1[BOARD_SIZE][BOARD_SIZE];
char revealed[BOARD_SIZE][BOARD_SIZE];

void initializeBoard() {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board1[i][j] = '+';
            revealed[i][j] = 0;
        }
    }
}

void placeMines(int numMines) {
    int i, j, count = 0;
    while (count < numMines) {
        i = rand() % BOARD_SIZE;
        j = rand() % BOARD_SIZE;
        if (board1[i][j] != '*') {
            board1[i][j] = '*';
            count++;
        }
    }
}

void printBoard() {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (revealed[i][j]) {
                printf("%c ", board1[i][j]);
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

int mines_game() {
    srand(time(NULL));
    initializeBoard();
    int ans1=0;

    int numMines;
    printf("\nEnter the number of mines (up to %d): ", BOARD_SIZE * BOARD_SIZE - 1);
    scanf("%d", &numMines);
    if (numMines >= BOARD_SIZE * BOARD_SIZE) {
        printf("Invalid number of mines. Exiting.\n");
        return 0;
    }

    placeMines(numMines);

    printf("Welcome to the Mines and Gems game!\n");
    printf("Try to find the gems without stepping on the mines.\n");
    printf("Enter row and column to reveal a cell.\n");

    int row, col;
    while (1) {
        printBoard();
        printf("Enter row and column (0-%d): ", BOARD_SIZE - 1);
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
            printf("Invalid input. Please enter valid coordinates.\n");
            continue;
        }

        if (board1[row][col] == '*') {
            printf("Game Over! You stepped on a mine.\n\n");
            break;
        } else {
            printf("You revealed: %c\n", board[row][col]);
            revealed[row][col] = 1;
        }

        int count = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board1[i][j] == '+' && revealed[i][j] == 0)
                    count++;
            }
        }

        if (count == 0) {
            printf("Congratulations! You've found all the gems!\n\n");
            ans1=1;
            break;
        }
    }

    return ans1;
}


//****************************************************************************************
