#pragma once

#include <wx/wx.h>
#include<wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/splitter.h>

#include "Path.h"
#include "List.h"

class Layer : public List<Path*>
{
public:
	Layer();
	~Layer();

	void Draw(wxGraphicsContext* gc);
};

