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
	
	static const string	operator_list[8];

				Calc(const Calc& rhs);
	Calc&		operator=(const Calc& rhs);


	void		intro() const;
	void		help() const;
	void		shutDown() const;

	void		clearBlocks();

	void		calculatorLoop();

	bool		textCommand(const string& command) const;

	void		trimSpaceFB(string& command_ref);

	void		readCommand(const string& command);
	void		validParenthese(const string& command) const;
	void		skipSpace(const string& command, int& i_ref);

	bool		isParenthese(const string& command, int& level_ref, int& i_offset_ref);
	bool		isOperator(const string& command, int& level_ref, int& i_offset_ref);

public:
				Calc();
	virtual		~Calc();

	void		routine();
};

#endif