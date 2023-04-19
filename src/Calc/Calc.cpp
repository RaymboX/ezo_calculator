#include "Calc.hpp"

const string	Calc::operator_list[8] = 
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

Calc::Calc(): _ans(0) {routine();}

Calc::~Calc()
{
	clearBlocks();
}

void	Calc::routine()
{
	intro();
	help();
	calculatorLoop();
	shutDown();
}

void	Calc::intro() const
{
	cout << "Bonjour et bienvenue sur la calculatrice RaymboX pour EZO" << endl;
}

void	Calc::help() const
{
	cout << "Aide:" << endl
		<< "- Operations acceptées: <+, -, *, /, ^, sqrt()>" << endl
		<< "- Vous pouvez utiliser les parenthèses () pour la priorité des opérations" << endl
		<< "- Si vous ne mettez pas d'opérateur devant ou après une parenthèse," << endl
		<< "    l'opération sera considéré une multiplication" << endl
		<< "- Vous pouvez utiliser <ans> pour récupérer le dernier résultat valide" << endl
		<< "- Pour revoir cette aide, inscrivez <HELP>" << endl
		<< "- Pour quitter, inscrivez <QUIT> ou <EXIT>" << endl;
}

void	Calc::shutDown() const
{
	cout << endl << "Merci d'avoir utilisé la calculatrice RaymboX pour EZO. Au plaisir!" << endl;
}

void	Calc::clearBlocks()
{
	while (_blocks.begin() != _blocks.end())
		_blocks.erase(_blocks.begin());
}

//remove space at the front and back of command
void	Calc::trimSpaceFB(string& command_ref)
{
	command_ref.erase(0, command_ref.find_first_not_of(" "));
	command_ref.erase(command_ref.find_last_not_of(" ") + 1);
}

void	Calc::calculatorLoop()
{
	string	command = "";
	
	while (command != "EXIT" && command != "QUIT")
	{
		cout << "> ";
		getline(cin, command);
		if (cin.eof())
			exit(0);
		trimSpaceFB(command);
		if (!(textCommand(command)))
		{
			try
			{
				validParenthese(command);
				//block record
				//blocks calculation
				//cout answer
			}
			catch(const CalcException::SyntaxExcep& e) 
				{cerr << RED << e.what() << COLORDEF <<endl;}
			catch(const CalcException::Divide0Excep& e) 
				{cerr << RED << e.what() << COLORDEF <<endl;}
			catch(const CalcException::NonRealExcep& e) 
				{cerr << RED << e.what() << COLORDEF <<endl;}
		}
		clearBlocks();
	}
}

void	Calc::validParenthese(const string& command) const
{
	bool	error = false;
	bool	level = 0;

	for {int i = 0; i < command.length(); i++}
	{
		if (command.at(i) == '(')
		{
			error = true;
			level++;
		}
		else if (isDigit(command.at(i))
			error = false;
		else if (command.at(i) == ')')
		{
			level--;
			if (error == true || level < 0)
				throw CalcException::SyntaxExcep();			
		}
	}
}

bool	Calc::textCommand(const string& command) const
{
	if (command == "HELP" || command == "QUIT" || command == "EXIT")
	{
		if (command == "HELP")
			help();
		return true;
	}
	return false;
}

void	Calc::readCommand(const string& command)
{
	int level = 0;
	int i = 0;

	while (i < command.length())
	{
		_blocks.push_back();
		
		i = blockRecord(command, level, i);

		skipSpace(i);
	}
}

void	Calc::skipSpace(skipSpace(const string& command, int& i_ref)
{
	while (command.at(i_ref) == ' ')
		i_ref++;
}



bool	Calc::isParenthese(const string& command, int& level_ref, int& i_offset_ref)
{
	if (command.at(i_offset_ref) == '(' || command.at(i_offset_ref) == ')' )
	{
		if (command.at(i_offset_ref) == '(')
			level_ref++;
		else
			level_ref--;
		if (level_ref < 0)
			throw CalcException::SyntaxExcep();
		i_offset_ref += 1;
		return true;
	}
	return false;
}

bool	Calc::isOperator(const string& command, int& level_ref, int& i_offset_ref)
{
	if (command_ref.length() > i_offset + )
}