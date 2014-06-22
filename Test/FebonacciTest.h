#ifndef _FEBONACCI_TEST_H_
#define _FEBONACCI_TEST_H_

#include <utility>
#include <gtest\gtest.h>
#include "Febonacci.h"

namespace math
{
	namespace test
	{
		// usual test
		TEST (febonacci_test, should_work)
		{
			int index = 4;
			int expected = 5;

			int result = get_febonacci (index);

			ASSERT_EQ (result, expected);
		}

		// param test

		typedef std::pair<int, int> pair;

		/// @brief param test class.
		class febonacci_sequence : public testing::TestWithParam<pair> {};

		TEST_P (febonacci_sequence, should_be_expected)
		{
			pair params = GetParam ();

			int result = get_febonacci (params.first);

			ASSERT_EQ (result, params.second);
		}

		/// @brief params for testing args with expected result.
		static std::pair<int, int> data[] =
		{
			pair (0, 1),
			pair (1, 1),
			pair (2, 2),
			pair (3, 3),
			pair (5, 8),
			pair (10, 89)
		};
		INSTANTIATE_TEST_CASE_P (febonacci_test, febonacci_sequence, testing::ValuesIn (data));
	}
}

#endif//_FEBONACCI_TEST_H_