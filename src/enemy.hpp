#ifndef ENEMY_H
#define ENEMY_H
#include "environment.hpp"
#include "actor.hpp"
#include <string>
#include <vector>
#include <memory>

namespace catEscape{
	//class Environment;
	class Enemy : public Actor {
	public:
		Enemy(const std::string&, const int&, const int&);
		virtual ~Enemy();
		virtual std::string type() const {return "Enemy";}
		virtual std::string str() const;
		virtual bool damage(const int&);
	};
}
#endif