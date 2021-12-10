//
// Created by maxpo on 30.11.2021.
//

#ifndef ROUTES_STOP_H
#define ROUTES_STOP_H

#include <string>
#include <vector>

using std::vector;
using std::string;

class Stop {
public:
    Stop(int route, string name, double wait, double from_prev);

    int graph_index() const;
    int route() const;
    string name() const;
    double wait() const;
    double from_prev() const;
    bool end_point() const;

    void set_graph_index(int index);
    void set_end_point();


private:
    int graph_index_;
    int route_;
    string name_;
    double wait_;
    double from_prev_;
    bool is_end_ = false;
};

#endif //ROUTES_STOP_H
