#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <numeric>
#include <chrono>

using namespace std;


class House {
public:
    string prefix;
    string type;
    int x_pos;
    int y_pos;
    int number;
    bool is_tavern;

    House(string a, string b, int c, int d, int e, bool f) : prefix(a), type(b), x_pos(c), y_pos(d), number(e), is_tavern(f) {};

    double calculateDistance(const House& otherHouse) const {
        int dx = x_pos - otherHouse.x_pos;
        int dy = y_pos - otherHouse.y_pos;
        return std::sqrt(dx * dx + dy * dy);
    }

    bool operator==(const House& other) const {
        return x_pos == other.x_pos && y_pos == other.y_pos;
    }

};

class Metric {
private:
    int distance;
    pair<House, House> house_pair;

public:
    Metric(int dist, const pair<House, House>& pair) : distance(dist), house_pair(pair) {}

    int getDistance() const {
        return distance;
    }

    pair<House, House> getHousePair() const {
        return house_pair;
    }

    bool operator<(const Metric& other) const {
        return distance > other.distance;
    }
};

class District {
public:
    vector<House> dist;
    int houses;
    int taverns;
    float priority;
    District(vector<House> d) {
        dist = d;
        for (auto house : dist) {
            houses++;
            if (house.is_tavern) taverns++;
        }
        priority = static_cast<float>(taverns) / houses;
    }
    bool operator<(const District& other) const {
        return priority < other.priority;
    }

    bool operator>(const District& other) const {
        return priority > other.priority;
    }

    bool operator==(const District& other) const {
        return priority == other.priority;
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
        
        if (!type.empty() && type.back() == ',') {
            type.pop_back();
        }

        for (House& h : houses) {
            if (h.prefix == street && h.number == pos && h.type == type) {
                h.is_tavern = true;
            }
        }
    }


    for (int i = 0; i < houses.size(); i++) {
        for (int j = i + 1; j < houses.size();) {
            if (houses[i].x_pos == houses[j].x_pos && houses[i].y_pos == houses[j].y_pos) {
                if (houses[i].is_tavern) {
                    houses.erase(houses.begin() + j);
                }
                else if (houses[j].is_tavern) {
                    houses.erase(houses.begin() + i);
                }
                else {
                    houses.erase(houses.begin() + j);
                }
            }
            else {
                j++;
            }
        }
    }
    vector<int> info = { N, S, T };

    file.close();
    return make_pair(houses, info);
}



priority_queue<Metric> metrics(const vector<House>& houses) {
    priority_queue<Metric> result;
    int numHouses = houses.size();

    for (int i = 0; i < numHouses; i++) {
        // if (i % 100 == 0 ) cout << i << endl;
        for (int j = i + 1; j < numHouses; j++) {
            const House& h1 = houses[i];
            const House& h2 = houses[j];
            double metric = h1.calculateDistance(h2);
            Metric m(metric, make_pair(h1, h2));
            result.push(m);
        }
    }
    return result;
}


void merge(const House& h1, const House& h2, vector<vector<House>>& districts) {
    vector<House> h1District;
    vector<House> h2District;

    for (auto it = districts.begin(); it != districts.end(); ) {
        if (find(it->begin(), it->end(), h1) != it->end()) {
            h1District = std::move(*it);
            it = districts.erase(it);
        }
        else if (find(it->begin(), it->end(), h2) != it->end()) {
            h2District = std::move(*it);
            it = districts.erase(it);
        }
        else {
            ++it;
        }
    }

    h1District.insert(h1District.end(), std::make_move_iterator(h2District.begin()), std::make_move_iterator(h2District.end()));

    districts.push_back(std::move(h1District));
}

void angry(priority_queue<District>& districts) {
    int sum = 0;
    int totalHousesConnected = 0;

    while (!districts.empty()) {
        District d = districts.top();
        totalHousesConnected += d.houses;
        sum += totalHousesConnected * d.taverns;
        districts.pop();
    }

    cout << sum;
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
    auto start_time = std::chrono::high_resolution_clock::now();

    pair<vector<House>, vector<int>> p = parser("1.txt");
    vector<House> houses = p.first;
    vector<int> info = p.second;

    priority_queue<Metric> distances = metrics(houses);
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    cout << "Complete 1: " << duration.count() << endl;
    start_time = std::chrono::high_resolution_clock::now();
    vector<vector<House>> districts;
    
    for (const House& h: houses) {
        vector<House> district = { h };
        districts.push_back(district);
    }

    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    start_time = std::chrono::high_resolution_clock::now();

    cout << "Complete 2: " << duration.count() << endl;
    while (districts.size() > info[0]) {
        Metric distance = distances.top();
        merge(distance.getHousePair().first, distance.getHousePair().second, districts);
        distances.pop();
    }

    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    cout << "Complete 3: " << duration.count() << endl;
    priority_queue<District> newDistricts;
    for (auto dist : districts) {
        District a(dist);
        newDistricts.push(a);
    }

    angry(newDistricts);


    //print_districts(districts);
    
     //for (auto h : houses) {
     //    if (!h.is_tavern) cout << h.x_pos << " " << h.y_pos << "\n";
     //    else              cout << h.x_pos << " " << h.y_pos << " tavern\n";
     //}

    return 0;
}
