#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

const int WIDTH = 21;
const int HEIGHT = 11;

const char WALL = '#';
const char EMPTY = ' ';
const char MOUSE = 'M';
const char GOAL = 'G';

struct Position {
  int x, y;
};

char maze[HEIGHT][WIDTH];
Position mouse, goal;
vector<Position> path;

#ifdef _WIN32
void clearScreen() { system("cls"); }
#else
void clearScreen() {
  cout << "\033[2J\033[1;1H"; // ANSI 清屏
}
int kbhit() {
  termios oldt, newt;
  int ch;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if (ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}
#endif

void generateMaze() {
  // Step 1: 全部设为墙
  for (int y = 0; y < HEIGHT; ++y)
    for (int x = 0; x < WIDTH; ++x)
      maze[y][x] = WALL;

  mouse = {1, 1};
  goal = {WIDTH - 2, HEIGHT - 2};
  path.clear();

  // Step 2: 主路径挖通
  Position pos = mouse;
  maze[pos.y][pos.x] = EMPTY;
  path.push_back(pos);

  while (!(pos.x == goal.x && pos.y == goal.y)) {
    int dx = 0, dy = 0;
    if (pos.x != goal.x && (rand() % 2 || pos.y == goal.y))
      dx = (goal.x > pos.x) ? 1 : -1;
    else if (pos.y != goal.y)
      dy = (goal.y > pos.y) ? 1 : -1;

    pos.x += dx;
    pos.y += dy;

    if (pos.x >= 1 && pos.x < WIDTH - 1 && pos.y >= 1 && pos.y < HEIGHT - 1) {
      maze[pos.y][pos.x] = EMPTY;
      path.push_back(pos);
    }
  }

  // Step 3: 遍历地图，加随机空地或障碍（不动边框和主路径）
  for (int y = 1; y < HEIGHT - 1; ++y) {
    for (int x = 1; x < WIDTH - 1; ++x) {
      // 忽略主路径
      bool isPath = false;
      for (auto &p : path) {
        if (p.x == x && p.y == y) {
          isPath = true;
          break;
        }
      }
      if (!isPath) {
        // 60% 概率为空地
        maze[y][x] = (rand() % 100 < 60) ? EMPTY : WALL;
      }
    }
  }

  // Step 4: 设置鼠标和目标
  maze[mouse.y][mouse.x] = MOUSE;
  maze[goal.y][goal.x] = GOAL;
}

void drawMaze() {
  clearScreen();
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x)
      cout << maze[y][x];
    cout << endl;
  }
  cout << "使用 WASD 移动老鼠 (M) 到粮仓 (G)，按 q 退出。" << endl;
}

bool moveMouse(char dir) {
  int dx = 0, dy = 0;
  if (dir == 'w')
    dy = -1;
  else if (dir == 's')
    dy = 1;
  else if (dir == 'a')
    dx = -1;
  else if (dir == 'd')
    dx = 1;

  int newX = mouse.x + dx;
  int newY = mouse.y + dy;

  if (maze[newY][newX] == WALL)
    return false;

  // 移动
  maze[mouse.y][mouse.x] = EMPTY;
  mouse.x = newX;
  mouse.y = newY;
  maze[mouse.y][mouse.x] = MOUSE;
  return mouse.x == goal.x && mouse.y == goal.y;
}

int main() {
  srand(time(0));
  generateMaze();

  bool won = false;
  drawMaze();

  auto start = chrono::steady_clock::now();
  int timeLimit = 60; // 秒

  while (true) {
    if (
#ifdef _WIN32
        _kbhit()
#else
        kbhit()
#endif
    ) {
      char ch =
#ifdef _WIN32
          _getch();
#else
          getchar();
#endif

      if (ch == 'q')
        break;
      if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') {
        won = moveMouse(ch);
        drawMaze();
        if (won)
          break;
      }
    }

    auto now = chrono::steady_clock::now();
    int elapsed = chrono::duration_cast<chrono::seconds>(now - start).count();
    if (elapsed >= timeLimit)
      break;

    this_thread::sleep_for(chrono::milliseconds(50));
  }

  drawMaze();
  if (won)
    cout << "🎉 恭喜你找到粮仓，游戏胜利！" << endl;
  else
    cout << "⏰ 游戏结束，未能在时间内找到粮仓。" << endl;

  return 0;
}
