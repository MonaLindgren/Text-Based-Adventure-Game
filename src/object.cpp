#include "object.hpp"

namespace catEscape{
	
	Object::Object(const std::string& name, const int& weight){
		_weight = weight;
		_name = name;
	}
	
	Object::~Object(){
		std::cout<<"~Object()"<<std::endl;
	}

	std::string Object::str() const {
		return "Object" + _name + 
		", weight: " + std::to_string(_weight);
	}
}
