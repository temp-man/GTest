#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include "Action.h"
#include <map>
#include <memory>
#include <algorithm>

namespace calc
{
	/// @brief calculator class.
	template <typename T>
	class calculator
	{
	public:
		typedef typename action<T>::type a_type;
		typedef action<T>* p_action;

		calculator (p_action p_actions, ...);
		calculator (calculator<T>  &other);
		calculator (calculator<T>  &&other) : map (std::move (other)) {}
		~calculator ();

		calculator<T> &operator= (calculator<T> &calculator);
		calculator<T> &operator= (calculator<T> &&calculator);

		/// @brief perfom action on args.
		/// @param id action id.
		/// @param args arguments.
		T calculate (a_type id, T args, ...);

	private:
		std::map<a_type, p_action> actions;

		class args_wrapper
		{
		public:
			args_wrapper (T &args, ...);
			~args_wrapper () { delete[] args; }

			T *get_args () const { return args; }

			size_t get_size () const { return size; }

		private:
			T* args;
			size_t size;
		};
	};

	template <typename T>
	calculator<T>::args_wrapper::args_wrapper (T &args, ...) : size (0)
	{
		T* p_arg = &args;

		while (*p_arg++)
			size++;

		this->args = new T[size];
		memcpy (this->args, &args, sizeof(T) * size);
	}
	
	template <typename T>
	calculator<T>::calculator (typename calculator<T>::p_action actions, ...)
	{
		p_action *p_actions = &actions;
		while (*p_actions)
		{
			p_action action = *p_actions++;
			this->actions[action->get_id()] = action;
		}
	}

	template <typename T>
	calculator<T>::~calculator ()
	{
		std::for_each (actions.begin (), actions.end (), [](std::pair<a_type, p_action> pair) 
		{ 
			delete pair.second; 
		});
	}

	template <typename T>
	calculator<T>& calculator<T>::operator= (calculator<T> &&other)
	{
		if (this != &other)
		{
			this->actions.clear ();
			std::swap (this->actions, other.actions);
		}
		return *this;
	}

	template <typename T>
	T calculator<T>::calculate (typename calculator<T>::a_type id, T args, ...)
	{
		args_wrapper args_array (args);
		return actions[id]->do_action (args_array.get_size(), args_array.get_args());
	}
}

#endif//_CALCULATOR_H_