#include "test_header.hpp"
#include "../src/Calc/Calc.hpp"
#include "../src/Calc/CalcException.hpp"
#include "doctest.h"

#include <iostream>

using namespace std;

string	good_command[] = {
	"",
	"2",
	"1234567890",
	"2+2",
	"2 + 2",
	"-2 + 2",
	"-sqrt(3)",
	"-2--2",
	"-((3)3)",
	"2+3",
	"5 -  8",
	"4*6",
	"10/5",
	"2^ 3",
	"sqrt( 4)",
	"2*(3+4)",
	"(2+  3) *4",
	"2sqrt(9)",
	"4(2 +3)",
	"2^2^3",
	"((2+ 3)^2)/5",
	"(4*sqrt(16 ))/(2 +2)",
};
size_t good_command_size = sizeof(good_command)/sizeof(good_command[0]);

string	errSyntax_command[] = {
	"e",
	"ezo",
	"help",
	"--2",
	"2---2",
	"--sqrt(3)",
	"sqrt(3-)",
	"(3-)",
	"(-3-)",
	"- 2",
	"3 3",
	"3 (*) 3",
	"- sqrt()",
	"(3",
	")(3",
	"((3)"
};
size_t errSyntax_command_size = sizeof(errSyntax_command)/sizeof(errSyntax_command[0]);

string	ezoTest[] = {
	"1+1",
	"1 + 2",
	"1 + -1",
	"-1 - -1",
	"5-4",
	"5*2",
	"(2+5)*3",
	"10/2",
	"2+2*5+5",
	"2.8*3-1",
	"2^8",
	"2^8*5-1",
	"sqrt(4)"
};

// modification de la reponse 1 -> pas 1 mais 2
float ezoAns[] = {
	2,
	3,
	0,
	0,
	1,
	10,
	21,
	5,
	17,
	7.4,
	256,
	1279,
	2
};

TEST_CASE("Calc::parsing")
{
    Calc calculator;
    SUBCASE("NO THROW COMMAND")
    {
        for (size_t i = 0; i < good_command_size; i++)
        {
            CHECK_NOTHROW(calculator.parsing(good_command[i]));
			
            calculator.clearBlocks();
			try
			{
				calculator.parsing(good_command[i]);
			}
			catch (const std::exception& e)
			{
				MESSAGE("Error :" << e.what() << " ---- case: " << good_command[i]);
			}
			calculator.clearBlocks();
        }
    }
	
	SUBCASE("THROW EXCEPTION COMMAND")
    {
        for (size_t i = 0; i < errSyntax_command_size; i++)
        {
            CHECK_THROWS_AS(calculator.parsing(errSyntax_command[i]), const CalcException::SyntaxExcep&);
			
            calculator.clearBlocks();
			try
			{
				calculator.parsing(errSyntax_command[i]);
				cout << "No exception syntax on :" << errSyntax_command[i] << endl;
			}
			catch (const std::exception& e)
			{
				(void)e;
			}
			calculator.clearBlocks();
        }
    }
}

TEST_CASE("Calc::calculationLoop")
{
    Calc calculator;
	SUBCASE("EzoQC tests")
	{
		for (size_t i = 0; i < 13; i++)
		{
			CHECK_NOTHROW(calculator.parsing(ezoTest[i]));
			CHECK_NOTHROW(calculator.calculationLoop());
			CHECK(calculator._blocks.begin()->getNum() == doctest::Approx(ezoAns[i]));
			calculator.clearBlocks();
		}
	}
}