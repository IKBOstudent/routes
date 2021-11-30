//
// Created by maxpo on 30.11.2021.
//

#include "Route.h"

Route::Route(int route_n, const vector<Stop>& stops){
    this->route_n_ = route_n;
    this->stops_ = stops;
}

int Route::route() const {
    return this->route_n_;
}

const vector<Stop>& Route::stops() const {
    return this->stops_;
}
