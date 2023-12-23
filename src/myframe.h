//
// Created by Michael Reid on 8/16/23.
//

#ifndef NOTEBOOK_MYFRAME_H
#define NOTEBOOK_MYFRAME_H
#include <wx/wx.h>
#include "myframe.h"


namespace cybercritter {
class MyFrame : public wxFrame
    {
    public:
        MyFrame();
        ~MyFrame() = default;

    private:
        void OnHello(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);

        struct tm current_time{};
    };

    enum class ID
    {
        Unknown,
        ID_Hello
    };
}


#endif //NOTEBOOK_MYFRAME_H
