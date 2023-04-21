#include "Calc.hpp"

const string	Calc::_operator_list[NB_OP_LIST] = 
{
	"",
	"+",
	"-",
	"*",
	"/",
	"^",
	"sqrt(",
	"-sqrt("
};


Calc::Calc(): _ans(0)	{routine();}
Calc::~Calc()			{clearBlocks();}

//Main of calc
void	Calc::routine()
{
	intro();
	calculatorLoop();
	shutDown();
}

//main loop de la calculatrice
void	Calc::calculatorLoop()
{
	string	command;
	while (command != "EXIT" && command != "QUIT")
	{
		command = getUserInput();
		if (command.length() != 0 && !(textCommand(command)))
		{
			try
			{
				parsing(command);
				calculationLoop();
				_ans = _blocks.begin()->getNum();
				coutAnswer();
			}
			catch(const CalcException::SyntaxExcep& e) 
				{cerr << RED << e.what() << COLORDEF <<endl;}
			catch(const CalcException::Divide0Excep& e) 
				{cerr << RED << e.what() << COLORDEF <<endl;}
			catch(const CalcException::NonRealExcep& e) 
				{cerr << RED << e.what() << COLORDEF <<endl;}
			catch(const exception& e)
				{cerr << RED << e.what() << COLORDEF <<endl;}
		}
		clearBlocks();
	}
}

//Lit la command via getline
// exit si eof (ctrl+d)
// trim space front and back
string	Calc::getUserInput()
{
	string	command;
	cout << WHITE << "> ";
	getline(cin, command);
	cout << COLORDEF;
	if (cin.eof())
		exit(0);
	trimSpaceFB(command);
	return command;
}

//remove space at the front and back of command
void	Calc::trimSpaceFB(string& command_ref)
{
	command_ref.erase(0, command_ref.find_first_not_of(" "));
	command_ref.erase(command_ref.find_last_not_of(" ") + 1);
}



//supprime les containers de _blocks
void	Calc::clearBlocks()
{
	while (_blocks.begin() != _blocks.end())
		_blocks.erase(_blocks.begin());
}

//Outils de debug pour afficher le contenu des blocks
void	Calc::coutBlocks()
{
	int index = -1;
	for (list<Block>::iterator it = _blocks.begin(); it != _blocks.end(); it++)
	{
		index++;
		cout << "index:" << index 
				<< " OP:" << it->getOp() 
				<< " level:" << it->getLevel()
				<< " Rhsnum:" << it->getNum()
				<< " spaceBefore:" << it->getSpaceBefore() << endl;
	}
	sleep(1);
}