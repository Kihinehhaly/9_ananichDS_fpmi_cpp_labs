#include <iostream>
#include <random>
#include <iomanip>

bool comparison_1(int first_number, int second_number) {
	return first_number > second_number;
}

bool comparison_2(int first_number, int second_number) {
    return first_number < second_number;
}

int get_variant() {
    int variant;
    if (!(std::cin >> variant)) {
        std::cout << "Next time enter integers";
    }

    return variant;
}

void input_sides(int& n, int& m) {
    std::cout << "Enther n (rows) for your matrice: ";
    if (!(std::cin >> n) || n < 1) {
        std::cout << "Next time enter integer > 0";
        std::exit(404);
    }
    std::cout << "\nNow enther m (columns) for your matrice: ";
    if (!(std::cin >> m) || m < 1) {
        std::cout << "Next time enter integer > 0";
        std::exit(404);
    }
}

void creating_matrices(int**& matrices, int n, int m) {
    matrices = new int* [n];
    for (int i = 0; i < n; i++) {
        matrices[i] = new int[m];
    }
}

void filing_matrices_with_random_number(int** matr, int n, int m, std::mt19937* gen) {
    int lower, upper;
    std::cout << "Enter the integer calculation boundaries: ";
    if (!(std::cin >> lower >> upper)) {
        std::cout << "You had one task: enter integer boundaries...";
        std::exit(404);
    }

    if (lower > upper) {
        std::swap(lower, upper);
    }

    std::uniform_int_distribution<int> dist(lower, upper);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matr[i][j] = dist(*gen);
        }
    }
}

void manual_input(int** matr, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!(std::cin >> matr[i][j])) {
                std::cout << "Next time enter integers >:(";
                std::exit(404);
            }
        }
    }
}

void printing_matrices(int** matr, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << std::setw(5) << matr[i][j];
        }
        std::cout << "\n";
    }
}

void chousing_variant_of_input(int** matrices, int n, int m) {
    std::cout << "\nDo you want a random numbers(enter 1) or the ones you'll enter(enter 2)?\n";
    int variant = get_variant();
    if (variant == 1) {
        std::random_device rd;
        std::mt19937 gen(rd());

        filing_matrices_with_random_number(matrices, n, m, &gen);

        std::cout << "\nThis is your random numbers:\n";
        printing_matrices(matrices, n, m);
    }
    else if (variant == 2) {

        std::cout << "Then enter your elements:\n";
        manual_input(matrices, n, m);

    }
    else {
        std::cout << "I asked to you enter 1 or 2 >:(";
        std::exit(404);
    }
}

void bubble_sort(int* array, int m, bool (*comparison)(int a, int b)) {
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (comparison(array[j], array[j+1])) {
                std::swap(array[j], array[j + 1]);
            }
        }
    }
}

int finding_max_element(int* array, int length_of_array) {
    int max_element = array[0];

    for (int i = 0; i < length_of_array; i++) {
        if (array[i] > max_element) {
            max_element = array[i];
        }
    }

    return max_element;
}

int finding_min_element(int* array, int length) {
    int min_element = array[0];

    for (int i = 0; i < length; i++) {
        if (array[i] < min_element) {
            min_element = array[i];
        }
    }

    return min_element;
}


void counting_sort(int* array, int length, int variant) {
    int min = finding_min_element(array, length);
    int max = finding_max_element(array, length);

    int amount_of_element_value = max - min + 1;
    int* count = new int[amount_of_element_value] {};


    for (int j = 0; j < length; j++) {
        count[array[j] - min]++;
    }

    if (variant == 1) {
        for (int i = 0; i < amount_of_element_value; i++) {
            for (int j = 0; j < count[i]; j++) {
                std::cout << std::setw(5) << (i + min) << " ";
            }
        }
    }
    else {
        for (int i = amount_of_element_value - 1; i >= 0; i--) {
            for (int j = 0; j < count[i]; j++) {
                std::cout << std::setw(5) << (i + min) << " ";
            }
        }
    }

    delete[] count;
}

void quick_sort(int* array, int m, bool (*comparison)(int a, int b)) {
    int i = 0, j = m - 1;

    while (i != j) {
        if (comparison(array[i], array[j])) {
            std::swap(array[i], array[j]);
            ++i;
        }
        else {
            --j;
        }
    }

    for (int k = 0; k < (m - 1); k++) {
        if (comparison(array[i], array[i+1])) {
            quick_sort(array, m, comparison);
        }
    }
}

void merge_sort() {

}

void input_sort() {

}

int finding_index_of_element(int* array, int i, int m, bool (*comparison)(int a, int b)) {
    int index = i;
    for (i; i < m; i++) {
        if (comparison(array[index], array[i])) {
            index = i;
        }
    }

    return index;
}

void choise_sort(int* array, int m, bool (*comparison)(int a, int b)) {
    for (int i = 0; i < m; i++) {
        int max_index = finding_index_of_element(array, i, m, comparison);
        std::swap(array[i], array[max_index]);
    }
}


//bool ascending_or_descending_order(int** matrices, int n, int m) {
//    std::cout << "Do you want an ascending order(enter 1) or a descending order(enter 2)?\n";
//    int variant = get_variant();
//    if (variant == 1) {
//        
//    }
//    else if (variant == 2) {
//
//    }
//    else {
//        std::cout << "I asked to you enter 1 or 2 >:(";
//        std::exit(404);
//    }
//}
//
//void choosing_type_of_sort(int** matrices, int n, int m) {
//    std::cout << "Would you like a bubble sort(enter 1), counting sort(enter 2), quick sort(enter 3), merge sort(enter 4), input sort(enter 5), choise sort(enter 6)";
//    switch (int variant = get_variant(); variant) {
//    case 1: {
//        for (int i = 0; i < n; i++) {
//            bubble_sort(matrices[i], m, );
//        }
//    }
//    case 2: {
//        for (int i = 0; i < n; i++) {
//            counting_sort(matrices[i], m);
//        }
//    }
//    case 3: {
//        for (int i = 0; i < n; i++) {
//            quick_sort(matrices[i], m);
//        }
//    }
//    case 4: {
//        for (int i = 0; i < n; i++) {
//            merge_sort(matrices[i], m);
//        }
//    }
//    case 5: {
//        for (int i = 0; i < n; i++) {
//            input_sort(matrices[i], m);
//        }
//    }
//    case 6: {
//        for (int i = 0; i < n; i++) {
//            choise_sort(matrices[i], m);
//        }
//    }
//    default: {
//        std::cout << "Next time enter 1 - 6 >:(";
//        std::exit(404);
//    }
//    }
//}

void deleting_matrices(int** matrices, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrices[i];
    }
    delete[] matrices;
}


int main() {
    int n, m;
    input_sides(n, m);

    int** matrices;
    creating_matrices(matrices, n, m);

    chousing_variant_of_input(matrices, n, m);

    

    deleting_matrices(matrices, n);

    return 0;
}