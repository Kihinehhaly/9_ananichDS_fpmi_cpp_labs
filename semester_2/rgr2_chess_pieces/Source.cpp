#include "Chess.h"




int main() {

	Bishop b(Color::black, 3, 5);
	std::cout << b.GetInfo();

	Rook r(Color::white, 2, 1);
	std::cout << r.GetInfo();

	Queen q(Color::black, 8, 6);
	std::cout << q.GetInfo();

	MoveLogger logger;

	try {
		b.Move(5, 7);
		logger.AddMove(b, 3, 5, 5, 7);
		r.Move(2, 4);
		logger.AddMove(r, 2, 1, 2, 4);
		q.Move(7, 7);
		logger.AddMove(q, 8, 6, 7, 7);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}