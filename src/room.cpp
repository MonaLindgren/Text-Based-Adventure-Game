#include "room.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

namespace catEscape{
	Room::Room(const std::string& name, const std::string& description, std::shared_ptr<Object> key) {
		_name = name;
		_description = description;
		_key = key;
	}
	
	Room::~Room(){
		std::cout<<"~Room()"<<std::endl;
	}
	
	std::string Room::description() const {
		std::string ret =  _name + ": " + "\n" + _description + "\nContains objects: \n";
		for(auto i : _objects){
			ret = ret + i->name() + ": " + i->str() + "\n";
		}
		ret = ret + "\nActors in this room:\n";
		for(std::size_t i = 0; i< _actors.size(); ++i){
			ret = ret + _actors[i].lock()->name() + ": " + _actors[i].lock()->str() + "\n";
		}
		ret = ret + "\nThis room has doors that leads to :\n";
		for(auto i : directions()){
			int x = i[0];
			int y = i[1];
			std::pair<int, int> p(x,y);
			ret = ret + _dir_to_str.at(i) + ": " + _neighbors.at(p).lock()->name() + "\n";
		}
		return ret;
	}
	bool Room::enter(std::shared_ptr<Actor> a){
	 	//if room requires no key:
	 	if (_key==0)
	 	{
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