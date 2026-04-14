#include "Function.h"
#include <fstream>
#include <string>
#include <vector>

void write_functions_to_file(const std::string& filename, const std::vector<Function*>& functions) {
    std::ofstream out(filename);

    if (!out.is_open()) {
        throw std::runtime_error("Can't open file!");
    }

    for (int i = 0; i < functions.size(); i++) {
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

void task1(const std::vector<Function*>& functions) {
    size_t linear{ 0 }, quadratic{ 0 };

    for (int i = 0; i < functions.size(); i++) {
        if (dynamic_cast<LinearFunction*>(functions[i])) {
            linear++;
        }
        if (dynamic_cast<QuadraticFunction*>(functions[i])) {
            quadratic++;
        }
    }

    std::cout << "1) You have " << linear << " linear and " << quadratic << " quadratic functions\n";
}

void task2(const std::vector<Function*>& functions) {
    std::cout << "\n2) Functions without solutions:\n";
    for (int i = 0; i < functions.size(); i++) {
        double sol1, sol2;
        if (functions[i]->solve(sol1, sol2) == 0) {
            functions[i]->print_equation(std::cout);
            std::cout << '\n';
        }
    }
}

void task3(const std::vector<Function*>& functions) {
    double x0, y0;
    std::cout << "\nEnter your x0 and y0 for task3: ";
    if (!(std::cin >> x0 >> y0)) {
        throw std::invalid_argument("\nYou entered wrong type of number!");
    }

    std::cout << "3) Functions, that have solution (" << x0 << ", " << y0 << "):\n";
    for (int i = 0; i < functions.size(); i++) {
        if (functions[i]->evaluate(x0) == y0) {
            functions[i]->print_equation(std::cout);
            std::cout << '\n';
        }
    }
}

void task4(const std::vector<Function*>& functions) {
    const int SIZE = 7;
    LinearFunction* temp[SIZE];
    size_t count{ 0 };

    std::cout << "\n4) Linear functions that have b > a:\n";
    for (int i = 0; i < functions.size(); i++) {
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

void task5(const std::vector<Function*>& functions) {
    const int SIZE = 7;
    QuadraticFunction* temp[SIZE];
    size_t count{ 0 };

    std::cout << "\n5) Quadratic functions with perfect squere:\n";
    for (int i = 0; i < functions.size(); i++) {
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

void menu(const std::vector<Function*>& functions) {
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
        task1(functions);
        break;
    }
    case 2: {
        task2(functions);
        break;
    }
    case 3: {
        task3(functions);
        break;
    }
    case 4: {
        task4(functions);
        break;
    }
    case 5: {
        task5(functions);
        break;
    }
    default:
        throw std::invalid_argument("\nNext time enter number from the list!");
    }

}

int main() {
    std::string filename = "result.txt";
    std::vector<Function*> functions;

    try {
        LinearFactory* linear_factory = new LinearFactory;
        QuadraticFactory* quadratic_factory = new QuadraticFactory;
        functions.push_back(Function::createFunction(LinearFunction_ID, 2, 3, 0));
        functions.push_back(Function::createFunction(LinearFunction_ID, 1, 5, 0));
        functions.push_back(linear_factory->createFunction(2, 10, 0));
        functions.push_back(linear_factory->createFunction(0, 1, 0));
        functions.push_back(Function::createFunction(QuadraticFunction_ID, 1, 2, 1));
        functions.push_back(Function::createFunction(QuadraticFunction_ID, 1, 1, 5));
        functions.push_back(quadratic_factory->createFunction(1, -5, 6));

        write_functions_to_file(filename, functions);

        menu(functions);

        std::cout << "\nProgram complited!";
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}