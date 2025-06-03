#include "entity.hpp"
#pragma once
class Enemy : public Entity {
	private:
		//void attack(std::vector<std::unique_ptr<Entity>>& entities);
	public:
		Enemy(Rectangle start_pos, int start_hp, int start_atk, float start_speed, const std::shared_ptr<Rectangle> m) : Entity{start_pos, start_hp, start_atk, start_speed, m} {
			std::cout << "miau jucatorule\n";
		}
		void render() override {DrawRectangleRec(model, RED);}
		void update(float& delta, std::list<std::unique_ptr<Entity>>& entities) override; 
};

inline void Enemy::update(float& delta, std::list<std::unique_ptr<Entity>>& entities) {
	//if (IsKeyDown(KEY_LEFT)) move(-1.0*delta, 0, entities);
	//if (IsKeyDown(KEY_RIGHT)) move(1.0*delta, 0*delta, entities);
	//if (IsKeyDown(KEY_UP)) move(0*delta, -1.0*delta, entities);
	//if (IsKeyDown(KEY_DOWN)) move(0*delta, 1.0*delta, entities);
	//if (IsKeyPressed(KEY_SPACE)) attack(entities);

} 

/*inline void attack(std::vector<std::unique_ptr<Entity>>& entities) {	
	float size = 30.0;
	entities.push_back(std::make_unique<Projectile>(Rectangle {model.x, model.y, size, size}, 100, 20, 200.0, map));
}*/
