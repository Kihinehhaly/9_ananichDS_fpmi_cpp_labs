#include <iostream>
#include <random>
#include <algorithm>

int main() {
    const int NMAX = 10000;
    int n, variant;
    long double sum{ 0 };
    double static_array[NMAX];

    std::cout << "Enter the length for the array: ";
    if (!(std::cin >> n) || n > 10000) {
        std::cout << "\nPlease, next time enter integer n < 10000";
        std::exit(404);
    }
    else if (n < 0) {
        std::cout << "How do you imagine that? ~_~";
        std::exit(404);
    }

    std::cout << "Do you want a random numbers(enter 1) or the ones you'll enter(enter 2)?\n";
    if (!(std::cin >> variant)) {
        std::cout << "Next time enter 1 or 2 >:(";
        std::exit(404);
    }
    if (variant == 1) {
        double lower, upper;
        std::cout << "Enter the double calculation boundaries: ";
        if (!(std::cin >> lower >> upper)) {
            std::cout << "You had one task: enter double boundaries...";
            std::exit(404);
        }

        if (lower > upper) {
            std::swap(lower, upper);
        }

        std::mt19937 gen(45218965);
        std::uniform_real_distribution<double> dist(lower, upper);

        for (int i = 0; i < n; i++) {
            static_array[i] = dist(gen);
        }

        std::cout << "\nThis is your random numbers:\n";
        for (int i = 0; i < n; i++) {
            std::cout << static_array[i] << "   ";
        }
        std::cout << "\n";
    }
    else if (variant == 2) {
        std::cout << "Then enter your " << n << " elements:\n";
        for (int i = 0; i < n; i++) {
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

    for (int i = 0; i < n; i += 2) {
        sum += static_array[i];
    }

    std::cout << "\n\n1) Sum = " << sum << "\n";


    long double mult{ 1 };
    int first_number{ 0 }, last_number{ n };

    for (int i = 0; i < n; i++) {
        if (static_array[i] < 0) {
            first_number = i;
            break;
        }
    }

    if (static_array[first_number] >= 0) {
        std::cout << "\n2) There are no negative numbers\n";
    }
    else {
        for (int i = n - 1; i > 0; i--) {
            if (static_array[i] < 0) {
                last_number = i;
                break;
            }
        }

        if (first_number == last_number) {
            std::cout << "\n2) There's only one negetive number\n";
        }
        else {
            for (int i = first_number + 1; i < last_number; i++) {
                mult = mult * static_array[i];
            }
            std::cout << "\n2) The result is " << mult << "\n";
        }
    }

    int element_number_in_new_array{ 0 };
    std::cout << "\n3) Yor new array: \n";

    for (int i = 0; i < n; i++) {
        if (static_array[i] > 1 || static_array[i] < -1) {
            static_array[element_number_in_new_array] = static_array[i];
            element_number_in_new_array++;
        }
    }

    for (int i = element_number_in_new_array; i < n; i++) {
        static_array[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        std::cout << static_array[i] << "   ";
    }
    std::cout << "\n";

    return 0;
}