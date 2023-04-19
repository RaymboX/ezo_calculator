#include "Calc.hpp"

Calc::Calc(): _actualLevel(0), _ans(0) {routine();}

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

void	Calc::intro()
{
	cout << "Bonjour et bienvenue sur la calculatrice RaymboX pour EZO" << endl;
}

void	Calc::help()
{
	cout << "Aide:" << endl
		<< "- Operations acceptées: <+, -, *, /, ^, sqrt()>" << endl
		<< "- Vous pouvez utiliser les parenthèses () pour la priorité des opérations" << endl
		<< "- Si vous ne mettez pas d'opérateur devant ou après un parenthèse," << endl
		<< "    l'opération sera considéré une multiplication" << endl
		<< "- Vous pouvez utiliser <ans> pour récupérer le dernier résultat valide" << endl
		<< "- Pour revoir cette aide, inscrivez HELP" << endl
		<< "- Pour quitter, inscrivez QUIT ou EXIT" << endl;
}

void	Calc::shutDown()
{
	cout << endl << "Merci d'avoir utilisé la calculatrice RaymboX pour EZO. Au plaisir!" << endl;
}

void	Calc::clearBlocks()
{
	for (block_t::iterator it = _blocks.begin(); it != _blocks.end(); it++)
		_blocks.erase(it);
}

void	Calc::calculatorLoop()
{
	string	input = "";
	
	while (input != "EXIT" && input != "QUIT")
	{
		cout << "> ";
		getline(cin, input);
		if (cin.eof())
			exit(0);
		//verifier si text input
		//try
		//line parsing
		//block record
		//blocks calculation
		//cout answer
		//catch error syntax
		//catch error not divide zero
		//catch error nonreal answer (squareroot negative)
	}
}



