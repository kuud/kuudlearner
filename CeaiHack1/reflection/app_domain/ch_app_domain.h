#pragma once
#include <string>
#include <vector>
#include <metahost.h>
#include "../assembly/ch_assembly.h"

#import <mscorlib.tlb> raw_interfaces_only \
    	high_property_prefixes("_get","_put","_putref") \
    	rename("ReportEvent", "InteropServices_ReportEvent") \
	    rename("or", "InteropServices_or")

using namespace mscorlib;

namespace ceaihack::clr {
	class app_domain {
	public:
		app_domain();
		~app_domain();

		assembly get_assembly(const std::wstring_view signature);
		std::vector<assembly> get_assemblies();

		_AppDomainPtr get_def_domain();
	private:
		ICorRuntimeHost* if_clr_runtime{};
		ICLRRuntimeInfo* itx_clr_runtime{};
		ICLRMetaHost* itx_clr_metahost{};
	};

}