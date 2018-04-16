#include "catgameobserver.hpp"
#include <iostream>

namespace catEscape{
	CatGameObserver::CatGameObserver(std::shared_ptr<Actor> a, 
									std::shared_ptr<Environment> e)
	{
		_main_actor = a;
		_exit = e;
	}
	CatGameObserver::~CatGameObserver(){
		std::cout<<"~CatGameObserver()"<<std::endl;
	}

	bool CatGameObserver::game_over() const{
		return false;
	}
	bool CatGameObserver::win() const{
		std::shared_ptr<Actor> tmp = _main_actor.lock();
		return tmp->location() == _exit;
	}
	bool CatGameObserver::alive(std::shared_ptr<Actor> a) const{
		return a->life()>0;
	}
	std::shared_ptr<Actor> CatGameObserver::get_main_actor() const {
		std::shared_ptr<Actor> tmp = _main_actor.lock();
		return tmp;
	}
}
