#pragma once

#include "Human.h"
#include <TimEng/InputManager.h>
#include <TimEng/Camera2D.h>
#include "Bullet.h"

class Gun;

class Player : public Human
{
public:
	Player();
	~Player();

	void init(float speed, glm::vec2 pos, TimEng::InputManager* inputManager, TimEng::Camera2D* camera, std::vector<Bullet>* bullets);

	void addGun(Gun* gun);

	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies,
		float deltaTime);

private:
	TimEng::InputManager* _inputManager;

	std::vector<Gun*> _guns;
	int _currentGunIndex;

	TimEng::Camera2D* _camera;
	std::vector<Bullet>* _bullets;
};

