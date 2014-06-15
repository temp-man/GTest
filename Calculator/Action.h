#ifndef _ACTION_H_
#define _ACTION_H_

namespace calc
{
	/// @brief represents action.
	template <typename T>
	class action
	{
	public:
		typedef unsigned char type;

		action (type id) : id (id) {}
		virtual ~action () {} 

		/// @brief do action.
		/// @param n count of arguments.
		/// @param args arguments.
		virtual T do_action (size_t n, T* args) const = 0;

		/// @brief get id of action.
		/// @return id.
		type get_id () { return id; }

	private:
		type id;
	};
}

#endif//_ACTION_H_