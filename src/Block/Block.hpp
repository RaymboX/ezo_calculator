#ifndef BLOCK_HPP
# define BLOCK_HPP

# include <iostream>

class Block
{
private:
	int					_level; 	//Parenthesis level
	int					_op;		//operator enum number
	float				_num;		//right hand number (number at right of operator)
	bool				_spaceBefore;	//if sqrt, check if space before

public:

//CANONICAL FORM CONSTRUCTOR DESTRUCTOR OPERATOR=###############################

						Block();
						Block(const int& level, const int& op, const float& num, const bool& spaceBefore);
						Block(const Block& rhs);
	Block&				operator=(const Block& rhs);
	virtual				~Block();

//GET/SET/TER###################################################################

	const int&			getLevel() const;
	const int&			getOp() const;
	const float&		getNum() const;
	const bool&			getSpaceBefore() const;

	void				setLevel(const int& level);
	void				setOp(const int& op);
	void				setNum(const float& Num);
	void				setSpaceBefore(const float& spaceBefore);

};


#endif