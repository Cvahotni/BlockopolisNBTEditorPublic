#pragma once

#include "wx/wx.h"
#include "c_main.h"

class cApp : public wxApp {
public:
    cApp();
    ~cApp();

    virtual bool OnInit() override;

private:
    cMain* mainFrame = nullptr;
};