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
	int		level = 0;

	for (size_t i = 0; i < command.length(); i++)
	{
		if (command.at(i) == '(')
		{
			error = true;
			level += 1;
		}
		else if (isdigit(command.at(i)))
			error = false;
		else if (command.at(i) == ')')
		{
			level -= 1;
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

void	Calc::tokenization(const string& command)
{
	size_t i = 0;
	int level = 0;
	Block	blank_block;

	while (i < command.length())
	{
		_blocks.push_back(blank_block);
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

bool	Calc::isAns(const string& command, const int& level, size_t& i_ref)
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

void	Calc::skipSpace(const string& command, size_t& i_ref)
{
	while (command.at(i_ref) == ' ')
		i_ref++;
}


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

bool	Calc::isOperator(const string& command, int& level_ref, size_t& i_ref)
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
					_blocks.back().setSpaceBefore(true);
				level_ref++;
			}
			i_ref += _operator_list[i_op].length();
			return true;
		}
	}
	return false;
}

bool	Calc::isNumber(const string& command, const int& level, size_t& i_ref)
{
	bool	dot = false;
	bool	numBeforeDot = false;
	bool	numAfterDot = false;
	int		i_offset = 0;
	int		len = 0;

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
		_blocks.back().setRhnum(stof(command.substr(i_ref, i_offset)));
		_blocks.back().setLevel(level);
		if (i_ref > 0 && command.at(i_ref - 1) == ' ')
			_blocks.back().setSpaceBefore(true);
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
	list<Block>::iterator prev_it;
	list<Block>::iterator next_it;

	while (it != _blocks.end())
	{
		next_it = next(it);
		if (it == _blocks.begin())
		{
			if (it->getOp() != OP_NONE || it->getOp() != OP_SQR || it->getOp() != OP_SQRM)
			{
				if (exceptionTwoOp(it) == false)
					throw CalcException::SyntaxExcep();
			}
		}
		else if (next_it == _blocks.end())
		{
			if (it->getOp() != OP_NONE)
				throw CalcException::SyntaxExcep();
		}
		else
		{
			if (it->getOp() != OP_NONE)
			{
				prev_it = prev(it);
				if ((prev_it->getOp() == OP_NONE && prev_it->getLevel() < it->getLevel())
					&& (next_it->getOp() == OP_NONE && next_it->getLevel() < it->getLevel()))
					throw CalcException::SyntaxExcep();
				if (next_it->getOp() != OP_NONE && next_it->getOp() != OP_SUB)
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
	list<Block>::iterator next_it = next(it);
	if (it->getOp() == OP_SUB
		&& it->getLevel() == next_it->getLevel()
		&& next_it->getSpaceBefore() == false)
	{
		if (next_it->getOp() == OP_SQR)
		{
			sqrtmMerge(it);
			return true;
		}
		else if (next_it->getOp() == OP_NONE)
		{
			negativeNumMerge(it);
			return true;
		}
	}
	return false;
}

void	Calc::sqrtmMerge(list<Block>::iterator it)
{
	list<Block>::iterator next_it = next(it);
	it->setOp(7);
	_blocks.erase(next_it);
}

void	Calc::negativeNumMerge(list<Block>::iterator it)
{
	list<Block>::iterator next_it = next(it);
	it->setOp(OP_NONE);
	it->setRhnum(next_it->getRhnum() * -1);
	_blocks.erase(next_it);
}

//Insert une multiplication entre deux nombre qui ne sont pas au meme level
// au level le plus bas
void	Calc::addParentheseMultiplication()
{
	list<Block>::iterator next_it;
	for (list<Block>::iterator it = _blocks.begin(); next(it) != _blocks.end(); it++)
	{
		next_it = next(it);
		if (it->getOp() == 0 && next_it->getOp() == 0
				&& it->getLevel() != next_it->getLevel())
		{
			Block newMultBlock;
			newMultBlock.setOp(OP_MUL);
			if (it->getLevel() > next_it->getLevel())
				newMultBlock.setLevel(it->getLevel());
			else
				newMultBlock.setLevel(next_it->getLevel());			
			_blocks.insert(next_it, newMultBlock);
			it++;
		}
	}
}

void	Calc::calculationLoop()
{
	list<Block>::iterator it;

	while (_blocks.size() != 1)
	{
		operation();
		levelDown();
		coutDemarche();
	}
}

int	Calc::higherLevel()
{
	int level = 0;
	for (list<Block>::iterator it = _blocks.begin(); it != _blocks.end(); it++)
	{
		if (it->getLevel() > level)
			level = it->getLevel();
	}
	return level;
}

list<Block>::iterator	Calc::getHigherOperation()
{
	list<Block>::iterator higherOp = _blocks.begin();
	for (list<Block>::iterator it = _blocks.begin(); it != _blocks.end(); it++)
	{
		if ((it->getOp() != OP_NONE && higherOp->getOp() == OP_NONE)
			|| (it->getLevel() >= higherOp->getLevel()
				&& it->getOp() > higherOp->getOp()))
			higherOp = it;
	}
	return higherOp;
}

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

void	Calc::coutAnswer() const
{
	cout << "La reponse est: " << _blocks.begin()->getRhnum() << endl;
}

void	Calc::coutDemarche()
{
	list<Block>::iterator last_it;
	list<Block>::iterator next_it;

	int level_offset;
	
	for (list<Block>::iterator it = _blocks.begin(); it != _blocks.end(); it++)
	{
		if (it != _blocks.begin())
		{
			next_it = prev(it);
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