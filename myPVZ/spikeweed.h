#pragma once

#include "Plants.h"
#include <qpoint.h>

class Spikeweed : public Plants
{
public:
	Spikeweed(int row, int column);
	~Spikeweed();

	enum { Type = UserType + 15 };
	int type() const override;
	void advance(int phase);
};
