#include "game.hpp"
int main() {

	//Game game(800, 600, "hopa");
	//game.Run();
	Game& game = Game::Init(800, 600, "squares and squares");
	game.Run();
	return 0;
}
