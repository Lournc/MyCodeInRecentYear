#include <iostream>
#include <utility>
#include <ctime>
#include <map>
using namespace std;
pair<int, int> djsFind(map<pair<int, int>, pair<int, int>> &map, pair<int, int>& locate) {
    if (map[locate] == locate) {
        return locate;
    }
    return djsFind(map, map[locate]);
}
void djs(map<pair<int, int>, pair<int, int>>& map, int m, int n) {
    int v;
    int num{};
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            cin >> v;
            if (v == 1) {
                map[{i, j}] = {i, j};
                num++;
                if(map[{i - 1, j}] != make_pair(0, 0)) {
                    map[{i, j}] = map[{i - 1, j}];
                    num--;
                }
                if (map[{i, j - 1}] != make_pair(0, 0)) {
                    if(map[{i, j}] != make_pair(i, j)) {
                        if (djsFind(map ,map[{i, j}]) == djsFind(map, map[{i, j - 1}])) {
                            num++;
                        }
                        map[map[{i, j}]] = map[{i, j - 1}];
                    } else {
                        map[{i, j}] = map[{i, j - 1}];
                    }
                    num--;
                }
            }
        }
    }
    cout << "岛屿数量" << num << endl;
}
// 计算从(i, j)位置开始的岛屿数量
void countIslands(int** grid, int rows, int cols, int i, int j) {
    // 如果当前位置不是陆地，返回
    if (i < 0 || j < 0 || i >= rows || j >= cols || grid[i][j] == 0) {
        return;
    }

    // 将当前位置标记为已访问
    grid[i][j] = 0;

    // 继续搜索相邻的位置
    countIslands(grid, rows, cols, i - 1, j);
    countIslands(grid, rows, cols, i + 1, j);
    countIslands(grid, rows, cols, i, j - 1);
    countIslands(grid, rows, cols, i, j + 1);
}
int main() {
    int m, n;
    cout << "输入整个地图长和宽\n";
    cin >> m >> n;
    map<pair<int, int>, pair<int, int>> mapp;
    cout << "输入地图信息 0代表水域 1代表陆地\n";
    cout << "并查集实现：\n";
    djs(mapp, m, n);
    cout << "dfs算法实现: \n";
    srand(time(NULL));
    // 创建二维数组
    int rows = m;
    int cols = n;
    int** grid = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        grid[i] = (int*)malloc(cols * sizeof(int));
    }

    // 随机生成二维数组
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = rand() % 2;
        }
    }
    // 打印二维数组
    printf("随机生成的二维数组：\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    // 计算岛屿数量
    int islandCount = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                islandCount++;
                countIslands(grid, rows, cols, i, j);
            }
        }
    }

    printf("岛屿的数量为：%d\n", islandCount);
    // 释放内存
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
    return 0;
}