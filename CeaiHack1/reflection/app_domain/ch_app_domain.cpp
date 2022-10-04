#include "ch_app_domain.h"
#include <iostream>

using namespace ceaihack::clr;

app_domain::app_domain() {
	CLRCreateInstance(CLSID_CLRMetaHost, IID_PPV_ARGS(&itx_clr_metahost));
	itx_clr_metahost->GetRuntime(L"v4.0.30319", IID_PPV_ARGS(&itx_clr_runtime));
	itx_clr_runtime->GetInterface(CLSID_CorRuntimeHost, IID_PPV_ARGS(&if_clr_runtime));
	if_clr_runtime->Start();
}

app_domain::~app_domain() {
	if_clr_runtime->Stop();
}

assembly app_domain::get_assembly(const std::wstring_view signature) {
	auto assemblies = this->get_assemblies();

	for (auto& it : assemblies) {
		if (it.get_name().find(signature) != std::string::npos) {
			std::wcout << "assembly found from signature: " << signature << std::endl;
			return assembly(it);
		}
	}

	return assembly({});
}

std::vector<assembly> app_domain::get_assemblies() {
	SAFEARRAY* sa_assemblies;
	get_def_domain()->GetAssemblies(&sa_assemblies);

	safe_array assemblies = safe_array(sa_assemblies);
	std::vector<assembly> ret;

	for (auto i = 0; i < assemblies.element_count(); i++) {
		_AssemblyPtr curr_assembly = assemblies.get_values<_AssemblyPtr>()[i];
		ret.push_back(curr_assembly);
	}

	return ret;
}

_AppDomainPtr app_domain::get_def_domain() {
	IUnknownPtr def_app_domain;
	_AppDomainPtr domain;

	if_clr_runtime->GetDefaultDomain(&def_app_domain);
	def_app_domain->QueryInterface(&domain);

	return domain;
}