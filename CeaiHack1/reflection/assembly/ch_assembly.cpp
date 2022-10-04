#include "ch_assembly.h"
#include <iostream>

using namespace ceaihack::clr;

assembly::assembly(_AssemblyPtr assembly) {
	this_assembly = assembly;
}

std::wstring assembly::get_name() {
	BSTR name;
	this_assembly->get_FullName(&name);
	return name;
}

std::vector<type> assembly::get_types() {
	SAFEARRAY* sa_types;

	this_assembly->GetTypes(&sa_types);

	safe_array types_array = safe_array(sa_types);
	std::vector<type> ret;

	for (auto i = 0; i < types_array.element_count(); i++) {
		type curr_type = types_array.get_values<type>()[i];
		ret.push_back(curr_type);
	}

	return ret;
}

type assembly::find_type(const std::wstring_view name) {
	const auto types_list = this->get_types();

	for (auto it : types_list) {
		if (it.get_name() == name) {
			std::wcout << "found type: " << name << std::endl;
			return it;
		}
	}

	return type({});
}