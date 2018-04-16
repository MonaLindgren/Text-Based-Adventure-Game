#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <iostream>

namespace catEscape{
	class Object{
	public:
		Object(const std::string&, const int&);
		virtual ~Object();
		virtual int weight() const {return _weight;}
		virtual std::string str() const;
		virtual std::string name() const {return _name;}
		virtual std::string type() const {return "Object";}
	protected:
		int _weight;
		std::string _name;
	};
}
#endif