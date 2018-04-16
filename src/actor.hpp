#ifndef ACTOR_H
#define ACTOR_H
#include "object.hpp"
#include "container.hpp"
#include <string>
#include <memory>
#include <vector>

namespace catEscape{
    class Environment;
	class Actor{
	public:
        Actor();
		virtual ~Actor();
    	virtual std::string type() const = 0; //returnerar namnet på arten t. ex trollkarl eller drake. 
    	virtual std::string str() const = 0;
    	virtual std::string name() const;
    	virtual std::pair<bool, std::string> fight(std::shared_ptr<Actor>);
        virtual bool damage(const int&);
        virtual void gain_life(const int& i) {_life+=i;}
        bool set_location(std::shared_ptr<Environment>);
        virtual std::shared_ptr<Environment> location() const;
        //virtual const std::weak_ptr<Environment>& location() const;
        virtual std::pair<bool, std::string> pick_up(std::shared_ptr<Object>); //take an object
        virtual std::pair<bool, std::string> drop(int);
        virtual int object_index(const std::string&);
        std::vector<std::shared_ptr<Object>> objects() const;
        virtual const std::shared_ptr<Container>& bag() const {return _objects;}
        int life() const {return _life;}
        int strength() const {return _strength;}
    protected:
    	//objects ägs av actor eller environment
    	std::shared_ptr<Container> _objects; // är en container
        std::weak_ptr<Environment> _location;
    	std::string _name;
    	int _strength; 
    	int _life;
	};
}
#endif 
