//
// Created by maxpo on 30.11.2021.
//

#include "Stop.h"

Stop::Stop(string name, double wait, double from_prev){
    this->name_ = name;
    this->wait_ = wait;
    this->from_prev_ = from_prev;
}

void Stop::append_change(int route) {
    this->transfers_.push_back(route);
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

bool Stop::transfer() const {
    return !this->transfers_.empty();
}