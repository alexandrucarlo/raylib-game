#include <iostream>
#include <string>
#include <optional>
#include <raylib.h>
#include "map.hpp"
#define W_WIDTH 800
#define W_HEIGHT 600
#pragma once

class Entity {
protected:
		Rectangle model;
		int hp, atk;
		float speed;
		const Map& map;
		virtual void move(float x, float y, std::vector<std::unique_ptr<Entity>>& entities);
		std::optional<Rectangle> collision(Entity& other);
	public:
		Rectangle& getBounds() {
			return model;
		}
		virtual void render() {
			DrawRectangleRec(model, BLUE);
		}
		virtual void update(float& delta, std::vector<std::unique_ptr<Entity>>& entities);


		Entity(Rectangle start_pos, int start_hp, int start_atk, float start_speed, const Map& m) : model{start_pos}, hp{start_hp}, atk{start_atk}, speed{start_speed}, map{m} {
			std::cout << "miau\n";
		}
};

inline void Entity::move(float x, float y, std::vector<std::unique_ptr<Entity>>& entities) { 
	model.x += x * speed;
	model.y += y * speed;

	// in bounds
	if (model.x < 0) model.x = 0;
	if (model.x + model.width > map.width) model.x = map.width - model.width;
	if (model.y < 0) model.y = 0;
	if (model.y + model.height > map.height) model.y = map.height - model.height;

	// collision
	for (auto& e : entities) {
		auto collision_rect = collision(*e);
		if (collision_rect) {
			std::cout << "COLLISION\n";
			
		}
	}
}

inline void Entity::update(float& delta, std::vector<std::unique_ptr<Entity>>& entities) {
	/*if (IsKeyDown(KEY_LEFT)) std::cout << ";)\n";
	if (IsKeyDown(KEY_RIGHT)) std::cout << ";)\n";
	if (IsKeyDown(KEY_UP)) std::cout << ";)\n";
	if (IsKeyDown(KEY_DOWN)) std::cout << ";)\n";*/
		// if (IsKeyPressed(KEY_SPACE)) attack();

}

inline std::optional<Rectangle> Entity::collision(Entity& other) {
	if (&other == this) return std::nullopt; // cannot collide with self

	Rectangle& other_model = other.getBounds();
	/*if (model.x > other_model.x && model.x < other_model.x + other_model.width && model.y > other_model.y && model.y < other_model.y + other_model.height) return Rectangle {model.x, model.y, other_model.width + other_model.x - model.x, other_model.height + other_model.y - model.y};*/
	if (CheckCollisionRecs(model, other_model)) return GetCollisionRec(model, other_model);

	return std::nullopt;
}
