
#ifndef _WXRAYTRACER_H_
#define _WXRAYTRACER_H_

/**
 * Ray Tracer skeleton
 *
 * Author : Sverre Kvaale <sverre@kvaale.com>
 * Version: 0.8
 *
 */

#include <wx/wx.h>
#include "World.h"
#include <vector>

using namespace std;


class wxraytracerFrame;
class RenderCanvas;
class RenderThread;
class RenderPixel;

class wxraytracerapp : public wxApp
{
public:
   virtual bool OnInit();
   virtual int OnExit();
   virtual void SetStatusText(const wxString&  text, int number = 0);

private:
   wxraytracerFrame *frame;
   DECLARE_EVENT_TABLE()
};

class wxraytracerFrame : public wxFrame
{
public:
   wxraytracerFrame(const wxPoint& pos, const wxSize& size);
   
   //event handlers
   void OnQuit( wxCommandEvent& event );
   void OnOpenFile( wxCommandEvent& event );
   void OnSaveFile( wxCommandEvent& event );
   void OnRenderStart( wxCommandEvent& event );
   void OnRenderCompleted( wxCommandEvent& event );
   void OnRenderPause( wxCommandEvent& event );
   void OnRenderResume( wxCommandEvent& event );

private:
   RenderCanvas *canvas; //where the rendering takes place
   wxString currentPath; //for file dialogues
   DECLARE_EVENT_TABLE()
};

//IDs for menu items
enum
{
   Menu_File_Quit = 100,
   Menu_File_Open,
   Menu_File_Save,
   Menu_Render_Start,
   Menu_Render_Pause,
   Menu_Render_Resume
};

class RenderCanvas: public wxScrolledWindow
{
public:
   RenderCanvas(wxWindow *parent);
   virtual ~RenderCanvas(void);
    
   void SetImage(wxImage& image);
   wxImage GetImage(void);
   
   virtual void OnDraw(wxDC& dc);
   void renderStart(void);
   void renderPause(void);
   void renderResume(void);
   void OnRenderCompleted( wxCommandEvent& event );
   void OnTimerUpdate( wxTimerEvent& event );
   void OnNewPixel( wxCommandEvent& event );

protected:
   wxBitmap *m_image;
   World* w;

private:
   RenderThread* thread;
   wxStopWatch* timer;
   long pixelsRendered;
   long pixelsToRender;
   wxTimer updateTimer;
   
   DECLARE_EVENT_TABLE()
};


class RenderPixel
{
public:
   RenderPixel(int x, int y, int red, int green, int blue);

public:
   int x, y;
   int red, green, blue;
};


DECLARE_EVENT_TYPE(wxEVT_RENDER, -1)
#define ID_RENDER_COMPLETED 100
#define ID_RENDER_NEWPIXEL  101
#define ID_RENDER_UPDATE    102

class RenderThread : public wxThread
{
public:
   RenderThread(RenderCanvas* c, World* w) : wxThread(), world(w), canvas(c){}
   virtual void *Entry();
   virtual void OnExit();
   virtual void setPixel(int x, int y, int red, int green, int blue);

private:
   void NotifyCanvas();
   
   World* world;
   RenderCanvas* canvas;
   
   vector<RenderPixel*> pixels;
   wxStopWatch* timer;
   long lastUpdateTime;
};


#endif
