#pragma once
#include <string>
#include "repository.h"
using namespace std;

class DTO {

public:
	string tip = {};
	string denumire = {};
	DTO(string _tip) :tip{ _tip } {

	}
	DTO() = default;
	DTO(const DTO& ot) = default;

	~DTO() = default;
	DTO(DTO&&) = default;
	DTO& operator=(DTO&&) = default;

	bool operator==(const DTO& ot) noexcept;
	int count = 0;
};