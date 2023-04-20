#ifndef CALC_HPP
# define CALC_HPP

# include <iostream>
# include <list>
# include <stdlib.h>
# include <cmath>
# include <string>
# include <unistd.h>

# include "../../include/colors.hpp"
# include "../Block/Block.hpp"
# include "CalcException.hpp"
# include "../../include/ezo_calculator.hpp"

using namespace std;

typedef	list<Block> block_t;

class Calc
{
private:
	int			_ans;
	block_t		_blocks;
	
	static const string	_operator_list[NB_OP_LIST];
	static bool	_demarche;

				Calc(const Calc& rhs);
	Calc&		operator=(const Calc& rhs);


	void		intro() const;
	void		help() const;
	void		shutDown() const;

	void		clearBlocks();

	void		calculatorLoop();

	bool		textCommand(const string& command) const;

	void		trimSpaceFB(string& command_ref);


	void		validParenthese(const string& command) const;
	void		skipSpace(const string& command, size_t& i_ref);
	void		tokenization(const string& command);
	bool		isParenthese(const string& command, int& level_ref, size_t& i_ref);
	bool		isOperator(const string& command, int& level_ref, size_t& i_ref);
	bool		isAns(const string& command, const int& level, size_t& i_ref);
	bool		isNumber(const string& command, const int& level, size_t& i_ref);
	void		tokenParsing();
	void		addParentheseMultiplication();
	bool		exceptionTwoOp(list<Block>::iterator it);
	void		sqrtmMerge(list<Block>::iterator it);
	void		negativeNumMerge(list<Block>::iterator it);
	void		calculationLoop();
	void		operation();
	void		levelDown();
	void		coutDemarche();
	void		demarcheParenthese(const int& fromLevel, const int& toLevel);
	int			higherLevel();
	list<Block>::iterator	getHigherOperation();

	void		coutAnswer() const;

	void		coutBlocks();

public:
				Calc();
	virtual		~Calc();

	void		routine();
};

#endif