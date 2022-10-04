#pragma once
#include "Windows.h"

namespace ceaihack::utils {
	template<typename T>
	class memptr_var {
	public:
		memptr_var() {}

		memptr_var(uintptr_t base_address) {
			base_addy = base_address;
		}

		T get() {
			return *(T*)base_addy;
		};

		T& operator=(const T& other) {
			*(T*)base_addy = other;
			return *(T*)base_addy;
		};

	private:
		uintptr_t base_addy;
	};

	template<class T>
	memptr_var<T> make_memptr_var(uintptr_t address) {
		return memptr_var<T>(address);
	}
}