#include "inputoutput.hpp"
#include "environment.hpp"
#include "cat.hpp"
#include <iostream>
#include <memory>
#include <algorithm>
#include <stdlib.h>

namespace catEscape{
	InputOutput::InputOutput(){
		srand(time(0));
	}
	InputOutput::~InputOutput(){
		std::cout<<"~InputOutput()"<<std::endl;
	}
	void InputOutput::win(){
		std::cout<<_win<<"\n"<<std::endl;
	}
	void InputOutput::set_welcome(const std::string& s){
		_welcome = s;
	}
	
	void InputOutput::welcome(){
		std::cout<<_welcome<<"\n"<<std::endl;
	}

	void InputOutput::set_win(const std::string& s){
		_win = s;
	}
	void InputOutput::set_dies(const std::string& s){
		_dies = s;
	}
	void InputOutput::quit(const std::shared_ptr<Actor> actor){
		std::cout<<actor->name()<<" quits the game. \n Bye Bye! \n";
	}
	void InputOutput::dies(const std::string& name){
		std::cout<<name<<" "<<_dies<<std::endl;
	}
	void InputOutput::set_game_over(const std::string& s){
		_gameOver = s;
	}
	void InputOutput::print(const std::string& s){
		std::cout<<"-----------------Message------------------\n";
		std::cout<<s<<"\n\n";
		std::cout<<"------------------------------------------\n\n\n\n";
	}
	void InputOutput::print_round(const std::size_t& i) const{
		std::cout<<"####################### ROUND "<<i<<" ########################\n\n\n";
	}

	void InputOutput::print_stats(std::shared_ptr<Actor> a){
		std::cout<<"\t\t------------------------\n";
		std::cout<<"\t\t.                       .\n";
		std::cout<<"\t\t.   Life: "<<std::to_string(a->life())<<"\n";
//		auto objects = a->objects();
		//if actor has weapon:
		//kanske måste göra en dynamisk cast... 
		if(a->type() == "Cat"){
			Cat* c = dynamic_cast<Cat*>(a.get());
			if (c->weapon()!=0)
			{
				std::cout<<"\t\t.   Weapon: "<<c->weapon()->name()<<"\n";
			}
		}
		
		if(a->objects().size()>0){
		std::cout<<"\t\t.   Items in bag: ("<<a->bag()->weight()<<"/"<<a->bag()->hold_weight()<< ").\n";	
		}
		
		for(auto i: a->objects()){
		std::cout<<"\t\t.          "<<i->name()<<"\n";	
		}
		std::cout<<"\t\t.                       .\n";
		std::cout<<"\t\t------------------------\n\n\n";

	}
	void InputOutput::game_over(){
		std::cout<<_gameOver<<"\n";
	}

	std::pair<std::string, std::string> InputOutput::action(std::vector< std::pair<std::string, std::string> > valid_actions, 
							std::shared_ptr<Actor> actor, bool is_main_actor){
		if(!is_main_actor){
			std::size_t ran = rand() % valid_actions.size();
			std::pair<std::string, std::string> value(valid_actions[ran]);
			return value;
		}
		std::cout<<"It is now "<<actor->name()<<":s turn. You are in "<<actor->location()->description()<<".\n";
		// std::cout<<"Contains objects: \n";
		// for(auto i : actor->location()->objects()){
		// 	std::cout<<i->name()<<": "<<i->str()<<"\n";
		// }
		// std::cout<<"Actors in this room: \n";
		// for(auto i : actor->location()->actors()){
		// 	std::cout<<i->name()<<": "<<i->str()<<"\n";
		// }

		std::cout<<"\nPossible actions: \n";
		for (std::size_t i = 0; i < valid_actions.size(); ++i)
		{
			std::cout<<valid_actions[i].first<<" "<<valid_actions[i].second<<"\n";
		}

		bool valid = false;
		while(valid == false){
			std::cout<<"Your move: >>";
			std::string input;
			std::getline(std::cin, input);
			std::size_t i = 0;
			char c;
			while(input[i])
			{
				c = input[i];
				if(isspace(c)) break;
				i++;
			}
			if(i<input.length()){
				std::string first_key = input.substr(0,i);
				std::string second_key = input.substr(i+1);
				//kolla om detta move finns bland de tillåtna movesen:
				std::pair<std::string, std::string> value(first_key, second_key);
				if (std::find(valid_actions.begin(), 
								valid_actions.end(), value) != valid_actions.end()){
					//valid move:
					valid = true;
					return value;
				} else {
					std::cout<<"Not a valid move!\n";
				}
			} else {
				std::cout<<"Not a valid move!\n";
			}
		}
		return std::make_pair<std::string, std::string>("","");
	}
	/* 
	std::pair<std::string, std::string> InputOutput::random_action(std::vector< std::pair<std::string, std::string> > valid_actions, 
							std::shared_ptr<Actor> actor){
		if (valid_actions.size() == 0)
		{
			return std::pair<std::string, std::string>("","");
		}
		int ran;
		if (valid_actions.size()<2)
		{
			ran=0;
		} else {
			ran = rand() % valid_actions.size() - 1;
		}
		return valid_actions[ran];
	}
	*/
}