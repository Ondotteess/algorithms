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

    vector<int> frees;

    Timetable(int size) {
        table = vector<Task>(size, Task(' ', 0, 0));
        frees.resize(size);
        for (int i = 0; i < size; i++) {
            frees[i] = i;
        }
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

    vector<int> parent;
    vector<int> elements;
    vector<int> rank;

    void print() {
        for (int i = 0; i < parent.size(); i++) {
            cout << parent[i] << " ";
        }
        cout << endl;
    }

    UnionFind(vector<int> elements) {
        int size = elements.size();
        parent.resize(size);
        elements = elements;
        rank.resize(size, 0);

        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }


    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {

        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return;
        else {
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

int I(char c) {
    return c - 'A';
}

int main() {
     
     priority_queue<Task> taskQueue1;
     priority_queue<Task> taskQueue2;
     
     
     int size = 5;
     
     // srand(time(0));
     // for (int i = 0; i < size; i++) {
     //     char name = 'A' + i;
     //     int deadline = abs(rand()) % size;
     //     int fine = abs(rand()) % size * 10;
     // 
     //     taskQueue1.push(Task(name, deadline, fine));
     //     taskQueue2.push(Task(name, deadline, fine));
     // }
     
     // taskQueue1.push(Task('A', 2, 22));
     // taskQueue1.push(Task('B', 4, 12));
     // taskQueue1.push(Task('C', 1, 41));
     // taskQueue1.push(Task('D', 3, 49));
     // taskQueue1.push(Task('E', 3, 21));
     // taskQueue1.push(Task('F', 5, 30));
     // 
     // 
     // taskQueue2.push(Task('A', 2, 22));
     // taskQueue2.push(Task('B', 4, 12));
     // taskQueue2.push(Task('C', 1, 41));
     // taskQueue2.push(Task('D', 3, 49));
     // taskQueue2.push(Task('E', 3, 21));
     // taskQueue2.push(Task('F', 5, 30));

     taskQueue1.push(Task('A', 3, 25));
     taskQueue1.push(Task('B', 4, 10));
     taskQueue1.push(Task('C', 1, 30));
     taskQueue1.push(Task('D', 3, 50));
     taskQueue1.push(Task('E', 3, 20));
  


     taskQueue2.push(Task('A', 3, 25));
     taskQueue2.push(Task('B', 4, 10));
     taskQueue2.push(Task('C', 1, 30));
     taskQueue2.push(Task('D', 3, 50));
     taskQueue2.push(Task('E', 3, 20));
    

     vector<int> els(size+1);
     for (int i = 0; i < size; i++) {
         els[i] = i;
     }
     UnionFind uf1(els);
     UnionFind uf2(els);
     
     Timetable tt1(els.size());
     Timetable tt2(els.size());

    
    while (!taskQueue1.empty()) {
        Task maxTask = taskQueue1.top();                               // free - вектор, в каждом индексе день в который можно поставить таску
        taskQueue1.pop();
        int deadline = maxTask.deadline;
        
        int day = tt1.frees[uf1.find(deadline)];                       // ищем самый правый слева
        if (day <= 0) day = tt1.frees[uf1.find(tt1.table.size() - 1)]; // day постепенно уменьшается
        
        tt1.table[day - 1] = maxTask;                                  // вписываем таску
        int new_free = min(day - 1, tt1.frees[uf1.find(day - 1)]);     // проверяем не залезли на чужой класс
        uf1.unite(day, day - 1);                                       // объединяем дни
        tt1.frees[uf1.find(day)] = new_free;                           // обновляем free
    }
    
    for (auto t : tt1.table) {
        cout << t.name << " ";
    }
    cout << endl << tt1.table.size() << endl;

    int i = 0;
    while (!taskQueue2.empty()) {
        Task maxTask = taskQueue2.top();
        taskQueue2.pop();
        tt2.table[i] = maxTask;
        i++;
    }
     
     for (auto t : tt2.table) {
        cout << t.name << " ";
    }
     
     cout << endl;
     cout << tt2.table.size();


    return 0;
}
