#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "object.hpp"
#include "actor.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <map>

namespace catEscape{
	class Environment{
		typedef std::weak_ptr<Environment> env_type;
		typedef std::vector<int> key_type;
		typedef std::map<std::pair<int, int>, env_type> map_type;
	public:
		Environment();
		virtual ~Environment();
		virtual std::string description() const = 0;
		virtual std::string name() const {return _name;}
		virtual bool enter(std::shared_ptr<Actor>); // aktör kommer till platsen
		bool leave(std::shared_ptr<Actor>);
		std::vector<std::shared_ptr<Actor>> actors() const;
		bool drop(std::shared_ptr<Object>); // någon lägger ner ett föremål på platsen
		std::pair<bool, std::string> take(std::shared_ptr<Object>); // överlämna ägandeskap till actor
		bool connect(std::shared_ptr<Environment>, const std::pair<int, int>&); //connects environment with other environment. 
		bool disconnect(const std::pair<int, int>&); //disconnects a neighbor in a connection;
		std::vector<std::shared_ptr<Object>> objects() const;
		int object_index(const std::string&); //TODO
		std::shared_ptr<Environment> neighbor(const std::vector<int>&);
		virtual std::vector<std::vector<int>> directions() const;
		virtual std::vector<std::vector<int>> valid_directions() const;
		
		std::string dir_to_str(std::vector<int>);
		std::vector<int> str_to_dir(std::string);
	protected:
		std::map<std::vector<int>, std::string> _dir_to_str;
		std::map<std::string, std::vector<int>> _str_to_dir;
		
		std::string _name = "";
		std::string _description = "";
		map_type _neighbors;
		std::vector<std::shared_ptr<Object>> _objects;
		std::vector<std::weak_ptr<Actor>> _actors;
	};
}
#endif