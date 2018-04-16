#ifndef GAME_H
#define GAME_H
#include "environment.hpp"
#include "inputoutput.hpp"
#include "actor.hpp"
#include "catgameobserver.hpp"
#include <memory>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

//Game act as a controller
namespace catEscape{
class Actor;

class Game{
public:
	Game(bool);
	~Game();

	void start();
	std::pair<bool, std::string> stop(std::shared_ptr<Actor>, std::vector<int>); //stops the game
	virtual void doStep();
protected:
	std::vector<std::shared_ptr<Actor>> _actors;
	std::vector<std::shared_ptr<Environment>> _environments;
	std::shared_ptr<Environment> _trap_door_entrance;
	std::shared_ptr<Environment> _trap_door;
	std::pair<int, int> _trap_door_direction;
	std::pair<bool, std::string> go(std::shared_ptr<Actor>, std::vector<int>); //Move an actor in a direction
	std::pair<bool, std::string> take(std::shared_ptr<Actor>, std::vector<int>); //Actor takes an object
	std::pair<bool, std::string> drop(std::shared_ptr<Actor>, std::vector<int>);
	std::pair<bool, std::string> fight(std::shared_ptr<Actor>, std::vector<int>); //Actor fights another actor
	std::pair<bool, std::string> action(std::shared_ptr<Actor>);
	std::pair<bool, std::string> create_food(std::shared_ptr<Actor>, std::vector<int>); //a new food-object is created at random 
	void create_trapdoor();
	void remove_trapdoor();
	void remove_actor(std::shared_ptr<Actor>);
	void check_alive();
	bool _running = false;
	std::shared_ptr<Observer> _observer;
	InputOutput _io;
	std::shared_ptr<Actor> _current_player;
	std::size_t _round = 0;
	bool _debug_mode = false;
};
}
#endif