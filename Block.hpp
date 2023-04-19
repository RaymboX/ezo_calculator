#ifndef BLOCK_HPP
# define BLOCK_HPP

# include <iostream>

enum operator_e
{
	OP_ADD = 1,		// addition					+
	OP_SUB = 2,		// substraction				-
	OP_MUL = 3,		// multiplication			* or () with no operator
	OP_DIV = 4,		// division					/
	OP_POW = 5,		// power					^
	OP_SQR = 6,		// square root				sqrt(
	OP_SQRM = 7,	// square root minus		-sqrt(
};


class Block
{
private:
	int					_level; 	//Parenthesis level
	int					_op;		//operator enum number
	float				_rhnum;		//right hand number (number at right of operator)

public:
						Block();
						Block(const int& level, const int& op, const float& rhnum);
						Block(const Block& rhs);
	Block&				operator=(const Block& rhs);
	virtual				~Block();

	const int&			getLevel() const;
	const int&			getOp() const;
	const float&		getRhnum() const;

	void				setLevel(const int& level);
	void				setOp(const int& op);
	void				setRhnum(const float& rhnum);
};


#endif