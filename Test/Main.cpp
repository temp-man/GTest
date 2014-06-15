#include <gtest/gtest.h>
#include "FebonacciTest.h"
#include "CalculatorTest.h"
#include "ActionsTest.h"

int main (int argc, char **argv)
{
	testing::InitGoogleTest (&argc, argv);
	int result = RUN_ALL_TESTS();
	return result;
}