#include <iostream>

int main() {
    long long n, result{ 0 }, original, mult{ 1 };

    std::cout << "Enter n for task 2: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Please, enter long long n > 0\n";
        std::exit(404);
    }

    original = n;

    while (n > 0) {
        int count = 0;
        int digit = n % 10;
        long long n_count = original;

        while (n_count > 0) {
            if (n_count % 10 == digit) {
                count++;
            }
            n_count /= 10;
        }

        if (count % 2 != 0) {
            result = digit * mult + result;
            mult *= 10;
        }

        n /= 10;
    }

    if (result == 0) {
        std::cout << "Each digit of your number occurs an even number of times :(";
    }
    else {
        std::cout << "The final number is " << result;
    }

    return 0;
}