#pragma once
#include <string>
#include <vector>

#include "../method/ch_method.h"
#include "../field/ch_field.h"

#import <mscorlib.tlb> raw_interfaces_only \
    	high_property_prefixes("_get","_put","_putref") \
    	rename("ReportEvent", "InteropServices_ReportEvent") \
	    rename("or", "InteropServices_or")

using namespace mscorlib;

namespace ceaihack::clr {
	class type {
	public:
		type(_TypePtr type);

		std::wstring get_name();

		std::vector<method> get_methods();
		method find_method(const std::wstring_view name);

		std::vector<field> get_fields();
		field find_field(const std::wstring_view name);
	private:
		_TypePtr this_type;
	};
}