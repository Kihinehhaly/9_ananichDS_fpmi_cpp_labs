#include <iostream>
#include <random>
#include <cmath>

void entering_random_borders(double& lower, double& upper, double* array) {
    std::cout << "\nEnter the integer calculation boundaries: ";
    if (!(std::cin >> lower >> upper)) {
        std::cout << "You had one task: enter integer boundaries...";

        delete[] array;

        std::exit(404);
    }

    if (lower > upper) {
        std::swap(lower, upper);
    }
}

void filing_array_with_random_numbers(double* array, int lenth_of_array, std::mt19937* gen) {
    double lower, upper;
    entering_random_borders(lower, upper, array);

    std::uniform_real_distribution<double> dist(lower, upper);

    for (int i = 0; i < lenth_of_array; i++) {
        array[i] = dist(*gen);
    }
}

void print_array(double* array, int lenth_of_array) {
    for (int i = 0; i < lenth_of_array; i++) {
        std::cout << array[i] << "   ";
    }
    std::cout << "\n";
}

double counting_differens(double* array, int lenth_of_array, int element_number) {
    double differens, sum_before{ 0 }, sum_after{ 0 };

    for (int i = 0; i < element_number; i++) {
        sum_before += array[i];
    }

    for (int i = lenth_of_array - 1; i > element_number; i--) {
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

    int length, variant;
    std::cout << "Enter the lenth of your dynamic array: ";
    if (!(std::cin >> length)) {
        std::cout << "Please, next time enter integer n";
        std::exit(404);
    }
    else if (length < 0) {
        std::cout << "How do you imagine that? ~_~";
        std::exit(404);
    }

    double* dynamic_array = new double[length];

    std::cout << "\nDo you want a random numbers(enter 1) or the ones you'll enter(enter 2)? ";
    if (!(std::cin >> variant)) {
        std::cout << "Next time enter 1 or 2 >:(";
        delete[] dynamic_array;
        std::exit(404);
    }
    if (variant == 1) {
        std::random_device rd;
        std::mt19937 gen(rd());

        filing_array_with_random_numbers(dynamic_array, length, &gen);

        std::cout << "\nThis is your random numbers:\n";
        print_array(dynamic_array, length);
    }
    else if (variant == 2) {
        std::cout << "\nThen enter your " << length << " elements:\n";
        for (int i = 0; i < length; i++) {
            if (!(std::cin >> dynamic_array[i])) {
                std::cout << "Next time enter real numbers";

                delete[] dynamic_array;

                std::exit(404);
            }
        }
    }
    else {
        std::cout << "I asked you to enter 1 or 2 >:(";

        delete[] dynamic_array;

        std::exit(404);
    }


    int number{ 2 };
    double difference, current_difference;
    difference = counting_differens(dynamic_array, length, 1);

    for (int i = 1; i < length - 1; i++) {
        current_difference = counting_differens(dynamic_array, length, i);

        if (current_difference < difference) {
            difference = current_difference;
            number = i + 1;
        }
    }

    std::cout << "\n\n1) The element with the smallest difference in the sum of the elements before and after it is "
        << number << " in the array\n";

    double max_element{ abs(dynamic_array[0]) };
    int number_of_max_element{ 1 };

    for (int i = 0; i < length; i++) {
        if (abs(dynamic_array[i]) > max_element) {
            max_element = abs(dynamic_array[i]);
            number_of_max_element = i + 1;
        }
    }

    std::cout << "\n2) The element with the maximum absolute value is " << max_element
        << " and is found at index " << number_of_max_element << " in the array\n";

    double a, b;
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

    for (int i = 0; i < length; i++) {
        if (dynamic_array[i] > b || dynamic_array[i] < a) {
            dynamic_array[element_number_in_new_array] = dynamic_array[i];
            element_number_in_new_array++;
        }
    }

    for (int i = element_number_in_new_array; i < length; i++) {
        dynamic_array[i] = 0;
    }

    print_array(dynamic_array, length);

    delete[] dynamic_array;
    return 0;
}