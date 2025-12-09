#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

bool is_empty_file(std::ifstream& file) {
	return file.peek() == std::ifstream::traits_type::eof();
}

std::vector<std::string> taking_words_from_line(const std::string& line) {
	std::vector<std::string> words;
	std::stringstream ss(line);
	std::string word;

	while (ss >> word) {
		words.push_back(word);
	}

	return words;
}

void counting_amount_of_first_word(const std::string& line, const std::string& word, int& amount_of_word) {
	std::stringstream ss(line);
	std::string current_word;
	while (ss >> current_word) {
		if (current_word == word) {
			++amount_of_word;
		}
	}
}

void taking_information_and_counting(const std::string& file_name) {
	std::ifstream in{ file_name };

	if (!in.is_open()) {
		throw ("Error: couldn't open file \"" + file_name + "\"...");
	}

	if (is_empty_file(in)) {
		throw ("Error: file \"" + file_name + "\" is empty");
	}

	std::string line;
	getline(in, line);
	if (line.empty()) {
		throw std::runtime_error("Error: you need to enter one word in the first line");
	}

	std::vector<std::string> words_in_line_1 = taking_words_from_line(line);

	if (words_in_line_1.size() != 1) {
		throw std::runtime_error("Error: you need to enter one word in the first line");
	}

	const std::string word = words_in_line_1[0];
	int amount_of_word{ 0 };


	while (getline(in, line)) {
		counting_amount_of_first_word(line, word, amount_of_word);
	}

	if (amount_of_word == 0) {
		std::cout << "There is no word " << word << " in text";
	}
	else {
		std::cout << "There is " << amount_of_word << " " << word << "s in text";
	}

	in.close();
}

int main() {
	const std::string input_file = "input.txt";

	try {
		taking_information_and_counting(input_file);
	}
	catch (const std::exception& message) {
		std::cerr << message.what() << std::endl;
	}

	return 0;
}