#pragma once

#include <wx/wx.h>
#include <wx/wrapsizer.h>

#include "DrawingCanvas.h"
#include "ColorPane.h"
#include "ShapePane.h"
#include "SizePane.h"
#include "ImagePane.h"
#include "Shape.h"

class Panel : public wxScrolled<wxPanel>
{
public:
	Panel(wxWindow* parent, DrawingCanvas *canvas, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	
	void OnKeyDown(wxKeyEvent& event);
	void OnKeyUp(wxKeyEvent& event);

private:
	void SetupButtons();
	void SetupMouseButtons();
	void SetupColorPanes();
	void SetupSizePanes();	
	void SetupShapePanes();
	void SetupBrushPanes();

	void SelectColorPane(ColorPane* colorPane);
	void SelectSizePane(SizePane* sizePane);
	void SelectSizePane(int size);
	void SelectShapePane(ShapePane* shapePane);
	void SelectBrushPane(ColorPane* brushPane);
	
	enum {
		COLOR = 1,
		SIZE = 2,
		SHAPE = 4,
		BRUSH = 8,
		FUNCTION = 16
	};

	void Layout(int msk);

	void SelectMode(ImagePane* pane);
	void SelectMouse();
	void SelectPaint();
	void SelectShape();
	void SelectText();

private:
	bool shifting;

	int lastMode;
	DrawingCanvas* canvas;

	wxBoxSizer* mainSizer;

	std::vector<ImagePane*> buttonPanes;
	wxWrapSizer* buttonSizer;

	wxStaticText* functionText;
	std::vector<ImagePane*> functionPanes;
	wxWrapSizer* functionSizer;

	std::vector<ColorPane*> colorPanes;
	wxWrapSizer* colorPaneSizer;
	wxStaticText* colorText;
	wxBitmapButton* colorPicker;

	std::vector<ColorPane*> brushPanes;
	wxWrapSizer* brushPaneSizer;
	wxStaticText* brushText;
	wxBitmapButton* brushPicker;

	wxSlider* penSlider;
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

