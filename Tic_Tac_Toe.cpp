#include <iostream>
#include <stdlib.h>
#include <limits>
#include <iomanip>
#include <windows.h>
#include <cstring>

using namespace std;

void score();
void input_name();
bool exit_game();
void Show_game();
bool check();
void input_game();
void body();
void end();
void SetColor(int text, int background);
void rules();
int win_color();
bool check_color(int i, int j);

int x[3][3]{}, k = 0, first_score = 0, second_score = 0, first_win = 1, second_win = 0;
char first_input, second_input, first_name[20], second_name[20];

void rules()
{
    setlocale(0, "");

    cout << "Rules:\n" <<
    "* Whoever gets 3 'X's or 'O' in a row diagonally, horizontally or vertically first gets 1 point *\n" <<
    "* If someone decides to stop the game, then a point is awarded to the opponent, but no side switching occurs *\n" <<
    "* If zero wins the game, then in the next game the player who played zero already plays crosses *\n" <<
    "* After the end of the number of games you need, the winner is displayed on the screen *\n\n";
}

void SetColor(int text, int background)
{
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void score()
{
    cout << setw(32) << "SCORE:\n";

    if(first_win == 1) SetColor(2, 0);
    else SetColor(4, 0);

    cout << setw(20) << first_name << " = " << first_score << "\n";

    if(second_win == 1) SetColor(2, 0);
    else SetColor(4, 0);

    cout << setw(20) << second_name << " = " << second_score << "\n";

    SetColor(15, 0);

    cout << "-----------------------------------------------------\n";
}

void input_name()
{
    cout << "Enter the nickname of the first player:";
    gets(first_name);

    cout << "Enter the nickname of the second player:";
    gets(second_name);
}

bool exit_game()
{
    bool c = true;

    if(first_input - 48 == 0 && second_input - 48 == 0) c = false;

    return c;
}

void Show_game()
{
    system("cls");

    cout << setw(55) <<"Welcome to the game Tic Tac Toe! by \"Vova)\"\n\n";

    score();

    int i, j;

    const int n = 3;

    int a = win_color();

    cout << setw(35) << "    1   2   3\n  ";

    cout << setw(23);
    for (i = 0; i < n; i++)
        cout << "----";
    cout << "-\n";

    for (i = 0; i < n; i++)
    {
        cout << setw(20) << i + 1 << " ";

        for (j = 0; j < n; j++)
        {
            cout << "| ";

            if (x[i][j] == 1)
            {

                if(check_color(i, j)) SetColor(2, 14);

                else SetColor(2, 0);
                cout << "X";
                SetColor(15, 0);
            }

            else if (x[i][j] == 2)
            {
                if(check_color(i, j)) SetColor(4, 14);

                else SetColor(4, 0);
                cout << "O";
                SetColor(15, 0);
            }

            else cout << " ";

            cout << " ";
        }

        if (i != n - 1)
        {
            cout << "|\n" << setw(22) << "  |";

            for (j = 0; j < n; j++)
            {
                if (j == n - 1) cout << "---";
                else cout << "---+";
            }

            cout << "|\n";
        }

        else cout << "|\n  ";
    }

    cout << setw(23);
    for (i = 0; i < n; i++)
        cout << "----";
    cout << "-\n\n";
}

bool check()
{
    bool c = true;

    int const n = 3;

    for(int i = 0; i < n; i++ && c)
        if(x[i][0] == x[i][1] && x[i][1] == x[i][2] && x[i][0] != 0) c = false;

    for(int i = 0; i < n; i++ && c)
        if(x[0][i] == x[1][i] && x[1][i] == x[2][i] && x[0][i] != 0) c = false;

    if((x[0][0] == x[1][1] && x[1][1] == x[2][2] && x[0][0] != 0) ||
      (x[2][0] == x[1][1] && x[1][1] == x[0][2] && x[2][0] != 0)) c = false;

    return c;

}

bool check_color(int i, int j)
{
    int a = win_color();

    bool c = false;

    if(a)
    {
        if(a % 10 == i && a / 10 == 1) c = true;
        else if(a % 10 == j && a / 10 == 2) c = true;
        else if(a / 10 == 3 && a % 10 == 1 && i == j) c = true;
        else if(a / 10 == 3 && a % 10 == 2 && i + j == 2) c = true;
    }

    return c;
}

int win_color()
{
    bool c = true;

    int const n = 3;

    int a = 0;

    for(int i = 0; i < n; i++ && c)
        if(x[i][0] == x[i][1] && x[i][1] == x[i][2] && x[i][0] != 0)
        {
            a = 10 + i;
            c = false;
        }

    for(int i = 0; i < n; i++ && c)
        if(x[0][i] == x[1][i] && x[1][i] == x[2][i] && x[0][i] != 0)
        {
            a = 20 + i;
            c = false;
        }

    if(x[0][0] == x[1][1] && x[1][1] == x[2][2] && x[0][0] != 0 && c)
        {
            a = 30 + 1;
            c = false;
        }


    if(x[2][0] == x[1][1] && x[1][1] == x[0][2] && x[2][0] != 0 && c)
        {
            a = 30 + 2;
            c = false;
        }

    return a;

}

void input_game()
{
    int first, second, mistake = 0;

    do
        {
            cout << "[00] - Exit game\n";

            if(k % 2 == 1)
            {
                SetColor(2, 0);
                if(first_win == 1) cout << "(" << first_name << ")";
                else cout << "(" << second_name << ")";
            }

            else
            {
                SetColor(4, 0);
                if(second_win == 1) cout << "(" << first_name << ")";
                else cout << "(" << second_name << ")";
            }

            SetColor(15, 0);

            if (mistake == 0)
            {
                if(k % 2 == 1) SetColor(2, 0);
                else SetColor(4, 0);

                cout << "Enter coordinates " << (k % 2 ? "\"X\":" : "\"O\":");

                SetColor(15, 0);
            }

            else
            {
                Show_game();

                cout << "[00] - Exit game\n";

                if(k % 2 == 1)
                {
                    SetColor(2, 0);
                    if(first_win == 1) cout << "(" << first_name << ")";
                    else cout << "(" << second_name << ")";
                }

                else
                {
                    SetColor(4, 0);
                    if(second_win == 1) cout << "(" << first_name << ")";
                    else cout << "(" << second_name << ")";
                }

                cout << "The coordinates are incorrect, please enter them again " << (k % 2 ? "\"X\":" : "\"O\":");

                SetColor(15, 0);
            }

            cin >> first_input >> second_input;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            first = first_input - 49;

            second = second_input - 49;

            mistake++;

        } while ((first > 2 || first < 0 || second > 2 || second < 0 || x[second][first] != 0) && !(first == -1 && second == -1));

    k % 2 ? x[second][first] = 1 : x[second][first] = 2;

}

void body()
{

    do
    {
        Show_game();

        k++;

        input_game();

    } while (check() && k != 9 && exit_game());
}

void end()
{
    if(!exit_game())
    {
        cout << "Game was stoped!\n";

        if(first_win == 1 && k % 2 == 1) second_score += 1;
        else first_score += 1;
    }

    else if(k == 9 && check()) cout << "Game over, draw!\n";

    else
    {
        k % 2 ? SetColor(2, 0) : SetColor(4, 0);

        cout << "\nGame over, " << (k % 2 ? "\"X\" " : "\"O\" ") << "won!";

        if(k % 2 == 1)
            {
                if(first_win == 1) cout << "(" << first_name << ")";
                else cout << "(" << second_name << ")";
            }

        else
        {
            if(second_win == 1) cout << "(" << first_name << ")";
            else cout << "(" << second_name << ")";
        }

        cout << "\n";

        SetColor(15, 0);

        if(k % 2 == 0) swap(first_win, second_win);

        first_score += first_win;
        second_score += second_win;
    }
}

int main()
{
    setlocale(0, "");

    int repeat = 1;

    cout << setw(55) <<"Welcome to the game Tic Tac Toe! by \"Vova)\"\n\n";

    rules();

    input_name();

    do
    {
        body();

        Show_game();

        end();

        do
        {
            cout << "Do you want to play 1 more game?";
            cout << "\n  [1] - YES";
            cout << "\n  [0] - NO\n";

            cin >> repeat;
        }while(repeat > 1 || repeat < 0);

        if(repeat)
        {
            for(int i = 0; i < 3; i++)
                for(int j =0; j < 3; j++)
                    x[i][j] = 0;
            k = 0;
        }

    }while(repeat);

    Show_game();

    if(first_score > second_score) cout << setw(23) << first_name <<" won!!!\n";
    else if (first_score < second_score) cout << setw(23) << second_name <<" won!!!\n";
    else cout << "DRAW!!!\n";

    system("pause");
}
