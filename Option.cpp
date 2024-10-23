#pragma once
#include <iostream>
#include "Option.h"

Option::Option(double expiry) {
	_expiry = expiry;
}

double Option::GetExpiry() const {
	return _expiry;
}