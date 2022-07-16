#include "winnowing.hpp"

winnowingFilter::winnowingFilter(const size_t window_length)
  : window_length(window_length), window_stack_in(window_length), window_stack_out(window_length) {
    window_stat = WINDOW_INITIAL_FILLING;
  }

void winnowingFilter::append(const hash &val) {
  switch (window_stat) {
    case WINDOW_INITIAL_FILLING:
      {
	hash window_prev_min = 0;
	if (window_stack_in.size() > 0)
	  window_prev_min = window_stack_in.min();

	window_stack_in.push(val);
	if (window_stack_in.size() == window_length - 1) {
	  window_stat = WINDOW_OUTPUTING;
	}
      }
      break;
    case WINDOW_OUTPUTING:
      {
	window_stack_in.push(val);
	hash hash_min;
	if (window_stack_out.size() == 0) {
	  while (window_stack_in.size() != 0) {
	    window_stack_out.push(window_stack_in.pop());
	  }
	  hash_min = window_stack_out.min();
	} else {
	  hash_min = min(window_stack_out.min(), window_stack_in.min());
	}
	if (filtered.back() != hash_min) {
	  filtered.push_back(hash_min);
	}
      }
      break;
    default:
      {
	cout << "unexpected stat in function" << __func__ << endl;
	cout << __FILE__ << ':' << __LINE__ << endl;
	exit(EXIT_WINNOWING_UNDEFINED_STATE);
      }
      break;
  }
}

vector<hash> winnowingFilter::into_vec() {
  vector<hash> filtered_vec;
  filtered_vec.swap(filtered);
  return filtered_vec;
}
