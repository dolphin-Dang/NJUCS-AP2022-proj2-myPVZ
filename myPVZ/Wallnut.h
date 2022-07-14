#pragma once

#include "Plants.h"
#include <qpoint.h>

class Wallnut : public Plants
{
public:
	Wallnut(int row,int column);
	~Wallnut();

	enum { Type = UserType + 11 };
	int type() const override;
	void advance(int phase);
};
