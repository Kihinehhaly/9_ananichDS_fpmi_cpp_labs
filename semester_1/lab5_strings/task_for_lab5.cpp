#include <iostream>
#include <string>
#include <vector>

void filling_line(std::string& line) {
	std::cout << "Enter your line: ";
	std::getline(std::cin, line);

	if (line.empty()) {
		throw "Your line is empty!";
	}
}

void printing_line(std::string line) {
	std::cout << "\nYour new line: " << line << "\n";
}

void changing_letters(std::string& line) {
	for (char& symbol : line) {
		if (symbol >= 'A' && symbol <= 'Z') {
			symbol = std::tolower(symbol);
		}
		else if (symbol >= 'a' && symbol <= 'z') {
			symbol = std::toupper(symbol);
		}
	}

	printing_line(line);
}

std::vector<std::string> divide_into_words(const std::string& line, const std::string& delimeters) {
	std::vector<std::string> words;

	std::string::size_type begin_index = line.find_first_not_of(delimeters, 0);
	std::string::size_type end_index = line.find_first_of(delimeters, begin_index);

	while (begin_index != std::string::npos) {
		std::string word = line.substr(begin_index, end_index - begin_index);
		if (!word.empty()) {
			words.push_back(word);
		}

		begin_index = line.find_first_not_of(delimeters, end_index);
		end_index = line.find_first_of(delimeters, begin_index);
	}

	return words;
}

std::vector<std::string> saving_delimeters(const std::string& line, const std::string& delimeters) {
	std::vector<std::string> delimeters_in_line;

	std::string::size_type begin_index = line.find_first_of(delimeters, 0);
	std::string::size_type end_index = line.find_first_not_of(delimeters, begin_index);

	while (begin_index != std::string::npos) {
		std::string word = line.substr(begin_index, end_index - begin_index);
		if (!word.empty()) {
			delimeters_in_line.push_back(word);
		}

		begin_index = line.find_first_of(delimeters, end_index);
		end_index = line.find_first_not_of(delimeters, begin_index);
	}

	return delimeters_in_line;
}

int amount_of_capital_letters(std::string word) {
	int amount_of_capital_letters{ 0 };

	for (char symbol : word) {
		if (symbol >= 'A' && symbol <= 'Z') {
			++amount_of_capital_letters;
		}
	}

	return amount_of_capital_letters;
}

void bubble_sort_words(std::vector<std::string>& words) {
	for (int i = 0; i < words.size() - 1; i++) {
		for (int j = 0; j < words.size() - i - 1; j++) {
			if (amount_of_capital_letters(words[j]) > 
				amount_of_capital_letters(words[j+1])) {
				std::swap(words[j], words[j + 1]);
			}
			else if (amount_of_capital_letters(words[j]) == 
				amount_of_capital_letters(words[j + 1])) {
				if (std::toupper(words[j][0]) > std::toupper(words[j + 1][0])) {
					std::swap(words[j], words[j + 1]);
				}
			}
		}
	}
}

void changing_line_after_sort(std::string& line, std::vector<std::string> words, std::vector<std::string> delimeters_in_line) {
	int i{ 0 };
	if (line[0] == ' ') {
		line.clear();
		while (i < words.size() && i < delimeters_in_line.size()) {
			line.append(delimeters_in_line[i]);
			line.append(words[i]);

			++i;
		}
	}
	else {
		line.clear();
		while (i < words.size() && i < delimeters_in_line.size()) {
			line.append(words[i]);
			line.append(delimeters_in_line[i]);

			++i;
		}
	}

	if (i < words.size()) {
		line.append(words[i]);
	}

	if (i < delimeters_in_line.size()) {
		line.append(delimeters_in_line[i]);
	}
}

void sorting_line(std::string line, const std::string& delimeters) {
	std::vector<std::string> words = divide_into_words(line, delimeters);
	std::vector<std::string> delimeters_in_line = saving_delimeters(line, delimeters);

	bubble_sort_words(words);

	changing_line_after_sort(line, words, delimeters_in_line);

	printing_line(line);
}

int main() {
	std::string line;
	std::string delimeters = " ,.?!:;/|";

	try {
		filling_line(line);
		
		changing_letters(line);

		sorting_line(line, delimeters);
	}
	catch (const char* message) {
		std::cout << message;
	}

	return 0;
}