#include "Block.hpp"

//CANONICAL FORM CONSTRUCTOR DESTRUCTOR OPERATOR=###############################
Block::Block():_level(0), _op(0), _rhnum(0), _spaceBefore(false) {}

Block::Block(const int& level, const int& op, const float& rhnum, const bool& spaceBefore):
		_level(level), _op(op), _rhnum(rhnum), _spaceBefore(spaceBefore) {}

Block::Block(const Block& rhs) {*this = rhs;}

Block&	Block::operator=(const Block& rhs)
{
	_level = rhs.getLevel();
	_op = rhs.getOp();
	_rhnum = rhs.getRhnum();
	_spaceBefore = rhs.getSpaceBefore(); 
	return *this;
}

Block::~Block() {}
//##############################################################################

//GET/SET/TER###################################################################
const int&		Block::getLevel() const 				{return _level;}
const int&		Block::getOp() const 					{return _op;}
const float&	Block::getRhnum() const					{return _rhnum;}
const bool&		Block::getSpaceBefore() const			{return _spaceBefore;}

void	Block::setLevel(const int& level)				{_level = level;}
void	Block::setOp(const int& op)						{_op = op;}
void	Block::setRhnum(const float& rhnum)				{_rhnum = rhnum;}
void	Block::setSpaceBefore(const float& spaceBefore)	{_spaceBefore = spaceBefore;}
//##############################################################################