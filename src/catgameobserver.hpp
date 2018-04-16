#ifndef CATGAMEOBSERVER_H
#define CATGAMEOBSERVER_H
#include <memory>
#include "observer.hpp"
#include "actor.hpp"
#include "environment.hpp"

namespace catEscape{
class CatGameObserver : public Observer{
	public:
	CatGameObserver(std::shared_ptr<Actor>, std::shared_ptr<Environment>);
	virtual ~CatGameObserver();
	virtual bool game_over() const;
	virtual bool win() const;
	virtual bool alive(std::shared_ptr<Actor>) const;
	virtual std::shared_ptr<Actor> get_main_actor() const override;
	private:
	std::weak_ptr<Actor> _main_actor;
	std::shared_ptr<Environment> _exit;
};
}

#endif