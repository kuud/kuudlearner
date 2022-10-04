#include "ch_method.h"
#include "../safe_array/ch_safe_array.h"

using namespace ceaihack::clr;

method::method(_MethodInfoPtr method) {
	this_method = method;
}

std::wstring method::get_name() {
	BSTR name;
	this_method->get_name(&name);

	return name;
}

variant_t method::invoke(const std::initializer_list<variant_t>& arguments, variant_t instance) {
	variant_t ret;
	safe_array sa_arguments = safe_array(arguments);

	this_method->Invoke_3(instance, sa_arguments.get_array(), &ret);
	return ret;
}