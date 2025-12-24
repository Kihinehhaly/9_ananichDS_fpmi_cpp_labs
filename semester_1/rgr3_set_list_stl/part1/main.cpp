#include <iostream>
#include <set>
#include <vector>

std::set<int> sieve_of_eratosthenes(int n) {
    if (n < 2) {
        throw "N must be greater than 1";
    }

    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    std::set<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.insert(i);
        }
    }

    if (primes.empty()) {
        throw "No primes found";
    }

    return primes;
}

void print_primes(const std::set<int>& primes) {
    std::cout << "Prime numbers: ";
    for (int prime : primes) {
        std::cout << prime << " ";
    }
    std::cout << "\nCount: " << primes.size() << "\n";
}

int main() {
    std::cout << "Enter N for sieve: ";
    int n;
    std::cin >> n;

    try {
        std::set<int> primes = sieve_of_eratosthenes(n);
        print_primes(primes);
    }
    catch (const char* error) {
        std::cout << "Error: " << error << "\n";
    }

    return 0;
}