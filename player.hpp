#include "entity.hpp"
#include "projectile.hpp"
#pragma once
class Player : public Entity {
	private:
		void attack(std::list<std::unique_ptr<Entity>>& entities);
		void move(float x, float y, const std::list<std::unique_ptr<Entity>>& entities) override;
	public:
		Player(Rectangle start_pos, int start_hp, int start_atk, float start_speed, const std::shared_ptr<Rectangle> m) : Entity{start_pos, start_hp, start_atk, start_speed, m} {
			std::cout << "miau jucatorule\n";
		}
		void render() override {DrawRectangleRec(model, BLUE);}
		void update(float& delta, std::list<std::unique_ptr<Entity>>& entities) override;
};

inline void Player::move(float x, float y, const std::list<std::unique_ptr<Entity>>& entities) {
	model.x += x * speed;
	model.y += y * speed;

	// in bounds
	if (model.x < 0) model.x = 0;
	if (model.x + model.width > map->width) model.x = map->width - model.width;
	if (model.y < 0) model.y = 0;
	if (model.y + model.height > map->height) model.y = map->height - model.height;

	
}
inline void Player::update(float& delta, std::list<std::unique_ptr<Entity>>& entities) {
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) move(-1.0*delta, 0, entities);
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) move(1.0*delta, 0*delta, entities);
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) move(0*delta, -1.0*delta, entities);
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) move(0*delta, 1.0*delta, entities);
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) attack(entities);
	// collision
	for (auto& e : entities) {
		auto collision_rect = collision(*e);
		if (collision_rect) {
			//std::cout << "COLLISION\n";

		}
	}
}

inline void Player::attack(std::list<std::unique_ptr<Entity>>& entities) {
	float size = 30.0;
	Vector2 direction = Vector2Normalize(Vector2Subtract(GetMousePosition(), get_origin()));
	entities.push_back(std::make_unique<Projectile>(Rectangle {model.x + (model.width - size)/2, model.y + (model.height - size)/2, size, size}, 1, atk, 400.0, map, direction));
}

