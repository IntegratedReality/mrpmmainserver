#include "ItemManager.h"

using namespace std;

void ItemManager::init() {

}

void ItemManager::update() {
	for (int i = 0; i < items.size(); i++) {
		items[i]->update();
		if (items[i]->getDeleteFlag()) {
			delete items[i];
			items.erase(items.begin() + i);
		}
	}
}

void ItemManager::draw() {
	for (auto item : items) {
		item->draw();
	}
}

void ItemManager::makeItem(Position _pos, EItem _item) {
	Item *p = new Item();
	p->init(_pos, _item);
	items.push_back(p);
}
