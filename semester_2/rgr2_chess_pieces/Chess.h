#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

enum class Color { white, black };

class ChessPiece {
protected:
	Color color_;
	uint16_t curr_x_;
	uint16_t curr_y_;
public:
	ChessPiece(Color, uint16_t, uint16_t);
	ChessPiece(const ChessPiece&);
	ChessPiece& operator=(const ChessPiece&);
	virtual ~ChessPiece() = default;

	Color GetColor() const { return color_; }

	virtual std::string GetInfo() const = 0;
	virtual bool CanMove(uint16_t, uint16_t) const = 0;
	virtual void Move(uint16_t, uint16_t) = 0;
};

class Bishop : virtual public ChessPiece {
public:
	Bishop(Color, uint16_t, uint16_t);
	Bishop(const Bishop&);
	Bishop& operator=(const Bishop&);
	~Bishop() override = default;

	std::string GetInfo() const override;
	bool CanMove(uint16_t, uint16_t) const override;
	void Move(uint16_t, uint16_t) override;
};

class Rook : virtual public ChessPiece {
public:
	Rook(Color, uint16_t, uint16_t);
	Rook(const Rook&);
	Rook& operator=(const Rook&);
	~Rook() override = default;

	std::string GetInfo() const override;
	bool CanMove(uint16_t, uint16_t) const override;
	void Move(uint16_t, uint16_t) override;
};

class Queen : public Bishop, public Rook {
public:
	Queen(Color, uint16_t, uint16_t);
	Queen(const Queen&);
	Queen& operator=(const Queen&);
	~Queen() override = default;

	std::string GetInfo() const override;
	bool CanMove(uint16_t, uint16_t) const override;
	void Move(uint16_t, uint16_t) override;
};

class MoveLogger {
private:
	static size_t counter_;
	size_t id_;
	std::vector<std::string> moves_;
public:
	MoveLogger();
	~MoveLogger();

	void AddMove(const ChessPiece&, uint16_t, uint16_t, uint16_t, uint16_t);
};