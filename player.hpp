#include "entity.hpp"
#include "projectile.hpp"
#pragma once
class Player : public Entity {
	private:
		void attack(std::list<std::unique_ptr<Entity>>& entities);
	public:
		Player(Rectangle start_pos, int start_hp, int start_atk, float start_speed, const std::shared_ptr<Rectangle> m) : Entity{start_pos, start_hp, start_atk, start_speed, m} {
			std::cout << "miau jucatorule\n";
		}
		void render() override {DrawRectangleRec(model, RED);}
		void update(float& delta, std::list<std::unique_ptr<Entity>>& entities) override;
};

inline void Player::update(float& delta, std::list<std::unique_ptr<Entity>>& entities) {
	if (IsKeyDown(KEY_LEFT)) move(-1.0*delta, 0, entities);
	if (IsKeyDown(KEY_RIGHT)) move(1.0*delta, 0*delta, entities);
	if (IsKeyDown(KEY_UP)) move(0*delta, -1.0*delta, entities);
	if (IsKeyDown(KEY_DOWN)) move(0*delta, 1.0*delta, entities);
	if (IsKeyPressed(KEY_SPACE)) attack(entities);
}

inline void Player::attack(std::list<std::unique_ptr<Entity>>& entities) {
	float size = 30.0;
	try {
	entities.push_back(std::make_unique<Projectile>(Rectangle {model.x, model.y, size, size}, 0, atk, 400.0, map));
	}
	catch (...) {
		std::cerr << "cplm?";
	}
}
