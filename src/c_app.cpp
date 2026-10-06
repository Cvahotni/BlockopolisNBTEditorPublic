#include "c_app.h"

cApp::cApp() {

}

cApp::~cApp() {

}

bool cApp::OnInit() {
    mainFrame = new cMain();
    mainFrame->Centre();
    mainFrame->Show(); 

    return true;
}

wxIMPLEMENT_APP(cApp);