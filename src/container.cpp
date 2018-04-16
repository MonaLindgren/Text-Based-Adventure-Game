#include "container.hpp"
#include <iostream>
#include <vector>
#include <memory>

namespace catEscape{
 
	Container::Container(const std::string& name, 
						const int& weight, 
						const int& hold_weight) : Object(name, weight) {
		_hold_weight = hold_weight;
	}

	Container::~Container(){
		std::cout<<"~Container()"<<std::endl;
	}
	
	bool Container::push_back(std::shared_ptr<Object> o){
	 	if (this->weight() + o->weight() > _hold_weight)
	 	{
	 		return false;
	 	}
	 	_members.push_back(std::move(o));
	 	return true;
	}
	bool Container::erase(std::shared_ptr<Object> o){
		for (auto it = _members.begin(); it != _members.end(); )
		{
			if(*it==o){
				_members.erase(it);
				return true;
			}else{
				++it;
			}
		}
		return false;
	}
	int Container::weight() const {
		int weight = _weight;
		for (std::size_t i = 0; i < _members.size(); ++i)
		{
			weight+=_members[i]->weight();
		}
		return weight;
	}

	std::string Container::str() const {
		return "Container";
	}

	std::size_t Container::size() const{
		return _members.size();
	}

	std::vector<std::shared_ptr<Object>> Container::objects() const{
		return _members;
	}
}
