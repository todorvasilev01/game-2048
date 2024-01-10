#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include <fstream>
#include <vector>

using namespace std;


class Game {

public:

    void startGame()
    {

        setcolor(0x06);

        // Display logo
        cout << "\t\t\t\t      ####        ###            #   #       ####        \n";
        cout << "\t\t\t\t     #    #      #   #          #    #      #    #       \n";
        cout << "\t\t\t\t    #      #    #     #        #     #     #      #      \n";
        cout << "\t\t\t\t           #   #       #      #      #    #        #     \n";
        cout << "\t\t\t\t          #   #         #    #       #     #      #      \n";
        cout << "\t\t\t\t         #   #           #  ##########      ######       \n";
        cout << "\t\t\t\t        #     #         #            #     #      #      \n";
        cout << "\t\t\t\t       #       #       #             #    #        #     \n";
        cout << "\t\t\t\t      #         #     #              #    #        #     \n";
        cout << "\t\t\t\t     #    #      #   #               #     #      #      \n";
        cout << "\t\t\t\t    #######       ###                #      ######       \n\n";
        cout << "\t\t\t\t    ###############################################      \n\n";
        cout << "\t\t\t\t              Press any key to continue";


        char key;

        key = _getch();

        system("cls");

        // invokes the function that formats initial state of the game
        initializeGame();
    }



    // function that saves current state of the game
    // receives file name as parameter
    void saveGame(string filename)
    {

        // attach the file 
        ofstream outFile(filename);

        // check if the stream is attached to file
        if (outFile.is_open())
        {
            // saves current scores
            outFile << score << endl;

            // iterates current state of the game field
            for (int row = 0; row < 4; row++)
            {
                for (int col = 0; col < 4; col++)
                {
                    // saves every row in new line 
                    outFile << gameField[row][col] << " ";

                }
                outFile << "\n";
            }
        }
    }

    // function that loads current state of game
    // this function is analogous to the save function
    void loadGame(string filename)
    {

        ifstream inFile(filename);

        if (inFile.is_open())
        {

            inFile >> score;

            for (int row = 0; row < 4; row++)
            {
                for (int col = 0; col < 4; col++)
                {

                    inFile >> gameField[row][col];

                }
            }
        }
    }



private:

    // Start score
    int score = 0;

    // Game field 2d-array with 4 rows and 4 cols with starting numbers - 0
    int gameField[4][4] = { 0 };

    // Temporary field to check for movement in the initial game field
    int tempField[4][4] = { 0 };


    // this function set up color of the interface relative to where it is invoked
    void setcolor(unsigned char color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }


    // function that initiliaze tile start possition 
    void initializeGame()
    {

        // initializing of 2 numbers for game field start position
        int num1, num2;

        // this method produces a series of random numbers
        srand((unsigned int)time(0));

        // generating 2 random numbers for game field position 
        num1 = rand() % 4;
        num2 = rand() % 4;

        // start random positition value = 2
        gameField[num1][num2] = 2;

        // invoking game visualisation function to draw the game field with the start number
        displayGameField(gameField);

        // invoking function that creates move logic
        createMove();

    }


    // this function creates move logic
    void createMove()
    {

        // initializing command for the moves
        int cmd;

        // this loop will create new moves before the game ends 
        while (true)
        {

            // iterate the game field to assign its value in the temporary field.
            // So that it can be checked for movement in the game field
            for (int row = 0; row < 4; row++)
            {
                for (int col = 0; col < 4; col++)
                {

                    tempField[row][col] = gameField[row][col];

                }
            }

            // gets command ASCII value from keyboard
            cmd = _getch();

            system("cls");

            // Compares whether the command numbers match ASCII representation of the characters

            // 72 is UP ARROW KEY
            if (cmd == 72)
            {
                // invokes up move and up sum logic with argument - current game field state
                upMove(gameField);
                sumUp(gameField);
            }

            // 75 is LEFT ARROW KEY
            if (cmd == 75)
            {
                // invokes left move and left sum logic
                leftMove(gameField);
                sumLeft(gameField);
            }

            // 77 is RIGHT ARROW KEY 
            if (cmd == 77)
            {
                // invokes right move and right sum logic
                rigthMove(gameField);
                sumRigth(gameField);
            }

            // 80 is DOWN ARROW KEY 
            if (cmd == 80)
            {
                // invokes down move and down sum logic
                downMove(gameField);
                sumDown(gameField);
            }

            // Key "Esc" for quit the game
            if (cmd == 27)
            {
                // diplays final score
                cout << "YOUR GAME HAS ENDED\n";
                cout << "Your score is:" << score << "\n";
                break;

            }

            // Key "SPACE" to start a new game
            if (cmd == 32)
            {

                system("cls");

                cout << "\n\n\t\t\t\t\tDo you want to start a new game?\n\n";
                cout << " \t\t\t\t\t       Press 'Y' for YES\n\n" << "\t\t\t\t\t       Press 'N' for No";

                char key;

                key = _getch();

                system("cls");

                // if key 'Y' ot 'y' is pressed starts new game
                if (key == 121 || key == 89)
                {

                    // Resets the score
                    score = 0;

                    // Resets the game and temporary field
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            gameField[i][j] = 0;
                            tempField[i][j] = 0;
                        }

                    }

                    // invokes a new initialization of the game
                    initializeGame();
                    break;

                }
                // otherwise, pressing 'N' or 'n' key invokes current game state   
                else if (key == 78 || key == 110)
                {
                    initializeGame();
                    break;
                }
                else
                {
                    break;
                }
            }

            // checks if the game field and temporary field аre equal
            if (check(tempField, gameField))
            {

                // if they аre equal the function "addNewNum" adds new number in the field
                addNewNum(gameField);
            }


            // invokes "displayGameField" to visualise the game field with one more number
            displayGameField(gameField);


            // checks the game field. If there are non zero nums the game is over
            if (gameOver(gameField))
            {

                system("cls");

                // displays information
                cout << "\t\t\t\t\t       GAME OVER!\n\n";
                setcolor(0x06);
                cout << "\t\t\t\t\t Your final score is: " << score << "\n\n";
                setcolor(0x07);
                cout << " \t\t\t\t\t  Do you want a new game?\n\n";
                cout << " \t\t\t\t\t    Press 'Y' for YES\n\n" << "\t\t\t\t\t    Press 'N' for No";

                char key;

                // gets the pressed key value from keyboard
                key = _getch();

                system("cls");

                // Reseting the score
                score = 0;

                // Reseting the game and temporary field
                for (int row = 0; row < 4; row++)
                {
                    for (int col = 0; col < 4; col++)
                    {
                        gameField[row][col] = 0;
                        tempField[row][col] = 0;
                    }
                }


                // if key 'Y' or 'y' is pressed 
                // invokes a new initialization of the game
                if (key == 121 || key == 89)
                {
                    initializeGame();
                    break;

                }
                else
                {
                    break;
                }
            }
        }
    }


    // function that checks if the game is over
    // function receives 2d array as parameter
    int gameOver(int a[4][4])
    {

        // initializing row and col of the field
        int row, col;

        // flag = 1 by default
        // if function return flag = 1 then the game ends
        int flag = 1;

        // iterating the game field 
        for (row = 0; row < 4; row++)
        {
            for (col = 0; col < 4; col++)
            {
                // if there are zero the function return flag = 0 and the game continoes
                if (a[row][col] == 0)
                {

                    flag = 0;
                    break;
                }
            }
        }

        return flag;
    }



    // func that checks for changes in the playing field
    // receives two arrays as parameters  - game field and temporary game field
    int check(int tempField[4][4], int gameField[4][4])
    {

        // flag is 0 by default
        // if function return flag = 0, a new number must be added to the field

        int flag = 0;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {

                // this statement checks if current number in temp field is different that initial field number
                // if they are different then there already has been movement on the game field 
                // then function returns flag = 1 and there should be no action on the field

                if (tempField[i][j] != gameField[i][j])
                {

                    flag = 1;

                    break;
                }
            }
        }

        return flag;
    }

    // left move logic
    // receives 2d array as parameter - Game Field
    void leftMove(int a[4][4])
    {
        int row, col;

        // iterating every row of the game field
        for (row = 0; row < 4; row++)
        {

            // iterating every tile from left to right
            for (col = 1; col < 4; col++)
            {

                // checks if current tile is non-zero
                if (a[row][col] != 0)
                {

                    // this loop moves current non-zero element in the left side 
                    // while col is in range and each next element is zero

                    //                <-
                    // e.g: | 0 | 0 | 2 | 0 |     =>    | 2 | 0 | 0 | 0 |

                    while (col > 0 && a[row][col - 1] == 0)
                    {

                        // moves current tile
                        a[row][col - 1] = a[row][col];
                        a[row][col] = 0;
                        col--;
                    }
                }
            }
        }
    }


    // left sum logic
    // receives 2d array as parameter - Game Field
    void sumLeft(int a[4][4])
    {
        int row, col;

        // iterates game field

        for (row = 0; row < 4; row++)
        {

            for (col = 0; col < 3; col++)
            {

                // checks if the current element is equal to the next element
                // if they are equal the next element is merged with the current one, i.e their values are added in one tile
                // next element becomes 0
                // game score increase by their values
                if (a[row][col] == a[row][col + 1])
                {
                    a[row][col] *= 2;
                    a[row][col + 1] = 0;
                    score += a[row][col];
                }

                // checks if current element is zero
                // if it is zero, the function "leftMove" will be invoked which moves the current tile in next zero possitions.

                // e.g: 
                // | 2 | 2 | 4 | 0 | 
                // after adding the tiles with the same values the result will be:
                // | 4 | 0 | 4 | 0 |
                // then we invoke this function to move the tile with value 4 in this way =>
                // | 4 | 4 | 0 | 0 |
                if (a[row][col] == 0)
                {
                    leftMove(gameField);
                }
            }
        }
    }

    // right move logic is analogous to the move left function
    void rigthMove(int a[4][4])
    {

        int row, col;


        // iterates game field 
        for (row = 0; row < 4; row++)
        {


            // starts iterate every tile from right to left
            // e.g:
            //     <--------
            // | 2 | 4 | 0 | 2 |
            for (col = 2; col >= 0; col--)
            {

                if (a[row][col] != 0)
                {

                    // this loop moves current non-zero element in the right side 
                    // while col is in range and each next element is zero
                    while (col < 3 && a[row][col + 1] == 0)
                    {

                        // moves current tile
                        a[row][col + 1] = a[row][col];
                        a[row][col] = 0;

                        // increment tile position
                        col++;

                    }
                }
            }
        }
    }

    void sumRigth(int a[4][4])
    {
        int row, col;


        for (row = 0; row < 4; row++)
        {

            for (col = 3; col > 0; col--)
            {

                // here we starts adding tiles to the rigth side
                // checks if the next right element has the same value as the current
                if (a[row][col] == a[row][col - 1])
                {
                    a[row][col] *= 2;
                    a[row][col - 1] = 0;
                    score += a[row][col];
                }

                if (a[row][col] == 0)
                {
                    rigthMove(gameField);
                }
            }
        }
    }


    void upMove(int a[4][4])
    {

        int row, col;

        // starts iterating the game field from top to bottom 

        for (row = 1; row < 4; row++)
        {

            for (col = 0; col < 4; col++)
            {
                // checks if current tile is non-zero
                if (a[row][col] != 0)
                {

                    // this loop will move the current tile up if each element above is 0
                    while (row > 0 && a[row - 1][col] == 0)
                    {
                        a[row - 1][col] = a[row][col];
                        a[row][col] = 0;
                        row--;
                    }
                }
            }
        }
    }

    void sumUp(int a[4][4])
    {
        int row, col;

        for (row = 0; row < 4; row++)
        {

            for (col = 0; col < 4; col++)
            {

                // here we starts adding tiles to the top side
                // e.g:
                //  this is current row
                //        | 2 |  <- current tile
                //        | 2 |
                //        | 4 |
                //        | 0 | 
                //        
                //    adding equal values  =>
                //        
                //        | 4 | <- current tile
                //        | 0 |
                //        | 4 | 
                //        | 0 | 
                //
                //   the second check is for zeros
                //   if the next tile is 0 we invoke upMove 
                //   the result should be:
                //
                //        | 4 | 
                //        | 4 |
                //        | 0 |
                //        | 0 | 

                if (a[row][col] == a[row + 1][col])
                {
                    a[row][col] *= 2;
                    a[row + 1][col] = 0;
                    score += a[row][col];
                }

                if (a[row][col] == 0)
                {
                    upMove(gameField);
                }
            }
        }
    }


    void downMove(int a[4][4])
    {

        int row, col;

        // iterates the gamefield from bottom to top 
        for (row = 2; row >= 0; row--)
        {

            for (col = 0; col < 4; col++)
            {

                // checks if current tile is non-zero
                if (a[row][col] != 0)
                {

                    // this loop will move the current element down if each next element below is zero
                    while (row < 3 && a[row + 1][col] == 0)
                    {

                        a[row + 1][col] = a[row][col];
                        a[row][col] = 0;
                        row++;
                    }
                }
            }
        }
    }

    void sumDown(int a[4][4])
    {
        int row, col;

        for (row = 3; row > 0; row--)
        {

            for (col = 0; col < 4; col++)
            {

                // here we starts adding tiles to the bottom side
                // e.g:
                //  this is current row
                //        | 0 | 
                //        | 4 |
                //        | 2 |
                //        | 2 | <- current tile
                //        
                //    adding equal values  =>
                //        
                //        | 0 | 
                //        | 4 |
                //        | 0 | 
                //        | 4 | <- current tile
                //
                //   the second check is for zeros
                //   if the next tile is 0 we invoke DownMove 
                //   the result should be:
                // 
                //        | 0 | 
                //        | 0 |
                //        | 4 |
                //        | 4 | 

                if (a[row][col] == a[row - 1][col])
                {
                    a[row][col] *= 2;
                    a[row - 1][col] = 0;
                    score += a[row][col];
                }

                if (a[row][col] == 0)
                {
                    downMove(gameField);
                }
            }
        }
    }

    // function that adds new random number in the game field
    // receives an 2d arr as parameter
    void addNewNum(int a[4][4])
    {

        int num1, num2;

        srand((unsigned int)time(0));

        while (true) {

            num1 = rand() % 4;
            num2 = rand() % 4;

            // adds rand number in the game field where game position number is 0
            if (a[num1][num2] == 0) {

                a[num1][num2] = pow(2, num1 % 2 + 1);

                break;
            }
        }
    }


    // Game field visualization function
    // this function receives as parameter an 2d-array that should iterate and draw the game field
    void displayGameField(int array[4][4])
    {

        // this lines visualises game logo and score table
        setcolor(0x03);
        cout << "\n\t\t\t\t\t\t" << "     **********";
        cout << "\n\t\t\t\t\t\t" << "     *  2048  *";
        cout << "\n\t\t\t\t\t\t" << "     ********** " << "\n\n";
        setcolor(0x06);
        cout << "\t\t\t\t" << "Total score: " << score << "\n\n\n\n";
        setcolor(0x07);
        cout << "\t\t\t\t\t---------------------------------\n";


        // iterates the game field
        // first for-loop draws the rows 

        for (int i = 0; i < 4; i++)
        {

            cout << "\t\t\t\t";

            // second for-loop draws every cell in the current row
            for (int j = 0; j < 4; j++)
            {

                setcolor(0x07);

                // this is separator between the tiles
                cout << "\t|";

                // tiles width;
                cout.width(4);

                setcolor(0x0B);


                // if current tile position numbers is zero, 
                // colorizes them in red color
                if (array[i][j] == 0) {
                    setcolor(0x04);
                }

                cout << array[i][j];

            }

            setcolor(0x07);
            cout.width(4);
            cout << "|";
            // separator after the rows
            cout << "\n\t\t\t\t\t---------------------------------" << endl;
        }


        setcolor(0x06);
        cout << "\n\n\n" << "\t\t\t\t\t\t" << "  Game Controls:" << "\n\n" << endl;

        cout << "\tUP: UP ARROW KEY" << "\tDOWN: DOWN ARROW KEY " << "\t LEFT: LEFT ARROW KEY " << "\t RIGHT: RIGHT ARROW KEY " << "\n\n";
        cout << "\t\tQUIT: ESCAPE" << "\t\t\t\t\t\t" << "SPACE: START NEW GAME";
        setcolor(0x07);

    }
};

int main()
{

    Game game;

    game.loadGame("savegame.txt");

    game.startGame();

    game.saveGame("savegame.txt");

    return 0;

}

