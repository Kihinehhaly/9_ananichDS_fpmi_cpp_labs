#include <iostream>
#include <random>
#include <cmath>

float counting_differens(float array[], int n, int item_number) {
    float differens, sum_before{ 0 }, sum_after{ 0 };

    for (int i = 0; i < item_number; i++) {
        sum_before += array[i];
    }

    for (int i = n - 1; i > item_number; i--) {
        sum_after += array[i];
    }

    if (sum_after > sum_before) {
        differens = sum_after - sum_before;
    }
    else {
        differens = sum_before - sum_after;
    }

    return differens;
}

int main() {

    int n, variant;
    std::cout << "Enter the lenth of your dynamic array: ";
    if (!(std::cin >> n)) {
        std::cout << "Please, next time enter integer n";
        std::exit(404);
    }
    else if (n < 0) {
        std::cout << "How do you imagine that? ~_~";
        std::exit(404);
    }

    float* dynamic_array = new float[n];

    std::cout << "Do you want a random numbers(enter 1) or the ones you'll enter(enter 2)?\n";
    if (!(std::cin >> variant)) {
        std::cout << "Next time enter 1 or 2 >:(";
        std::exit(404);
    }
    if (variant == 1) {
        double lower, upper;
        std::cout << "Enter the real calculation boundaries: ";
        if (!(std::cin >> lower >> upper)) {
            std::cout << "You had one task: enter real boundaries...";
            std::exit(404);
        }

        if (lower > upper) {
            std::swap(lower, upper);
        }

        std::mt19937 gen(45218965);
        std::uniform_real_distribution<double> dist(lower, upper);

        for (int i = 0; i < n; i++) {
            dynamic_array[i] = dist(gen);
        }

        std::cout << "\nThis is your random numbers:\n";
        for (int i = 0; i < n; i++) {
            std::cout << dynamic_array[i] << "   ";
        }
        std::cout << "\n";
    }
    else if (variant == 2) {
        std::cout << "\nThen enter your " << n << " elements:\n";
        for (int i = 0; i < n; i++) {
            if (!(std::cin >> dynamic_array[i])) {
                std::cout << "Next time enter real numbers";
                std::exit(404);
            }
        }
    }
    else {
        std::cout << "I asked you to enter 1 or 2 >:(";
        std::exit(404);
    }


    int number{ 2 };
    float difference, current_difference;
    difference = counting_differens(dynamic_array, n, 1);

    for (int i = 1; i < n - 1; i++) {
        current_difference = counting_differens(dynamic_array, n, i);

        if (current_difference < difference) {
            difference = current_difference;
            number = i + 1;
        }
    }

    std::cout << "\n\n1) The element with the smallest difference in the sum of the elements before and after it is "
        << number << " in the array\n";

    float max_element{ abs(dynamic_array[0]) };
    int number_of_max_element{ 1 };

    for (int i = 0; i < n; i++) {
        if (abs(dynamic_array[i]) > max_element) {
            max_element = abs(dynamic_array[i]);
            number_of_max_element = i + 1;
        }
    }

    std::cout << "\n2) The element with the maximum absolute value is " << max_element
        << " and is found at index " << number_of_max_element << " in the array\n";

    float a, b;
    std::cout << "\n3) Insert real borders for interval, please: ";
    if (!(std::cin >> a >> b)) {
        std::cout << "You had one task: enter real boundaries...";
        std::exit(404);
    }

    if (a > b) {
        std::swap(a, b);
    }

    int element_number_in_new_array{ 0 };
    std::cout << "\nYor new array without elements from the interval: \n";

    for (int i = 0; i < n; i++) {
        if (dynamic_array[i] > b || dynamic_array[i] < a) {
            dynamic_array[element_number_in_new_array] = dynamic_array[i];
            element_number_in_new_array++;
        }
    }

    for (int i = element_number_in_new_array; i < n; i++) {
        dynamic_array[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        std::cout << dynamic_array[i] << "   ";
    }

    std::cout << "\n";

    delete[] dynamic_array;
    return 0;
}