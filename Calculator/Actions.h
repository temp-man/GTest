#ifndef _ACTIONS_H_
#define _ACTIONS_H_

#include "Action.h"
#include <exception>

namespace calc
{
	/// @brief suported actions types.
	enum action_type
	{
		add,
		sub,
		mull,
		div
	};

	/// @brief class realize action by delegate.
	template <typename T>
	class configurable_action : public action<T>
	{
	public:
		typedef T (*processor)(size_t n, T* args);

		configurable_action (type id, processor proc) : action<T> (id)
		{
			action_processor = proc;
		}

		T do_action (size_t n, T* args) const override
		{
			return action_processor (n, args);
		}

	private:
		processor action_processor;
	};

	/// @brief macro generate little factori functions for actions.
#define CREATE_ACTION(name, count, operation) \
	template <typename T> \
	configurable_action<T> *create_##name##_action () \
	{ \
		return new configurable_action<T> (action_type::name, [](size_t n, T* args) \
		{ \
			if (n != (count)) \
				throw std::invalid_argument ("count"); \
			return (operation); \
		}); \
	}

	CREATE_ACTION (add, 2, args[0] + args[1])

	CREATE_ACTION (sub, 2, args[0] - args[1])

	CREATE_ACTION (mull, 2, args[0] * args[1])

	CREATE_ACTION (div, 2, args[0] / args[1])

	/// @brief factory method for actions.
	template <typename T>
	configurable_action<T> *create_action (action_type type)
	{
		switch (type)
		{
			case calc::add:
				return create_add_action<T> ();
				break;
			case calc::sub:
				return create_sub_action<T> ();
				break;
			case calc::mull:
				return create_mull_action<T> ();
				break;
			case calc::div:
				return create_div_action<T> ();
				break;
			default:
				throw std::invalid_argument("type");
				break;
		}
	}
}

#endif//_ACTIONS_H_