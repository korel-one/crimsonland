#pragma once

#include <memory>
#include <vector>

class GameObject;
class Enemy;
struct IMG_LOAD;

class EnemyManager {
public:
	explicit EnemyManager(int i_num_enemies);

	//we know that avatar is always in the center of the screen
	void GenerateEnemies(const char* path
		, int win_width, int win_height
		, int target_x, int target_y
		, int target_w, int target_h);

	bool AnyTouchedPlayer() const;

	//not safe to return a raw pointer (TODO:)
	Enemy* IntersectAny(const GameObject& e) const;

	void RenderAll();
	void UpdateAll();

	void Clear();

	void PlayerMoved(int x, int y);

	void RemoveEnemy(const Enemy* p_enemy);

private:
	int num_enemies;
	std::unique_ptr<IMG_LOAD> image_loader;

	using TEnemies = std::vector<std::unique_ptr<Enemy>>;
	TEnemies _enemies;
};