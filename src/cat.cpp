#include "cat.hpp"
#include "food.hpp"
#include "weapon.hpp"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

namespace catEscape{

		Cat::Cat(const std::string& name, const int& strength, const int& life) {
			_name = name;
			_strength = strength;
			_life = life;
		}

		Cat::~Cat(){
			std::cout<<"~Cat()"<<std::endl;
		}

		std::string Cat::str() const {
			std::string return_str = "Cat. Strength: " + std::to_string(_strength) + " Life: " + std::to_string(_life);
			return return_str;
		}
		std::string Cat::type() const {
			return "Cat";
		}

		std::pair<bool, std::string> Cat::fight(std::shared_ptr<Actor> other){
			int extra_strength = 0;
			if(_weapon!=0){
				//dynamic cast, huvudklassen har inte damage
				Weapon* w = dynamic_cast<Weapon*>(_weapon.get());
				extra_strength = w->damage();
			}
			int your_strike = rand() % (_strength + extra_strength);
			int other_strike = rand() % other->strength();
			(your_strike>=other_strike) ? other->damage(your_strike/2) : damage(other_strike/2);

			std::pair<bool, std::string> ret = (your_strike>=other_strike) ? 
				std::make_pair<bool, std::string>(true, "You won!") : std::make_pair<bool, std::string>(false, "You lose!");
			return ret;
	}
		std::pair<bool, std::string> Cat::pick_up(std::shared_ptr<Object> o){
			//if food - eat it
			if(o->type().compare("Food") == 0){
				//för att komma åt nutrition som INTE finns i allmänna objektklassen.
				Food* f = dynamic_cast<Food*>(o.get());
				_life+=f->nutrition();
				std::string s = "You gained " + std::to_string(f->nutrition()) + " in nutrition!";
				return std::make_pair(true, s);
			} else {
				bool b = _objects->push_back(o);
				if(o->type() == "Weapon")_weapon = o;
				if(b) return std::make_pair(true, "Picked up object.");
				//annars- det gick inte att plocka upp objektet:
				return std::make_pair(false, "Bag is full");
			}
		}
		std::pair<bool, std::string> Cat::drop(int index){
		//ta bort weapon-referens:
			if (_objects->objects()[index] == _weapon)
			{
				_weapon = 0;
				//TODO select a new weapon. 
			}
			std::shared_ptr<Environment> tmp = _location.lock();
		tmp->drop(_objects->objects()[index]);

		//ta bort tom pekare ur vektorn: 
		_objects->erase(_objects->objects()[index]);
		return std::make_pair(true, "Dropped object.");
	}
}