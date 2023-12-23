//
// Created by Michael Reid on 8/16/23.
//

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include "wx/log.h"
  	#include "wx/frame.h"
	#include "wx/menu.h"
  	#include "wx/layout.h"
  	#include "wx/msgdlg.h"
  	#include "wx/sizer.h"
#endif

#include "myframe.h"

namespace cybercritter {
    MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Hello World")  {
        auto menuFile = new wxMenu();
        (void)menuFile->Append(static_cast<int32_t>(ID::ID_Hello), "&Hello...\tCtrl-H",
                         "Help string shown in status bar for this menu item");
        (void)menuFile->AppendSeparator();
        (void)menuFile->Append(wxID_EXIT);

        auto menuHelp = new wxMenu;
        (void)menuHelp->Append(wxID_ABOUT);

        auto menuBar = new wxMenuBar;
        (void)menuBar->Append(menuFile, "&File");
        (void)menuBar->Append(menuHelp, "&Help");

        SetMenuBar(menuBar);

        (void)CreateStatusBar();
        SetStatusText("Welcome to wxWidgets!");

        Bind(wxEVT_MENU, &MyFrame::OnHello, this, static_cast<int>(ID::ID_Hello));
        Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
        Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    }

    void MyFrame::OnExit(wxCommandEvent &) {
        (void)Close(true);
    }

    void MyFrame::OnAbout(wxCommandEvent &) {
        (void)wxMessageBox("This is a wxWidgets Hello World example",
                     "About Hello World", wxOK | wxICON_INFORMATION);
    }

    void MyFrame::OnHello(wxCommandEvent &) {
        wxLogMessage("Hello world from wxWidgets!");
    }
}