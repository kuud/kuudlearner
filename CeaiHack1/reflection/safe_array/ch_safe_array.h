#pragma once
#include <initializer_list>
#include <tuple>
#include <vector>
#include <memory>

#import <mscorlib.tlb> raw_interfaces_only \
    	high_property_prefixes("_get","_put","_putref") \
    	rename("ReportEvent", "InteropServices_ReportEvent") \
	    rename("or", "InteropServices_or")

namespace ceaihack::clr {
	class safe_array {
	public:
		safe_array(const std::initializer_list<variant_t>& elements, unsigned short variant = VT_VARIANT);
		safe_array(SAFEARRAY* psa);
		~safe_array();

		std::tuple<long, long> get_bounds();
		int element_count();

		void get_element(int idx, void* value);
		void set_element(int idx, void* value);

		SAFEARRAY* get_array();

		template <typename T>
		T* get_values() {
			T* values;
			SafeArrayAccessData(itx_array, reinterpret_cast<void**>(&values));

			return values;
		}
	private:
		SAFEARRAY* itx_array;
	};
}