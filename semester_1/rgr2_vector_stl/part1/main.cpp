#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

void input_vector(std::vector<int>& vec) {
    std::cout << "Enter numbers in one line: ";
    std::string line;
    std::getline(std::cin, line);

    std::istringstream iss(line);
    int x;
    while (iss >> x) {
        vec.push_back(x);
    }

    if (vec.empty()) {
        throw "Error, please, enter some integers";
    }
}

void print_vector(const std::vector<int>& vec) {
    std::cout << "Your new vector:\n";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

int sum(const std::vector<int>& vec) {
    int sum = 0;
    for (int num : vec) {
        sum += num;
    }
    return sum;
}

int entering_element_to_find() {
    int element_to_find;
    std::cout << "Enter what element you want to find: ";
    if (!(std::cin >> element_to_find)) {
        throw "Error, enter integer";
    }
    return element_to_find;
}

void finding_amount_of_equal_element(const std::vector<int>& vec, int element_to_find) {
    int amount_of_equal = std::count(vec.begin(), vec.end(), element_to_find);
    std::cout << "Amount of number you looking for is " << amount_of_equal << "\n";
}

int entering_egreater_n() {
    int greater_n;
    std::cout << "Enter n to find amount of numbers greater then n: ";
    if (!(std::cin >> greater_n)) {
        throw "Error, enter integer";
    }
    return greater_n;
}

void finding_amount_of_greater_elements(const std::vector<int>& vec, int greater_n) {
    int counting = std::count_if(vec.begin(), vec.end(), [greater_n](int num) { return num > greater_n; });
    std::cout << "There is " << counting << " of numbers greater then n\n";
}

void entering_borders(int& border1, int& border2, int size) {
    std::cout << "Enter border1 and border2 for the interval: ";
    std::cin >> border1 >> border2;
    if (border1 > border2) {
        std::swap(border1, border2);
    }
    if (border2 > size || border1 < 0) {
        throw "Error, you neede to enter borders of vec";
    }
}

int main() {
    try {
        std::vector<int> vec;

        input_vector(vec);

        std::cout << "Sum of elements in your vector is " << sum(vec) << "\n";

        std::cout << "Your vector size is " << vec.size() << "\n";

        int element_to_find = entering_element_to_find();
        finding_amount_of_equal_element(vec, element_to_find);

        int greater_n = entering_egreater_n();
        finding_amount_of_greater_elements(vec, greater_n);

        for (int& num : vec) {
            if (num == 0) {
                num = (sum(vec) / vec.size());
            }
        }
        print_vector(vec);

        int border1, border2;
        entering_borders(border1, border2, vec.size());
        int sum_of_interval{ 0 };
        for (int i = border1; i <= border2; i++) {
            sum_of_interval += vec[i];
        }
        for (int& num : vec) {
            num += sum_of_interval;
        }
        print_vector(vec);

        int max_val = *std::max_element(vec.begin(), vec.end());
        int min_val = *std::min_element(vec.begin(), vec.end());
        for (int& num : vec) {
            if (std::abs(num) % 2 == 0) {
                num = max_val - min_val;
            }
        }
        print_vector(vec);

        std::vector<int>::iterator begin_index = vec.begin();
        for (int i = 0; i < vec.size(); i++) {
            for (int j = i + 1; j < vec.size();) {
                if (vec[i] == vec[j]) {
                    vec.erase(begin_index + j);
                }
                else {
                    ++j;
                }
            }
        }
        print_vector(vec);
    } 
    catch (const char* message) {
        std::cerr << message;
    }
    return 0;
}
