#include <wx/wx.h>
#include "MainFrame.h"

class ComputerAccessControllerApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(ComputerAccessControllerApp);

bool ComputerAccessControllerApp::OnInit() {
    MainFrame* frame = new MainFrame();
    frame->Show(true);
    return true;
}
