#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <microsoft.ui.xaml.window.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

using namespace Microsoft::UI;
using namespace Microsoft::Graphics::Canvas::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Andong_Nation_University::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();

        px = 200;
        py = 200;
        flag = false;
        colorview = true;
        mySize = 16;

        auto windowNative{ this->try_as<::IWindowNative>() };
        HWND hWnd{ 0 };
        windowNative->get_WindowHandle(&hWnd);
        SetWindowPos(hWnd, NULL, 400, 300, 810, 580, NULL);
    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}

struct winrt::Windows::UI::Color mYcol = winrt::Microsoft::UI::Colors::Green();
void winrt::Andong_Nation_University::implementation::MainWindow::Slider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
{
    mySize = e.NewValue();
}


void winrt::Andong_Nation_University::implementation::MainWindow::CanvasControl_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    px = e.GetCurrentPoint(canvas).Position().X;
    py = e.GetCurrentPoint(canvas).Position().Y;
    if (flag) {
        vx.push_back(px);
        vy.push_back(py);
        col.push_back(mYcol);
        size.push_back(mySize);
        canvas.Invalidate();
    }
}


void winrt::Andong_Nation_University::implementation::MainWindow::CanvasControl_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    flag = true;
}


void winrt::Andong_Nation_University::implementation::MainWindow::CanvasControl_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    flag = false;
    px = py = 0.0;
    vx.push_back(px);
    vy.push_back(py);
    col.push_back(mYcol);
    size.push_back(mySize);
}


void winrt::Andong_Nation_University::implementation::MainWindow::CanvasControl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender, winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    int n = vx.size();
    for (int i = 1; i < n; i++) {
        if (vx[i] == 0 && vy[i] == 0) {
            i++; continue;
        }
        args.DrawingSession().DrawLine(vx[i - 1], vy[i - 1], vx[i], vy[i], mYcol, 4);
        args.DrawingSession().FillCircle(vx[i - 1], vy[i - 1], size[i] / 2, col[i]);
        args.DrawingSession().FillCircle(vx[i], vy[i], size[i] / 2, col[i]);
    }
    canvas.Invalidate();
}


void winrt::Andong_Nation_University::implementation::MainWindow::ColorPicker_ColorChanged(winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& sender, winrt::Microsoft::UI::Xaml::Controls::ColorChangedEventArgs const& args)
{
    mYcol = args.NewColor();
}


void winrt::Andong_Nation_University::implementation::MainWindow::newFile_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    vx.clear();
    vy.clear();
    size.clear();
    col.clear();
}


void winrt::Andong_Nation_University::implementation::MainWindow::Save_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    FILE* fw;
    errno_t err = fopen_s(&fw, "C:/Users/1/source/repos/Gallery/saves_txt/1.txt", "w");// +, ccs = UTF - 8");
    if (err == 0)
    {
        int num = vx.size();
        fprintf_s(fw, "%d\n", num);
        for (int i = 0; i < num; i++) {
            fprintf_s(fw, "%f %f %hhu %hhu %hhu %hhu %f\n", vx[i], vy[i],
                col[i].A, col[i].B, col[i].G, col[i].R, size[i]);
        }
        fclose(fw);
    }
}


void winrt::Andong_Nation_University::implementation::MainWindow::Load_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    FILE* fr;
    errno_t err = fopen_s(&fr, "C:/Users/1/source/repos/Gallery/saves_txt/1.txt", "r");// +, ccs = UTF - 8");
    if (err == 0)
    {
        int num;

        float vx1, vy1, size1;
        unsigned char colA, colB, colG, colR;

        fscanf_s(fr, "%d", &num);
        for (int i = 0; i < num; i++) {
            fscanf_s(fr, "%f %f %hhu %hhu %hhu %hhu %f ", &vx1, &vy1, &colA, &colB, &colG, &colR, &size1);
            vx.push_back(vx1);
            vy.push_back(vy1);
            mYcol.A = colA;
            mYcol.B = colB;
            mYcol.G = colG;
            mYcol.R = colR;
            col.push_back(mYcol);
            size.push_back(size1);
        }
        fclose(fr);
    }
}


void winrt::Andong_Nation_University::implementation::MainWindow::ColorPicker_hide_show_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    if (colorview) {
        colorview = false;

        colorP().Visibility(Visibility::Collapsed);

        auto windowNative{ this->try_as<::IWindowNative>() };
        HWND hWnd{ 0 };
        windowNative->get_WindowHandle(&hWnd);
        SetWindowPos(hWnd, NULL, 400, 300, 498, 580, NULL);
    }
    else {
        colorview = true;

        colorP().Visibility(Visibility::Visible);

        auto windowNative{ this->try_as<::IWindowNative>() };
        HWND hWnd{ 0 };
        windowNative->get_WindowHandle(&hWnd);
        SetWindowPos(hWnd, NULL, 400, 300, 810, 580, NULL);
    }
}


void winrt::Andong_Nation_University::implementation::MainWindow::Exit_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    this->Close();
}
