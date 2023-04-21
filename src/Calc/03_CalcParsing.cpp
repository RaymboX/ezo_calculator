#include "Calc.hpp"

//Toutes les etapes de parsing
void	Calc::parsing(const string& command)
{
	validParenthese(command);
	tokenization(command);
	addParentheseMultiplication();
	ParseNegativeNumber();
	tokenParsing();
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

//detecte si ans, set le dernier _blocks
bool	Calc::isAns(const string& command, const int& level, size_t& i_ref)
{
	if (command.substr(i_ref, 3) == "ans")
	{
		//cout << "token ans" << endl;
		_blocks.back().setNum(_ans);
		_blocks.back().setOp(OP_NONE);
		_blocks.back().setLevel(level);
		if (i_ref > 0 && command.at(i_ref - 1) == ' ')
			_blocks.back().setSpaceBefore(true);
		i_ref += 3;
		return true;
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
		_blocks.back().setNum(stof(command.substr(i_ref, len)));
		_blocks.back().setLevel(level);
		if (i_ref > 0 && command.at(i_ref - 1) == ' ')
			_blocks.back().setSpaceBefore(true);
	}
	i_ref += len;
	return numBeforeDot;
}

//modifie le i_ref pour pointer sur le prochain char qui n'est pas space
// ou arrete au dernier
void	Calc::skipSpace(const string& command, size_t& i_ref)
{
	while (i_ref < command.length() && command.at(i_ref) == ' ')
		i_ref++;
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
// + si negatif devant parenthese en debut de command
void	Calc::ParseNegativeNumber()
{
	int index = 0;
	for (list<Block>::iterator it = _blocks.begin(); it != _blocks.end() && next(it) != _blocks.end(); it++)
	{
		if (it->getOp() == OP_SUB)
		{
			if (it == _blocks.begin()
					&& (next(it)->getOp() == OP_NONE || next(it)->getOp() >= OP_SQR)
					&& it->getLevel() < next(it)->getLevel())
				negativeParenthese(it);
			else if (next(it)->getSpaceBefore() == false
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

//remplace  -(  a _blocks.begin() par  -1*(
void	Calc::negativeParenthese(list<Block>::iterator it)
{
	Block	temp_num;
	temp_num.setNum(-1);
	temp_num.setLevel(it->getLevel());
	_blocks.insert(it, temp_num);
	Block	temp_sub;
	it->setOp(OP_MUL);
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
	it->setNum(next_it->getNum() * -1);
	_blocks.erase(next_it);
}

//Verifie si l'ordre des tokens (block) est bon (nombre - operateur - nombre...)
// (petites exceptions pour sqrt())
void	Calc::tokenParsing()
{
	list<Block>::iterator it = _blocks.begin();
	if ((it->getOp() > OP_NONE && it->getOp() < OP_SQR) 
		|| (next(it) != _blocks.end() && 
			it->getOp() == OP_NONE && next(it)->getOp() == OP_NONE))
		throw CalcException::SyntaxExcep();
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
	if (it->getOp() != OP_NONE && it != _blocks.end())
		throw CalcException::SyntaxExcep();
}
