#include "entity.hpp"
#include "player.hpp"
#pragma once
<template typename S>
class Enemy : public Entity {
	private:
		//void attack(std::vector<std::unique_ptr<Entity>>& entities);
		void move(float x, float y, const std::list<std::unique_ptr<Entity>>& entities) override;
	public:
		Enemy(Rectangle start_pos, int start_hp, int start_atk, float start_speed, const std::shared_ptr<Rectangle> m) : Entity{start_pos, start_hp, start_atk, start_speed, m} {
			//std::cout << "un om rau!\n";
		}
		void render() override {DrawRectangleRec(model, RED);}
		void update(float& delta, std::list<std::unique_ptr<Entity>>& entities) override; 
};


inline void Enemy::move(float x, float y, const std::list<std::unique_ptr<Entity>>& entities) {
	model.x += x * speed;
	model.y += y * speed;

	// in bounds - no need

	
}
  inline void Enemy::update(float& delta, std::list<std::unique_ptr<Entity>>& entities) {
	auto player_itr = std::find_if(entities.begin(), entities.end(), [](const auto& e) {
    	return dynamic_cast<Player*>(e.get()) != nullptr;
	}); // this should never fail
	Vector2 direction = Vector2Normalize(Vector2Subtract(player_itr->get()->get_origin(), get_origin()));
      move(direction.x*delta, direction.y*delta, entities);


	// collision
	for (auto& e : entities) {
		auto collision_rect = collision(*e);
		if (collision_rect) {
			if (dynamic_cast<Projectile*>(e.get()) != nullptr) {
				//std::cout << "oof\n";
				hp -= e->get_atk();
			}

		}
	}

  }
