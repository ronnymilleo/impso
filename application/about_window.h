#pragma once

#include "window_interface.h"

class AboutWindow : public IWindowInterface
{
public:
    AboutWindow();
    ~AboutWindow() override = default;

    void Create() override;
    void Destroy() override;
    void DrawContents() override;
    void Show() override;
    void Hide() override;
};
