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
		TEST (febonacci, should_work)
		{
			int index = 4;
			int expected = 5;

			int result = get_febonacci (index);

			ASSERT_EQ (result, expected);
		}

		// param test
		typedef std::pair<int, int> pair;

		class febonacci_param_test : public testing::TestWithParam<pair> {};

		TEST_P (febonacci_param_test, range_test)
		{
			pair params = GetParam ();

			int result = get_febonacci (params.first);

			ASSERT_EQ (result, params.second);
		}

		static std::pair<int, int> data[] =
		{
			pair (0, 1),
			pair (1, 1),
			pair (2, 2),
			pair (3, 3),
			pair (5, 8),
			pair (10, 89)
		};
		INSTANTIATE_TEST_CASE_P (febonacci_test_params, febonacci_param_test, testing::ValuesIn (data));
	}
}

#endif//_FEBONACCI_TEST_H_