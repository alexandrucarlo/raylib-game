#include <raylib.h>
#include <iostream>
#include <string>
#define W_WIDTH 800
#define W_HEIGHT 600
class Entity {
	public:
		Vector2 origin;
		Rectangle model;
		void render() {
			DrawRectangleRec(model, BLUE);
		}
		
		void move(float x, float y) {
			model.x = model.x + x;
			model.y += y;
			
			if (model.x < 0) model.x = 0;
			if (model.x + model.width > W_WIDTH) model.x = W_WIDTH - model.width;
			if (model.y < 0) model.y = 0;
			if (model.y + model.height > W_HEIGHT) model.y = W_HEIGHT - model.height;
		}


	Entity(Vector2 start_pos, Rectangle rect) : origin{start_pos}, model{rect} {
		std::cout << "mmm new entity\n";
	}
};


int main() {
	InitWindow(W_WIDTH, W_HEIGHT, "hello");
	std::string fps;	
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
	Entity eu({3.0, 5.0}, {12.0, 12.0, 76.0, 76.0});

	while (!WindowShouldClose()) {
		
		if (IsKeyDown(KEY_LEFT)) eu.move(-2.0, 0);
		if (IsKeyDown(KEY_RIGHT)) eu.move(2.0, 0);
		if (IsKeyDown(KEY_UP)) eu.move(0, -2.0);
		if (IsKeyDown(KEY_DOWN)) eu.move(0, 2.0);

		BeginDrawing();
		fps = "FPS: " + std::to_string(GetFPS());
		SetWindowTitle(fps.c_str());
		ClearBackground(WHITE);
		eu.render();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
