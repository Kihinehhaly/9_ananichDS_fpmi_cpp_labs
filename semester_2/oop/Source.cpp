#include "Function.h"
#include <fstream>
#include <string>

const int SIZE = 7;

void write_functions_to_file(const std::string& filename, Function* functions[], int size) {
    std::ofstream out(filename);

    if (!out.is_open()) {
        throw std::runtime_error("Can't open file!");
    }

    for (int i = 0; i < size; i++) {
        functions[i]->print_equation(out);
        out << " Solutions: ";
        double sol1, sol2;

        int amount_of_sol = functions[i]->solve(sol1, sol2);

        switch (amount_of_sol) {
        case 0: {
            out << "No solutions\n";
            break;
        }
        case 1: {
            out << '(' << sol1 << ", 0)\n";
            break;
        }
        case 2: {
            out << '(' << sol1 << ", 0), (" << sol2 << ", 0)\n";
            break;
        }
        default: {
            out << "Unexpected result\n";
        }
        }
    }
}

void task1(Function* functions[], int size) {
    size_t linear{ 0 }, quadratic{ 0 };

    for (int i = 0; i < size; i++) {
        if (dynamic_cast<LinearFunction*>(functions[i])) {
            linear++;
        }
        if (dynamic_cast<QuadraticFunction*>(functions[i])) {
            quadratic++;
        }
    }

    std::cout << "1) You have " << linear << " linear and " << quadratic << " quadratic functions\n";
}

void task2(Function* functions[], int size) {
    std::cout << "\n2) Functions without solutions:\n";
    for (int i = 0; i < size; i++) {
        double sol1, sol2;
        if (functions[i]->solve(sol1, sol2) == 0) {
            functions[i]->print_equation(std::cout);
            std::cout << '\n';
        }
    }
}

void task3(Function* functions[], int size) {
    double x0, y0;
    std::cout << "\nEnter your x0 and y0 for task3: ";
    if (!(std::cin >> x0 >> y0)) {
        throw std::invalid_argument("\nYou entered wrong type of number!");
    }

    std::cout << "3) Functions, that have solution (" << x0 << ", " << y0 << "):\n";
    for (int i = 0; i < size; i++) {
        if (functions[i]->evaluate(x0) == y0) {
            functions[i]->print_equation(std::cout);
            std::cout << '\n';
        }
    }
}

void task4(Function* functions[], int size) {
    LinearFunction* temp[SIZE];
    size_t count{ 0 };

    std::cout << "\n4) Linear functions that have b > a:\n";
    for (int i = 0; i < size; i++) {
        LinearFunction* lin_fun = dynamic_cast<LinearFunction*>(functions[i]);

        if (lin_fun && lin_fun->get_b() > lin_fun->get_a()) {
            temp[count++] = lin_fun;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (temp[i]->get_b() < temp[j]->get_b()) {
                std::swap(temp[i], temp[j]);
            }
        }
    }

    for (int i = 0; i < count; i++) {
        temp[i]->print_equation(std::cout);
        std::cout << '\n';
    }
}

void task5(Function* functions[], int size) {
    QuadraticFunction* temp[SIZE];
    size_t count{ 0 };

    std::cout << "\n5) Quadratic functions with perfect squere:\n";
    for (int i = 0; i < size; i++) {
        QuadraticFunction* quad_fun = dynamic_cast<QuadraticFunction*>(functions[i]);

        if (quad_fun && quad_fun->get_b() * quad_fun->get_b() == (quad_fun->get_a() * quad_fun->get_c() * 4)) {
            temp[count++] = quad_fun;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (temp[i]->get_a() > temp[j]->get_a()) {
                std::swap(temp[i], temp[j]);
            }
        }
    }

    for (int i = 0; i < count; i++) {
        temp[i]->print_equation(std::cout);
        std::cout << '\n';
    }
}

void menu(Function* functions[], int size) {
    size_t variant;
    std::cout << "Enter the number of the required request from the list:\n";
    std::cout << "1) Count the number of linear / quadratic functions.\n";
    std::cout << "2) Find all equations that have no solutions.\n";
    std::cout << "3) Find all functions that have f(x0) = y0, where x0, y0 you can enter yourself.\n";
    std::cout << "4) Find all linear equations that have b > a.\n";
    std::cout << "5) Find all quadratic equations for which f(x) is a perfect square.\n";
    std::cout << "\nYour choise: ";
    if (!(std::cin >> variant)) {
        throw std::invalid_argument("\nYou entered wrong type of number!");
    }

    switch (variant)
    {
    case 1: {
        task1(functions, size);
        break;
    }
    case 2: {
        task2(functions, size);
        break;
    }
    case 3: {
        task3(functions, size);
        break;
    }
    case 4: {
        task4(functions, size);
        break;
    }
    case 5: {
        task5(functions, size);
        break;
    }
    default:
        throw std::invalid_argument("\nNext time enter number from the list!");
    }

}

int main() {
    std::string filename = "result.txt";
    Function* functions[SIZE] = { nullptr };

    try {
        functions[0] = new LinearFunction(2, 3);
        functions[1] = new LinearFunction(1, 5);
        functions[6] = new LinearFunction(2, 10);
        functions[2] = new LinearFunction(0, 1);
        functions[3] = new QuadraticFunction(1, 2, 1);
        functions[4] = new QuadraticFunction(1, 1, 5);
        functions[5] = new QuadraticFunction(1, -5, 6);

        write_functions_to_file(filename, functions, SIZE);

        menu(functions, SIZE);

        std::cout << "\nProgram complited!";
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    for (int i = 0; i < SIZE; i++) {
        delete functions[i];
    }

    return 0;
}