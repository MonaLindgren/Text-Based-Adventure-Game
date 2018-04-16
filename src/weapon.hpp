#ifndef WEAPON_H
#define WEAPON_H
#include "object.hpp"
#include <string>
#include <iostream>

namespace catEscape{
	class Weapon : public Object{
	public:
		Weapon(const std::string&, const int&, const int&);
		virtual ~Weapon();
		virtual std::string str() const;
		virtual std::string type() const {return "Weapon";}
		virtual int damage() const { return _damage;}
	protected:
		int _damage;
	};
}
#endif