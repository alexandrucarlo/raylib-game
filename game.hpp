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
		float timer = 0;
		std::string title;
		State state{State::Game_Start};
		const std::shared_ptr<Rectangle> map;
		std::list<std::unique_ptr<Entity>> entities;

		Game &operator=(const Game &) = delete; // we're overloading this for singleton
		Game(int w, int h, std::string t);
		Game(const Game& o) = delete;
	public:
		static Game& Init(int w, int h, std::string t) {
			static Game game(w, h, t);
			return game;
		}
		void Run();
};

inline Game::Game(int w, int h, std::string t) : width{w}, height{h},title{t}, map{std::make_shared<Rectangle>(0, 0, w, h)} {
	std::cout << "we're up and running! -alext";
}

inline void Game::Run() {
	InitWindow(width, height, title.c_str());
	entities.push_back(std::make_unique<Player>(Rectangle{12.0, 12.0, 76.0, 76.0}, 100, 20, 200.0, map));
	//entities.push_back(std::make_unique<Entity>(Rectangle{60.0, 60.0, 76.0, 76.0}, 100, 20, 200.0, map));
	while (!WindowShouldClose()) {	
		delta = GetFrameTime();	
		timer += delta;
		float spawn_time = 3;
		if (timer >= spawn_time) {
	entities.push_back(std::make_unique<Enemy>(Rectangle{12.0, 12.0, 76.0, 76.0}, 100, 20, 200.0, map));
		timer -= spawn_time;
		}

		for (auto &e: entities) {
			e->update(delta, entities);
		}

		entities.erase(
            std::remove_if(entities.begin(), entities.end(),
                [](const std::unique_ptr<Entity>& e) {
                    return (e->get_hp() <= 0) ? 1 : 0;
                }),
            entities.end()
        );

		BeginDrawing();
		ClearBackground(WHITE);
		

		for (auto &e: entities) {
			e->render();
		}
		
		DrawText(std::to_string(GetTime()).c_str(), 12, 12, 24, BLACK);

		EndDrawing();
	}

	CloseWindow();
}
