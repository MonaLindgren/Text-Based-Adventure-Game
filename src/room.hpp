#ifndef ROOM_H
#define ROOM_H
#include "environment.hpp"
#include "object.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <vector>

namespace catEscape{
	class Room : public Environment{
	public:
		Room(const std::string&, const std::string&, std::shared_ptr<Object> = 0);
		virtual ~Room();
		virtual std::string description() const;
		virtual bool enter(std::shared_ptr<Actor>);
	protected:
		std::shared_ptr<Object> _key;
	};
}
#endif