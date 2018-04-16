#ifndef KITCHEN_H
#define KITCHEN_H
#include "room.hpp"
#include "object.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <vector>

namespace catEscape{
	class Kitchen : public Room{
	public:
		Kitchen(const std::string&, const std::string&);
		virtual ~Kitchen();
		//virtual std::string description() const;
		virtual bool enter(std::shared_ptr<Actor>);
	};
}
#endif