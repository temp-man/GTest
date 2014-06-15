#include "Febonacci.h"

namespace math
{
	int get_febonacci (int index)
	{
		int prev_value = 1;
		int current_value = 1;

		if (index == 0)
			return prev_value;

		if (index == 1)
			return current_value;

		for (int i = 2; i <= index; i++)
		{
			int next = current_value + prev_value;
			prev_value = current_value;
			current_value = next;
		}

		return current_value;
	}
}