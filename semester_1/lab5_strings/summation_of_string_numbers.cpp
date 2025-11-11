#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

void inputing_numbers(std::string& number1, std::string& number2) {
    std::cout << "Enter your numbers: ";
    std::cin >> number1 >> number2;
    
    for (char element : number1) {
        if (!std::isdigit(element)) {
            throw "You need to enter numbers";
        }
    }

    for (char element : number2) {
        if (!std::isdigit(element)) {
            throw "You need to enter numbers";
        }
    }
}

std::string counting_string_numbers(std::string number1, std::string number2) {
    int max_length = std::max(number1.length(), number2.length());

    std::vector<int> result;

    while (number1.length() < max_length) {
        number1 = '0' + number1;
    }

    while (number2.length() < max_length) {
        number2 = '0' + number2;
    }

    for (int i = 0; i < max_length; i++) {
        result.push_back(0);
    }

    for (int i = max_length - 1; i > 0; i--) {
        result[i - 1] = (result[i] + (number1[i] - '0') + (number2[i] - '0')) / 10;
        result[i] = (result[i] + (number1[i] - '0') + (number2[i] - '0')) % 10;
    }

    result[0] += (number1[0] - '0') + (number2[0] - '0');

    std::string final_number;
    
    for (int i = 0; i < max_length; i++) {
        final_number += std::to_string(result[i]);
    }
    
    final_number.erase(0, final_number.find_first_not_of("0"));

    return final_number;
}

int main() {
    std::string number1, number2;

    try {
        inputing_numbers(number1, number2);

        std::string answer = counting_string_numbers(number1, number2);

        int max_length = std::max(std::max(number1.length(), number2.length()), answer.length());

        std::cout << "\n " << std::setw(max_length) << number1 << "\n"
            << "+" << std::setw(max_length) << number2 << "\n"
            << std::string(max_length + 1, '-') << "\n"
            << " " << std::setw(max_length) << answer << std::endl;
    }
    catch (const char* message) {
        std::cout << message;
    }

    return 0;
}