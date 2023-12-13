#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib> 
#include <ctime>   

using namespace std;
using namespace chrono;

const int VOID = 0;
const int COMPARTMENT = 1;
const int PLATING = 2;

class Cell {
private:
    int type;
    int damage;

public:
    Cell(int t) : type(t), damage(0) {}

    int get_damage() const {
        return damage;
    }

    int get_type() const {
        return type;
    }

    void inc_damage(int delta) {
        damage += delta;
    }

    void setType(int t) {
        type = t;
    }
};

class Ship {
private:
    vector<vector<Cell>> shipGrid;
    vector<vector<int>> fenwickTree;
    int rows;
    int cols;

public:

    Ship(int rows, int cols) : rows(rows), cols(cols) {
        shipGrid.resize(rows, vector<Cell>(cols, Cell(VOID)));
        fenwickTree.resize(rows + 1, vector<int>(cols + 1, 0));
    }

    void update(int x, int y, int amount) {
        shipGrid[x][y].inc_damage(amount);
        for (int i = x; i < rows; i |= i + 1) {
            for (int j = y; j < cols; j |= j + 1) {
                fenwickTree[i + 1][j + 1] += amount;
            }
        }
    }

    void updateRange(int x1, int y1, int x2, int y2, int value) {
        for (int i = x1; i < x2; i++) {
            for (int j = y1; j < y2; j++) {
                update(i, j, value);
            }
        }
    }

    int query(int x, int y) const {
        int result = 0;
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                result += fenwickTree[i][j];
            }
        }
        return result;
    }

    int queryRange(int x1, int y1, int x2, int y2) const {
        return query(x2, y2) - query(x1, y2) - query(x2, y1) + query(x1, y1);
    }

    void addCell(int x, int y, int type) {
        shipGrid[x][y].setType(type);
        update(x, y, shipGrid[x][y].get_damage());
    }

    int getTotalDamage() const {
        return query(rows, cols);
    }

    void printShip() {
        for (const vector<Cell>& shipRow : shipGrid) {
            for (const Cell& cell : shipRow) {
                cout << cell.get_damage() << " ";
            }
            cout << endl;
        }
    }

    int sillySum(int x_1, int y_1, int x_2, int y_2) {
        int result = 0;
        for (int i = x_1; i < x_2; i++) {
            for (int j = y_1; j < y_2; j++) {
                result += shipGrid[i][j].get_damage();
            }
        }
        return result;
    }

    void printFenwickShip() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << fenwickTree[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

void testSum() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int x_size = rand() % 100;
    int y_size = rand() % 100;

    Ship ship = Ship(x_size, y_size);

    int damage = rand() % 100;
    int checkSum = 0;

    for (int i = 0; i < 1000; i++) {
        
        checkSum += damage;                                      //  Fill with the damage
        ship.update(rand() % x_size, rand() % y_size, damage);   //
        damage = rand() % 100;                                   //
    }                                                            //

    cout << "Checksum:\t" << checkSum << endl;
    cout << "Fenwick sum:\t" << ship.getTotalDamage() << endl;
    cout << "Silly sum:\t" << ship.sillySum(0, 0, x_size, y_size) << endl << endl;

    if (ship.getTotalDamage() != ship.sillySum(0, 0, x_size, y_size)) {
        cout << "Uncorrect sum function!";
        exit(0);
    }

    cout << "Success!" << endl;

}

void testQuery() {

    int x_size = rand() % 100;
    int y_size = rand() % 100;

    Ship ship = Ship(x_size, y_size);

    int damage = rand() % 100;
    int checkSum = 0;

    for (int i = 0; i < 1000; i++) {
        checkSum += damage;
        ship.update(rand() % x_size, rand() % y_size, damage);
        damage = rand() % 100;
    }

    long long checkSum1 = 0;
    long long checkSum2 = 0;

    int x_1 = rand() % x_size;
    int y_1 = rand() % y_size;

    int x_2 = x_1 + (rand() % (x_size - x_1));
    int y_2 = y_1 + (rand() % (y_size - y_1));

    for (int i = 0; i < 9999; i++) {

        checkSum1 += ship.queryRange(x_1, y_1, x_2, y_2);
        checkSum2 += ship.sillySum(x_1, y_1, x_2, y_2);

        x_1 = rand() % x_size;
        y_1 = rand() % y_size;
        x_2 = x_1 + (rand() % (x_size - x_1));
        y_2 = y_1 + (rand() % (y_size - y_1));

    }

    if (checkSum1 != checkSum2) {
        cout << "Uncorrect queryrange";
        exit(0);
    }

    cout << "Fenwick multysum:\t" << checkSum1 << endl;
    cout << "Silly checksum:\t\t" << checkSum2 << endl;

    cout << "Success!" << endl;

}


void testUpdateRange() {

    int x_size = 5;    // rand() % 100;
    int y_size = 5;    // rand() % 100;

    Ship ship = Ship(x_size, y_size);

    ship.updateRange(1, 1, 3, 3, 6);

    ship.updateRange(3, 3, 5, 5, 12);
    ship.updateRange(0, 0, 2, 2, 1);


    ship.printShip();

    cout << ship.getTotalDamage();

    //long long checkSum1 = 0;
    //long long checkSum2 = 0;
    //
    //int x_1 = rand() % x_size;
    //int y_1 = rand() % y_size;
    //
    //int x_2 = x_1 + (rand() % (x_size - x_1));
    //int y_2 = y_1 + (rand() % (y_size - y_1));

}

int main() {

    testUpdateRange();

}
