#include "entity.hpp"
#pragma once

class Projectile: public Entity {
	public:
		Projectile(Rectangle start_pos, int start_hp, int start_atk, float start_speed, const std::shared_ptr<Rectangle> m) : Entity{start_pos, start_hp, start_atk, start_speed, m} {
			std::cout << "miau proiectil\n";
		}
		void render() override {DrawRectangleRec(model, YELLOW);}
		void update(float& delta, std::list<std::unique_ptr<Entity>>& entities) override;
};

  inline void Projectile::update(float& delta, std::list<std::unique_ptr<Entity>>& entities) {
    if (CheckCollisionRecs(model, *map)) {      
      move(1.0*delta, 0*delta, entities);
    } 
  }
