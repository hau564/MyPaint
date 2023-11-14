#include "DrawingCanvas.h"

DrawingCanvas::DrawingCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
	:wxWindow(parent, id, pos, size)
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::onMouseDown, this);
	this->Bind(wxEVT_LEFT_UP, &DrawingCanvas::onMouseUp, this);
	this->Bind(wxEVT_MOTION, &DrawingCanvas::onMouseMove, this);
	this->Bind(wxEVT_PAINT, &DrawingCanvas::onPaint, this);
	this->Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::onMouseUp, this);
	
	layers.push_back(new Layer());
	activeLayer = layers[0];
}

void DrawingCanvas::SetExplorer(Explorer* explorer)
{
	history = new History(this, explorer);
}

DrawingCanvas::~DrawingCanvas()
{
	while (!layers.empty()) {
		delete layers.back();
		layers.pop_back();
	}
}



void DrawingCanvas::SetPenColor(wxColor color)
{
	penColor = color;
}

void DrawingCanvas::SetPenSize(int size)
{
	penSize = size;
}

void DrawingCanvas::SetMode(int mode)
{
	if (editor) delete editor;
	editor = nullptr;

	switch (mode) {
	case DRAW:
		editor = new EditorDraw(this);
		break;

	case CURSOR:
		std::vector<Path*> paths;
		for (auto layer : layers) {
			auto pathOfLayer = layer->GetVectorData();
			for (auto path : pathOfLayer) {
				paths.push_back(path);
			}
		}
		editor = new EditorMouse(this, paths);
		break;
	}
	Refresh();
}





void DrawingCanvas::OnExport(wxCommandEvent& event)
{
	wxFileDialog saveFileDialog(this, _("Save drawing"), "", "",
		"PNG files (*.png)|*.png|JPEG files (*.jpeg)|*.jpeg", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;

	wxBitmap bitmap(this->GetSize() * this->GetContentScaleFactor());

	wxMemoryDC memDC;

	memDC.SetUserScale(this->GetContentScaleFactor(), this->GetContentScaleFactor());

	memDC.SelectObject(bitmap);
	memDC.SetBackground(*wxWHITE_BRUSH);
	memDC.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(memDC);

	if (gc)
	{
		draw(gc);
		delete gc;
	}

	bitmap.SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_PNG);
	bitmap.SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_JPEG);
}

void DrawingCanvas::OnUndo(wxCommandEvent& event)
{
	history->Undo();
	Refresh();
}

void DrawingCanvas::OnRedo(wxCommandEvent& event)
{
	history->Redo();
	Refresh();
}






void DrawingCanvas::AddPath(Path* path)
{
	if (!activeLayer) return;

	activeLayer->Last()->InsertNext(path);
	history->AddDoneAction(new ActionNewObject<Path*>(activeLayer->Last()));
	Refresh();
}

void DrawingCanvas::AddUndoneAction(Action* action)
{
	history->AddUndoneAction(action);
	Refresh();
}



void DrawingCanvas::onMouseDown(wxMouseEvent& event)
{
	if (editor) {
		editor->OnMouseDown(event);
		Refresh();
	}
}

void DrawingCanvas::onMouseUp(wxMouseEvent& event)
{
	if (editor) {
		editor->OnMouseUp(event);
		Refresh();
	}
}

void DrawingCanvas::onMouseMove(wxMouseEvent& event)
{
	if (editor) {
		editor->OnMouseMove(event);
		Refresh();
	}
}

void DrawingCanvas::onMouseLeave(wxMouseEvent& event)
{
	if (editor) {
		editor->OnMouseLeave(event);
		Refresh();
	}
}

void DrawingCanvas::onKeyDown(wxKeyEvent& event)
{
	if (editor) editor->OnKeyDown(event);
}

void DrawingCanvas::onKeyUp(wxKeyEvent& event)
{
	if (editor) editor->OnKeyUp(event);
}



void DrawingCanvas::draw(wxGraphicsContext* gc)
{
	for (Layer* layer : layers) {
		layer->Draw(gc);
	}
	if (editor) editor->Draw(gc);
}

void DrawingCanvas::onPaint(wxPaintEvent&)
{
	wxAutoBufferedPaintDC dc(this);
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		draw(gc);
		delete gc;
	}
}

