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

void	Calc::routine()
{
	intro();
	calculatorLoop();
	shutDown();
}

//message introduction au programme
void	Calc::intro() const
{
	cout << PURPLE << "Bonjour et bienvenue sur la calculatrice RaymboX pour EZO" << endl
		<< "Pour de l'aide, inscrivez <HELP>, pour quitter <QUIT> ou <EXIT>" << COLORDEF << endl;
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
	cout << endl << PURPLE << "Merci d'avoir utilisé la calculatrice RaymboX pour EZO. Au plaisir!" << endl;
}

//supprime les containers de _blocks
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

//main loop de la calculatrice
void	Calc::calculatorLoop()
{
	string	command;
	
	while (command != "EXIT" && command != "QUIT")
	{
		cout << WHITE << "> ";
		getline(cin, command);
		cout << COLORDEF;
		if (cin.eof())
			exit(0);
		trimSpaceFB(command);
		if (command.length() != 0 && !(textCommand(command)))
		{
			try
			{
				validParenthese(command);
				tokenization(command);
				addParentheseMultiplication();
				ParseNegativeNumber();
				tokenParsing();
				calculationLoop();
				_ans = _blocks.begin()->getRhnum();
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

//verifie si le nombre de parenthese ouverte et fermer est bon
//Verifie les parentheses vides
void	Calc::validParenthese(const string& command) const
{
	bool	parentheseVide = false;
	int		level = 0;

	for (size_t i = 0; i < command.length(); i++)
	{
		if (command.at(i) == '(')
		{
			parentheseVide = true;
			level += 1;
		}
		else if (isdigit(command.at(i)))
			parentheseVide = false;
		else if (command.at(i) == ')')
		{
			level -= 1;
			if (parentheseVide == true || level < 0)
				throw CalcException::SyntaxExcep();			
		}
	}
	if (level != 0)
		throw CalcException::SyntaxExcep();			
}

//Parse pour les commandes textes
bool	Calc::textCommand(const string& command) const
{
	if (command == "HELP" || command == "QUIT" || command == "EXIT" || command == "EZO")
	{
		if (command == "HELP")
			help();
		else if (command == "EZO")
			ezo();
		return true;
	}
	return false;
}

//Creer les tokens (block) pour chaque opérateurs/nombres
void	Calc::tokenization(const string& command)
{
	size_t i = 0;
	int level = 0;
	Block	blank_block;

	while (i < command.length())
	{
		if (isParenthese(command, level, i) == false)
		{
			_blocks.push_back(blank_block);
			if (isOperator(command, level, i) == false)
			{
				if (isAns(command, level, i) == false)
				{
					if (isNumber(command, level, i) == false)
						throw CalcException::SyntaxExcep();
				}
			}
		}
		skipSpace(command, i);
	}
}

//detecte si ans, set le dernier _blocks
bool	Calc::isAns(const string& command, const int& level, size_t& i_ref)
{
	if (command.substr(i_ref, 3) == "ans")
	{
		//cout << "token ans" << endl;
		_blocks.back().setRhnum(_ans);
		_blocks.back().setOp(OP_NONE);
		_blocks.back().setLevel(level);
		if (i_ref > 0 && command.at(i_ref - 1) == ' ')
			_blocks.back().setSpaceBefore(true);
		i_ref += 3;
		return true;
	}
	return false;
}

//modifie le i_ref pour pointer sur le prochain char qui n'est pas space
// ou arrete au dernier
void	Calc::skipSpace(const string& command, size_t& i_ref)
{
	while (i_ref < command.length() && command.at(i_ref) == ' ')
		i_ref++;
}

//Detecte si le char pointer par i_ref est une parenthese et modifie level_ref selon
bool	Calc::isParenthese(const string& command, int& level_ref, size_t& i_ref)
{
	if (command.at(i_ref) == '(' || command.at(i_ref) == ')' )
	{
		if (command.at(i_ref) == '(')
			level_ref++;
		else
			level_ref--;
		i_ref++;
		return true;
	}
	return false;
}

//Detecte si c'est un operateur et set le dernier block le cas echeant
bool	Calc::isOperator(const string& command, int& level_ref, size_t& i_ref)
{
	for (int i_op = 1; i_op < NB_OP_LIST; i_op++)
	{
		if (i_ref + _operator_list[i_op].length() < command.length()
			&& command.substr(i_ref, _operator_list[i_op].length()) == _operator_list[i_op])
		{
			_blocks.back().setOp(i_op);
			_blocks.back().setLevel(level_ref);
			if(i_op >= OP_SQR)
			{
				if (i_ref > 0 && command.at(i_ref - 1) == ' ')
					_blocks.back().setSpaceBefore(true);
				level_ref++;
			}
			i_ref += _operator_list[i_op].length();
			return true;
		}
	}
	return false;
}

//Detecte si c'est un chiffre valide (si invalide throw exception) et set le dernier block selon
bool	Calc::isNumber(const string& command, const int& level, size_t& i_ref)
{
	bool	dot = false;
	bool	numBeforeDot = false;
	bool	numAfterDot = false;
	size_t	len = 0;

	while (i_ref + len < command.length() && command.at(i_ref + len) != ' '
			&& ((command.at(i_ref + len) == '.') || (isdigit(command.at(i_ref + len)) == true)))
	{
		if (command.at(i_ref + len) == '.')
		{
			if (dot == true || numBeforeDot == false)
				throw CalcException::SyntaxExcep();
			dot = true;
		}
		else if(isdigit(command.at(i_ref + len)) == true)
		{
			if (dot == false)
				numBeforeDot = true;
			else
				numAfterDot = true;
		}
		len++;
	}
	if (dot == true && numAfterDot == false)
		throw CalcException::SyntaxExcep();
	else if (numBeforeDot == true)
	{
		_blocks.back().setRhnum(stof(command.substr(i_ref, len)));
		_blocks.back().setLevel(level);
		if (i_ref > 0 && command.at(i_ref - 1) == ' ')
			_blocks.back().setSpaceBefore(true);
	}
	i_ref += len;
	return numBeforeDot;
}

//Verifie si l'ordre des tokens (block) est bon (nombre - operateur - nombre...)
// (petites exceptions pour sqrt())
void	Calc::tokenParsing()
{
	list<Block>::iterator it = _blocks.begin();
	if ((it->getOp() > OP_NONE && it->getOp() < OP_SQR) 
		|| (next(it) != _blocks.end() && 
			it->getOp() == OP_NONE && next(it)->getOp() == OP_NONE))
	{
		throw CalcException::SyntaxExcep();
	}
	it++;
	while (next(it) != _blocks.end() && it != _blocks.end())
	{
		if ((it->getOp() == OP_NONE 
				&& (prev(it)->getOp() == OP_NONE || next(it)->getOp() == OP_NONE))
			|| (it->getOp() > OP_NONE && it->getOp() < OP_SQR
				&& ((prev(it)->getOp() > OP_NONE)
					|| (next(it)->getOp() > OP_NONE && next(it)->getOp() < OP_SQR))))
			throw CalcException::SyntaxExcep();
		it++;
	}
	if (it->getOp() != OP_NONE)
		throw CalcException::SyntaxExcep();
}

//Merge dans le block it (premier) le block operation substration et le block sqrt en -sqrt OP_SQRM
// erase le block next(it) = original sqrt
void	Calc::sqrtmMerge(list<Block>::iterator it)
{
	list<Block>::iterator next_it = next(it);
	it->setOp(OP_SQRM);
	_blocks.erase(next_it);
}

//Merge dans le block it (premier) le block operation substration et le block number en number negatif
// erase le block next(it) = original number
void	Calc::negativeNumMerge(list<Block>::iterator it)
{
	list<Block>::iterator next_it = next(it);
	it->setOp(OP_NONE);
	it->setRhnum(next_it->getRhnum() * -1);
	_blocks.erase(next_it);
}

//remplace  -(  a _blocks.begin() par  -1*(
void	Calc::negativeParenthese(list<Block>::iterator it)
{
	Block	temp_num;
	temp_num.setRhnum(-1);
	temp_num.setLevel(it->getLevel());
	_blocks.insert(it, temp_num);
	Block	temp_sub;
	it->setOp(OP_MUL);
}

//Insert une multiplication entre deux nombre qui ne sont pas au meme level
// le Block est set au level le plus bas des deux
void	Calc::addParentheseMultiplication()
{
	list<Block>::iterator next_it;
	for (list<Block>::iterator it = _blocks.begin(); next(it) != _blocks.end(); it++)
	{
		next_it = next(it);
		if (it->getOp() == OP_NONE 
				&& (next_it->getOp() == OP_NONE || next_it->getOp() >= OP_SQR || next_it->getOp() == OP_SUB)
				&& it->getLevel() != next_it->getLevel())
		{
			Block newMultBlock;
			newMultBlock.setOp(OP_MUL);
			if (it->getLevel() < next_it->getLevel())
				newMultBlock.setLevel(it->getLevel());
			else
				newMultBlock.setLevel(next_it->getLevel());
			_blocks.insert(next_it, newMultBlock);
			it++;
		}
	}
}

//Merge tous les chiffres negatifs et les sqrt negatif
void	Calc::ParseNegativeNumber()
{
	int index = 0;
	for (list<Block>::iterator it = _blocks.begin(); it != _blocks.end() && next(it) != _blocks.end(); it++)
	{
		if (it->getOp() == OP_SUB)
		{
			if (next(it)->getSpaceBefore() == false
				&& (it == _blocks.begin() 
					|| prev(it)->getLevel() < it->getLevel()
					|| prev(it)->getOp() > OP_NONE)
				&& (next(it)->getOp() == OP_NONE || next(it)->getOp() >= OP_SQR)
				&& it->getLevel() == next(it)->getLevel())
			{
				if (next(it)->getOp() == OP_NONE)
					negativeNumMerge(it);
				else if (next(it)->getOp() >= OP_SQR)
					sqrtmMerge(it);
			}
		}
		index++;
	}
}


//Loop de calcul des tokens et d'affichage de la demarche
void	Calc::calculationLoop()
{
	list<Block>::iterator it;

	while (_blocks.size() != 1)
	{
		operation();
		coutDemarche();
		levelDown();
	}
}

//retourne l'iterator de l'operation avec la priorite level en premier lieu et operation ensuite
list<Block>::iterator	Calc::getHigherOperation()
{
	list<Block>::iterator higherOp = _blocks.begin();
	int index = -1;
	for (list<Block>::iterator it = _blocks.begin(); it != _blocks.end(); it++)
	{
		index++;
		if ((it->getOp() != OP_NONE && higherOp->getOp() == OP_NONE)
				|| ((it->getLevel() > higherOp->getLevel())
				|| ((it->getLevel() == higherOp->getLevel()) && (it->getOp() > higherOp->getOp()))))
			higherOp = it;
	}
	return higherOp;
}

//selon l'operation execute les bonnes commande et supprime les block executer.
// Conserve le resultat dans le block de left side
void	Calc::operation()
{
	list<Block>::iterator it = getHigherOperation();
	list<Block>::iterator prev_it = prev(it);
	list<Block>::iterator next_it = next(it);
	
	switch	(it->getOp())
	{
		case OP_ADD:
		{
			prev_it->setRhnum(prev_it->getRhnum() + next_it->getRhnum());
			_blocks.erase(next_it);
			_blocks.erase(it); 
			break;
		}
		case OP_SUB:
		{
			prev_it->setRhnum(prev_it->getRhnum() - next_it->getRhnum());
			_blocks.erase(next_it);
			_blocks.erase(it); 
			break;
		}
		case OP_MUL:
		{
			prev_it->setRhnum(prev_it->getRhnum() * next_it->getRhnum());
			_blocks.erase(next_it);
			_blocks.erase(it); 
			break;
		}
		case OP_DIV:
		{
			if (next_it->getRhnum() == 0)
				throw CalcException::Divide0Excep();
			prev_it->setRhnum(prev_it->getRhnum() / next_it->getRhnum());
			_blocks.erase(next_it);
			_blocks.erase(it); 
			break;
		}
		case OP_POW:
		{
			prev_it->setRhnum(pow(prev_it->getRhnum(), next_it->getRhnum()));
			_blocks.erase(next_it);
			_blocks.erase(it); 
			break;
		}
		case OP_SQR:
		{
			if (next_it->getRhnum() < 0)
				throw CalcException::NonRealExcep();
			it->setRhnum(sqrt(next_it->getRhnum()));
			it->setOp(OP_NONE);
			_blocks.erase(next_it);
			break;
		}
		case OP_SQRM:
		{
			if (next_it->getRhnum() < 0)
				throw CalcException::NonRealExcep();
			it->setRhnum(sqrt(next_it->getRhnum()) * -1);
			it->setOp(OP_NONE);
			_blocks.erase(next_it);
			break;
		}
	}
}

//Si un chiffre est seul sur sont level
// cette fonction la detecte et la rabaisse au niveau inferieur
void	Calc::levelDown()
{
	bool	rhsIsLower;
	bool	lhsIsLower;
	list<Block>::iterator it = _blocks.begin();
	list<Block>::iterator prev_it;
	list<Block>::iterator next_it;
	if (_blocks.size() > 1)
	{
		while (it != _blocks.end())
		{
			prev_it = prev(it);
			next_it = next(it);
			lhsIsLower = false;
			if (it == _blocks.begin() || prev_it->getLevel() < it->getLevel())
				lhsIsLower = true;
			rhsIsLower = false;
			if (next_it == _blocks.end() || next_it->getLevel() < it->getLevel())
				rhsIsLower = true;
			if (lhsIsLower == true && rhsIsLower == true)
			{
				it->setLevel(it->getLevel() - 1);
				it = _blocks.begin();
			}
			else
				it++;
		}
	}
}

//message de la reponse
void	Calc::coutAnswer() const
{
	cout << GREEN << "La reponse est: " <<  _blocks.begin()->getRhnum() << COLORDEF << endl;
}

//Affiche en format demarche, le present status des tokens (_blocks)
void	Calc::coutDemarche()
{
	int prevLevel = 0;
	
	cout << BLUE << "  ";
	for (list<Block>::iterator it = _blocks.begin(); it != _blocks.end(); it++)
	{
		if (it != _blocks.begin())
			prevLevel = prev(it)->getLevel();
		if (it != _blocks.begin() && prev(it)->getOp() >= OP_SQR)
			demarcheParenthese(prevLevel + 1, it->getLevel());
		else
			demarcheParenthese(prevLevel, it->getLevel());
		if (it->getOp() == OP_NONE)
			cout << it->getRhnum() << " ";
		else
			cout << _operator_list[it->getOp()] << " ";
		if (next(it) == _blocks.end() && it->getLevel() > 0)
			demarcheParenthese(it->getLevel(), 0);
	}
	cout << COLORDEF << endl;
}

//Affiche les parenthese dans la demarche selon le niveau from a to
void	Calc::demarcheParenthese(const int& fromLevel, const int& toLevel)
{
	int level_offset = 0;
	while (fromLevel + level_offset != toLevel)
	{
		if (fromLevel < toLevel)
		{
			level_offset++;
			cout << "( ";
		}
		else
		{
			level_offset--;
			cout << ") ";
		}
	}
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
				<< " Rhsnum:" << it->getRhnum()
				<< " spaceBefore:" << it->getSpaceBefore() << endl;
	}
	sleep(1);
}