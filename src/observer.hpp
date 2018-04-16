#ifndef OBSERVER_H
#define OBSERVER_H
#include "actor.hpp"
#include <memory>

namespace catEscape{
	class Observer{
		public:
		virtual ~Observer();
		virtual bool game_over() const = 0;
		virtual bool win() const = 0;
		virtual bool alive(std::shared_ptr<Actor>) const = 0;
		virtual std::shared_ptr<Actor> get_main_actor() const = 0;
	};
}
#endif