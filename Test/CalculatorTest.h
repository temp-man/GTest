#ifndef _CALCULATOR_TEST_H_
#define _CALCULATOR_TEST_H_

#include <gtest\gtest.h>
#include <gmock\gmock.h>
#include "Calculator.h"
#include "Actions.h"

using testing::_;

namespace calc
{
	namespace test
	{
		TEST (calculator_test, calculate_should_work)
		{
			action<int> *add_action = create_add_action<int> ();
			calculator<int>  calculator (add_action, nullptr);

			int first = 4;
			int secod = 5;
			int expected = 9;

			int result = calculator.calculate (action_type::add, 4, 5, nullptr);

			ASSERT_EQ (expected, result);
		}

		/// @brief mock for action class.
		class fake_action : public action<int>
		{
		public:
			const static type ID = (1 << sizeof(type)) - 1;
			fake_action () : action (ID) {}
			MOCK_CONST_METHOD2 (do_action, int (size_t, int*));
		};

		TEST (calculator_test, calculate_should_call_action_by_id)
		{
			fake_action *action = new fake_action ();
			calculator<int> calculator (action, nullptr);

			EXPECT_CALL (*action, do_action (_, _)).Times (testing::AtLeast(1));

			calculator.calculate (fake_action::ID, 0, nullptr);
		}
	}
}

#endif//_CALCULATOR_TEST_H_