#pragma once

#include <vector>
#include "Item.h"

class ItemManager {
	public:
		void init();
		void update();
		void draw();

		void makeItem(Position _pos, EItem _item);
	private:
		std::vector<Item*> items;
};
