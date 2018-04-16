#include "kitchen.hpp"
#include "object.hpp"
#include "food.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

namespace catEscape{
	Kitchen::Kitchen(const std::string& name, const std::string& description) : Room(_name, _description) {
		_name = name;
		_description = description;
		std::shared_ptr<Object> f1 = std::make_shared<Food>("Meat", 4, 5);
		this->drop(f1);
		std::shared_ptr<Object> f2 = std::make_shared<Food>("Fish", 4, 4);
		this->drop(f2);
		std::shared_ptr<Object> f3 = std::make_shared<Food>("Egg", 2, 2);
		this->drop(f3);
	}
	
	Kitchen::~Kitchen(){
		std::cout<<"~Kitchen()"<<std::endl;
	}
	
	//std::string Kitchen::description() const {
	//	return  _name + ": " + "\n" + _description + "\n";
		 //+ "nr of objects: " + std::to_string(_objects.size());
	//}
	bool Kitchen::enter(std::shared_ptr<Actor> a){

	 	//if Kitchen requires no key:
	 	if (_key==0)
	 	{
	 		a->gain_life(5);
	 		_actors.push_back(a);
	 		return true;
	 	}
	 	//check if actor has the key:
	 	for (auto i : a->objects())
	 	{
	 		if(i==_key){
	 			_actors.push_back(a);
	 			return true;
	 		}
	 	}
	 	return false;
	}
}