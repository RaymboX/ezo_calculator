#include "Block.hpp"

//CANONICAL FORM CONSTRUCTOR DESTRUCTOR OPERATOR=###############################
Block::Block():_level(0), _op(0), _rhnum(0) {}

Block::Block(const int& level, const int& op, const float& rhnum):
		_level(level), _op(op), _rhnum(rhnum) {}

Block::Block(const Block& rhs) {*this = rhs;}

Block&	Block::operator=(const Block& rhs)
{
	_level = rhs.getLevel();
	_op = rhs.getOp();
	_rhnum = rhs.getRhnum();
	return *this;
}

Block::~Block() {}
//##############################################################################

//GET/SET/TER###################################################################
const int&		Block::getLevel() const 	{return _level;}
const int&		Block::getOp() const 		{return _op;}
const float&	Block::getRhnum() const		{return _rhnum;}

void	Block::setLevel(const int& level)	{_level = level;}
void	Block::setOp(const int& op)			{_op = op;}
void	Block::setRhnum(const float& rhnum)	{_rhnum = rhnum;}
//##############################################################################