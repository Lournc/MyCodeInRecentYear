#include <ctime>
#include <iostream>

#define length 7 // 行列，正方形，雷数与之相同

using namespace std;

void panduan(int, int, int);
void zhadan();
void shuchu();
void qingchu();
void win();
int wina = 0;
int map[length + 2][length + 2];
bool vimap[length + 2][length + 2];
bool de = 0;

int main() {

  while (1) {
    qingchu();
    de = 0;
    zhadan();
    while (!de) {
      shuchu();
      int x, y;
      cin >> x >> y;
      panduan(x, y, 1);
      win();
      if (wina == length) {
        cout << "You win!\n";
        wina = 0;
        break;
      }
      wina = 0;
    }
  }
}

void zhadan() {
  srand((int)time(0));
  for (int i = 0; i < length; i++) {
    int x = rand() % length + 1;
    int y = rand() % length + 1;
    if (map[x][y] < length + 1) {
      map[x][y] += length + 1;
      map[x - 1][y - 1]++;
      map[x][y - 1]++;
      map[x + 1][y - 1]++;
      map[x - 1][y]++;
      map[x + 1][y]++;
      map[x - 1][y + 1]++;
      map[x][y + 1]++;
      map[x + 1][y + 1]++;
    } else
      i--;
  }
}

void shuchu() {
  printf("    ");
  for (int i = 1; i <= length; i++)
    printf("%d  ", i);
  cout << endl;
  for (int m = 1; m < length + 1; m++) {
    printf("%d  ", m);
    for (int n = 1; n < length + 1; n++) {
      if (vimap[m][n] == 1) {
        if (map[m][n] >= length + 1)
          printf(" * ");
        else
          cout << " " << map[m][n] << " ";
      } else
        cout << " □ ";
    }
    cout << endl;
  }
}

void panduan(int x, int y, int a) {
  if (x > length || y > length || x < 1 || y < 1)
    return;
  if (vimap[x - 1][y - 1] == 1 && vimap[x][y - 1] == 1 &&
      vimap[x + 1][y - 1] == 1 && vimap[x - 1][y] == 1 &&
      vimap[x + 1][y] == 1 && vimap[x - 1][y + 1] == 1 &&
      vimap[x][y + 1] == 1 && vimap[x + 1][y + 1] == 1)
    return;
  if (map[x][y] < length + 1) {
    vimap[x][y] = 1;
    if (map[x][y] == 0) {
      vimap[x - 1][y - 1] = 1;
      vimap[x][y - 1] = 1;
      vimap[x + 1][y - 1] = 1;
      vimap[x - 1][y] = 1;
      vimap[x + 1][y] = 1;
      vimap[x - 1][y + 1] = 1;
      vimap[x][y + 1] = 1;
      vimap[x + 1][y + 1] = 1;
      panduan(x, y - 1, 2);
      panduan(x - 1, y, 2);
      panduan(x + 1, y, 2);
      panduan(x, y + 1, 2);
    }
  } else if (a == 2)
    ;
  else {
    de = 1;
    for (int i = 1; i < length + 1; i++)
      for (int m = 1; m < length + 1; m++)
        vimap[i][m] = 1;
    shuchu();
    cout << "你死了\n";
  }
}

void qingchu() {
  for (int i = 0; i < length + 2; i++)
    for (int m = 0; m < length + 2; m++) {
      map[i][m] = 0;
      vimap[i][m] = 0;
    }
}

void win() {
  for (int i = 1; i < length + 1; i++)
    for (int m = 1; m < length + 1; m++)
      if (vimap[i][m] == 0)
        wina++;
}