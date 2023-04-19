#include "Calc.hpp"

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
void	Calc::trimFB(std::string& command_ref)
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
		trimFB(command);
		if (!(textCommand(command)))
		{
			//try
			//line parsing
			//block record
			//blocks calculation
			//cout answer
		}
		//catch error syntax
		//catch error not divide zero
		//catch error nonreal answer (squareroot negative)
	}
}

bool	Calc::textCommand(const std::string& command) const
{
	if (command == "HELP" || command == "QUIT" || command == "EXIT")
	{
		if (command == "HELP")
			help();
		return true;
	}
	return false;
}


