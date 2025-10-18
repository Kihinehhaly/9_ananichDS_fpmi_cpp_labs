#include <iostream>
#include <random>
#include <iomanip>

void input_length(int& length) {
    std::cout << "Enther the lenth of the side of you matrice: ";
    if (!(std::cin >> length) || length < 1) {
        std::cout << "Next time enter integer length > 0";
        std::exit(404);
    }
}

void creating_matrices(int**& matrices, int length) {
    matrices = new int* [length];
    for (int i = 0; i < length; i++) {
        matrices[i] = new int[length];
    }
}

void filing_matrices_with_random_number(int** matr, int length) {
    int lower, upper;
    std::cout << "Enter the integer calculation boundaries: ";
    if (!(std::cin >> lower >> upper)) {
        std::cout << "You had one task: enter integer boundaries...";
        std::exit(404);
    }

    if (lower > upper) {
        std::swap(lower, upper);
    }

    std::mt19937 gen(45218965);
    std::uniform_int_distribution<int> dist(lower, upper);

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            matr[i][j] = dist(gen);
        }
    }
}

void manual_input(int** matr, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (!(std::cin >> matr[i][j])) {
                std::cout << "Next time enter integers >:(";
                std::exit(404);
            }
        }
    }
}

void printing_matrices(int** matr, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            std::cout << std::setw(5) << matr[i][j];
        }
        std::cout << "\n";
    }
}

void chousing_variant_of_input(int** matrices, int length) {
    int variant;

    std::cout << "Do you want a random numbers(enter 1) or the ones you'll enter(enter 2)?\n";
    if (!(std::cin >> variant)) {
        std::cout << "Next time enter 1 or 2 >:(";
        std::exit(404);
    }
    if (variant == 1) {

        filing_matrices_with_random_number(matrices, length);

        std::cout << "\nThis is your random numbers:\n";
        printing_matrices(matrices, length);
    }
    else if (variant == 2) {

        std::cout << "Then enter your elements:\n";
        manual_input(matrices, length);

    }
    else {
        std::cout << "I asked to you enter 1 or 2 >:(";
        std::exit(404);
    }
}

void swaping_coloms(int** matr, int length) {
    bool find_zero = false;
    for (int j = 0; j < length; j++) {
        if (matr[0][j] == 0) {
            for (int i = 0; i < length; i++) {
                std::swap(matr[i][j], matr[i][0]);
            }
            find_zero = true;
            break;
        }
    }
    if (!find_zero) {
        std::cout << "\n1) There is no 0 in first line\n";
    }
    else {
        std::cout << "\n1) Your new matrices:\n";
        printing_matrices(matr, length);
    }
}

void finding_max_element(int** matr, int length) {
    int max_element = matr[0][0];

    for (int i = 0; i < length; i++) {
        for (int j = i; j < length; j++) {
            if (matr[i][j] > max_element) {
                max_element = matr[i][j];
            }
        }
    }

    std::cout << "\n2) Max element is " << max_element << "\n";
}

void deleting_matrices(int** matrices, int length) {
    for (int i = 0; i < length; i++) {
        delete[] matrices[i];
    }
    delete[] matrices;
}

int main() {
    int length;
    input_length(length);

    int** matrices;
    creating_matrices(matrices, length);

    chousing_variant_of_input(matrices, length);

    swaping_coloms(matrices, length);

    finding_max_element(matrices, length);

    deleting_matrices(matrices, length);

    return 0;
}