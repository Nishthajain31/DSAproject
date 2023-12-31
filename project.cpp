#include<iostream>
#include<time.h>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include<conio.h>
#include<cstdio>
using namespace std;
struct ChessCell
{
    int xCoordinate, yCoordinate;
    int distance; // Number of moves needed to reach this cell from the starting cell.
    ChessCell() {}
    ChessCell(int x1, int y1, int d)
    {
        int topforcomputer = -1;
        xCoordinate = x1;
        yCoordinate = y1;
        distance = d;
    }
};

/*
dx[]: Represents the horizontal movement of the knight.
dy[]: Represents the vertical movement of the knight.
Each pair of values (dx[i], dy[i]) from these arrays represents one of the eight possible moves a knight can make on a chessboard.
*/
int dx[] = {-2, -1, 1, 2, -2, -1, 1, 2};
int dy[] = {-1, -2, -2, -1, 1, 2, 2, 1};

bool isValidChessBoardCell(int xCoord, int yCoord, int N)
/*
x: The x-coordinate (row) of a ChessCell on the chessboard.
y: The y-coordinate (column) of a ChessCell on the chessboard.
N: The size of the chessboard (assumed to be N x N).
*/
{
    if (xCoord >= 1 && xCoord <= N && yCoord >= 1 && yCoord <= N)
        return true;
    return false;
}
void visualizeKnightMoves(int initialX, int initialY, int targetX, int targetY , int N) {
   cout << "---------------------------------------\n";

    for (int i = N; i >= 1; --i) {
        for (int j = 1; j <= N; ++j) {
            if (initialX == i && initialY == j) {
               cout << "| I "; // Initial position
            } else if (targetX == i && targetY == j) {
               cout << "| T "; // Target position
            } else {
               cout << "| . ";
            }
        }
        cout<<endl;
    }
           cout << "---------------------------------------\n";

}
void visualizeBoard(const map<int, int>& ladders, const map<int, int>& snakes, int playerPosition) {

cout<<"--------------------------SNAKE AND LADDER---------------------------------";
cout<<endl;
    const int boardSize = 10;

    for (int row = boardSize; row >= 1; --row) {
        for (int col = 1; col <= boardSize; ++col) {
            int cellNumber = (row - 1) * boardSize + col;
            
            if (ladders.find(cellNumber) != ladders.end()) {
                cout << "L\t";
            } else if (snakes.find(cellNumber) != snakes.end()) {
                cout << "S\t";
            } else if (cellNumber == playerPosition) {
                cout << "P\t";
            } else {
                
                cout << "-\t";
            }
         
        }
       
        cout << "\n";
    }
}

int minKnightsmove(int knightPosition[], int targetPosition[], int N)
/*
The minKnightsmove function calculates the minimum number of moves a knight on a chessboard needs to reach a given target position from its current position. This function employs the Breadth-First Search (BFS) algorithm, which is suitable for finding the shortest path in a graph—in this case, the chessboard where each ChessCell is a vertex and each valid knight's move is an edge.
knightPos[]: An array of two integers representing the starting position (x, y) of the knight on the chessboard.
targetPos[]: An array of two integers representing the target position (x, y) the knight needs to reach.
N: The size of the chessboard (N x N).
*/
{
    queue<ChessCell> q;
    q.push(ChessCell(knightPosition[0], knightPosition[1], 0)); // knightPosition[0], knightPosition[1] is the starting position of the knight on chessboard
    bool cellVisited[N + 1][N + 1];
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cellVisited[i][j] = false;
        }
    }
    cellVisited[knightPosition[0]][knightPosition[1]] = true;

    ChessCell t;
    int x, y;
    while (!q.empty())
    {
        t = q.front();
        q.pop();
        if (t.xCoordinate == targetPosition[0] && t.yCoordinate == targetPosition[1])
            return t.distance;
        for (int i = 0; i < 8; i++)
        {
            x = t.xCoordinate + dx[i]; // dx[i] is the horizontal movement of the knight. It is added to the current x-coordinate of the knight to get the new x-coordinate.
            y = t.yCoordinate + dy[i]; // dy[i] is the vertical movement of the knight. It is added to the current y-coordinate of the knight to get the new y-coordinate.
            if (isValidChessBoardCell(x, y, N) && !cellVisited[x][y])
            {
                cellVisited[x][y] = true;
                q.push(ChessCell(x, y, t.distance + 1));
            }
        }
    }
    return 0;
}

void seedRandGenerator()
{
    srand(time(0)); // seeds the rand function with a new unpredictable stating value ie. current time in seconds
}

int call_answerforKnights()
/*

Sets up and execute the knight's move problem.

The function first generates a random size N for the chessboard, with N ranging between 6 and 10 (inclusive). This is done using the rand() function.
Random Starting and Target Positions:

It then randomly generates the starting position (knightPos) and the target position (targetPos) for the knight on the chessboard. Both positions are ensured to be within the bounds of the generated chessboard size.
Displaying Game Information:

The function prints out the size of the chessboard and the starting and target positions of the knight, informing the user about the current game setup.

It calls minKnightsmove with the starting position, target position, and chessboard size to compute the minimum number of moves required for the knight to reach the target.

The function returns the number of moves calculated by minKnightsmove.
*/
{
    seedRandGenerator();
    int N = (rand() % (11 - 6)) + 6;
    int knightPosition[2], targetPosition[2];

    knightPosition[0] = rand() % (N) + 1;
    knightPosition[1] = rand() % (N) + 1;
    targetPosition[0] = rand() % (N) + 1;
    targetPosition[1] = rand() % (N) + 1;
    cout << endl;
    cout << "\t\t THE KNIGHT'S MOVE" << endl;
    cout << "Given a square chessboard of " << N << "x" << N << "size, the position of Knight and position of atarget is given, Your task is to find out the minimum steps a Knight will take to reach the target position. Can you answer this puzzle?" << endl;
    cout << "........If you answer it correctly then you go onto the next game otherwise the Game ends here........" << endl;
    cout << "The Knight's Position is {" << knightPosition[0] << "," << knightPosition[1] << "}" << endl;
    cout << "The target Position is {" << targetPosition[0] << "," << targetPosition[1] << "}" << endl;
    int minMoves = minKnightsmove(knightPosition, targetPosition, N);
    visualizeKnightMoves(knightPosition[0],knightPosition[1], targetPosition[0],targetPosition[1],N );
    return minMoves;
}

int minSnakeLadderMoves(map<int, int> ladders, map<int, int> snakes)
/*
It calculates the minimum number of moves required to reach the 100th square from the 1st square on the game board. The function uses a breadth-first search (BFS) algorithm.
ladders is a map that stores the starting and ending positions of all the ladders on the game board.
snakes is a map that stores the starting and ending positions of all the snakes on the game board.

*/
{
    int numberOfMoves = 0; // as initially moves is 0.
    queue<int> q;
    q.push(1);
    /*
    Snakes and Ladders game is played on a 10x10 board, comprising 100 squares, numbered from 1 to 100.
    In C++, arrays and vectors are zero-indexed.
    However, in the context of the game, squares are numbered starting from 1, not 0.
    Hence we create a vector of size 101, and initialize all elements to 0.
    */
    vector<int> isVisited(101, 0);
    isVisited[1] = true;
    bool found = false;
    while (!q.empty() and !found)
    {
        int sz = q.size();
        while (sz--)
        {
            int t = q.front();
            q.pop();
            for (int die = 1; die <= 6; die++)
            {
                if (t + die == 100)
                {
                    found = true;
                }
                if (t + die <= 100 && ladders[t + die] && !isVisited[ladders[t + die]])
                {
                    isVisited[ladders[t + die]] = true; // it means we have visited the top of the ladder.
                    if (ladders[t + die] == 100)
                    {
                        found = true;
                    }
                    q.push(ladders[t + die]);
                }
                else if (t + die <= 100 && snakes[t + die] && !isVisited[snakes[t + die]])
                {
                    isVisited[snakes[t + die]] = true; // it means we have visited the tail of the snake.
                    if (snakes[t + die] == 100)
                        found = true;
                    q.push(snakes[t + die]);
                }
                else if (t + die <= 100 && !isVisited[t + die] && !snakes[t + die] && !ladders[t + die])
                {
                    isVisited[t + die] = true;
                    q.push(t + die);
                }
            }
        }
        numberOfMoves++;
    }
    return numberOfMoves;
}

int call_answerforSnakeLadder()
/*
The call_answerforSnakeLadder function in your code orchestrates the setup and execution of the "Snakes and Ladders" game problem, ultimately calculating the minimum number of moves required to win the game given a specific configuration of snakes and ladders. Here's a detailed breakdown of its functionality
*/
{

    seedRandGenerator();
    cout << endl;
    cout << "You are the square 1 and have to reach the square 100. You have complete";
    cout << "control over the die and can get any number from 1-6. There will be several";
    cout << "ladders and snake in between. If you moved to the square having ladder then";
    cout << "you will climb up to the square till which the ladder ends. But if you moved to";
    cout << " the square having the head of the snake then you have to move down back to";
    cout << " the square having the tail of that particular snake.";
    cout << "For the given snakes and ladders you have to find the minimum steps to reach";
    cout << "the square 100";
    cout << endl
         << endl;

    // Randomly determines the number of ladders and snakes on the board, ensuring that there are at least 1 and no more than 3 of each.
    int maxLadders = 3;
    int numberOfLadders = (rand() % (maxLadders)) + 1;

    cout << "Number of Ladders = " << numberOfLadders << endl;

    seedRandGenerator();
 

    map<int, int> ladders;
    int ladderStart, ladderEnd;
    for (int i = 0; i < numberOfLadders; i++)
    {
        ladderStart = (rand() % (30 - 2)) + 2;
        ladderEnd = (rand() % (99 - 31)) + 31;
        ladders.insert(pair<int, int>(ladderStart, ladderEnd));
        cout << "Ladder " << i + 1 << " " << ladderStart << "->" << ladderEnd << endl;
    }

    int maxSnakes = 3;
    int numberOfSnakes = (rand() % (maxSnakes)) + 1;
    cout << "Number of Snakes = " << numberOfSnakes << endl;

    fflush(stdin);

    map<int, int> snakes;
    int snakeHead, snakeTail;
    seedRandGenerator();
    for (int i = 0; i < numberOfSnakes; i++)
    {
        snakeHead = (rand() % (99 - 31)) + 31;
        snakeTail = (rand() % (30 - 1)) + 1;
        snakes.insert(pair<int, int>(snakeHead, snakeTail));
        cout << "Snake " << i + 1 << " " << snakeHead << "->" << snakeTail << endl;
    }
       visualizeBoard(ladders, snakes, 1);    
    int moves = minSnakeLadderMoves(ladders, snakes);
    return moves;
}

int stackForComputer[4];
int stackForUser[4];
int topForUser = -1;
int topForComputer = -1;

void pushforcomputer(int value)
{
    topForComputer++;
    stackForComputer[topForComputer] = value;
}
void pushforuser(int value)
{
    topForUser++;
    stackForUser[topForUser] = value;
}
void MasterMind()
{
    cout << "\n Welcome to the last level, MASTERMIND !!" << endl;
    cout << "Here are the rules for the game " << endl;
    cout << "We will be setting a 5 digit/color code for you and you have to break it to win CHICKEN DINNER" << endl;
    cout << "1-If a digit/color is correct and is at correct position then it will get marked with @" << endl;
    cout << "2-If a digit/color is correct but at incorrect position then it will get marked with!" << endl;
    cout << "3-If the digit/color is not in the code then it will get marked with *" << endl
         << endl;
    cout << "😈  You have to guess in less than 12 attempts" << endl;
    string choice;
    againchoice:
    cout << "Choose between COLOR or DIGIT,Enter your choice" << endl;
    cin >> choice;
    transform(choice.begin(), choice.end(), choice.begin(), ::toupper);

    cout << endl;
    if (choice == "COLOR")
    {
        cout << endl;
        cout << endl
             << "Now you have to guess a 4 color code and remember that 2 colors can be repeated" << endl
             << endl;
        cout << "Variety of colors- White(0),Black(1),Orange(2),Yellow(3),Purple(4),Cyan(5),Green(6),Violet(7),Peach(8),Brown(9)" << endl
             << endl;

        // creates a unique number in between 1000 and 9999
        int computernumber = rand() % (9999 - 1000 + 1) + 1000;
        int localvariable2 = computernumber;
        while (localvariable2 > 0)
        {
            pushforcomputer(localvariable2 % 10);
            localvariable2 = localvariable2 / 10;
        }
        int usernumber;
        int attempts = 0;
        cout << "Guess the color code";
        while (attempts <= 12)
        {
            cout << endl;
            cin >> usernumber;
            cout << endl;
            topForUser = -1;
            attempts++;
            if (usernumber == computernumber)
            {
                cout << "VICTORY" << endl;
                return;
            }
            else
            {
                while (usernumber > 0)
                {
                    pushforuser(usernumber % 10);
                    usernumber = usernumber / 10;
                }
                for (int i = topForComputer; i >= 0; i--)
                {
                    int j = 0;
                    if (stackForUser[i] == stackForComputer[i])
                    {
                        cout << "@";
                    }
                    else if (stackForUser[i] != stackForComputer[i])
                    {
                        int top = 0;
                        for (int j = topForComputer; j >= 0; j--)
                        {
                            if (stackForUser[i] == stackForComputer[j])
                            {
                                top++;
                            }
                        }
                        if (top == 0)
                        {
                            cout << "*";
                        }
                        else
                        {
                            cout << "!";
                        }
                    }
                    else
                    {
                        cout << "*";
                    }
                }
            }
        }
    }
    else if (choice == "DIGIT")
    {
        cout << "Now you have to guess a 4 digit number and remember that 2 digits can be repeated" << endl;
        int computernumber = rand() % (9999 - 1000 + 1) + 1000;
        // creates a unique number in between 1000 and 9999
        int localvariable2 = computernumber;
        while (localvariable2 > 0)
        {
            pushforcomputer(localvariable2 % 10);
            localvariable2 = localvariable2 / 10;
        }
        int usernumber;
        int attempts = 0;
        cout << endl
             << "Guess the number" << endl
             << endl;
        while (attempts <= 12)
        {
            cout << endl;
            cin >> usernumber;
            cout << endl;
            topForUser = -1;
            attempts++;
            if (usernumber == computernumber)
            {
                cout << "VICTORY IN " << attempts << " ATTEMPTS" << endl;
                return;
            }
            else
            {
                while (usernumber > 0)
                {
                    pushforuser(usernumber % 10);
                    usernumber = usernumber / 10;
                }
                for (int i = topForComputer; i >= 0; i--)
                {
                    int j = 0;
                    if (stackForUser[i] == stackForComputer[i])
                    {
                        cout << "@";
                    }
                    else if (stackForUser[i] != stackForComputer[i])
                    {
                        int top = 0;
                        for (int j = topForComputer; j >= 0; j--)
                        {
                            if (stackForUser[i] == stackForComputer[j])
                            {
                                top++;
                            }
                        }
                        if (top == 0)
                        {
                            cout << "*";
                        }
                        else
                        {
                            cout << "!";
                        }
                    }
                    else
                    {
                        cout << "*";
                    }
                }
            }
        }
    }
    else
    {
        cout << "Please Enter a valid choice " << endl;
        goto againchoice;
    }
}
void printSeparator() {
    cout << "============================================\n";
}

int main()
{
 srand(time(0)); // Seed for randomization

    printSeparator();
    cout << "           Welcome to the Ultimate Gaming Challenge!\n";
    printSeparator();
    cout << "Complete three levels to prove your gaming prowess.\n\n";

  
    cout << "Level 1: Roll the dice in 'Snake and Ladders'. Reach 100 to advance.\n";
    cout << "   ___         ___         ___         ___\n";
    cout << "  |       |       |       |       |       |       |       |\n";
    cout << "  |       |       |       |       |       |       |       |\n";
    cout << "  |   " << rand() % 6 + 1 << "   |       |       |       |       |       |       |\n";
    cout << "  |__|__|__|__|__|__|___|\n\n";

    
    cout << "Level 2: Guess 'The Knight's Move' steps from source to target.\n";
    cout << "   ___         ___         ___\n";
    cout << "  |       |       |       |       |       |\n";
    cout << "  |       |       |       |       |       |\n";
    cout << "  |   K   |       |       |   T   |       |\n";
    cout << "  |__|__|__|__|___|\n\n";

    
    cout << "Level 3: 'Mastermind Break the Code' in <12 attempts.\n";
    cout << "   ___   ___   ___   ___   ___\n";
    cout << "  |       | |       | |       | |       | |       |\n";
    cout << "  |   *   | |   *   | |   *   | |   *   | |   *   |\n";
    cout << "  |__| |__| |__| |__| |___|\n\n";

    cout << "Can you conquer all three levels and emerge victorious? Let the games begin!\n";
    getch();
    fflush(stdin);
    system("cls");

    cout << "\t \t \t Welcome to our First Game i.e 'Snakes and Ladders'" << endl;
    int movesSnake = call_answerforSnakeLadder();
    int b;
    cout << "Enter the minimum steps you think it is required to win the game: ";
    cin >> b;
    if (b == movesSnake)
    {
        cout << "CONGRATULATIONS!! Your answer is correct.You can proceed further to our next game i.e. Knight's Tour";
        system("cls");

        int Knightsmove = call_answerforKnights();
        int usermoves;
        cout << "Enter the minimum number of moves: ";
        int f = 0;
        while (f == 0)
        {
            cin >> usermoves;
            if (usermoves > 0)
                f = 1;
            else
                cout << "Please enter a non negative number";
        }
        if (usermoves == Knightsmove)
        {
            cout << "Yayy!! You have answered it correctly" << endl;
            system("cls");
            MasterMind();
        }
        else
        {
            cout << "Oh No!! Your answer is wrong" << endl;
            cout << "The Minimum No of moves are " << Knightsmove << endl;
            cout << "The game ends here";
        }
    }
    else
    {
        cout << "OOPS!! The required steps are:" << movesSnake;
        cout << "\n Since your answer was wrong.You cannot proceed further!!! The game ends here!" << endl;
    }
}