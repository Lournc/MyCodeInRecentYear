from collections import deque

start = (2, 8, 3,
         1, 0, 6,
         7, 5, 4)

goal = (2, 8, 3,
        1, 5, 0,
        7, 4, 6)

moves = {
    0: [1, 3],
    1: [0, 2, 4],
    2: [1, 5],
    3: [0, 4, 6],
    4: [1, 3, 5, 7],
    5: [2, 4, 8],
    6: [3, 7],
    7: [4, 6, 8],
    8: [5, 7]
}

def bfs(start, goal):
    queue = deque()
    visited = set()
    queue.append((start, []))  # 每个元素是 (状态, 路径)
    visited.add(start)

    while queue:
        current, path = queue.popleft()
        if current == goal:
            return path + [current]

        zero_index = current.index(0)
        for move in moves[zero_index]:
            new_state = list(current)
            # 交换 0 和目标位置
            new_state[zero_index], new_state[move] = new_state[move], new_state[zero_index]
            new_state_tuple = tuple(new_state)

            if new_state_tuple not in visited:
                visited.add(new_state_tuple)
                queue.append((new_state_tuple, path + [current]))

    return None  # 未找到路径

def print_state(state):
    for i in range(0, 9, 3):
        print(state[i:i+3])
    print()

solution = bfs(start, goal)

if solution:
    print("解路径如下，共", len(solution)-1, "步：")
    for step, state in enumerate(solution):
        print(f"Step {step}:")
        print_state(state)
else:
    print("未找到解。")
