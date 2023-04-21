#include "Calc.hpp"

//Parse pour les commandes textes
bool	Calc::textCommand(const string& command) const
{
	if (command == "HELP" || command == "EZO"
		|| command == "EXIT" || command == "QUIT")
	{
		if (command == "HELP")
			help();
		else if (command == "EZO")
			ezo();
		return true;
	}
	return false;
}

//message introduction au programme
void	Calc::intro() const
{
	cout << PURPLE << "Bonjour et bienvenue sur la calculatrice RaymboX pour EZO" << endl
		<< "Pour de l'aide, inscrivez <HELP>, pour quitter <QUIT> ou <EXIT>"
		<< COLORDEF << endl;
}



//aide sur les fonctions disponibles
void	Calc::help() const
{
	cout << CYAN << "Aide:" << endl
		<< "- Operations acceptées: <+, -, *, /, ^, sqrt()>" << endl
		<< "- Vous pouvez utiliser les parenthèses () pour la priorité des opérations" << endl
		<< "- Si vous ne mettez pas d'opérateur devant ou après une parenthèse," << endl
		<< "    l'opération sera considéré une multiplication" << endl
		<< "- Vous pouvez utiliser <ans> pour récupérer le dernier résultat valide" << endl
		<< "- Pour revoir cette aide, inscrivez <HELP>" << endl
		<< "- Pour quitter, inscrivez <QUIT> ou <EXIT>" << COLORDEF << endl;
}

void	Calc::ezo() const
{
	cout << CYAN << "LES TROIS RÈGLES:" << endl
		<< "1) Aime françois Pérusse" << endl
		<< "2) N'aime pas League of Legends (lol)" << endl
		<< "3) Chocolatine ou pain au chocolat....." << COLORDEF << endl;
}

//message fermeture du programme
void	Calc::shutDown() const
{
	cout << PURPLE 
		<< "Merci d'avoir utilisé la calculatrice RaymboX pour EZO. Au plaisir!" 
		<< endl << endl;
}

//message de la reponse
void	Calc::coutAnswer() const
{
	cout << GREEN << "La reponse est: " <<  _blocks.begin()->getNum() << COLORDEF << endl;
}