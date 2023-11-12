#include "Layer.h"

Layer::Layer()
{

}

Layer::~Layer()
{
	
}

void Layer::Draw(wxGraphicsContext* gc)
{
	auto it = First();
	while (it != Tail()) {
		it->data->Draw(gc);
		it = it->next;
	}
}
