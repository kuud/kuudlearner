#pragma once
#include <string>

#import <mscorlib.tlb> raw_interfaces_only \
    	high_property_prefixes("_get","_put","_putref") \
    	rename("ReportEvent", "InteropServices_ReportEvent") \
	    rename("or", "InteropServices_or")

using namespace mscorlib;

namespace ceaihack::clr {
	class method {
	public:
		method(_MethodInfoPtr method);

		std::wstring get_name();
		variant_t invoke(const std::initializer_list<variant_t>& arguments, variant_t instance = {});
	private:
		_MethodInfoPtr this_method;
	};
}