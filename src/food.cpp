#include "food.hpp"
#include <iostream>
#include <memory>

namespace catEscape{

	//anropa med defaultargument för Food. 
	Food::Food(const std::string& name, const int& weight, const int& nutrition) : Object(name, weight) {
		_nutrition = nutrition;
	}

	Food::~Food(){
		std::cout<<"~Food()"<<std::endl;
	}

	std::string Food::str() const {
		std::string return_string = "Food: " + _name + 
		", nutrition: " + std::to_string(_nutrition) + 
		", weight: " + std::to_string(_weight);
		return return_string;
	}
}