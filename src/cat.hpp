#ifndef CAT_H
#define CAT_H
#include "environment.hpp"
#include "object.hpp"
#include "actor.hpp"
#include <string>
#include <vector>
#include <memory>

namespace catEscape{
	//class Environment;
	class Cat : public Actor {
	public:
		Cat(const std::string& name, const int& strength, const int& life);
		virtual ~Cat();
		virtual std::string type() const;
		virtual std::string str() const;
		virtual std::pair<bool, std::string> pick_up(std::shared_ptr<Object>) override;
		virtual std::pair<bool, std::string> drop(int index) override;
		virtual std::pair<bool, std::string> fight(std::shared_ptr<Actor> other) override;
		const std::shared_ptr<Object>& weapon() const {return _weapon;}
	private:
		std::shared_ptr<Object> _weapon = 0;
	};

}
#endif