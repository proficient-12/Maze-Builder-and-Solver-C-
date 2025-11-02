/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <iostream>
#include <stack>
#include <utility>
using namespace std;

class MazeSolver {
private:
    char maze[5][5];
    bool visited[5][5];
    pair<int, int> start, end;

    bool isValid(int x, int y) {
        return (x >= 0 && x < 5 && y >= 0 && y < 5 && maze[x][y] != '1' && !visited[x][y]);
    }

public:
    MazeSolver() {
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++) {
                maze[i][j] = '0';
                visited[i][j] = false;
            }
    }

    void inputMaze() {
        cout << "\nEnter your 5x5 maze row by row (use 0=path, 1=wall, S=start, E=end):\n";
        int sCount = 0, eCount = 0;
        for (int i = 0; i < 5; i++) {
            cout << "Row " << i + 1 << ": ";
            for (int j = 0; j < 5; j++) {
                cin >> maze[i][j];
                visited[i][j] = false;
                if (maze[i][j] == 'S') {
                    start = {i, j};
                    sCount++;
                }
                if (maze[i][j] == 'E') {
                    end = {i, j};
                    eCount++;
                }
            }
        }
        if (sCount != 1 || eCount != 1)
            cout << "\n⚠️ Error: Maze must contain exactly one 'S' and one 'E'.\n";
        else
            cout << "\n✅ Maze input successfully!\n";
    }

    void displayMaze() {
        cout << "\nCurrent Maze:\n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++)
                cout << maze[i][j] << " ";
            cout << endl;
        }
    }

    void solveMaze() {
        stack<pair<int, int>> s;
        s.push(start);
        visited[start.first][start.second] = true;
        int dx[4] = {-1, 0, 1, 0};
        int dy[4] = {0, 1, 0, -1};
        bool pathFound = false;
        while (!s.empty()) {
            pair<int, int> current = s.top();
            int x = current.first;
            int y = current.second;
            if (maze[x][y] == 'E') {
                pathFound = true;
                break;
            }
            bool moved = false;
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (isValid(nx, ny)) {
                    visited[nx][ny] = true;
                    s.push({nx, ny});
                    moved = true;
                    break;
                }
            }
            if (!moved)
                s.pop();
        }
        if (pathFound) {
            cout << "\n✅ Path Found! Displaying solved maze:\n";
            while (!s.empty()) {
                pair<int, int> p = s.top();
                s.pop();
                if (maze[p.first][p.second] != 'S' && maze[p.first][p.second] != 'E')
                    maze[p.first][p.second] = '*';
            }
            displayMaze();
        } else
            cout << "\n❌ No solution found.\n";
    }
};

int main() {
    MazeSolver solver;
    int choice;
    do {
        cout << "\n========= MAZE BUILDER AND SOLVER =========\n";
        cout << "1. Input and Solve Maze\n";
        cout << "2. Display Current Maze\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                solver.inputMaze();
                solver.solveMaze();
                break;
            case 2:
                solver.displayMaze();
                break;
            case 0:
                cout << "\nExiting program... Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 0);
    return 0;
}
