#pragma once
#include <string>

#include "../safe_array/ch_safe_array.h"
#include "../type/ch_type.h"

#import <mscorlib.tlb> raw_interfaces_only \
    	high_property_prefixes("_get","_put","_putref") \
    	rename("ReportEvent", "InteropServices_ReportEvent") \
	    rename("or", "InteropServices_or")

using namespace mscorlib;

namespace ceaihack::clr {
	class assembly {
	public:
		assembly(_AssemblyPtr assembly);

		std::wstring get_name();
		std::vector<type> get_types();
		type find_type(const std::wstring_view name);
	private:
		_AssemblyPtr this_assembly;
	};
}