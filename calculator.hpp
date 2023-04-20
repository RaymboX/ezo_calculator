#ifndef CALCULATOR_HPP
# define CALCULATOR_HPP

# include <iostream>

class Calculator
{
private:
	double			_ans;

					Calculator(const Calculator& rhs);
	Calculator&		operator=(const Calculator& rhs);

	

public:
					Calculator();
	virtual			~Calculator();

	

};




#endif