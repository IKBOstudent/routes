//
// Created by maxpo on 30.11.2021.
//

#include "Stop.h"

Stop::Stop(int route, string name, double wait, double from_prev){
    this->route_ = route;
    this->name_ = name;
    this->wait_ = wait;
    this->from_prev_ = from_prev;
}

int Stop::graph_index() const {
    return this->graph_index_;
}

int Stop::route() const {
    return this->route_;
}

string Stop::name() const {
    return this->name_;
}

double Stop::wait() const {
    return this->wait_;
}

double Stop::from_prev() const {
    return this->from_prev_;
}

bool Stop::end_point() const {
    return this->is_end_;
}

void Stop::set_graph_index(int index) {
    this->graph_index_ = index;
}

void Stop::set_end_point() {
    this->is_end_ = true;
}