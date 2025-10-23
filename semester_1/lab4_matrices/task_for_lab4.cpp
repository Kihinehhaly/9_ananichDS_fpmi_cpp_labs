#include <iostream>
#include <random>
#include <iomanip>

void deleting_matrices(int** matrices, int length) {
    for (int i = 0; i < length; i++) {
        delete[] matrices[i];
    }
    delete[] matrices;
}

void input_length(int& length) {
    std::cout << "Enther the lenth of the side of you matrice: ";
    if (!(std::cin >> length) || length < 1) {
        std::cout << "Next time enter integer length > 0";
        std::exit(404);
    }
}

int get_variant() {
    int variant;
    if (!(std::cin >> variant)) {
        std::cout << "Next time enter integers";
    }

    return variant;
}

void creating_matrices(int**& matrices, int length) {
    matrices = new int* [length];
    for (int i = 0; i < length; i++) {
        matrices[i] = new int[length];
    }
}

void entering_random_borders(int& lower, int& upper, int** matrices, int length) {
    std::cout << "\nEnter the integer calculation boundaries: ";
    if (!(std::cin >> lower >> upper)) {
        std::cout << "You had one task: enter integer boundaries...";

        deleting_matrices(matrices, length);

        std::exit(404);
    }

    if (lower > upper) {
        std::swap(lower, upper);
    }
}

void filing_matrices_with_random_number(int** matr, int length, std::mt19937* gen) {
    int lower, upper;
    entering_random_borders(lower, upper, matr, length);

    std::uniform_int_distribution<int> dist(lower, upper);

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            matr[i][j] = dist(*gen);
        }
    }
}

void manual_input(int** matr, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (!(std::cin >> matr[i][j])) {
                std::cout << "Next time enter integers >:(";

                deleting_matrices(matr, length);

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
    std::cout << "\nDo you want a random numbers(enter 1) or the ones you'll enter(enter 2)?\n";
    int variant = get_variant();
    if (variant == 1) {
        std::random_device rd;
        std::mt19937 gen(rd());

        filing_matrices_with_random_number(matrices, length, &gen);

        std::cout << "\nThis is your random numbers:\n";
        printing_matrices(matrices, length);
    }
    else if (variant == 2) {

        std::cout << "\nThen enter your elements:\n";
        manual_input(matrices, length);

    }
    else {
        std::cout << "\nI asked to you enter 1 or 2 >:(";

        deleting_matrices(matrices, length);

        std::exit(404);
    }
}

void swaping_coloms(int** matr, int length) {
    bool find_zero = false;
    for (int j = 1; j < length; j++) {
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

