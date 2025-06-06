#include <iostream>
#include <string>
#include <optional>
#include <algorithm>
#include <raylib.h>
#include <raymath.h>
#define W_WIDTH 800
#define W_HEIGHT 600
#pragma once
class Entity {
	protected:

		Rectangle model;
		int hp, atk;
		float speed;
		const std::shared_ptr<Rectangle> map;
		virtual void move(float x, float y, const std::list<std::unique_ptr<Entity>>& entities) = 0;
		std::optional<Rectangle> collision(Entity& other);
		Entity(Rectangle start_pos, int start_hp, int start_atk, float start_speed, const std::shared_ptr<Rectangle> m) : model{start_pos}, hp{start_hp}, atk{start_atk}, speed{start_speed}, map{m} {
		}
	public:
		Rectangle& get_bounds() {
			return model;
		}
		Vector2 get_origin() {
			return Vector2{model.x + model.width/2, model.y + model.height/2};
		}
		const int& get_hp() {
			return hp;
		}
		const int& get_atk() {
			return atk;
		}
		virtual void render() = 0;
		virtual void update(float& delta, std::list<std::unique_ptr<Entity>>& entities) = 0;
		virtual ~Entity() {}

		
};

inline std::optional<Rectangle> Entity::collision(Entity& other) {
	if (&other == this) return std::nullopt; // cannot collide with self

	Rectangle& other_model = other.get_bounds();
	if (CheckCollisionRecs(model, other_model)) return GetCollisionRec(model, other_model);

	return std::nullopt;
}





