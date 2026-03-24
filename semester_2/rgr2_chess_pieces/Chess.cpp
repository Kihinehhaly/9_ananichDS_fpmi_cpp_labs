#include "Chess.h"

ChessPiece::ChessPiece(Color color, uint16_t curr_x, uint16_t curr_y) : color_(color), curr_x_(curr_x), curr_y_(curr_y) {};

ChessPiece::ChessPiece(const ChessPiece& other) : ChessPiece(other.color_, other.curr_x_, other.curr_y_) {};

ChessPiece& ChessPiece::operator=(const ChessPiece& other) {
	if (this == &other) {
		return *this;
	}

	color_ = other.color_;
	curr_x_ = other.curr_x_;
	curr_y_ = other.curr_y_;

	return *this;
}

Bishop::Bishop(Color color, uint16_t curr_x, uint16_t curr_y) : ChessPiece(color, curr_x, curr_y) {}

Bishop::Bishop(const Bishop& other) : ChessPiece(other){}

Bishop& Bishop::operator=(const Bishop& other) {
	if (this != &other) {
		ChessPiece::operator=(other);
	}

	return *this;
}

std::string Bishop::GetInfo() const {
	char symble_x = 'a' + (curr_x_ - 1);

	std::string result = "B";
	result += symble_x;
	result += std::to_string(curr_y_);

	return result;
}

bool Bishop::CanMove(uint16_t x, uint16_t y) const {
	return std::abs(curr_x_ - x) == std::abs(curr_y_ - y);
}

void Bishop::Move(uint16_t x, uint16_t y) {
	if (!CanMove(x, y)) {
		throw std::invalid_argument("Error: Bishop can't move like that!");
	}
	curr_x_ = x;
	curr_y_ = y;
}

Rook::Rook(Color color, uint16_t curr_x, uint16_t curr_y) : ChessPiece(color, curr_x, curr_y) {}

Rook::Rook(const Rook& other) : ChessPiece(other) {}

Rook& Rook::operator=(const Rook& other) {
	if (this != &other) {
		ChessPiece::operator=(other);
	}

	return *this;
}

std::string Rook::GetInfo() const {
	char symble_x = 'a' + (curr_x_ - 1);

	std::string result = "R";
	result += symble_x;
	result += std::to_string(curr_y_);

	return result;
}

bool Rook::CanMove(uint16_t x, uint16_t y) const {
	return curr_x_ == x || curr_y_ == y;
}

void Rook::Move(uint16_t x, uint16_t y) {
	if (!CanMove(x, y)) {
		throw std::invalid_argument("Error: Rook can't move like that!");
	}
	curr_x_ = x;
	curr_y_ = y;
}

Queen::Queen(Color color, uint16_t curr_x, uint16_t curr_y) : ChessPiece(color, curr_x, curr_y), Bishop(color, curr_x, curr_y), Rook(color, curr_x, curr_y) {}

Queen::Queen(const Queen& other) : ChessPiece(other), Bishop(other), Rook(other) {}

Queen& Queen::operator=(const Queen& other) {
	if (this != &other) {
		ChessPiece::operator=(other);
		Bishop::operator=(other);
		Rook::operator=(other);
	}

	return *this;
}

std::string Queen::GetInfo() const {
	char symble_x = 'a' + (curr_x_ - 1);

	std::string result = "Q";
	result += symble_x;
	result += std::to_string(curr_y_);

	return result;
}

bool Queen::CanMove(uint16_t x, uint16_t y) const {
	return Bishop::CanMove(x, y) || Rook::CanMove(x, y);
}

void Queen::Move(uint16_t x, uint16_t y) {
	if (!CanMove(x, y)) {
		throw std::invalid_argument("Error: Queen can't move like that!");
	}
	curr_x_ = x;
	curr_y_ = y;
}

size_t MoveLogger::counter_ = 1;

MoveLogger::MoveLogger() : id_(counter_++) {}

MoveLogger::~MoveLogger() {
	std::ofstream out("game_" + std::to_string(id_) + "_log.txt");

	for (int i = 0; i < moves_.size(); i++) {
		out << i + 1 << ". " << moves_[i] << "\n";
	}
}

void MoveLogger::AddMove(const ChessPiece& piece, uint16_t from_x, uint16_t from_y, uint16_t to_x, uint16_t to_y) {
	std::string result;

	result = (piece.GetColor() == Color::white) ? "white: " : "black: ";
	result += piece.GetInfo()[0];

	char symble_from_x = 'a' + (from_x - 1);
	char symble_to_x = 'a' + (to_x - 1);

	result += symble_from_x;
	result += std::to_string(from_y) + " - ";
	result += symble_to_x;
	result += std::to_string(to_y);

	moves_.push_back(result);
}