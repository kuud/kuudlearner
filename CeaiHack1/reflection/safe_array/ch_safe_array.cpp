#include "ch_safe_array.h"

using namespace ceaihack::clr;

safe_array::safe_array(const std::initializer_list<variant_t>& elements, unsigned short variant) {
	SAFEARRAYBOUND bounds;
	bounds.cElements = elements.size();
	bounds.lLbound = 0;

	itx_array = SafeArrayCreate(variant, 1, &bounds);

	variant_t* data{};
	SafeArrayAccessData(itx_array, reinterpret_cast<void**>(&data));

	const auto array_of_elements = std::vector<variant_t>(elements);

	for (size_t i = 0; i < elements.size(); i++)
		*data++ = array_of_elements[i];
}

safe_array::safe_array(SAFEARRAY* psa) {
	itx_array = psa;
}

safe_array::~safe_array() {
	SafeArrayDestroy(itx_array);
}

void safe_array::get_element(int idx, void* value) {
	auto index = std::get<0>(get_bounds()) + idx;

	SafeArrayGetElement(itx_array, &index, value);
}

void safe_array::set_element(int idx, void* value) {
	auto index = std::get<0>(get_bounds()) + idx;

	SafeArrayPutElement(itx_array, &index, value);
}

std::tuple<long, long> safe_array::get_bounds() {
	long upper_bound, lower_bound;

	SafeArrayGetUBound(itx_array, 1, &upper_bound);
	SafeArrayGetLBound(itx_array, 1, &lower_bound);

	return std::make_tuple(upper_bound, lower_bound);
}

int safe_array::element_count() {
	const auto bounds = get_bounds();

	return std::get<0>(bounds) - std::get<1>(bounds) + 1;
}

SAFEARRAY* safe_array::get_array() {
	return itx_array;
}