#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;


class House {
public:
    string prefix;
    string type;
    int x_pos;
    int y_pos;
    int number;
    bool is_tavern;

    House(string a, string b, int c, int d, int e, bool f) : prefix(a), type(b), x_pos(c), y_pos(d),number(e), is_tavern(f) {};

    double calculateDistance(const House& otherHouse) const {
        int dx = x_pos - otherHouse.x_pos;
        int dy = y_pos - otherHouse.y_pos;
        return std::sqrt(dx * dx + dy * dy);
    }

    bool operator==(const House& other) const {
        // Здесь вы должны определить, как сравнивать два объекта House
        // Возвращайте true, если они равны, и false в противном случае
        // Например, сравнение по какому-то полю
        return x_pos == other.x_pos && y_pos == other.y_pos;
    }

};

struct CompareFirst {
    bool operator()(const pair<int, pair<House, House>>& a, const pair<int, pair<House, House>>& b) const {
        return a.first < b.first; 
    }
};

pair<vector<House>, vector<int>> parser(string path) {
    ifstream file(path);

    if (!file.is_open()) {
        cerr << "open file error" << endl;
        exit(0);
    }

    vector<House> houses;

    int N, S, T;
    file >> N >> S >> T;


    for (int i = 0; i < S; ++i) {
        string prefix, street_type;
        int start_x, start_y, number_of_houses, distance_between_houses;

        file >> prefix >> street_type >> start_x >> start_y >> number_of_houses >> distance_between_houses;


        if (street_type == "Road") {
            for (int j = 0; j < number_of_houses; j++) {
                House h(prefix, street_type, start_x, start_y + j * distance_between_houses, j, false);
                houses.push_back(h);
            }
        }
        else if (street_type == "Avenue") {
            for (int j = 0; j < number_of_houses; j++) {
                House h(prefix, street_type, start_x + j * distance_between_houses, start_y, j, false);
                houses.push_back(h);
            }
        }
    }

    for (int i = 0; i < T; ++i) {
        string street;
        string type;
        int pos;

        file >> street >> type >> pos;

        for (House& h : houses) {
            if (h.prefix == street && h.number == pos) {
                h.is_tavern = true;
            }
        }
    }

    for (int i = 0; i < houses.size(); i++) {                                                        // 
        House h1 = houses[i];                                                                        // 
        for (int j = 0; j < houses.size(); j++) {                                                    // 
            if (i == j) continue;                                                                    // Причесываем дома на пересечении улиц
            House h2 = houses[j];                                                                    // 
            if (h1.x_pos == h2.x_pos && h1.y_pos == h2.y_pos) houses.erase(houses.begin() + j);      // 
        }                                                                                            // 
    }                                                                                                // 

    vector<int> info = { N, S, T };

    file.close();
    return make_pair(houses, info);
}



vector<pair<int, pair<House, House>>> metrics(vector<House>& houses) {
    vector<pair<int, pair<House, House>>> result;
    for (int i = 0; i < houses.size(); i++) {
        for (int j = i + 1; j < houses.size(); j++) {
            auto h1 = houses[i]; 
            auto h2 = houses[j];
            double metric = h1.calculateDistance(h2);
            result.push_back(make_pair(metric, make_pair(h1, h2)));
        }
    }
    return result;
}

pair<int, pair<House, House>> findMinFirstElement(const vector <pair<int, pair<House, House>>>& vec) {

    auto min_element = std::min_element(vec.begin(), vec.end(), CompareFirst());

    return *min_element;
}

void merge(House h1, House h2, vector<vector<House>>& districts) {
    vector<House> h1District;
    vector<House> h2District;

    for (vector<House>& district : districts) {
        for (House& house : district) {
            if (house == h1) {
                h1District = district;
            }
            if (house == h2) {
                h2District = district;
            }
        }
    }

    if (!h1District.empty() && !h2District.empty()) {
        h1District.insert(h1District.end(), h2District.begin(), h2District.end());

        districts.erase(std::remove(districts.begin(), districts.end(), h2District), districts.end());
    }
    else {
        std::cout << "Один из домов не найден в districts." << std::endl;
    }
}

void print_districts(vector<vector<House>>& districts) {
    for (int i = 0; i < districts.size(); i++) {
        cout << "[ ";
        for (int j = 0; j < districts[i].size(); j++) {
            cout << "(" << districts[i][j].x_pos << " , " << districts[i][j].y_pos << ") ";
        }
        cout << "]\n";
    }
    cout << districts.size() << endl;
}


int main() {

    pair<vector<House>, vector<int>> p = parser("1.txt");
    vector<House> houses = p.first;
    vector<int> info = p.second;
    vector<pair<int, pair<House, House>>> distances = metrics(houses);



    vector<vector<House>> districts;
    for (int i = 0; i < houses.size(); i++) {
        vector<House> district = { houses[i] };
        districts.push_back(district);
    }

    print_districts(districts);

    

    //cout << "---- " << findMinFirstElement(distances).first << " ----\n";

    House h1 = findMinFirstElement(distances).second.first;
    House h2 = findMinFirstElement(distances).second.second;

    merge(h1, h2, districts);
    print_districts(districts);
    
    // for (auto h : distances) {
    //     cout << h.first << " " << "(" << h.second.first.prefix << " " << h.second.first.number << " , " << h.second.second.prefix << " " << h.second.second.number << ")\n";
    // }
    // 





    // for (auto h : houses) {
    //     if (!h.is_tavern) cout << h.x_pos << " " << h.y_pos << "\n";
    //     else              cout << h.x_pos << " " << h.y_pos << " tavern\n";
    // }

    return 0;
}
