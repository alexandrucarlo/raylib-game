#include "entity.hpp"
#include "player.hpp"
#pragma once

template<typename RenderFunc>
class Enemy : public Entity {
private:
	// lambda functions for the win
    RenderFunc render_func;
    void move(float x, float y, const std::list<std::unique_ptr<Entity>>& entities) override;

public:
    Enemy(Rectangle start_pos, int start_hp, int start_atk, float start_speed, 
          const std::shared_ptr<Rectangle> m, RenderFunc rf) 
        : Entity{start_pos, start_hp, start_atk, start_speed, m}, render_func(rf) {
    }

    void render() override {
        render_func(model);
    }

    void update(float& delta, std::list<std::unique_ptr<Entity>>& entities) override;
};

template<typename RenderFunc>
inline void Enemy<RenderFunc>::move(float x, float y, const std::list<std::unique_ptr<Entity>>& entities) {
    model.x += x * speed;
    model.y += y * speed;
}

template<typename RenderFunc>
inline void Enemy<RenderFunc>::update(float& delta, std::list<std::unique_ptr<Entity>>& entities) {
    auto player_itr = std::find_if(entities.begin(), entities.end(), [](const auto& e) {
        return dynamic_cast<Player*>(e.get()) != nullptr;
    });
    
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
// "easier" adding in game loop
template<typename RenderFunc>
auto make_enemy(Rectangle pos, int hp, int atk, float speed, 
                std::shared_ptr<Rectangle> map, RenderFunc render_func) {
    return std::make_unique<Enemy<RenderFunc>>(pos, hp, atk, speed, map, render_func);
}

