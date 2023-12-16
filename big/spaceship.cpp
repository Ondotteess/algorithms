#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib> 
#include <ctime>   
#include <fstream>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;
using namespace chrono;

const int PLATING = 0;
const int COMPARTMENT = 1;
const int VOID = 2;

class Cell {
private:
    int type;
    int damage;
    int maxDamage;
    string name;
    int x1;
    int y1;
    int x2;
    int y2;

public:
    Cell(int t) : type(t), damage(0), name(""), maxDamage(0), x1(0), x2(0), y1(0), y2(0) {}

    int get_damage() const {
        return damage;
    }

    int get_type() const {
        return type;
    }

    void inc_damage(int delta) {
        damage += delta;
    }

    void setName(string n) {
        name = n;
    }

    string getName() {
        return name;
    }

    void setType(int t) {
        type = t;
    }

    void setMaxDamage(int md) {
        maxDamage = md;
    }

    void setRect(int x_1, int y_1, int x_2, int y_2) {
        x1 = x_1;
        y1 = y_1;
        x2 = x_2;
        y2 = y_2;
    }
};

class FenwickTree2D {
public:

    int n, m;
    vector<vector<vector<int>>> B;

    FenwickTree2D() : FenwickTree2D(0, 0) {}
    

    FenwickTree2D(int rows, int cols) : n(rows), m(cols) {
        B.resize(n + 1, vector<vector<int>>(m + 1, vector<int>(4, 0)));
    }

    void update(int x1, int y1, int x2, int y2, int v) {
        x1++; y1++; x2++; y2++;
        upd(x1, y1, v);
        upd(x1, y2 + 1, -v);
        upd(x2 + 1, y1, -v);
        upd(x2 + 1, y2 + 1, v);
    }

    int query(int x1, int y1, int x2, int y2) {
        x1++; y1++; x2++; y2++;
        return qry(x2, y2) - qry(x1 - 1, y2) - qry(x2, y1 - 1) + qry(x1 - 1, y1 - 1);
    }

    void print() {

        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                    cout << query(i, j, i, j) << " ";
                }
                cout << std::endl;
            }
    }

    int lowbit(int x) {
        return x & -x;
    }

    void upd(int x, int y, int v) {
        for (int i = x; i <= n; i += (i & -i)) {
            for (int j = y; j <= m; j += (j & -j)) {
                B[i][j][0] += v;
                B[i][j][1] += x * v;
                B[i][j][2] += y * v;
                B[i][j][3] += x * y * v;
            }
        }
    }

    int qry(int x, int y) {
        int ans = 0;
        for (int i = x; i > 0; i -= lowbit(i)) {
            for (int j = y; j > 0; j -= lowbit(j)) {
                ans += (x + 1) * (y + 1) * B[i][j][0] - (y + 1) * B[i][j][1] - (x + 1) * B[i][j][2] + B[i][j][3];
            }
        }
        return ans;
    }
};

class Ship {
private:
    vector<vector<Cell>> shipGrid;
    vector<vector<int>> rectVoids;
    vector<vector<int>> rectComps;
    FenwickTree2D fenwick;

    bool destroyed;
    int rows;
    int cols;
    int voids;
    int compartments;
    int damageLimit;
    int oneTimeDamageLimit;
    int collapseLimit;
    int damage;
    int collapses;

public:

    Ship(int rows, int cols, int voids, int compartments, int damageLimit, int oneTimeDamageLimit, int collapseLimit) :
        rows(rows),
        cols(cols),
        voids(voids),
        compartments(compartments),
        damageLimit(damageLimit),
        oneTimeDamageLimit(oneTimeDamageLimit),
        collapseLimit(collapseLimit),
        destroyed(false),
        damage(0),
        collapses(0) {
        shipGrid.resize(rows, vector<Cell>(cols, Cell(PLATING)));
        fenwick = FenwickTree2D(rows, cols);
    
    }

    void updateType(int x1, int y1, int x2, int y2, int type, string name, int maxDamage) {
        if (type == VOID) {
            vector<int> rectVoid = { x1, y1, x2 - 1, y2 - 1 };
            rectVoids.push_back(rectVoid);
        }

        if (type == COMPARTMENT) {
            vector<int> rectComp = {x1, y1, x2 - 1, y2 - 1};
            rectComps.push_back(rectComp);
        }

        for (int i = x1; i < x2; i++) {
            for (int j = y1; j < y2; j++) {
                shipGrid[i][j].setType(type);
                shipGrid[i][j].setName(name);
                shipGrid[i][j].setRect(x1, y1, x2, y2);

                if (name != "") shipGrid[i][j].setMaxDamage(maxDamage);
            }
        }
    }

    void updateDamage(int x1, int y1, int x2, int y2, int value) {
        bool voidInRect = false;
        bool compInRect = false;
        vector<string> compNames;
        for (const vector<int>& rect : rectVoids) {
            if (rect[0] < x2 && rect[2] >= x1 && rect[1] < y2 && rect[3] >= y1) {
                voidInRect = true;
                int interX1 = max(x1, rect[0]);
                int interY1 = max(y1, rect[1]);
                int interX2 = min(x2 - 1, rect[2]);
                int interY2 = min(y2 - 1, rect[3]);
                fenwick.update(interX1, interY1, interX2, interY2, -value);
            }
        }

        for (const vector<int>& rect : rectComps) {
            if (rect[0] < x2 && rect[2] >= x1 && rect[1] < y2 && rect[3] >= y1) {
                compNames.push_back(shipGrid[rect[0]][rect[1]].getName());
                compInRect = true;
            }
        }
        
        fenwick.update(x1, y1, x2 - 1 , y2 - 1, value);

        damage += fenwick.query(x1, y1, x2, y2);

        int area = (x2 - x1) * (y2 - y1);
        int areaDamage = fenwick.query(x1, y1, x2, y2);

        if (damage >= damageLimit) {
            cout << "Received " << damage << " damage in total, total damage limit " << damageLimit << " exceed. Ship is destroyed." << endl;
            destroyed = true;
            return;
        }

        if (areaDamage >= area * oneTimeDamageLimit) {

            if (voidInRect) return;
            vector<int> rect = { x1, y1, x2, y2 };
            rectVoids.push_back(rect);

            cout << "Received " << getTotalDamage() << " damage in total, section {" << x1 << ", " << y1 << ", " << x2 << ", " << y2 << "} collapsed." << endl;

            if (collapses >= collapseLimit) {
                cout << "And it was the last collapse the ship can handle. It was destroyed." << endl;
            }

            if (compInRect) {
                sort(compNames.begin(), compNames.end());
                string name = compNames[0];
                cout << name << " exploded! Ship is destroyed." << endl;
                destroyed = true;
                return;
            }

            collapses++;
           
        }

        cout << "Received " << getTotalDamage() << " damage in total." << endl;

    
    }
    
    bool isDestroyed() {
        return destroyed;
    }

    int sillySum(int x_1, int y_1, int x_2, int y_2) {
        int result = 0;
        for (int i = x_1; i < x_2; i++) {
            for (int j = y_1; j < y_2; j++) {
                result += fenwick.query(i, j, i, j);
            }
        }
        return result;
    }

    int getTotalDamage() {
        return fenwick.query(0, 0, rows - 1, cols -1);
    }

    void printShip() {
        fenwick.print();
    }

    void printTypes() {
        for (int j = 0; j < cols; j++){
            for (int i = 0; i < rows; i++) {
                cout << shipGrid[i][j].get_type() << " ";
            }
            cout << endl;
        }
    }


};

int main() {
    
    string filename = "1.txt";

    string line;
    ifstream in("1.txt");
    int size_x, size_y, voids, compartments, damageLimit, oneTimeDamageLimit, collapseLimit;

    if (in.is_open()) {
        in >> size_x >> size_y >> voids >> compartments >> damageLimit >> oneTimeDamageLimit >> collapseLimit;
    }
    else {
        cout << "File doesn't exist";
        exit(0);
    }

    Ship ship = Ship(size_x, size_y, voids, compartments, damageLimit, oneTimeDamageLimit, collapseLimit);

    int x1, y1, x2, y2;
    for (int i = 0; i < voids; i++) {
        in >> x1 >> y1 >> x2 >> y2;
        ship.updateType(x1, y1, x2, y2, VOID, "", 0);
    }

    string name;
    for (int i = 0; i < compartments; i++) {
        in >> name >> x1 >> y1 >> x2 >> y2 >> damageLimit;
        ship.updateType(x1, y1, x2, y2, COMPARTMENT, name, damageLimit);
    }

    int shots;
    int damage;
    in >> shots;

    for (int i = 0; i < shots; i++) {
        in >> x1 >> y1 >> x2 >> y2 >> damage;
        ship.updateDamage(x1, y1, x2, y2, damage);

        if (ship.isDestroyed()) {
            ship.printShip();
            exit(0);
        }
        else {
        }
    }

    ship.printShip();


}
