#pragma once
#include <string>

#import <mscorlib.tlb> raw_interfaces_only \
    	high_property_prefixes("_get","_put","_putref") \
    	rename("ReportEvent", "InteropServices_ReportEvent") \
	    rename("or", "InteropServices_or")

using namespace mscorlib;

namespace ceaihack::clr {
	class field {
	public:
		field(_FieldInfoPtr field);

		void set(variant_t value, variant_t instance = {});
		variant_t get(variant_t instance = {});
		uintptr_t get_ptr();

		std::wstring get_name();

	private:
		_FieldInfoPtr this_field;
	};
}