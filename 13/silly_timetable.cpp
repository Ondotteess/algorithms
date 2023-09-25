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

class UnionFind {
public:



    vector<char> parent;
    vector<int> rank;
    vector<int> frees;

    void print() {
        for (int i = 0; i < parent.size(); i++) {
            cout << i << " ";
        }
        cout << "\t <-Index" << "\n";

        for (int i = 0; i < parent.size(); i++) {
            cout << static_cast<char>(parent[i] + 'A') << " ";
        }
        cout << "\t <-Parent" << "\n";

        for (int i = 0; i < parent.size(); i++) {
            cout << rank[i] << " ";
        }
        cout << "\t\t <- Rank" << "\n";

        for (int i = 0; i < parent.size(); i++) {
            cout << frees[i] << " ";
        }
        cout << "\t <- Frees" << "\n";
    }


    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        frees.resize(size);
        frees[0] = 0;
        frees[1] = 0;
        for (int i = 0; i < size; i++) {
            parent[i] = i;
            frees[i] = i - 1;
        }
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
        // cout << endl << rootX << " " << rootY << endl;
        int min_root = min(frees[rootX], frees[rootY]);

        if (min_root == -1) {
            if (frees[rootX] == -1) {
                frees[rootX] = frees.size() - 1;
                unite(rootX, frees.size() - 1);

            }
            if (frees[rootY] == -1) {
                frees[rootY] = frees.size() - 1;
                unite(rootY, frees.size() - 1);
            }
        }
        else if (parent[min_root] == min_root) {
            frees[rootX], frees[rootY] = min_root;
        }
        else {
            while (parent[min_root] != min_root) {
                min_root = frees[min_root];
                frees[rootX], frees[rootY] = min_root;
            }
        }
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

    priority_queue<Task> taskQueue;

    Timetable_U tt(5);
    UnionFind uf(10);

    uf.unite(3, 4);
    uf.unite(3, 5);
    uf.unite(3, 6);
    uf.unite(3, 7);


    taskQueue.push(Task('A', 3, 25));
    taskQueue.push(Task('B', 4, 10));
    taskQueue.push(Task('C', 1, 30));
    taskQueue.push(Task('D', 3, 50));
    taskQueue.push(Task('E', 3, 20));

    // while (!taskQueue.empty()) {
    //     Task maxTask = taskQueue.top();
    //     taskQueue.pop();
    // 
    //     int name = static_cast<int>(maxTask.name - 'A');
    //     int deadline = maxTask.deadline;
    //     int fine = maxTask.fine;
    // 
    // }
    
    uf.print();
 

    //while (!taskQueue.empty()) {
    //    Task maxTask = taskQueue.top();
    //    taskQueue.pop();
    //
    //    char name = maxTask.name;
    //    int deadline = maxTask.deadline;
    //    int fine = maxTask.fine;
    //
    //    uf.unite(name, deadline);
    //    tt.table[uf.frees[uf.find(name)]] = name;
    //
    //}


    // while (!taskQueue.empty()) {
    //     Task maxTask = taskQueue.top();
    //     taskQueue.pop();
    // 
    //     if (tt.table[maxTask.deadline].name == ' ') {
    //         tt.table[maxTask.deadline] = maxTask;
    //     } else {
    //         tt.push_left(maxTask);
    //     }
    // }
    



    return 0;
}
