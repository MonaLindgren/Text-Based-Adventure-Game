#include "object.hpp"
#include "weapon.hpp"
#include <iostream>
#include <memory>

namespace catEscape{

	//anropa med defaultargument för Object. 
	Weapon::Weapon(const std::string& name, const int& weight, const int& damage) : Object(name, weight) {
		_damage = damage;
	}
	Weapon::~Weapon(){
		std::cout<<"~Weapon()"<<std::endl;
	}

	std::string Weapon::str() const {
		std::string return_string = "Weapon: " + _name + 
		", damage: " + std::to_string(_damage) + 
		", weight: " + std::to_string(_weight);
		return return_string;
	}
}