#ifndef BLOCK_HPP
# define BLOCK_HPP

# include <iostream>

class Block
{
private:
	int					_level; 	//Parenthesis level
	int					_op;		//operator enum number
	float				_rhnum;		//right hand number (number at right of operator)
	bool				_spaceBefore;	//if sqrt, check if space before

public:
						Block();
						Block(const int& level, const int& op, const float& rhnum, const bool& spaceBefore);
						Block(const Block& rhs);
	Block&				operator=(const Block& rhs);
	virtual				~Block();

	const int&			getLevel() const;
	const int&			getOp() const;
	const float&		getRhnum() const;
	const bool&			getSpaceBefore() const;

	void				setLevel(const int& level);
	void				setOp(const int& op);
	void				setRhnum(const float& rhnum);
	void				setSpaceBefore(const float& spaceBefore);


//operator

};


#endif