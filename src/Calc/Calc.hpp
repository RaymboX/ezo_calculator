#ifndef CALC_HPP
# define CALC_HPP

# include <iostream>
# include <list>
# include <stdlib.h>

# include "../../include/colors.hpp"
# include "../Block/Block.hpp"
# include "CalcException.hpp"

using namespace std;

typedef	list<Block> block_t;

class Calc
{
private:
	int			_ans;
	block_t		_blocks;
	
	static const string	operator_list[NB_OP_LIST];

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
	void		skipSpace(const string& command, int& i_ref);
	void		tokenization(const string& command);
	bool		isParenthese(const string& command, int& level_ref, int& i_ref);
	bool		isOperator(const string& command, const int& level, int& i_ref);
	bool		isAns(const string& command, const int& level, int& i_ref);
	bool		isNumber(const string& command, const int& level, int& i_ref);

public:
				Calc();
	virtual		~Calc();

	void		routine();
};

#endif