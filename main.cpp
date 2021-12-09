#include <iostream>
#include "Stop.h"
#include "Route.h"
#include <fstream>

#include <queue>

struct Point {
    void set_wait(double wait_time) {
        this->wait_time_ = wait_time;
    }

    void set_name(string name) {
        this->name_ = name;
    }

    void add_neighbour(const Point* new_neighbour) {
        neighbours.push_back(new_neighbour);
    }

    string name_ = " ";
    double wait_time_ = 0;
    vector<const Point*> neighbours;
};

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::queue;

void reading_table(const string& filename, vector<Route>& ROUTES, int& stops_count) {
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
                if (fin.eof()) break;

                if (a == '|') {
                    fin.get(a);
                    while (a != ':') {
                        name += a;
                        fin.get(a);
                    }

                    double wait, from_prev;
                    fin >> from_prev >> wait;
                    Stop stop(name, wait, from_prev);

                    fin.get(a);  // a = ':' or '|'
                    stops.push_back(stop);
                    ++stops_count;
                }
                if (fin.eof()) break;
            }
            Route route(route_num, stops);
            ROUTES.push_back(route);
        }
    }

    fin.close();
}

void set_point(Point& point, vector<Route>& ROUTES){
    while (true) {
        string stop_name;
        getline(cin, stop_name);
        bool found = false;
        for (auto & i : ROUTES) {
            for (const auto & j : i.stops()) {
                if (j.name() == stop_name) {
                    found = true;
                    point.set_name(stop_name);
                    point.set_wait(j.wait());
                }
            }
        }

        if (found) return;
        else cout << "invalid name\n";
    }
}

int main() {
    string filename = "../routes.txt";

    vector<Route> ROUTES;
    int stops_count = 0;
    // reading from file
    reading_table(filename, ROUTES, stops_count);

    Point A, B;
    set_point(A, ROUTES);
    set_point(B, ROUTES);

    vector<vector<int>> GRAPH(stops_count, vector<int>(stops_count));

    for (auto& i : GRAPH) {
        for (auto j : i)
            cout << j << " ";
        cout << endl;
    }

    for (int i = 0; i < stops_count; ++i) {
    }

    queue<Point> NODES;



    return 0;
}
