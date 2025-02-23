#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#define X 80
#define Y 25
#define SPMAX 1000000
#define SPMIN 1000
#define DEAD '.'
#define ALIVE '@'

void ncur_init();
int next_time(int matrix_a[Y][X]);
int neighbours(int i, int j, int matrix[Y][X]);
int input(int matrix[Y][X]);
int adjust_speed(int s, char ch);
void output(int matrix[Y][X]);

int main() {
    int matrix[Y][X];
    int speed = 910000;

    if (input(matrix)) {
        ncur_init();

        while (next_time(matrix) != 0) {
            char ch = getch();
            speed = adjust_speed(speed, ch);
            if (ch == 'q') {
                break;
            }
            erase();
            output(matrix);
            usleep(speed);
        }
        endwin();
    } else
        printf("n/a");
    return 0;
}

void ncur_init() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, 1);
    nodelay(stdscr, 1);
}

int input(int matrix[Y][X]) {
  int code = 1;
  int check = 0;
  for (int i = 0; i < Y && code == 1; i++) {
    for (int j = 0; j < X && code == 1; j++) {
      check = scanf("%d", &matrix[i][j]);
      printf("Read matrix[%d][%d] = %d\n", i, j,
             matrix[i][j]);  // Отладочный вывод
      if (check != 1)
        code = 0;
      else if (matrix[i][j] != 0 && matrix[i][j] != 1)
        code = 0;
    }
  }
  freopen("/dev/tty", "r", stdin);
  return code;
}

int adjust_speed(int speed, char ch) {
    if (ch == 'e' && speed < SPMAX - 90000) {
        speed += 90000;
    } else if ((ch == 'r') && (speed >= SPMIN + 90000)) {
        speed -= 90000;
    }
    return speed;
}

int next_time(int matrix_a[Y][X]) {
    int change = 0;
    int matrix_b[Y][X];
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            matrix_b[i][j] = matrix_a[i][j];
        }
    }
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            matrix_a[i][j] = neighbours(i, j, matrix_b);
            if (matrix_a[i][j] != matrix_b[i][j]) change = 1;
        }
    }
    return change;
}

int neighbours(int i, int j, int matrix[Y][X]) {
    int left_coor = j == 0 ? X - 1 : j - 1;
    int right_coor = j == X - 1 ? 0 : j + 1;
    int top_coor = i == 0 ? Y - 1 : i - 1;
    int bottom_coor = i == Y - 1 ? 0 : i + 1;
    int num_neignbours = matrix[top_coor][left_coor] + matrix[top_coor][j] + matrix[top_coor][right_coor];
    num_neignbours += matrix[i][left_coor] + matrix[i][right_coor];
    num_neignbours +=
        matrix[bottom_coor][left_coor] + matrix[bottom_coor][j] + matrix[bottom_coor][right_coor];
    int result;
    if ((num_neignbours == 3) || ((num_neignbours == 2) && (matrix[i][j] == 1)))
        result = 1;
    else
        result = 0;
    return result;
}

void output(int matrix[Y][X]) {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            printw("%c", (matrix[i][j] == 0 ? DEAD : ALIVE));
            if (j < X - 1) printw(" ");
        }
        printw("\n");
    }
}
