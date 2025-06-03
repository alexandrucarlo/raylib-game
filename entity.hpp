#include <iostream>
#include <string>
#include <optional>
#include <raylib.h>
#define W_WIDTH 800
#define W_HEIGHT 600
#pragma once

class Entity {
	protected:
		Rectangle model;
		int hp, atk;
		float speed;
		const std::shared_ptr<Rectangle> map;
		virtual void move(float x, float y, const std::list<std::unique_ptr<Entity>>& entities);
		std::optional<Rectangle> collision(Entity& other);
		Entity(Rectangle start_pos, int start_hp, int start_atk, float start_speed, const std::shared_ptr<Rectangle> m) : model{start_pos}, hp{start_hp}, atk{start_atk}, speed{start_speed}, map{m} {
			std::cout << "miau\n";
		}
	public:
		Rectangle& getBounds() {
			return model;
		}
		virtual void render() = 0;
		virtual void update(float& delta, std::list<std::unique_ptr<Entity>>& entities) = 0;

		virtual ~Entity() {}

		
};

inline void Entity::move(float x, float y, const std::list<std::unique_ptr<Entity>>& entities) {
	model.x += x * speed;
	model.y += y * speed;

	// in bounds
	if (model.x < 0) model.x = 0;
	if (model.x + model.width > map->width) model.x = map->width - model.width;
	if (model.y < 0) model.y = 0;
	if (model.y + model.height > map->height) model.y = map->height - model.height;

	// collision
	for (auto& e : entities) {
		auto collision_rect = collision(*e);
		if (collision_rect) {
			//std::cout << "COLLISION\n";

		}
	}
}

inline std::optional<Rectangle> Entity::collision(Entity& other) {
	if (&other == this) return std::nullopt; // cannot collide with self

	Rectangle& other_model = other.getBounds();
	if (CheckCollisionRecs(model, other_model)) return GetCollisionRec(model, other_model);

	return std::nullopt;
}
