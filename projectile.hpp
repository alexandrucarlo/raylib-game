#include "entity.hpp"

class Projectile: public Entity {
	private:
		const Vector2 direction;
		void move(float x, float y, const std::list<std::unique_ptr<Entity>>& entities) override;
	public:
		Projectile(Rectangle start_pos, int start_hp, int start_atk, float start_speed, const std::shared_ptr<Rectangle> m, const Vector2 d) : Entity{start_pos, start_hp, start_atk, start_speed, m}, direction{d} {
			//std::cout << "miau proiectil\n";
		}
		~Projectile() {std::cout << "arrivederci\n";}
		void render() override {DrawRectangleRec(model, YELLOW);}
		void update(float& delta, std::list<std::unique_ptr<Entity>>& entities) override;
};

inline void Projectile::move(float x, float y, const std::list<std::unique_ptr<Entity>>& entities) {
	model.x += x * speed;
	model.y += y * speed;

	// no need to check in bounds cuz we want to delete it when we get out of the map
}
  inline void Projectile::update(float& delta, std::list<std::unique_ptr<Entity>>& entities) {
    if (CheckCollisionRecs(model, *map)) {      
      move(direction.x*delta, direction.y*delta, entities);

	  // collision
	  for (auto& e : entities) {
		auto collision_rect = collision(*e);
		if (collision_rect) {
			//std::cout << "COLLISION\n";
			/*if (dynamic_cast<Enemy*>(e.get()) != nullptr) {
				//std::cout << "oof\n";
				hp--;
			}
			hp = 0;*/
			}
		}	
	}
	else hp = 0;
  }

