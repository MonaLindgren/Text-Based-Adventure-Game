#ifndef FOOD_H
#define FOOD_H

#include "object.hpp"
#include <string>
#include <vector>
#include <memory>

namespace catEscape{
	class Food : public Object {
	public:
		Food(const std::string&, const int&, const int&);
		virtual ~Food();
		virtual int nutrition() const {return _nutrition;}
		virtual std::string str() const;
		virtual std::string type() const {return "Food";}
	
	private:
		int _nutrition;
	};
}
#endif