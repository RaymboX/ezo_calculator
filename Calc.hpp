#ifndef CALC_HPP
# define CALC_HPP

# include <iostream>
# include <list>

# include "colors.hpp"
# include "Block.hpp"

using namespace std;

typedef	list<Block> block_t;

class Calc
{
private:
	int			_actualLevel;
	int			_ans;
	block_t		_blocks;

				Calc(const Calc& rhs);
	Calc&		operator=(const Calc& rhs);

	
	void		routine();
	
	void		intro();
	void		help();
	void		shutDown();

	void		clearBlocks();









public:
				Calc();
	virtual		~Calc();
};

#endif