#pragma once
#include "Plants.h"
class mapBlock : public Plants
{
public:
	mapBlock(int row, int column);
	~mapBlock();

	enum { Type = UserType + 14 };
	int type() const override;

};

