#pragma once

#include <string>
#include "time_utility.h"

using TrainId = size_t;
using namespace time_utility;


enum class TrainType { 
    PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED
};


class Train {
private:
    TrainId id_;
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

public:
    Train() : id_(0), type_(TrainType::PASSENGER), dispatch_time_(0), travelling_time_(0) {
    }

    Train(TrainId id, TrainType type, std::string dest, std::time_t disp_time,
          std::time_t travell_time)
        : id_(id), type_(type), destination_(dest), dispatch_time_(disp_time), travelling_time_(travell_time) {}

    TrainId get_id() const {
        return id_;
    }
    TrainType get_type() const {
        return type_;
    }
    std::string get_destination() const {
        return destination_;
    }
    std::time_t get_dispatch_time() const {
        return dispatch_time_;
    }
    std::time_t get_travelling_time() const {
        return travelling_time_;
    }

    bool operator<(const Train& other) const {
        return dispatch_time_ < other.dispatch_time_;
    }

    void print() const {
        std::tm* tm = std::localtime(const_cast<std::time_t*>(&dispatch_time_));
        std::tm* tm_travel = std::localtime(const_cast<std::time_t*>(&travelling_time_));

        std::cout << "Train ¹" << id_ << " " << static_cast<std::string>(type_) << " " << destination_
                  << " " << std::setfill('0') << std::setw(2) << tm->tm_hour << ":" << std::setw(2)
                  << tm->tm_min << " (travel " << std::setw(2) << tm_travel->tm_hour << ":"
                  << std::setw(2) << tm_travel->tm_min << ")";
    }

    bool in_time_range(std::time_t start_time, std::time_t end_time) const {
        std::tm* tm_train = std::localtime(const_cast<std::time_t*>(&dispatch_time_));
        std::tm* tm_start = std::localtime(const_cast<std::time_t*>(&start_time));
        std::tm* tm_end = std::localtime(const_cast<std::time_t*>(&end_time));

        int train_min = tm_train->tm_hour * 60 + tm_train->tm_min;
        int start_min = tm_start->tm_hour * 60 + tm_start->tm_min; 
        int end_min = tm_end->tm_hour * 60 + tm_end->tm_min;  

        return train_min >= start_min && train_min <= end_min;  
    }

    bool goes_to(const std::string& dest) const {
        return destination_ == dest;
    }

    bool matches_type_and_destination(TrainType t, const std::string& dest) const {
        return type_ == t && destination_ == dest;
    }
};
