#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define MAX_PATH_LEN (1024)

void getInput(void);
bool check(int row, int col);
void tryInsert(int num);
void printRes(void);

int sudoku[9][9];
clock_t start, finish;

void getInput(void)
{
    int i, j;
    int choice;

    printf("Choose input method (1=keyboard, 2=file): ");
    scanf("%d", &choice);
    while (choice != 1 && choice != 2) {
        printf("Invalid choice!\n");
        printf("Choose input method (1=keyboard, 2=file): ");
        scanf("%d", &choice);
    }
    setbuf(stdin, NULL);

    if (choice == 1) {	// input from keyboard
        printf("Input sudoku:\n");
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                scanf("%d", &sudoku[i][j]);
            }
        }
    }
    else {	// input from file
        FILE *fin;
        char *fpath = new char[MAX_PATH_LEN + 1];

        printf("Input file path: ");
        cin.getline(fpath, MAX_PATH_LEN);
        fin = fopen(fpath, "r");

        if (!fin) {
            printf("Open file error!\n");
            system("pause");
            exit(-1);
        }

        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                fscanf(fin, "%d", &sudoku[i][j]);
            }
        }

        fclose(fin);
    }
}

bool check(int row, int col)
{
    int i, j;

    // row check
    for (j = 0; j < 9; j++) {
        if (sudoku[row][j] == sudoku[row][col] && col != j) {
            return false;
        }
    }

    // column check
    for (i = 0; i < 9; i++) {
        if (sudoku[i][col] == sudoku[row][col] && row != i) {
            return false;
        }
    }

    // block check
    for (i = row / 3 * 3; i < row / 3 * 3 + 3; i++) {
        for (j = col / 3 * 3; j < col / 3 * 3 + 3; j++) {
            if (sudoku[i][j] == sudoku[row][col] && !(i == row && j == col)) {
                return false;
            }
        }
    }

    return true;
}

void tryInsert(int num)
{
    int row = num / 9, col = num % 9, tmp;
    if (num == 81) {  // Sudoku completed
        finish = clock();
        printRes();
        throw 'E';  // only need to find one solution
    }
    else if (sudoku[row][col] == 0) {
        for (tmp = 1; tmp <= 9; tmp++) {
            sudoku[row][col] = tmp;
            if (check(row, col)) tryInsert(num + 1);   // enter the next level
        }
        sudoku[row][col] = 0; // backtrace
    }
    else tryInsert(num + 1);
}

void printRes(void)
{
    int i, j;
    double dur;

    printf("\nSolution:\n");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%1d ", sudoku[i][j]);
        }
        printf("\n");
    }

    dur = double(finish - start) / CLOCKS_PER_SEC;    // calculate time
    printf("Time used: %.3fs\n", dur);
}

int main()
{
    getInput();
    start = clock();
    try {
        tryInsert(0);   // start recursion
    }
    catch (char e) {
        if (e != 'E') {
            printf("Oops! Something wrong!\n");
        }
    }

    system("pause");
    return 0;
}
