#include "time_utility.h"
#include "train.h"

#include <iostream>

bool is_empty_file(std::ifstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

std::vector<Train> read_trains_from_file(const std::string& input_file) {
    std::vector<Train> trains;
    std::ifstream file{ input_file };

    if (!file.is_open()) {
        throw "Error: Cannot open file\n";
    }

    if (is_empty_file(file)) {
        throw "Error: your file is empty\n";
    }

    TrainId id = 1;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss{ line };

        std::string type_str, destination;
        int dispatch_h, dispatch_m, travel_h, travel_m;

        if (!(iss >> type_str >> destination >> dispatch_h >> dispatch_m >> travel_h >> travel_m)) {
            throw "Error: next time enter information in the right way\n";
        }

        TrainType type;
        if (type_str == "PASSENGER") {
            type = TrainType::PASSENGER;
        } 
        else if (type_str == "FREIGHT") {
            type = TrainType::FREIGHT;
        } 
        else if (type_str == "HIGH_SPEED") {
            type = TrainType::HIGH_SPEED;
        } 
        else if (type_str == "SUBWAY") {
            type = TrainType::SUBWAY;
        }
        else if (type_str == "SPECIALIZED") {
            type = TrainType::SPECIALIZED;
        } 
        else {
            throw "Error: you entered something wrong in type of train\n";
        }

        trains.push_back(Train(id++, type, destination, dispatch_time, travel_time));

        std::time_t dispatch_time;
        std::time_t travel_time;

        dispatch_time = SetTime(dispatch_h, dispatch_m);
        travel_time = SetTime(travel_h, travel_m);

        trains.push_back(Train(id++, type, destination, dispatch_time, travel_time));
    }

    file.close();

    return trains;
}

void sorting_trains_by_dispatch_time(std::vector<Train>& trains) {
    std::sort(trains.begin(), trains.end());

    std::cout << "=========== All Trains ===========\n";
    for (size_t i = 0; i < trains.size(); ++i) {
        std::cout << (i + 1) << ". ";
        trains[i].print();
        std::cout << "\n";
    }
    std::cout << "\n";
}

void print_train_from_interval(const std::vector<Train>& trains) {
    std::cout << "Enter begining of interval (hours minutes): ";
    size_t start_h, start_m;
    if (!(std::cin >> start_h >> start_m)) {
        throw "Error: could enter begining of interval\n";
    }

    std::cout << "Enter end of interval (hours minutes): ";
    size_t end_h, end_m;
    if (!(std::cin >> end_h >> end_m)) {
        throw "Error: could enter the end of interval\n";
    }

    std::time_t start_range = SetTime(start_h, start_m);
    std::time_t end_range = SetTime(end_h, end_m);

    std::cout << "=========== " << start_range << " - " << end_range << " ===========\n";
    int count = 0;
    for (size_t i = 0; i < trains.size(); ++i) {
        if (trains[i].in_time_range(start_range, end_range)) {
            std::cout << ++count << ". ";
            trains[i].print();
            std::cout << "\n";
        }
    }
    if (count == 0) {
        std::cout << "There's no such trains\n";
    }
}

void trains_to_the_city(const std::vector<Train>& trains) {
    std::cout << "Enter your city: ";
    std::string city;
    if (!(std::cin >> city)) {
        throw "Error: couldn't read your city\n";
    }

    int count = 0;
    std::cout << "=========== Trains to " << city << " ===========\n";
    for (size_t i = 0; i < trains.size(); ++i) {
        if (trains[i].goes_to(city)) {
            std::cout << ++count << ". ";
            trains[i].print();
            std::cout << "\n";
        }
    }
    if (count == 0) {
        std::cout << "There's no such trains\n";
    }
}

void trains_with_same_type_and_city(const std::vector<Train>& trains) {
    std::cout << "Available types: PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED\n";
    std::cout << "Enter your type: ";
    std::string type_str;
    if (!(std::cin >> type_str)) {
        throw "Error: couldn't read your type\n";
    }

    std::cout << "Enter your city: ";
    std::string city;
    if (!(std::cin >> city)) {
        throw "Error: couldn't read your city\n";
    }

    TrainType train_type;
    if (type_str == "PASSENGER") {
        train_type = TrainType::PASSENGER;
    }
    else if (type_str == "FREIGHT") {
        train_type = TrainType::FREIGHT;
    }
    else if (type_str == "HIGH_SPEED") {
        train_type = TrainType::HIGH_SPEED;
    }
    else if (type_str == "SUBWAY") {
        train_type = TrainType::SUBWAY;
    }
    else if (type_str == "SPECIALIZED") {
        train_type = TrainType::SPECIALIZED;
    }
    else {
        throw "Wrong type!\n\n";
    }

    std::cout << "===========" << type_str << "trains to " << city << " ===========\n";
    int count = 0;
    for (size_t i = 0; i < trains.size(); ++i) {
        if (trains[i].matches_type_and_destination(train_type, city)) {
            std::cout << ++count << ". ";
            trains[i].print();
            std::cout << "\n";
        }
    }
    if (count == 0) {
        std::cout << "There's no such trains\n";
    }
}

void fastest_train_to_the_city(const std::vector<Train>& trains) {
    std::cout << "Enter your city: ";
    std::string city;
    if (!(std::cin >> city)) {
        throw "Error: couldn't read your city\n";
    }

    const Train* fastest = 0;
    for (size_t i = 0; i < trains.size(); ++i) {
        if (trains[i].goes_to(city)) {
            if (fastest == 0 || trains[i].is_faster_than(*fastest)) {
                fastest = &trains[i];
            }
        }
    }

    if (fastest == 0) {
        std::cout << "There's no such trains\n";
    } else {
        std::cout << "Fastes train to the " << city << ":\n";
        fastest->print();
        std::cout << "\n";
    }
}

int main() {

    using namespace time_utility;

    std::random_device rd;
    std::mt19937 generator(rd());

    std::time_t t1 = SetTime(12, 23);
    try {
        t1 = SetTime(12, 60);
    } catch (const std::out_of_range& err) {
        std::cerr << err.what() << std::endl;
    }

    std::time_t t2 = GenerateRandomTime(generator);

    std::cout << "t1: ";
    PrintTime(t1);
    
    std::cout << "t2: ";
    PrintTime(t2);
    
    std::cout << "t1 < t2: " << std::boolalpha << (t1 < t2) <<'\n';
    std::cout << "t2 < t1: " << std::boolalpha << (t2 < t1) << '\n';

    try {
        std::vector<Train> trains = read_trains_from_file("trains.txt");

        sorting_trains_by_dispatch_time(trains);

        print_train_from_interval(trains);

        trains_to_the_city(trains);

        trains_with_same_type_and_city(trains);

        fastest_train_to_the_city(trains);
    } 
    catch (...) {
        std::cerr << "Error!!!!!";
    }


    return EXIT_SUCCESS;
}
