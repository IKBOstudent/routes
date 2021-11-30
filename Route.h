//
// Created by maxpo on 30.11.2021.
//

#ifndef ROUTES_ROUTE_H
#define ROUTES_ROUTE_H

#include "Stop.h"
#include <vector>

using std::vector;

class Route {
public:
    Route(int route_n, const vector<Stop>& stops);

    int route_num() const;
    const vector<Stop>& stops() const;

private:
    int route_n_;
    vector<Stop> stops_;
};


#endif //ROUTES_ROUTE_H
