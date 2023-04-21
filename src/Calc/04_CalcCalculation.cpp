#include "Calc.hpp"

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

//selon l'operation execute les bonnes commande et supprime les block executer.
// Conserve le resultat dans le block de left side
void	Calc::operation()
{
	list<Block>::iterator it = getHigherOperation();
	list<Block>::iterator prev_it = prev(it);
	list<Block>::iterator next_it = next(it);
	
	if (it->getOp() != OP_NONE)
	{
		if (it->getOp() < OP_SQR)
		{
			switch	(it->getOp())
			{
				case OP_ADD:
					prev_it->setNum(prev_it->getNum() + next_it->getNum());
					break;

				case OP_SUB:
					prev_it->setNum(prev_it->getNum() - next_it->getNum());
					break;

				case OP_MUL:
					prev_it->setNum(prev_it->getNum() * next_it->getNum());
					break;

				case OP_DIV:
					if (next_it->getNum() == 0)
						throw CalcException::Divide0Excep();
					prev_it->setNum(prev_it->getNum() / next_it->getNum());
					break;

				case OP_POW:
					prev_it->setNum(pow(prev_it->getNum(), next_it->getNum()));
					break;
			}
			_blocks.erase(it);
		}
		else
		{
			if (next_it->getNum() < 0)
					throw CalcException::NonRealExcep();
			if (it->getOp() == OP_SQR)
				it->setNum(sqrt(next_it->getNum()));
			else
				it->setNum(sqrt(next_it->getNum()) * -1);
			it->setOp(OP_NONE);
		}
		_blocks.erase(next_it);
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
			cout << it->getNum() << " ";
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
