#ifndef EZO_CALCULATOR
# define EZO_CALCULATOR

# define NB_OP_LIST 8

enum operator_e
{
	OP_NONE = 0,
	OP_ADD = 1,		// addition					+
	OP_SUB = 2,		// substraction				-
	OP_MUL = 3,		// multiplication			* or () with no operator
	OP_DIV = 4,		// division					/
	OP_POW = 5,		// power					^
	OP_SQR = 6,		// square root				sqrt(
	OP_SQRM = 7,	// square root minus		-sqrt(
};

#include "colors.hpp"
#include "../src/Block/Block.hpp"
#include "../src/Calc/CalcException.hpp"
#include "../src/Calc/Calc.hpp"

#endif