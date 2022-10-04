#include <iostream>

#include "ch_type.h"
#include "../safe_array/ch_safe_array.h"

using namespace ceaihack::clr;

type::type(_TypePtr type) {
	this->this_type = type;
}

std::wstring type::get_name() {
	BSTR name;
	this->this_type->get_FullName(&name);
	return name;
}

std::vector<method> type::get_methods() {
	SAFEARRAY* sa_methods;

	this->this_type->GetMethods(static_cast<mscorlib::BindingFlags>(-1), &sa_methods); // lol

	safe_array methods_array = safe_array(sa_methods);
	std::vector<method> ret;

	for (auto i = 0; i < methods_array.element_count(); i++) {
		method meth = methods_array.get_values<method>()[i];
		ret.push_back(meth);
	}

	return ret;
}

method type::find_method(const std::wstring_view name) {
	const auto types_list = this->get_methods();

	for (auto it : types_list) {
		if (it.get_name() == name) {
			std::wcout << "found method: " << name << std::endl;
			return it;
		}
	}

	return method({});
}

std::vector<field> type::get_fields() {
	SAFEARRAY* sa_fields;

	this->this_type->GetFields(static_cast<mscorlib::BindingFlags>(-1), &sa_fields); // lol

	safe_array fields_array = safe_array(sa_fields);
	std::vector<field> ret;

	for (auto i = 0; i < fields_array.element_count(); i++) {
		field meth = fields_array.get_values<field>()[i];
		ret.push_back(meth);
	}

	return ret;
}

field type::find_field(const std::wstring_view name) {
	const auto fields_list = this->get_fields();

	for (auto it : fields_list) {
		if (it.get_name() == name) {
			std::wcout << "found field: " << name << std::endl;
			return it;
		}
	}

	return field({});
}