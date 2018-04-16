#ifndef CONTAINER_H
#define CONTAINER_H

#include "object.hpp"
#include <string>
#include <vector>
#include <memory>

namespace catEscape{
	class Container : public Object {
	public:
		Container(const std::string& name, const int& weight, const int& hold_weight);
		virtual ~Container();
		int hold_weight() const {return _hold_weight;}
		virtual int weight() const;
		virtual std::string str() const;
		bool push_back(std::shared_ptr<Object>);
		bool erase(std::shared_ptr<Object>);
		std::vector<std::shared_ptr<Object>> objects() const;
		std::size_t size() const;
	
	private:
		int _hold_weight;
		std::vector<std::shared_ptr<Object>> _members;
	};
}
#endif