#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>
#include "player.hpp"
#include "enemy.hpp"
#include "random.hpp"

enum class State {
	Game_Start,
	Game_Playing,
	Game_Pause,
	Game_End
};
class Game {
	private:
		int width;
		int height;
		float delta;
		float timer;
		std::string title;
		State state{State::Game_Start};
		const std::shared_ptr<Rectangle> map;
		std::list<std::unique_ptr<Entity>> entities;
	public:
		Game(int w, int h, std::string t);
		void Run();
};

inline Game::Game(int w, int h, std::string t) : width{w}, height{h},title{t}, map{std::make_shared<Rectangle>(0, 0, w, h)} {
	std::cout << "inshallah\n";
	

}

inline void Game::Run() {
	InitWindow(width, height, title.c_str());
	entities.push_back(std::make_unique<Player>(Rectangle{12.0, 12.0, 76.0, 76.0}, 100, 20, 200.0, map));
	//entities.push_back(std::make_unique<Entity>(Rectangle{60.0, 60.0, 76.0, 76.0}, 100, 20, 200.0, map));
	while (!WindowShouldClose()) {	
		delta = GetFrameTime();	
		timer = GetTime();
	
		/*if (timer % 3 == 0) {
	entities.push_front(std::make_unique<Enemy>(Rectangle{12.0, 12.0, 76.0, 76.0}, 100, 20, 200.0, map));
		}*/

		for (auto &e: entities) {
			e->update(delta, entities);
		}

		BeginDrawing();
		ClearBackground(WHITE);
		

		for (auto &e: entities) {
			e->render();
		}
		
		//DrawText("text", x, y, size=12, BLACK);

		EndDrawing();
	}

	CloseWindow();
}
