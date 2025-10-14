#include <iostream>
#include <random>

void filing_array_with_random_number(double* array, int lenth_of_array) {
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

    for (int i = 0; i < lenth_of_array; i++) {
        array[i] = dist(gen);
    }
}

void printing_array(double* array, int lenth_of_array) {
    for (int i = 0; i < lenth_of_array; i++) {
        std::cout << array[i] << "   ";
    }
    std::cout << "\n";
}

int main() {
    const int NMAX = 10000;
    int length, variant;
    long double sum{ 0 };
    double static_array[NMAX];

    std::cout << "Enter the length for the static array: ";
    if (!(std::cin >> length) || length > 10000) {
        std::cout << "\nPlease, next time enter integer n < 10000";
        std::exit(404);
    }
    else if (length < 0) {
        std::cout << "How do you imagine that? ~_~";
        std::exit(404);
    }

    std::cout << "Do you want a random numbers(enter 1) or the ones you'll enter(enter 2)?\n";
    if (!(std::cin >> variant)) {
        std::cout << "Next time enter 1 or 2 >:(";
        std::exit(404);
    }
    if (variant == 1) {

        filing_array_with_random_number(static_array, length);

        std::cout << "\nThis is your random numbers:\n";
        printing_array(static_array, length);
    }
    else if (variant == 2) {
        std::cout << "Then enter your " << length << " elements:\n";
        for (int i = 0; i < length; i++) {
            if (!(std::cin >> static_array[i])) {
                std::cout << "Next time enter real numbers";
                std::exit(404);
            }
        }
    }
    else {
        std::cout << "I asked to you enter 1 or 2 >:(";
        std::exit(404);
    }

    for (int i = 0; i < length; i += 2) {
        sum += static_array[i];
    }

    std::cout << "\n\n1) Sum of odd elements = " << sum << "\n";


    long double mult{ 1 };
    int first_number{ 0 }, last_number{ length };

    for (int i = 0; i < length; i++) {
        if (static_array[i] < 0) {
            first_number = i;
            break;
        }
    }

    if (static_array[first_number] >= 0) {
        std::cout << "\n2) There are no negative numbers in array\n";
    }
    else {
        for (int i = length - 1; i > 0; i--) {
            if (static_array[i] < 0) {
                last_number = i;
                break;
            }
        }

        if (first_number == last_number) {
            std::cout << "\n2) There's only one negetive number in array\n";
        }
        else {
            for (int i = first_number + 1; i < last_number; i++) {
                mult = mult * static_array[i];
            }
            std::cout << "\n2) Product of elements between the first and last negative elements =  "
                << mult << "\n";
        }
    }

    int element_number_in_new_array{ 0 };

    for (int i = 0; i < length; i++) {
        if (static_array[i] > 1 || static_array[i] < -1) {
            static_array[element_number_in_new_array] = static_array[i];
            element_number_in_new_array++;
        }
    }

    for (int i = element_number_in_new_array; i < length; i++) {
        static_array[i] = 0;
    }

    std::cout << "\n3) Yor new array without element |value| <= 1 : \n";
    printing_array(static_array, length);

    return 0;
}