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

bool Calc::_demarche = false;

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
	string	command;
	
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
				tokenization(command);
				addParentheseMultiplication();
				tokenParsing();
				//calculation loop
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
		command = "";
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

void	tokenization(const string& command)
{
	int i = 0;
	int level = 0;

	while (i < command.length())
	{
		_blocks.push_back();
		if (isParenthese(command, level, i) == false)
		{
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

bool	Calc::isAns(const string& command, const int& level, int& i_ref)
{
	if (command.substr(i_ref, 3) == "ans")
	{
		_blocks.back().setRhnum(_ans);
		_blocks.back().setOp(OP_NONE);
		_blocks.back().setLevel(level);
		if (i_ref > 0 && command.at(i_ref - 1) == ' ')
			_blocks.back().setSpaceBefore(true);
		return true;
	}
	return false;
}

void	Calc::skipSpace(skipSpace(const string& command, int& i_ref)
{
	while (command.at(i_ref) == ' ')
		i_ref++;
}


bool	Calc::isParenthese(const string& command, int& level_ref, int& i_ref)
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

bool	Calc::isOperator(const string& command, int& level_ref, int& i_ref)
{
	for (int i_op = 1; i_op < NB_OP_LIST; i_op++)
	{
		if (i_ref + _operator_list[i_op].length() < command.length()
			&& command.substr(i_ref, _operator_list[i_op].length()) == _operator_list[i_op])
		{
			_blocks.back().setOp(i_op);
			_blocks.back().setLevel(level_ref);
			if(i_op >= 6)
			{
				if (i_ref > 0 && command.at(i_ref - 1) == ' ')
					_blocks.back().setSpaceBefore = true;
				level_ref++;
			}
			i_ref += _operator_list[i_op].length();
			return true;
		}
	}
	return false;
}

bool	Calc::isNumber(const string& command, const int& level, int& i_ref)
{
	bool	dot = false;
	bool	numBeforeDot = false;
	bool	numAfterDot = false;
	int		i_offset = 0;

	while (i_ref + len < command.length() && command.at(i_ref + len) != ' '
			&& ((command.at(i_ref + len) == '.') || (isDigit(command.at(i_ref + len)) == true)))
	{
		if (command.at(i_ref + len) == '.')
		{
			if (dot == true || numBeforeDot == false)
				throw CalcException::SyntaxExcep();
			dot = true;
		}
		else if(isDigit(command.at(i_ref + len)) == true)
		{
			if (dot == false)
				numBeforeDot = true;
			else
				numAfterDot = true;
		}
		len++;
	}
	if (dot = true && numAfterDot == false)
		throw CalcException::SyntaxExcep();
	else if (numBeforeDot == true)
	{
		_blocks.back().setRhnum(stof(command.substr(i_ref, i_offset)));
		_blocks.back().setLevel(level);
		if (i_ref > 0 && command.at(i_ref - 1) == ' ')
			_blocks.back().setSpaceBefore = true;
	}
	i_ref += i_offset;
	return numBeforeDot;
}

//Error case
//1) operator with number lower level -> (2 +)2
//2) two simultaneous operator that is not exception -> +-3
//3) finish with operator -> 2+2+
void	Calc::tokenParsing()
{
	list<Block>::iterator it = _blocks.begin();

	while (it != _blocks.end())
	{
		if (it == _blocks.begin())
		{
			if (it->getOp() != OP_NONE || it->getOp() != OP_SQR || it->getOp() != OP_SQRM)
			{
				if (exceptionTwoOp(it) == false)
					throw CalcException::SyntaxExcep();
			}
		}
		else if (it[1] == _blocks.end())
		{
			if (it->getOp() != OP_NONE)
				throw CalcException::SyntaxExcep();
		}
		else
		{
			if (it->getOp() != OP_NONE)
			{
				if ((it[-1]->getOp() == OP_NONE && it[-1]->getLevel() < it->getLevel())
					&& (it[1]->getOp() == OP_NONE && it[1]->getLevel() < it->getLevel()))
					throw CalcException::SyntaxExcep();
				if (it[1]->getOp() != OP_NONE && it[1]->getOp != OP_SUB)
				{
					if (exceptionTwoOp(it) == false)
						throw CalcException::SyntaxExcep();
				}
			}
		}
		it++;
	}
}

//return true if need to skip first it
bool	Calc::exceptionTwoOp(list<Block>::iterator it)
{
	if (it->getOp() == OP_SUB
		&& it->getLevel() == it[1]->getLevel()
		&& it[1]->getSpaceBefore == false))
	{
		if (it[1]->getOp == OP_SQR)
		{
			sqrtmMerge(it);
			return true;
		}
		else if (it[1]->getOp == OP_NONE)
		{
			negativeNumMerge(it);
			return true;
		}
	}
	return false;
}

void	Calc::sqrtmMerge(list<Block>::iterator it)
{
	it->setOp(7);
	_blocks.erase(it[1]);
}

void	Calc::negativeNumMerge(list<Block>::iterator it)
{
	it->setOp(OP_NONE);
	it->setRhnum(it[1]->getRhnum() * -1);
	_blocks.erase(it[1]);
}

//Insert une multiplication entre deux nombre qui ne sont pas au meme level
// au level le plus bas
void	Calc::addParentheseMultiplication()
{
	for (list<Block>::iterator it = _blocks.begin(); it[1] != _blocks.end(); it++)
	{
		if (it->getOp() == 0 && it[1]->getOp() == 0
				&& it->getLevel() != it[1]->getLevel())
		{
			Block newMultBlock;
			newMultBlock.setOp(OP_MUL);
			if (it->getLevel() > it[1]->getLevel())
				newMultBlock = it->getLevel();
			else
				newMultBlock = it[1]->getLevel();			
			_blocks.insert(it[1], newMultBlock);
			it++;
		}
	}
}

void	Calc::calculationLoop();
{
	list<Block>::iterator it;

	while (_blocks.size() != 1)
	{
		operation();
		levelDown();
		coutDemarche();
	}
}

int	Calc::higherLevel() const
{
	int level = 0;
	for (list<Block>::iterator it = _blocks.begin(); it != _blocks.end(); it++)
	{
		if (it->getLevel() > level)
			level = it->getLevel();
	}
	return level;
}

list<Block>::iterator	Calc::getHigherOperation() const
{
	list<Block>::iterator higherOp = _blocks.begin();
	for (list<Block>::iterator it = _blocks.begin(); it != _blocks.end(); it++)
	{
		if ((it->getOp != OP_NONE && higherOp->getOp() == OP_NONE)
			|| (it->getLevel() >= higherOp->getLevel()
				&& it->getOp() > higherOp->getOp()))
			higherOp = it;
	}
	return higherOp;
}

void	Calc::operation()
{
	list<Block>::iterator higherOp = getHigherOperation();
	switch	(higherOp->getOp())
	{
		case OP_ADD:
		{
			it[-1]->getRhnum() += it[1]->getRhnum();
			_blocks.erase(it[1]);
			_blocks.erase(it); 
			break;
		}
		case OP_SUB:
		{
			it[-1]->getRhnum() -= it[1]->getRhnum();
			_blocks.erase(it[1]);
			_blocks.erase(it); 
			break;
		}
		case OP_MUL:
		{
			it[-1]->getRhnum() *= it[1]->getRhnum();
			_blocks.erase(it[1]);
			_blocks.erase(it); 
			break;
		}
		case OP_DIV:
		{
			if (it[1]->getRhnum() == 0)
				throw CalcException::Divide0Excep();
			it[-1]->getRhnum() += it[1]->getRhnum();
			_blocks.erase(it[1]);
			_blocks.erase(it); 
			break;
		}
		case OP_POW:
		{
			it[-1]->getRhnum() = pow(it[-1]->getRhnum(), it[1]->getRhnum());
			_blocks.erase(it[1]);
			_blocks.erase(it); 
			break;
		}
		case OP_SQR:
		{
			if (it[1]->getRhnum() < 0)
				throw CalcException::NonRealExcep();
			it->getRhnum() = sqrt(it[1]->getRhnum());
			it->setOp() = OP_NONE;
			_blocks.erase(it[1]);
			break;
		}
		case OP_SQRM:
		{
			if (it[1]->getRhnum() < 0)
				throw CalcException::NonRealExcep();
			it->getRhnum() = sqrt(it[1]->getRhnum()) * -1;
			it->setOp() = OP_NONE;
			_blocks.erase(it[1]);
			break;
		}
	}
}

void	Calc::levelDown()
{
	bool	rhsIsLower;
	bool	lhsIsLower;
	list<Block>::iterator it = _blocks.begin();

	if (_blocks.size() > 1)
	{
		while (it != _blocks.end())
		{
			lhsIsLower = false;
			if (it == _blocks.begin() || it[-1]->getLevel() < it->getLevel())
				lhsIsLower = true;
			rhsIsLower = false;
			if (it[1] == _blocks.end() || it[1]->getLevel() < it->getLevel())
				rhsIsLower = true;
			if (lhsIsLower == true && rhsIsLower == true)
			{
				it->setLevel(it->getLevel - 1)
				it = _blocks.begin();
			}
			else
				it++;
		}
	}
}

void	Calc::coutAnswer() const
{
	cout << "La reponse est: " << _blocks.begin()->getRhnum() << endl;
}

void	Calc::coutDemarche() const
{
	list<Block>::iterator last_it;
	int level_offset;
	
	for (list<Block>::iterator it = _blocks.begin(); it != _blocks.end(); it++)
	{
		if (it != _blocks.begin())
		{
			next_it = it - 1;
			level_offset = 0;
			if (it->getOp() >= OP_SQR)
				level_offset++;
			while (next_it->getLevel() + level_offset != it->getLevel())
			{
				if (next_it->getLevel() + level_offset < it->getLevel())
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
		if (it->getOp() == OP_NONE)
			cout << it->getRhnum() << " ";
		else
			cout << _operator_list[it->getOp()] << " ";
	}
	cout << endl;
}