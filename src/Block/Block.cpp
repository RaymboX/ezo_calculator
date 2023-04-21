#include "Block.hpp"

//CANONICAL FORM CONSTRUCTOR DESTRUCTOR OPERATOR=###############################
Block::Block():_level(0), _op(0), _num(0), _spaceBefore(false) {}

Block::Block(const int& level, const int& op, const float& num, const bool& spaceBefore):
		_level(level), _op(op), _num(num), _spaceBefore(spaceBefore) {}

Block::Block(const Block& rhs) {*this = rhs;}

Block&	Block::operator=(const Block& rhs)
{
	_level = rhs.getLevel();
	_op = rhs.getOp();
	_num = rhs.getNum();
	_spaceBefore = rhs.getSpaceBefore(); 
	return *this;
}

Block::~Block() {}
//##############################################################################

//GET/SET/TER###################################################################
const int&		Block::getLevel() const 				{return _level;}
const int&		Block::getOp() const 					{return _op;}
const float&	Block::getNum() const					{return _num;}
const bool&		Block::getSpaceBefore() const			{return _spaceBefore;}

void	Block::setLevel(const int& level)				{_level = level;}
void	Block::setOp(const int& op)						{_op = op;}
void	Block::setNum(const float& num)				{_num = num;}
void	Block::setSpaceBefore(const float& spaceBefore)	{_spaceBefore = spaceBefore;}
//##############################################################################