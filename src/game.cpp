#include "game.hpp"
#include "cat.hpp"
#include "room.hpp"
#include "kitchen.hpp"
#include "object.hpp"
#include "food.hpp"
#include "container.hpp"
#include "weapon.hpp"
#include "enemy.hpp"

#include <iostream>
#include <utility>
#include <string>
#include <cmath>
#include <algorithm>

#include <functional>
//next to do
//konverteringen till indexvektor skulle också kunna göras till en map
//alla aktörer kan inte plocka upp items utan väska

namespace catEscape{

	Game::Game(bool debug_mode){
		_debug_mode = debug_mode;
		_io.set_welcome("\n\n----------------------------------\nWelcome to Cat Escape!\nYou are a cat trapped in an apartment with pesky, lovesick humans...\nPretend to be cuddly and the humans give you food,\nbut when they least expects it - kill them!\nYour goal is to escape as soon as possible! \nYou will find the key to the balcony somewhere in this apartment...\n\nCommands:\nMove between the rooms by typing \n'go west' or 'go north' for example. \nPick up objects by typing 'take' followed by the name of the object.\nFight another actor by typing 'fight' followed by the name of the actor.\n\nGo go go!!!----------------------------");
		_io.set_win("Congratulations, you have escaped this horrible place!");
		_io.set_dies("dies and is no longer in the game.");
		_io.set_game_over("Game over!");
		//create _actors:
		std::shared_ptr<Actor> a1 = std::make_shared<Cat>("Calypso", 9, 9);
		std::shared_ptr<Actor> a2 = std::make_shared<Cat>("Styx", 9, 9);
		std::shared_ptr<Actor> a3 = std::make_shared<Enemy>("Human", 9, 9);
		_actors.push_back(a1);
		_actors.push_back(a2);
		_actors.push_back(a3);

		std::shared_ptr<Environment> A = std::make_shared<Room>("Living room", "A dangerous place for a cat...");
		std::shared_ptr<Object> o1 = std::make_shared<Object>("Balcony key", 4);
		
		std::shared_ptr<Environment> B = std::make_shared<Room>("Balcony", "Now you can finally escape from here!", o1);
		std::shared_ptr<Environment> C = std::make_shared<Room>("Bathroom", "Be careful you do not get wet!");
		//pusha på vektorn så inte environments frigörs. Vektorn används inte till något. 
		_environments.push_back(A);
		_environments.push_back(B);
		_environments.push_back(C);
		
		A->connect(B, std::pair<int, int>(0, 1) );

		B->connect(A, std::pair<int, int>(0, -1) );

		A->connect(B, std::pair<int, int>(1, 0) );

		A->connect(C, std::pair<int, int>(-1, 0) );
		C->connect(A, std::pair<int, int>(1, 0) );

		A->enter(a1);
		A ->enter(a2);
		A->enter(a3);
		a1->set_location(A);
		a2->set_location(A);
		a3->set_location(A);

		//drop food in room A:
		std::shared_ptr<Object> f1 = std::make_shared<Food>("Cat treats", 4, 5);
		A->drop(f1);
		std::shared_ptr<Object> f2 = std::make_shared<Food>("Pellets", 4, 5);
		A->drop(f2);
		
		std::shared_ptr<Object> o2 = std::make_shared<Weapon>("Sword", 5, 10);
		C->drop(o2);
		std::shared_ptr<Object> o3 = std::make_shared<Weapon>("Lawnmover", 10, 15);
		C->drop(o3);
		C->drop(o1);

		//set observer:
		std::shared_ptr<Observer> o(new CatGameObserver(a1, B));
        _observer = std::move(o);
	}

	Game::~Game(){
		std::cout<<"~Game()"<<std::endl;
	}
	
	void Game::start(){
		
		_running = true;
		_io.welcome();

		while(_running){
			++_round;
			if(_round == 1){
				create_trapdoor();
			}
			if(_round == 2){
				remove_trapdoor();
			}
			this->doStep();
		}
	}
	
	std::pair<bool, std::string> Game::stop(std::shared_ptr<Actor> actor, std::vector<int>){
		_running = false;
		_io.quit(actor);
		return std::make_pair<bool, std::string>(true, "");
	}
	void Game::create_trapdoor(){
		
		//create new room:
		std::shared_ptr<Environment> trap_door = std::make_shared<Kitchen>("Kitchen", "Eat as much as you can!");
		
		//find suitable place for trap door:
		bool done = false;
		for(auto i : _environments){
			if(done)break;
			//find available directions:
			std::vector<std::vector<int>> valid_dirs = i->valid_directions();
			std::vector<std::vector<int>> used_dirs = i->directions();
			if (valid_dirs.size()>used_dirs.size())
			{
				for(auto dir : valid_dirs){
					if (std::find(used_dirs.begin(), 
								used_dirs.end(), dir) == used_dirs.end()){
						//Found valid direction:
						//Connect this room with the new trap door:
						i->connect(trap_door, std::pair<int, int>(dir[0], dir[1]));
						trap_door->connect(i, std::pair<int, int>(dir[0], dir[1]));//i samma riktning men whatever
						_trap_door_entrance = i;
						_trap_door_direction = std::pair<int, int>(dir[0], dir[1]);
						_trap_door = trap_door;
						done = true;
						break;
					}
				}
			}
		}
		_environments.push_back(trap_door);//save new room to "main vector" 
		std::string s = "#############################################\n\nThe kitchen is open! GO GO GO!\nIt is located somewhere near the ";
		s = s + _trap_door_entrance->name();
		s = s + "\n\n\n####################################\n";
		_io.print(s);
	
	}
	void Game::remove_trapdoor(){
		//Kill actors in trap room:
		auto actors = _trap_door->actors();
		for(auto i : actors){
			remove_actor(i);
		}
		check_alive();
		//remove trap door room reference from its connected room:
		_trap_door_entrance->disconnect(_trap_door_direction);
		for(auto it = _environments.begin(); it!=_environments.end(); ){
			if((*it)==_trap_door){
				_environments.erase(it);//remove trap door room from the game
				break;
			} else {
				++it;
			}
		}
		std::string s = "#############################################\n\nThe door to the kitchen is closed! \nThe ones that are trapped inside are in big trouble!";
		s = s + "\n\n\n####################################\n";
		_io.print(s);
	}

	void Game::remove_actor(std::shared_ptr<Actor> a){
		_io.dies(a->name());
		if(a==_observer->get_main_actor()){
					stop(a, std::vector<int>());
		}
		//drop dead actors items in the current room:
		for(auto i : a->objects()){
			a->location()->drop(i);
		}
		//remove dead actor from room:
		a->location()->leave(a);
		for(auto it = _actors.begin(); it!=_actors.end(); ){
			if((*it)==a){
				it = _actors.erase(it);//remove actor from main reference vector;
				//break;
			} else {
				++it;
			}
		}
	}
	void Game::check_alive(){
		//remove dead actors:
		for (auto it = _actors.begin(); it != _actors.end(); )
		{
			if(!_observer->alive(*it)){
				//if main actor:
				if(*it==_observer->get_main_actor()){
					_io.game_over();
					_running=false;
					return;
				}
					remove_actor(*it);
			} else {
				++it;
			}
		}
	}

	void Game::doStep(){
		if(_running==false)return;
		//check win:
		if(_observer->win()){
			_io.win();
			_running = false;
			return;
		}
		
		//weaken each actor:
		for(auto it = _actors.begin(); it != _actors.end(); ++it){
			(*it)->damage(1);
		}
		
		//update active players:
		check_alive();
		//actor actions:
		for (size_t i = 0; i<_actors.size(); ++i)
		{	
			
			if(_running == false)break;
			
			if(_actors[i]==_observer->get_main_actor()){
				_io.print_round(_round);
				_io.print_stats(_actors[i]);		
			}
			_current_player = _actors[i];
			std::pair<bool, std::string> result = action(_actors[i]);
			
			_io.print(result.second);
			//update active players:
			check_alive();
		}
	}
	std::pair<bool, std::string> Game::action(std::shared_ptr<Actor> actor){
		using std::size_t;
		typedef std::pair<std::string, std::string> pair_t;
		typedef std::pair<bool, std::string> (Game::*function_t)(std::shared_ptr<Actor>, std::vector<int>);
		auto is_main_actor = [&]()->bool{return actor == _observer->get_main_actor();};
		//te reda på vilka olika val aktören har

		//skapa en map med alla möjliga actions. 
		std::map<pair_t, function_t> actions; 
		//map med möjliga actions som skickas till inputer:
		std::vector<pair_t> valid_actions;

		//a map with all present actors:
		std::map<std::string, std::shared_ptr<Actor>> actors;

		//Lägg till alla möjliga go-actions:
		std::shared_ptr<Environment> current_pos = actor->location();
		std::vector<std::vector<int>> dirs = current_pos->directions();

		//possible movements:
		for(size_t i=0; i<dirs.size(); ++i){
			std::string tmp_dir = current_pos->dir_to_str(dirs[i]);
			valid_actions.push_back(std::pair<std::string, std::string>("go", tmp_dir)); 
			pair_t tmp("go", tmp_dir);
			actions.insert(std::pair<pair_t, function_t>(tmp, &Game::go));
		}

		//possible objects to take:
		for(auto i : actor->location()->objects()){
			pair_t tmp("take", i->name());
			valid_actions.push_back(tmp);
			actions.insert(std::pair<pair_t, function_t>(tmp, &Game::take));
		}
		//possible drop objects
		for(auto i : actor->objects()){
			pair_t tmp("drop", i->name());
			valid_actions.push_back(tmp);
			actions.insert(std::pair<pair_t, function_t>(tmp, &Game::drop));
		}
		//if actor is an enemy(HUman) - randomly drop new food objects:
		if(actor->type() == "Enemy"){
			pair_t tmp("create", "food");
			valid_actions.push_back(tmp);
			actions.insert(std::pair<pair_t, function_t>(tmp, &Game::create_food));
		}

		//todo possible fights:
		for(auto i : actor->location()->actors()){
			if(actor->name()!=i->name()){
				pair_t tmp("fight", i->name());
				valid_actions.push_back(tmp);
				actions.insert(std::pair<pair_t, function_t>(tmp, &Game::fight));
				actors.insert(std::make_pair(i->name(), i));
			}
		}
		//key wordsen skickas in i Input
		//om huvudperson, ta input:
		std::pair<std::string, std::string> action;
		
		if (is_main_actor())
		{
			valid_actions.push_back(std::pair<std::string, std::string>("quit", "game"));
			actions.insert(std::pair<pair_t, function_t>(pair_t("quit", "game"), &Game::stop));
		}
			
		//lambda function - skicka funktion som avgör om denna aktör är huvudaktören:
		action = _io.action(valid_actions, actor, is_main_actor());
		//action = _io.action(valid_actions, actor, true);
		//gör om argument till rätt format:
		std::vector<int> args;
		//default target actor - current player
		std::shared_ptr<Actor> target_actor = actor;

		if((action.first).compare("go")==0){
			args = current_pos->str_to_dir(action.second);
		} else if((action.first).compare("quit") == 0){}
	
		else if((action.first).compare("take") == 0){
			//get index of selected object (an sue ptr)
			int index = current_pos->object_index(action.second);
			args.push_back(index);
		} else if((action.first).compare("drop") == 0){
			//get index of selected object (an unique ptr)
			int index = actor->object_index(action.second);
			args.push_back(index);
		}  else if((action.first).compare("fight") == 0){
			//change target actor:
			target_actor = actors.at(action.second);
		} else if((action.first).compare("create") == 0){
		}
		//utför draget:
		function_t function_call = actions.at(action);
		std::pair<bool, std::string> result = (*this.*function_call)(target_actor, args);
		return result;
	}

	//Move an actor in a direction
	std::pair<bool, std::string> Game::go(std::shared_ptr<Actor> actor, std::vector<int> arg){
		std::shared_ptr<Environment> current_location = actor->location();
		std::shared_ptr<Environment> new_location = current_location->neighbor(arg);
		//try to move actor to new location:
		bool res = new_location->enter(actor);
		//make actor leave current room in catEscape::Environment
		if(res){
			current_location->leave(actor);
			actor->set_location(new_location);
			return std::make_pair<bool, std::string>(true, actor->name() + " moved from " 
					+ current_location->name() + " to " + new_location->name() + ".");	
		}
		return std::make_pair<bool, std::string>(false, "Unable to open the door to "+ new_location->name()
													+ ". Perhaps there is a key to this door somewhere in this appartment?");

		
	}
	//Actor takes an object
	std::pair<bool, std::string> Game::take(std::shared_ptr<Actor> actor, std::vector<int> arg){
		//TODO - bool b actor->take(object) , if b - remove from environment.
		//arg är en vektor med ints. inten = index i objectsvektorn
		//1. hämta ut vektorn med alla rummets objekt:
		std::vector<std::shared_ptr<Object>> tmp = actor->location()->objects();
		//2. actor tar upp objekt nr i:
		std::pair<bool, std::string> ret = actor->pick_up(tmp[arg[0]]);
		//3. om detta gick bra - anropa rummets take-funktion. Denna raderar referensen ur sin vektor. 
		if(ret.first)actor->location()->take(tmp[arg[0]]);
		return ret;
	} 
	std::pair<bool, std::string> Game::drop(std::shared_ptr<Actor> actor, std::vector<int> arg){ //actor drops
		return actor->drop(arg[0]);
	} 
	//Actor fights another actor
	std::pair<bool, std::string> Game::fight(std::shared_ptr<Actor> actor, std::vector<int> arg){
		return _current_player->fight(actor);
	} 

	std::pair<bool, std::string> Game::create_food(std::shared_ptr<Actor> actor, std::vector<int> arg){
		std::shared_ptr<Object> f = std::make_shared<Food>("Whiskas", 4, 5);
		actor->location()->drop(f);
		return std::make_pair<bool, std::string>(true, actor->name()
							+" dropped food in " + actor->location()->name()+ ".");

	}
}