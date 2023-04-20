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
	//cout << __FUNCTION__ << endl;
	while (_blocks.begin() != _blocks.end())
		_blocks.erase(_blocks.begin());
}

//remove space at the front and back of command
void	Calc::trimSpaceFB(string& command_ref)
{
	//cout << __FUNCTION__ << endl;
	command_ref.erase(0, command_ref.find_first_not_of(" "));
	command_ref.erase(command_ref.find_last_not_of(" ") + 1);
}

void	Calc::calculatorLoop()
{
	//cout << __FUNCTION__ << endl;
	
	string	command;
	
	while (command != "EXIT" && command != "QUIT")
	{
		cout << WHITE << "> ";
		getline(cin, command);
		cout << COLORDEF;
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
				calculationLoop();
				coutAnswer();
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
	//cout << __FUNCTION__ << endl;
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
	if (level != 0)
		throw CalcException::SyntaxExcep();			
}

bool	Calc::textCommand(const string& command) const
{
	//cout << __FUNCTION__ << endl;
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
	//cout << __FUNCTION__ << endl;
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

bool	Calc::isAns(const string& command, const int& level, size_t& i_ref)
{
	//cout << __FUNCTION__ << endl;
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
	//cout << __FUNCTION__ << endl;
	while (i_ref < command.length() && command.at(i_ref) == ' ')
		i_ref++;
}


bool	Calc::isParenthese(const string& command, int& level_ref, size_t& i_ref)
{
	//cout << __FUNCTION__ << endl;
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
	//cout << __FUNCTION__ << endl;
	for (int i_op = 1; i_op < NB_OP_LIST; i_op++)
	{
		if (i_ref + _operator_list[i_op].length() < command.length()
			&& command.substr(i_ref, _operator_list[i_op].length()) == _operator_list[i_op])
		{
			//cout << "token operation OP:" << i_op << endl;
			_blocks.back().setOp(i_op);
			_blocks.back().setLevel(level_ref);
			if(i_op >= OP_SQR)
			{
				//cout << "is a sqrt" << endl;
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
	//cout << __FUNCTION__ << endl;
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

//Error case
//1) operator with number lower level -> (2 +)2
//2) two simultaneous operator that is not exception -> +-3
//3) finish with operator -> 2+2+
void	Calc::tokenParsing()
{
	//cout << __FUNCTION__ << endl;
	list<Block>::iterator it = _blocks.begin();
	list<Block>::iterator prev_it;
	list<Block>::iterator next_it;
	while (it != _blocks.end())
	{
		//sleep(1);
		next_it = next(it);
		if (it == _blocks.begin())
		{
			//cout << "check for first if operation" << endl;
			if (it->getOp() > OP_NONE && it->getOp() < OP_SQR)
			{
				//cout << "pas un chiffre au debut" << "it->getOp():" << it->getOp() << endl;
				if (exceptionTwoOp(it) == false)
					throw CalcException::SyntaxExcep();
			}
		}
		else if (next_it == _blocks.end())
		{
			//cout << "check for last if operation" << endl;
			if (it->getOp() != OP_NONE)
				throw CalcException::SyntaxExcep();
		}
		else
		{
			//cout << "middle check" << endl;
			if (it->getOp() != OP_NONE)
			{
				
				prev_it = prev(it);
				if ((prev_it->getOp() == OP_NONE && prev_it->getLevel() < it->getLevel())
					&& (next_it->getOp() == OP_NONE && next_it->getLevel() < it->getLevel()))
					throw CalcException::SyntaxExcep();
				if (it->getOp() < OP_SQR && !(it->getOp() == OP_SUB && next_it->getOp() == OP_SQR))
				{
					if (it->getOp() != OP_NONE && next_it->getOp() != OP_NONE)
					{
						//cout << "deux operations consecutives" << endl;
						if (exceptionTwoOp(it) == false)
							throw CalcException::SyntaxExcep();
					}
				}
			}
		}
		it++;
	}
}

//return true if need to skip first it
bool	Calc::exceptionTwoOp(list<Block>::iterator it)
{
	//cout << __FUNCTION__ << endl;
	list<Block>::iterator next_it = next(it);
	//coutBlocks();
	//cout << "exeption for it->getOp:" << it->getOp() << endl;
	if (it->getLevel() != next_it->getLevel())
		return false;
	//cout << "same level" << endl;
	//case1: -sqrt
	if (it->getOp() == OP_SUB && next_it->getOp() == OP_SQR && next_it->getSpaceBefore() == false)
	{
		sqrtmMerge(it);
		return true;
	}
	
	list<Block>::iterator next2_it = next(next_it);
	
	if (it != _blocks.begin() && it->getOp() != OP_NONE && next2_it != _blocks.end()
			&& prev(it)->getLevel() == it->getLevel()
			&& (prev(it)->getOp() == OP_NONE || prev(it)->getOp() >= OP_SQR))
	{
		//cout << "check for case + -sqrt" << endl;
		//case2:+ -sqrt
		if (next_it->getOp() == OP_SUB && next2_it->getOp() == OP_SQR 
				&& next2_it->getSpaceBefore() == false)
		{
			cout << "sqrtmerge" << endl;
			sqrtmMerge(next_it);
			return true;
		}
		
		//case3:+ -2
		//cout << "check for case + -2" << endl;
		if (next_it->getOp() == OP_SUB && next2_it->getOp() == OP_NONE)
		{
			//cout << "negativeNumMerge" << endl;
			negativeNumMerge(next_it);
			return true;
		}
	}

	return false;
}

void	Calc::sqrtmMerge(list<Block>::iterator it)
{
	//cout << __FUNCTION__ << endl;
	list<Block>::iterator next_it = next(it);
	it->setOp(7);
	_blocks.erase(next_it);
}

void	Calc::negativeNumMerge(list<Block>::iterator it)
{
	//cout << __FUNCTION__ << endl;
	list<Block>::iterator next_it = next(it);
	it->setOp(OP_NONE);
	it->setRhnum(next_it->getRhnum() * -1);
	_blocks.erase(next_it);
}

//Insert une multiplication entre deux nombre qui ne sont pas au meme level
// au level le plus bas
void	Calc::addParentheseMultiplication()
{
	//cout << __FUNCTION__ << endl;
	list<Block>::iterator next_it;
	for (list<Block>::iterator it = _blocks.begin(); next(it) != _blocks.end(); it++)
	{
		next_it = next(it);
		if (it->getOp() == 0 && next_it->getOp() == 0
				&& it->getLevel() != next_it->getLevel())
		{
			Block newMultBlock;
			newMultBlock.setOp(OP_MUL);
			//cout << "before deciding level side it->getLevel:" << it->getLevel() << " next_it->getLevel:" << next_it->getLevel() << endl;
			//coutBlocks();
			if (it->getLevel() < next_it->getLevel())
			{
			//	cout << "it choice" << endl;
				newMultBlock.setLevel(it->getLevel());
			}
			else
			{
			//	cout << "next_it choice" << endl;
				newMultBlock.setLevel(next_it->getLevel());			
			}
			_blocks.insert(next_it, newMultBlock);
			it++;
		}
	}
}

void	Calc::calculationLoop()
{
	//cout << __FUNCTION__ << endl;
	list<Block>::iterator it;

	while (_blocks.size() != 1)
	{
		//coutBlocks();
		operation();
		coutDemarche();
		levelDown();
		//if (_blocks.size() != 1)
			
	}
}

int	Calc::higherLevel()
{
	//cout << __FUNCTION__ << endl;
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
	//cout << __FUNCTION__ << endl;
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

void	Calc::operation()
{
	//cout << __FUNCTION__ << endl;
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
	//cout << __FUNCTION__ << endl;
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
	cout << GREEN << "La reponse est: " << _blocks.begin()->getRhnum() << COLORDEF << endl;
}

void	Calc::coutDemarche()
{
	//cout << __FUNCTION__ << endl;
	//list<Block>::iterator prev_it;
	//list<Block>::iterator next_it;
	//int level_offset;
	int prevLevel = 0;
	
	//coutBlocks();
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