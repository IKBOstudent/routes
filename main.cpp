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
    // ROUTE_num |STOP_name: FROM_PREV_time WAIT_time |STOP_name: ...

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
                    fin >> from_prev >> wait;

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

    vector<Route> ROUTES;
    // reading from file
    reading_table(filename, ROUTES);

    // reading points
    Point Point_A;
    Point Point_B;
    while (true) {
        string A_name, B_name;
//        getline(cin, A_name);
//        getline(cin, B_name);
        A_name = "A";
        B_name = "bs_1_2";
        if (A_name == B_name) {
            cout << "invalid input\n";
            continue;
        }

        Point_A = A_name;
        Point_B = B_name;
        for (int i = 0; i < ROUTES.size(); ++i){
            for (int j = 0; j < ROUTES[i].stops().size(); ++j) {
                if (ROUTES[i].stops()[j].name() == A_name)
                    Point_A.append(i, j);

                if (ROUTES[i].stops()[j].name() == B_name)
                    Point_B.append(i, j);
            }
        }
        if (Point_A.found_route() and Point_B.found_route())
            break;
        else
            cout << "no such name. repeat\n";
    }

    double total_time = 0;
    // if stop_A - ending:
    // time += wait time
    // else: time += from prev stop + wait time

    for(auto A_route : Point_A.routes()) {
        int route_i_A = A_route.first;
        int stop_i_A = A_route.second;

        for (auto B_route : Point_B.routes()) {
            int route_i_B = B_route.first;
            int stop_i_B = B_route.second;

            // if route_nums are equal
            if (route_i_A == route_i_B) {
                // both routes are the same
                const vector<Stop>& stops = ROUTES[route_i_A].stops();

                if (stop_i_A < stop_i_B) {
                    // moving forward

                    for (int i = stop_i_A; i <= stop_i_B; ++i) {
                        if (i != 0)
                            total_time += stops[i].from_prev();
                        if (i != stop_i_B)
                            total_time += stops[i].wait();
                    }
                }
                else {
                    // moving backward

                    for (int i = stop_i_A; i >= stop_i_B; --i) {
                        if (i != stops.size()-1)
                            total_time += stops[i+1].from_prev();
                        if (i != stop_i_B)
                            total_time += stops[i].wait();
                    }
                }
            }
            else {
                // routes are different => 1 or more changes required

            }
        }
    }

    cout << total_time << " min\n";

    return 0;
}
