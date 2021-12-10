#include <iostream>
#include "Stop.h"
#include <fstream>

#include <queue>
#include <map>
#include <set>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::queue;
using std::priority_queue;
using std::map;
using std::set;
using std::pair;
using std::make_pair;
using std::reverse;

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

    // setting end points
    {bool new_route = false;
    int prev_route = 0;
    Stop* prev_stop = nullptr;
    for (int i = 0; i < N; ++i){
        STOPS[i].set_graph_index(i);

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

        cout << STOPS[i].name()[0] << STOPS[i].name()[1] << " ";
    }
    cout << endl;
    }

    string A_name, B_name;
    int start_index;
    while (true) {
        getline(cin, A_name);
        getline(cin, B_name);

        bool found_A = false, found_B = false;
        for (auto & i : STOPS) {
            if (!found_A and i.name() == A_name) {
                found_A = true;
                start_index = i.graph_index();
            }

            if (!found_B and i.name() == B_name) {
                found_B = true;
            }
        }

        if (found_A and found_B and A_name != B_name) break;
        else cout << "invalid name\n";
    }

    vector<vector<pair<int, double>>> GRAPH(N);
    vector<vector<double>> GRAPH_V2(N, vector<double>(N));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            // i - from; j - to;
            double time = 0;

            if (STOPS[j].route() == STOPS[i].route() and abs(j - i) == 1) {
                if (STOPS[i].name() != A_name)
                    time += STOPS[i].wait();
                if (i < j)
                    time += STOPS[j].from_prev();
                else
                    time += STOPS[i].from_prev();

                GRAPH[i].push_back(make_pair(j, time));
            } else if (STOPS[j].name() == STOPS[i].name() and i != j) {
                GRAPH[i].push_back(make_pair(j, time));
            }

            cout << time << "  ";
            GRAPH_V2[i][j] = time;
        }
        cout << endl;
    }


    map<double, int> results;

    vector<double> total_cost(N, 2000);

    total_cost[start_index] = 0;

    map<Stop*, Stop*> came_from;
    came_from[&STOPS[start_index]] = nullptr;

    set<pair<int, double>> unused;
    unused.insert(make_pair(start_index, 0));

    while (!unused.empty()) {
        int current = unused.begin()->first;
        unused.erase(unused.begin());

        for (auto i : GRAPH[current]) {
            int end = i.first;
            double time = i.second;

            if (total_cost[current] + time < total_cost[end]) {
                unused.erase(make_pair(end, total_cost[end]));
                total_cost[end] = total_cost[current] + time;

                unused.insert(make_pair(end, total_cost[end]));
                came_from[&STOPS[end]] = &STOPS[current];
            }

            if (STOPS[end].name() == B_name)
                results[total_cost[end]] = end;
        }
    }

    int finish_index;
    double result_time = 2000;
    for (auto i : results) {
        if (i.first < result_time) {
            result_time = i.first;
            finish_index = i.second;
        }
    }

    vector<Stop*> path;
    Stop* current = &STOPS[finish_index];
    while (current != &STOPS[start_index]) {
        current = came_from[current];
        path.push_back(current);
    }

    reverse(path.begin(),  path.end());

    if (path.size() >= 2) {
        if (path[1]->name() == A_name) {
            path.erase(path.begin());
        }


        // time calibrating
        {
            int fst = path[0]->graph_index();
            int snd = path[1]->graph_index();
            if (!path[0]->end_point()) {
                if (fst < snd)
                    result_time += STOPS[fst].from_prev() / 2;
                else
                    result_time += STOPS[snd].from_prev() / 2;
            }
            result_time += path[0]->wait();
        }

        string prev = path[0]->name();
        for (int i = 1; i < path.size() - 1; ++i) {
            if (prev == path[i]->name()) { // transfer point
                int fst = path[i]->graph_index();
                int snd = path[i + 1]->graph_index();
                if (!path[i]->end_point()) {
                    if (fst < snd)
                        result_time += STOPS[fst].from_prev() / 2;
                    else
                        result_time += STOPS[snd].from_prev() / 2;
                }
            }
            prev = path[i]->name();
        }
    } else
        result_time += path[0]->wait();

    cout << "total time " << result_time << " mins" << endl;

    for (auto i : path) {
        cout << i->name() << " (bus No. " << i->route() << ") \n";
    }
    cout << STOPS[finish_index].name() << " (end)\n";





    return 0;
}
