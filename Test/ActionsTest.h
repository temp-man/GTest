#ifndef _ACTIONS_TEST_H_
#define _ACTIONS_TEST_H_

#include <gtest\gtest.h>
#include <tuple>
#include "Actions.h"

namespace calc
{
	namespace test
	{
		static const double ERROR = 0.00005;

		typedef std::tuple<action_type, double, double, double> args_with_result;
		typedef std::tuple<action_type, size_t> args_with_size;

		/// @brief valid params test class.
		class action_valid_args : public testing::TestWithParam<args_with_result> {};

		/// @brief invalid params test class.
		class action_invalid_args : public testing::TestWithParam<args_with_size> {};

		/// @brief valid args for action.
		static const args_with_result should_work_args[] =
		{
			args_with_result (action_type::add, 12, 4, 16),
			args_with_result (action_type::add, 3.3, -5.4, -2.1),
			args_with_result (action_type::sub, 12, 4, 8),
			args_with_result (action_type::sub, 3.3, -5.4, 8.7),
			args_with_result (action_type::mull, 12, 4, 48),
			args_with_result (action_type::mull, 3.3, -5.4, -17.82),
			args_with_result (action_type::div, 12, 4, 3),
			args_with_result (action_type::div, 3.3, -5.4, -0.6111),
		};

		/// @brief invalid args for action.
		static const args_with_size should_throw_exception_args[] =
		{
			args_with_size (action_type::add, 1),
			args_with_size (action_type::add, 3),
			args_with_size (action_type::sub, 1),
			args_with_size (action_type::sub, 3),
			args_with_size (action_type::mull, 1),
			args_with_size (action_type::mull, 3),
			args_with_size (action_type::div, 1),
			args_with_size (action_type::div, 3),
		};

		TEST_P (action_valid_args, should_work)
		{
			action_type type;
			rsize_t size = 2;
			double first, second;
			double expected = 25;
			std::tie(type, first, second, expected) = GetParam ();
			double params[] = { first, second };
			configurable_action<double> *action = create_action<double>(type);

			double result = action->do_action (size, params);

			ASSERT_NEAR(expected, result, ERROR);
			delete action;
		}

		TEST_P (action_invalid_args, should_throw_exception)
		{
			action_type type;
			rsize_t size = 2;
			std::tie (type, size) = GetParam ();
			double *params = new double[size];
			configurable_action<double> *action = create_action<double> (type);

			ASSERT_THROW (action->do_action (size, params), std::invalid_argument);

			delete[] params;
			delete action;
		}

		INSTANTIATE_TEST_CASE_P (actions_test, action_valid_args, testing::ValuesIn (should_work_args));
		INSTANTIATE_TEST_CASE_P (actions_test, action_invalid_args, testing::ValuesIn (should_throw_exception_args));
	}
}

#endif//_ACTIONS_TEST_H_