//
// Created by Michael Reid on 8/16/23.
//

#include "myapp.h"
#include "myframe.h"

namespace cybercritter {
    bool MyApp::OnInit()
    {
        MyFrame *frame = new cybercritter::MyFrame();
        frame->Show(true);
        return true;
    }
} // cybercritter