#pragma once

namespace ceaihack::utils {
	template<class T>
	class memptr_list {
	public:
		memptr_list() {}

		memptr_list(uintptr_t base_address) {
			base_addy = base_address;
			if(base_addy != NULL)
				length = *(int*)(base_addy + 0xc);
		}

		bool is_valid() {
			return base_addy != NULL && length >= 0;
		}

		T operator[](int index) {
			if (index < 0 || index > length) index = 0;

			auto list_ptr = *(uintptr_t*) (base_addy + 0x4);

			if (list_ptr != NULL) {
				auto type_ptr = *(uintptr_t*) (list_ptr + 0x8 + 0x4 * index);
				if (type_ptr != NULL)
					return T(type_ptr);
			}

			return T(0);
		}

		int length = 0;
	private:
		uintptr_t base_addy = NULL;
	};

	template<class T>
	memptr_list<T> make_memptr_list(uintptr_t address) {
		return memptr_list<T>(address);
	}
}