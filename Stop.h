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
    Stop(string name, double wait, double from_prev);

    string name() const;
    double wait() const;
    double from_prev() const;

private:
    string name_;
    double wait_;
    double from_prev_;
};

#endif //ROUTES_STOP_H
