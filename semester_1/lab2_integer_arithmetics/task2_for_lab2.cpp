#include <iostream>

int main() {
    long long n, result{ 0 }, original, mult{ 1 };
    int digit, count;

    std::cout << "Enter n for task 2: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Please, enter long n > 0\n";
        std::exit(404);
    }

    original = n;

    while (n > 0) {
        count = 0;
        digit = n % 10;
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

    std::cout << "The final number is " << result;

    return 0;
}