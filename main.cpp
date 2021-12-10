#include <iostream>
#include "Stop.h"
#include "Route.h"
#include <fstream>

#include <queue>
#include <map>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::queue;
using std::priority_queue;
using std::map;


int main() {
    string filename = "../routes.txt";
    ifstream fin;
    fin.open(filename);
    // ROUTE_num |STOP_name: FROM_PREV_time WAIT_time|

    vector<Stop> STOPS;

    if (fin.is_open()) {
        while (!fin.eof()) {
            int route_num;
            fin >> route_num;

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
                    Stop stop(route_num, name, wait, from_prev);
                    STOPS.push_back(stop);

                    fin.get(a);  // a = ':' or '|'
                }
                if (fin.eof()) break;
            }
        }
    }
    fin.close();

    auto N = STOPS.size();

    bool new_route = false;
    int prev_route = 0;
    Stop* prev_stop = nullptr;
    for (int i = 0; i < N; ++i){
        if (STOPS[i].route() != prev_route){
            if (prev_stop != nullptr)
                prev_stop->set_end_point();
            new_route = true;
            prev_route = STOPS[i].route();
        } else
            new_route = false;
        prev_stop = &STOPS[i];

        if (new_route) {
            STOPS[i].set_end_point();
        }
    }

    vector<vector<bool>> GRAPH(N, vector<bool>(N));

    for (int i = 0; i < N; ++i) {
        STOPS[i].set_graph_index(i);
        double total_time = STOPS[i].wait();

        for (int j = 0; j < N; ++j) {

            if ((STOPS[j].route() == STOPS[i].route() and abs(j - i) == 1)
                or (STOPS[j].name() == STOPS[i].name() and i != j))
                GRAPH[i][j] = true;
            else
                GRAPH[i][j] = false;

//            cout << GRAPH[i][j] << " ";
        }
//        cout << endl;
    }

    string A_name, B_name;
    Stop* start;
    Stop* finish;
    while (true) {
        getline(cin, A_name);
        getline(cin, B_name);

        bool found_A = false, found_B = false;
        for (auto & i : STOPS) {
            if (!found_A and i.name() == A_name) {
                found_A = true;
                start = &i;
            }

            if (!found_B and i.name() == B_name) {
                found_B = true;
                finish = &i;
            }
        }

        if (found_A and found_B) break;
        else cout << "invalid name\n";
    }

    cout << start->name() << start->route() << " ";
    cout << finish->name() << finish->route() << endl;


    queue<Stop*> path;
    path.push(start);
    map<Stop*, Stop*> came_from;
    came_from[start] = nullptr;

    while (!path.empty()) {
        Stop* current = path.front();
        path.pop();

        if (current->name() == B_name) break;

        int i = current->graph_index();
        for (int j = 0; j < N; j++) {
            if (came_from.find(&STOPS[j]) == came_from.end()) {
                if (GRAPH[i][j]) {
                    path.push(&STOPS[j]);
//                    cout << "next: " << STOPS[j].name() << " " << STOPS[j].route() << endl;
                    came_from[&STOPS[j]] = current;
                }
            }
        }
    }

    vector<Stop*> result;
    Stop* current = finish;
    result.push_back(finish);
    while (current != start) {
        current = came_from[current];
        result.push_back(current);
    }




    return 0;
}
