#include <iostream>
#include "Stop.h"
#include "Route.h"
#include <map>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::map;

using std::ifstream;

class Point {
public:
    Point()=default;

    Point& operator=(string name) {
        this->name_ = name;
        return *this;
    }

    void append(int route_n, int index) {
        this->route_indexes[route_n] = index;
    }

    bool found_route() const {
        return !route_indexes.empty();
    }

    map<int, int>& routes() {
        return this->route_indexes;
    }

private:
    string name_;
    map<int, int> route_indexes;
};

void reading_table(const string& filename, vector<Route>& ROUTES) {
    ifstream fin;
    fin.open(filename);
    // route format:
    // ROUTE_num |STOP_name: WAIT_time FROM_PREV_time ...

    if (fin.is_open()) {
        while (!fin.eof()) {
            int route_num;
            fin >> route_num;
            vector<Stop> stops;

            char a;
            fin.get(a);  // a = ' '
            while (a != '\n') {
                string name;

                fin.get(a);
                if (a == '|') {
                    fin.get(a);
                    while (a != ':') {
                        name += a;
                        fin.get(a);
                    }

                    double wait, from_prev;
                    fin >> wait >> from_prev;

                    Stop stop(name, wait, from_prev);
                    stops.push_back(stop);
                }
                if (fin.eof())
                    break;
            }

            Route route(route_num, stops);
            ROUTES.push_back(route);
        }
    }

    fin.close();
}

int main() {
    string filename = "../routes.txt";

    vector<Route> routes;
    // reading from file
    reading_table(filename, routes);

    // reading points
    Point Point_A;
    Point Point_B;
    while (true) {
        string A_name, B_name;
//        getline(cin, A_name);
//        getline(cin, B_name);
        A_name = "as_3_4";
        B_name = "es_1";
        if (A_name == B_name) {
            cout << "invalid input\n";
            continue;
        }

        Point_A = A_name;
        Point_B = B_name;
        for (int i = 0; i < routes.size(); i++){
            for (int j = 0; j < routes[i].stops().size(); j++) {
                if (routes[i].stops()[j].name() == A_name)
                    Point_A.append(i, j);

                if (routes[i].stops()[j].name() == B_name)
                    Point_B.append(i, j);
            }
        }
        if (Point_A.found_route() and Point_B.found_route())
            break;
        else
            cout << "no such name. repeat\n";
    }




    return 0;
}
