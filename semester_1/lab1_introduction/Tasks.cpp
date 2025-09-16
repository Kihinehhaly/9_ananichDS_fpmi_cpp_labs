#include <iostream>
#include <cmath>

void task1(int a, int b, int d) {
    if (b < a) {
        int n = a;
        a = b;
        b = n;
    }
    else if (d == 0) {
        std::cout << "d can't be equal 0!\n";
        std::exit(1);
    }

    while (b > a) {
        if ((a % 3) == 0) {
            std::cout << a << " ";
        }
        a += d;
    }
 
    std::cout << "\n";
}

void task2() {

    int sum{ 0 }, mult{1}, n;

    std::cout << "Enter n for task 2: ";
    if (!(std::cin >> n) || n <= 1) {
        std::cout << "Please, enter integer n > 1\n";
        std::exit(404);
    }
 
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) {
            sum += i;
        }
        else {
            mult *= i;
        }
    }
 
    std::cout << "Sum is " << sum << " and multiplication is " << mult << "\n";
}

void task3() {
    int sum{0}, n;

    std::cout << "Enter n for task 3: ";
    if (!(std::cin >> n) || n <= 1) {
        std::cout << "Please, enter integer n > 1\n";
        std::exit(404);
    }

    for (int i=0; i <= n; i++) {
        sum = sum + std::pow(i, i);
    }
    std::cout << "Sum = " << sum << "\n";

}

void task5() {

    int n, m;

    std::cout << "Enter n and m for task 5: ";
    if (!(std::cin >> n >> m) || m <= 0 || n <= 0) {
        std::cout << "Please, enter two integers > 0\n";
        std::exit(404);
    }

    if (m < n) {
        int x = n;
        n = m;
        m = x;
    }

    for (int i = 1; i <= n+1; i++) {
        if ((m % i) == 0 && (n % i) == 0) {
            std::cout << i << " ";
        }
    }

    std::cout << "\n";
}

void task6() {

    int sum{0}, n;

    std::cout << "Enter n for task 6: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Please, enter integer n > 0\n";
        std::exit(404);
    }


    for (int i = 1; i <= n * 2; i += 2) {
        sum += i;
    }

    std::cout << "Sum is " << sum << "\n";

}

void task8() {

    float numbers[10];
    int count{0};

    std::cout << "Insert 10 float numbers: ";

    for (int i = 0; i < 10; i++) {

        if (!(std::cin >> numbers[i])) {
            std::cout << "Please, enter float numbers >:(\n";
            std::exit(404);
        }
    }

    for (int i = 1; i < 11; i++) {
        if (numbers[i] < numbers[i - 1] && numbers[i] < numbers[i + 1]) {
            count++;
        }
    }

    std::cout << "Amount of required numbers: " << count << "\n";

}

int main() {
    
    int a, b;
    std::cout << "Enter two integers a and b: ";
    if (!(std::cin >> a >> b) || b == 0) {
        std::cout << "You enterd chepuha! :(\n";
        std::exit(1);
    }

    int p = a / b;
    int q = a % b;
    std::cout << "p = " << p << ", q = " << q << '\n';

    int a1, b1, d1;

    std::cout << "Enter a, b and d for task 1: ";
    std::cin >> a1 >> b1 >> d1;

    task1(a1, b1, d1);

    task2();

    task3();

    task5();

    task6();

    task8();

    return 0;
}