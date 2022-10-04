#pragma once
#include "Windows.h"

namespace ceaihack::osu::utils {
	int deobfuscate_int(uintptr_t address) {
		int salt = *(int*)(address + 0x08 + sizeof(int));
		return *(int*)(address + 0x08) ^ salt;
	}

	double deobfuscate_double(uintptr_t address) {
		int salt = *(int*)(address + 0x08 + sizeof(double));
		return *(double*)(address + 0x08) * (1.0f / salt);
	}

	float deobfuscate_float(uintptr_t address) {
		int salt = *(int*)(address + 0x08 + sizeof(float));
		return *(float*)(address + 0x08) * (1.0f / salt);
	}
}