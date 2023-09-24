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
            } else {
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

int main() {
    
    priority_queue<Task> taskQueue;
    Timetable tt(10);

    taskQueue.push(Task('A', 3, 25));
    taskQueue.push(Task('B', 4, 10));
    taskQueue.push(Task('C', 1, 30));
    taskQueue.push(Task('D', 3, 50));
    taskQueue.push(Task('E', 3, 20));

    while (!taskQueue.empty()) {
        Task maxTask = taskQueue.top();
        taskQueue.pop();

        if (tt.table[maxTask.deadline].name == ' ') {
            tt.table[maxTask.deadline] = maxTask;
        } else {
            tt.push_left(maxTask);
        }
    }

    tt.print();

    return 0;
}
