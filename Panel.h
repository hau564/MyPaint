#pragma once

#include <wx/wx.h>
#include <wx/wrapsizer.h>

#include "DrawingCanvas.h"
#include "ColorPane.h"
#include "ShapePane.h"
#include "SizePane.h"
#include "Shape.h"

class Panel : public wxScrolled<wxPanel>
{
public:
	Panel(wxWindow* parent, DrawingCanvas *canvas, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	
private:
	void SetupButtons();
	void SetupColorPanes();
	void SetupSizePanes();	
	void SetupShapePanes();
	void SetupBrushPanes();

	void SelectColorPane(ColorPane* colorPane);
	void SelectSizePane(SizePane* sizePane);
	void SelectShapePane(ShapePane* shapePane);
	void SelectBrushPane(ColorPane* brushPane);
	
	enum {
		COLOR = 1,
		SIZE = 2,
		SHAPE = 4,
		BRUSH = 8
	};

	void Layout(int msk);

	void SelectMouse();
	void SelectPaint();
	void SelectShape();

private:
	DrawingCanvas* canvas;

	wxBoxSizer* mainSizer;

	wxButton* mouseButton;
	wxButton* paintButton;	
	wxButton* shapeButton;	
	wxWrapSizer* buttonSizer;

	std::vector<ColorPane*> colorPanes;
	wxWrapSizer* colorPaneSizer;
	wxStaticText* colorText;
	wxBitmapButton* colorPicker;

	std::vector<ColorPane*> brushPanes;
	wxWrapSizer* brushPaneSizer;
	wxStaticText* brushText;
	wxBitmapButton* brushPicker;

	std::vector<SizePane*> sizePanes;
	wxWrapSizer* sizePaneSizer;
	wxStaticText * sizeText;

	std::vector<ShapePane*> shapePanes;
	wxWrapSizer* shapePaneSizer;
	wxStaticText * shapeText;


	const std::vector<std::string> niceColors = 
		{	"#000000", "#ffffff", "#fd7f6f",
			"#7eb0d5", "#b2e061", "#bd7ebe",
			"#ffb55a", "#ffee65", "#fdcce5" };

};

