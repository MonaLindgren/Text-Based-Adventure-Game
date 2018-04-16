#include "environment.hpp"
//#include "object.hpp"
#include "actor.hpp"
#include "container.hpp"
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <string>

//Objekt/saker växlar mellan environments och aktörers ägo. 
//fungerar som en nod med next och back-pekare
//lika med-operatorn kopierar inte ihopkopplingen, bara rummets egenskaper, tex objekt, namn, beskrivning. 
namespace catEscape{
	Actor::Actor(){
		srand(time(0));
		//skapa en ryggsäck:
		_objects = std::make_shared<Container>("Bag", 2, 20);
	}
	Actor::~Actor(){
		std::cout<<"~Actor()"<<std::endl;
	}
	
	std::string Actor::name() const {
		return _name;
	}
	
	bool Actor::set_location(std::shared_ptr<Environment> e){
		_location = e;
		return true;
	}

	std::pair<bool, std::string> Actor::fight(std::shared_ptr<Actor> other){
		int your_strike = rand() % _strength;
		int other_strike = rand() % other->strength();
		(your_strike>=other_strike) ? other->damage(your_strike/2) : damage(other_strike/2);

		std::pair<bool, std::string> ret = (your_strike>=other_strike) ? 
				std::make_pair<bool, std::string>(true, "You won!") : std::make_pair<bool, std::string>(false, "You lose!");
		return ret;
	}

	std::shared_ptr<Environment> Actor::location() const {
		auto ret = _location.lock();
		return ret;
	}

	std::pair<bool, std::string> Actor::pick_up(std::shared_ptr<Object> o){
		bool b = _objects->push_back(o);
		if(b) return std::make_pair(true, "Picked up object.");
		//annars- det gick inte att plocka upp objektet:
		return std::make_pair(false, "Bag is full");		
	}
	std::pair<bool, std::string> Actor::drop(int index){
		auto current_location = _location.lock();
		current_location->drop(_objects->objects()[index]);
		//ta bort tom pekare ur vektorn: 
		_objects->erase(_objects->objects()[index]);
		return std::make_pair(true, "Dropped object.");
	}
	std::vector<std::shared_ptr<Object>> Actor::objects() const{
		 return _objects->objects();
	}

	int Actor::object_index(const std::string& x){
		for (std::size_t i = 0; i < _objects->size(); ++i)
		{
			if(x.compare(_objects->objects()[i]->name())==0){
				return i;
			}
		}
		return -1;
	}
	bool Actor::damage(const int& i){
		_life-=i;
		return true;
	}
}