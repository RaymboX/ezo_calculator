#ifndef CALC_HPP
# define CALC_HPP

# include <iostream>
# include <list>		//blocks
# include <cmath>		//sqrt pow
# include <string>		//stof
# include <unistd.h>	//sleep

# include "../../include/ezo_calculator.hpp"

using namespace std;

typedef	list<Block> block_t;

# ifdef UTEST
#  include "../../test/test_Calc.hpp"
# else

class Calc
{
private:
	float		_ans;
	block_t		_blocks;
	static const string	_operator_list[NB_OP_LIST];

//01_ROUTINE####################################################################

	void		calculatorLoop();
	string		getUserInput();
	void		trimSpaceFB(string& command_ref);
	void		clearBlocks();
	void		coutAnswer() const;
	void		coutBlocks();

//02_TEXT#######################################################################

	bool		textCommand(const string& command) const;
	void		intro() const;
	void		help() const;
	void		ezo() const;
	void		shutDown() const;

//03_PARSING####################################################################

	void		parsing(const string& command);
	void		validParenthese(const string& command) const;
	void		tokenization(const string& command);
	bool		isParenthese(const string& command, int& level_ref, size_t& i_ref);
	bool		isOperator(const string& command, int& level_ref, size_t& i_ref);
	bool		isAns(const string& command, const int& level, size_t& i_ref);
	bool		isNumber(const string& command, const int& level, size_t& i_ref);
	void		skipSpace(const string& command, size_t& i_ref);
	void		addParentheseMultiplication();
	void		ParseNegativeNumber();
	void		negativeParenthese(list<Block>::iterator it);
	void		sqrtmMerge(list<Block>::iterator it);
	void		negativeNumMerge(list<Block>::iterator it);
	void		tokenParsing();

//04_CALCULATION################################################################

	void					calculationLoop();
	void					operation();
	list<Block>::iterator	getHigherOperation();
	void					coutDemarche();
	void					demarcheParenthese(const int& fromLevel, const int& toLevel);
	void					levelDown();

//CANONICAL FORM################################################################
				Calc(const Calc& rhs);
	Calc&		operator=(const Calc& rhs);

public:
				Calc();
	virtual		~Calc();

	void		routine();

//GET/SET/TER###################################################################

	const float&	getAns() const;
	void			setAns(const float& ans);

};

# endif

#endif