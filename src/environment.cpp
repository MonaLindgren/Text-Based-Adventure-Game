#include "environment.hpp"
#include <iostream>
#include <utility>
#include <stdexcept>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

//Objekt/saker växlar mellan environments och aktörers ägo. 
//fungerar som en nod med next och back-pekare
//lika med-operatorn kopierar inte ihopkopplingen, bara rummets egenskaper, tex objekt, namn, beskrivning. 
namespace catEscape{
	Environment::Environment(){
		std::vector<int> tmp = {-1, 0};
		_dir_to_str.insert( std::pair<std::vector<int>, std::string>(tmp, "west") );
		_str_to_dir.insert( std::pair<std::string, std::vector<int>>("west", tmp) );
		
		tmp = {0,1};
		_dir_to_str.insert( std::pair<std::vector<int>, std::string>(tmp, "north") );
		_str_to_dir.insert( std::pair<std::string, std::vector<int>>("north", tmp) );

		tmp = {1,0};
		_dir_to_str.insert( std::pair<std::vector<int>, std::string>(tmp, "east") );
		_str_to_dir.insert( std::pair<std::string, std::vector<int>>("east", tmp) );

		tmp = {0,-1};
		_dir_to_str.insert( std::pair<std::vector<int>, std::string>(tmp, "south") );
		_str_to_dir.insert( std::pair<std::string, std::vector<int>>("south", tmp) );
	}

	Environment::~Environment(){
		std::cout<<"~Environment()"<<std::endl;
	}
	
	bool Environment::enter(std::shared_ptr<Actor> a){
	 	_actors.push_back(a);
	 	return true;
	}
	
	bool Environment::leave(std::shared_ptr<Actor> a){
		for (auto it = _actors.begin(); it != _actors.end(); ++it)
		{
			std::shared_ptr<Actor> tmp = (*it).lock();
			if (tmp==a)
			{
				_actors.erase(it);
				return true;
			}
		}
		return false;
	}

	std::vector<std::shared_ptr<Actor>> Environment::actors() const {
		std::vector<std::shared_ptr<Actor>> ret;
		for(size_t i = 0; i<_actors.size(); ++i){
			ret.push_back(_actors[i].lock());
		}
		return ret;
	}

	bool Environment::drop(std::shared_ptr<Object> o){ //by value- funktionen måste ta över unique ptr med move. 
	 	_objects.push_back(o);
	 	return true;
	}
	
	std::pair<bool, std::string> Environment::take(std::shared_ptr<Object> o) {
		for(auto it= _objects.begin(); it!=_objects.end(); ++it){
			if(*it==o){
				_objects.erase(it);
				return std::make_pair(true, "Actor took object");
			}
		}
	 	return std::make_pair(false, "Object doesn't exist.");
	}

	bool Environment::connect(std::shared_ptr<Environment> other, const std::pair<int, int>& dir){
		std::pair<Environment::map_type::iterator,bool> ret;
		ret = _neighbors.insert ( std::pair<std::pair<int, int>, Environment::env_type>(dir, other) );
		return ret.second;
	}
	bool Environment::disconnect(const std::pair<int, int>& dir){
		_neighbors.erase(dir);
		return true;
	} 

	std::string Environment::dir_to_str(std::vector<int> dir){
		std::string ret;
		ret = _dir_to_str.at(dir);
		return ret;
	}

	std::vector<int> Environment::str_to_dir(std::string str){
		std::vector<int> ret;
		ret = _str_to_dir.at(str);
		return ret;
	}

	std::vector<std::shared_ptr<Object>> Environment::objects() const{
		 return _objects;
	}

	int Environment::object_index(const std::string& x){
		for (std::size_t i = 0; i < _objects.size(); ++i)
		{
			if(x.compare(_objects[i]->name())==0){
				return i;
			}
		}
		return -1;
	}

	std::shared_ptr<Environment> Environment::neighbor(const std::vector<int>& dir){
		std::shared_ptr<Environment> et; 
		try{
			std::pair<int, int> tmp_key(dir[0], dir[1]);
			et = _neighbors.at(tmp_key).lock();
		} catch (const std::out_of_range& oor) {
			et = 0;
  		}
  		return et;
	}

	std::vector<std::vector<int>> Environment::directions() const {
		std::vector<std::vector<int>> tmp;
		for (auto it = _neighbors.begin(); it != _neighbors.end(); ++it)
	 	{
	 		std::vector<int> tmp_dir;
	 		tmp_dir.push_back(it->first.first);
	 		tmp_dir.push_back(it->first.second);
	 		tmp.push_back(tmp_dir);
	 		
	 	}
	 	return tmp;
	}
	std::vector<std::vector<int>> Environment::valid_directions() const {
		std::vector<std::vector<int>> ret;
		//std::vector<int> tmp = {-1, 0};
	 	ret.push_back({-1,0});
	 	ret.push_back({0,1});
	 	ret.push_back({1,0});
	 	ret.push_back({0,-1});

	 	return ret;
	}
}