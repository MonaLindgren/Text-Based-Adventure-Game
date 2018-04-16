#include "enemy.hpp"
#include "actor.hpp"
#include "container.hpp"
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <string>
namespace catEscape{
	Enemy::Enemy(const std::string& name, const int& strength, const int& life)
	{
		_name = name;
		_strength = strength;
		_life = life;
	}
	Enemy::~Enemy(){
		std::cout<<"~Enemy()"<<std::endl;
	}

	std::string Enemy::str() const {
		std::string return_str = "Enemy. Strength: " + std::to_string(_strength) + " Life: " + std::to_string(_life);
			return return_str;
	}
	bool Enemy::damage(const int& i){
		_life-=i;
		if (_strength>1)
		{
			_strength-=1;
		}
		return true;
	}

}