#include <iostream>
#include <queue>

using namespace std;

class Task {
public:
    char name;
    int deadline;
    int fine;

    Task(char a, int b, int c) : name(a), deadline(b), fine(c) {
    }


    bool operator<(const Task& other) const {
        return fine < other.fine;
    }
};

class UnionFind {
public:
    vector<char> parent;
    vector<int> rank;
    vector<int> frees;

    void print_parent() {
        for (int i = 0; i < parent.size(); i++) {
            cout << parent[i] << " ";
        }
        cout << "\n";
    }

    void print_rank() {
        for (int i = 0; i < parent.size(); i++) {
            cout << rank[i] << " ";
        }
        cout << "\n";
    }

    void print_frees() {
        for (int i = 0; i < parent.size(); i++) {
            cout << frees[i] << " ";
        }
        cout << "\n";
    }
                

    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        frees.resize(size);
        frees[0] = 0;
        frees[1] = 0;
        for (int i = 0; i < size; i++) {
            if (i != 0) frees[i] = i-1;
        }

    }

    void add(Task t) {
        
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            }
            else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            }
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

class Timetable {
public:
    vector<Task> table;

    Timetable(int size) {
        table = vector<Task>(size, Task(' ', 0, 0));
        table[0] = Task('-', 0, 0);
    }

    void push_right(Task t) {
        int i = table.size() - 1;
        while (true) {
            if (table[i].name == ' ') {
                table[i] = t;
                return;
            }
            else {
                i--;
            }
            if (i == 0) { cout << "smthg wrong!"; exit(0); }
        }
    }

    void push_left(Task t) {
        int i = t.deadline - 1;
        while (i != 0) {
            if (table[i].name == ' ') {
                table[i] = t;
                return;
            }
            else {
                i--;
            }
        }
        push_right(t);
    }

    void print() {
        for (int i = 0; i < table.size(); i++) {

            if (table[i].name != ' ' && table[i].name != '-') cout << table[i].name << "   ";
        }
        cout << "\n";
    }
};

class Timetable_U {
public:
    vector<Task> table;

    Timetable_U(int size) {
        table = vector<Task>(size, Task(' ', 0, 0));
        table[0] = Task('-', 0, 0);
    }

};

int main() {

    /*
        СДЕЛАТЬ УФ ПО ДЕДЛАЙНАМ
        ДЛЯ КАЖДОГО КЛАССА СОХРАНЯТЬ БЛИЖАЙШЕЕ СВОБОДНОЕ МЕСТО
        -ВЕКТОР
    */

    UnionFind uf(5);
  

    priority_queue<Task> taskQueue;
    Timetable tt(10);
    
    taskQueue.push(Task('A', 3, 25));
    taskQueue.push(Task('B', 4, 10));
    taskQueue.push(Task('C', 1, 30));
    taskQueue.push(Task('D', 3, 50));
    taskQueue.push(Task('E', 3, 20));
    



    /*while (!taskQueue.empty()) {
        Task maxTask = taskQueue.top();
        taskQueue.pop();
    
        if (tt.table[maxTask.deadline].name == ' ') {
            tt.table[maxTask.deadline] = maxTask;
        } else {
            tt.push_left(maxTask);
        }
    }
    */



    return 0;
}
