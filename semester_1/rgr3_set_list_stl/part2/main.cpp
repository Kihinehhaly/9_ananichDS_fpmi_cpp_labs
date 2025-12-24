#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <fstream>

struct Author {
    std::string last_name;
    std::string first_name;
    std::string middle_name;

    Author(const std::string& last, const std::string& first, const std::string& middle)
        : last_name(last), first_name(first), middle_name(middle) {
    }

    bool operator<(const Author& other) const {
        return last_name < other.last_name;
    }
};

struct Book {
    int udk;
    std::list<Author> authors;
    std::string title;
    int year;

    Book(int u, const std::list<Author>& a, const std::string& t, int y)
        : udk(u), authors(a), title(t), year(y) {
    }

    bool operator<(const Book& other) const {
        return title < other.title;
    }
};

class Library {
private:
    std::list<Book> books;

public:
    void add_book() {
        std::cout << "Enter UDK: ";
        int udk;
        std::cin >> udk;

        std::cout << "Enter title: ";
        std::string title;
        std::cin.ignore();
        std::getline(std::cin, title);

        std::cout << "Enter year: ";
        int year;
        std::cin >> year;

        std::list<Author> authors;
        std::string last, first, middle;
        std::cout << "Enter authors (last first middle, empty last name to stop):\n";

        while (true) {
            std::cout << "Last name: ";
            std::getline(std::cin >> std::ws, last);
            if (last.empty()) break;

            std::cout << "First name: ";
            std::getline(std::cin, first);
            std::cout << "Middle name: ";
            std::getline(std::cin, middle);

            authors.emplace_back(last, first, middle);
        }

        if (authors.empty()) {
            throw "Book must have at least one author";
        }

        books.emplace_back(udk, authors, title, year);
        books.sort();

        std::cout << "Book added successfully\n";
    }

    void remove_book() {
        std::cout << "Enter title to remove: ";
        std::string title;
        std::cin.ignore();
        std::getline(std::cin, title);

        auto it = std::find_if(books.begin(), books.end(),
            [&title](const Book& book) { return book.title == title; });

        if (it != books.end()) {
            books.erase(it);
            std::cout << "Book removed\n";
        }
        else {
            throw "Book not found";
        }
    }

    void find_by_title() {
        std::cout << "Enter title to search: ";
        std::string title;
        std::cin.ignore();
        std::getline(std::cin, title);

        bool found = false;
        auto it = books.begin();
        while (it != books.end()) {
            if (it->title.find(title) != std::string::npos) {
                print_book(*it);
                found = true;
            }
            ++it;
        }

        if (!found) {
            throw "No books found with this title";
        }
    }

    void find_by_author() {
        std::cout << "Enter author last name: ";
        std::string last_name;
        std::cin >> last_name;

        bool found = false;
        for (const auto& book : books) {
            for (const auto& author : book.authors) {
                if (author.last_name == last_name) {
                    print_book(book);
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            throw "No books found for this author";
        }
    }

    void add_author_to_book() {
        std::cout << "Enter book title: ";
        std::string title;
        std::cin.ignore();
        std::getline(std::cin, title);

        auto book_it = std::find_if(books.begin(), books.end(),
            [&title](const Book& b) { return b.title == title; });

        if (book_it == books.end()) {
            throw "Book not found";
        }

        std::cout << "Enter new author (last first middle): ";
        std::string last, first, middle;
        std::getline(std::cin >> std::ws, last);
        std::getline(std::cin, first);
        std::getline(std::cin, middle);

        book_it->authors.emplace_back(last, first, middle);
        book_it->authors.sort();

        std::cout << "Author added\n";
    }

    void remove_author_from_book() {
        std::cout << "Enter book title: ";
        std::string title;
        std::cin.ignore();
        std::getline(std::cin, title);

        auto book_it = std::find_if(books.begin(), books.end(),
            [&title](const Book& b) { return b.title == title; });

        if (book_it == books.end()) {
            throw "Book not found";
        }

        std::cout << "Enter author last name to remove: ";
        std::string last_name;
        std::cin >> last_name;

        book_it->authors.remove_if([&last_name](const Author& a) {
            return a.last_name == last_name;
            });

        std::cout << "Author removed\n";
    }

    void load_from_file(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw "Cannot open file";
        }

        books.clear();
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int udk, year;
            std::string title, author_str;

            if (!(iss >> udk >> title >> year)) continue;

            std::list<Author> authors;
            while (iss >> author_str) {
                size_t pos1 = author_str.find('_');
                size_t pos2 = author_str.rfind('_');
                if (pos1 != std::string::npos && pos2 != pos1) {
                    std::string last = author_str.substr(0, pos1);
                    std::string first = author_str.substr(pos1 + 1, pos2 - pos1 - 1);
                    std::string middle = author_str.substr(pos2 + 1);
                    authors.emplace_back(last, first, middle);
                }
            }

            if (!authors.empty()) {
                books.emplace_back(udk, authors, title, year);
            }
        }
        file.close();
        books.sort();
        std::cout << "Library loaded from file\n";
    }

private:
    void print_book(const Book& book) {
        std::cout << "UDK: " << book.udk
            << ", Title: " << book.title
            << ", Year: " << book.year << "\n";
        std::cout << "Authors: ";
        for (const auto& author : book.authors) {
            std::cout << author.last_name << " " << author.first_name[0] << ". ";
        }
        std::cout << "\n";
    }
};

void print_menu() {
    std::cout << "\n=== LIBRARY MENU ===\n";
    std::cout << "1. Add book\n";
    std::cout << "2. Remove book\n";
    std::cout << "3. Find by title\n";
    std::cout << "4. Find by author\n";
    std::cout << "5. Add author to book\n";
    std::cout << "6. Remove author from book\n";
    std::cout << "7. Load from file\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

int main() {
    Library library;

    try {
        library.load_from_file("library.txt");
    }
    catch (const char* error) {
        std::cout << "File load error: " << error << "\n";
    }

    int choice;
    while (true) {
        print_menu();
        std::cin >> choice;
        std::cin.ignore();

        try {
            switch (choice) {
            case 1: library.add_book(); break;
            case 2: library.remove_book(); break;
            case 3: library.find_by_title(); break;
            case 4: library.find_by_author(); break;
            case 5: library.add_author_to_book(); break;
            case 6: library.remove_author_from_book(); break;
            case 7: {
                std::string filename;
                std::cout << "Enter filename: ";
                std::cin >> filename;
                library.load_from_file(filename);
                break;
            }
            case 0: return 0;
            default: std::cout << "Invalid choice\n";
            }
        }
        catch (const char* error) {
            std::cout << "Error: " << error << "\n";
        }
    }

    return 0;
}
