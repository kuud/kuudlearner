#pragma once
#include "Windows.h"

namespace ceaihack::utils {
	template<typename T>
	class memptr_var_obf {
	public:
		memptr_var_obf() : memptr_var_obf(0) {}

		memptr_var_obf(uintptr_t base_address) {
			base_addy = base_address;
		}

		T get() {
			int salt = *(int*)(base_addy + 0x08 + sizeof(T));
			return *(T*)(base_addy + 0x08) ^ salt;
		};
	private:
		uintptr_t base_addy;
	};

	template<class T>
	memptr_var_obf<T> make_memptr_var_obf(uintptr_t address) {
		return memptr_var_obf<T>(address);
	}
}