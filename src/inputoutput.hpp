#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H
#include "environment.hpp"
#include "actor.hpp"
#include <memory>
#include <vector>
#include <string>

//InputOutput act as a controller
namespace catEscape{
class Game;
class InputOutput{
	std::string _welcome = "";
	std::string _playersTurn = "";
	std::string _win = "";
	std::string _dies = "";
	std::string _gameOver = "";

public:
	InputOutput();
	~InputOutput();
	void welcome();
	void set_welcome(const std::string&);
	void set_win(const std::string&);
	void win();
	void set_game_over(const std::string&);
	void game_over();
	void quit(const std::shared_ptr<Actor>);
	void dies(const std::string&);
	void set_dies(const std::string&);
	void print_round(const std::size_t&) const;
	void print_stats(std::shared_ptr<Actor>);
	void print(const std::string&);
	std::pair<std::string, std::string> action(std::vector< std::pair<std::string, std::string> >, 
												std::shared_ptr<Actor>, bool);
};
}
#endif