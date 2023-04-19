#ifndef CALCEXCEPTION_HPP
# define CALCEXCEPTION_HPP

# include <stdexcept>

//EXCEPTION MESSAGE
# define CALCEX_SYNTAX "ERR: SYNTAX"
# define CALCEX_DIVIDE0 "ERR: DIVIDE BY 0"
# define CALCEX_NONREAL "ERR: NONREAL ANSWER"

class CalcException
{
public:
	class	SyntaxExcep: public std::exception
	{
	public:
		virtual const char* what() const throw() {return (CALCEX_SYNTAX);}
	};

	class	Divide0Excep: public std::exception
	{
	public:
		virtual const char* what() const throw() {return (CALCEX_DIVIDE0);}
	};

	class	NonRealExcep: public std::exception
	{
	public:
		virtual const char* what() const throw() {return (CALCEX_NONREAL);}
	};

};

#endif