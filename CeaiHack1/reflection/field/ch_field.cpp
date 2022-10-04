#include "ch_field.h"

using namespace ceaihack::clr;

field::field(_FieldInfoPtr field) {
	this->this_field = field;
}

void field::set(variant_t value, variant_t instance) {
	this->this_field->SetValue_2(instance, value);
}

variant_t field::get(variant_t instance) {
	variant_t value;
	this->this_field->GetValue(instance, &value);

	return value;
}

uintptr_t field::get_ptr() {
	//this_field->GetTypeInfo();
	auto b = get();
	return (uintptr_t) b.byref;
}

std::wstring field::get_name() {
	BSTR name;
	this->this_field->get_name(&name);

	return name;
}