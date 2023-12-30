#include "Layer.h"

Layer::Layer()
{

}

Layer::~Layer()
{
	auto it = First();
	std::vector<Node<Object*>*> nodes;
	while (it != Tail()) {
		delete it->data;
		it = it->next;
		nodes.push_back(it);
	}
	for (auto node : nodes) {
		delete node;
	}
}

void Layer::Draw(wxGraphicsContext* gc)
{
	auto it = First();
	while (it != Tail()) {
		it->data->Draw(gc);
		it = it->next;
	}
}
