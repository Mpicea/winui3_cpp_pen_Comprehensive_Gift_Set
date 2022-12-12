## 환경 & 수정한 것
Visual studio 2022에서 winui3 cpp 빈앱패키지됨으로 작성했습니다  
- MainWindow.Xaml
- MainWindow.Xaml.h
- MainWindow.Xaml.cpp  
위의 세 가지만 수정하였습니다.
---
환경설정으로서 프로젝트-속성-일반-visual studio 2022  
또한 nuget툴을 이용하여 Win2d를 설치하였습니다.  
  
## MainWindow.Xaml  
- Grid라는 레이아웃을 이용하였습니다.  
- Grid안에는 질서있게 MenuBar와 Slider, canvas, ColorPicker를 정렬해 줍니다.
- MenuBar에는 새파일, 세이브, 로드, 비가시, 가시, exit 등으로 이루었습니다.  
- Slider로 펜의 크기를 조절하고 canvas에 그림을 그리며 ColorPicker를 통해 다양한 색을 조합할 수 있습니다.  
  
## MainWindow.Xaml.h
- 필요한 밑작업인 전역변수들과 필요한 라이브러리를 들고 옵니다.  
  
## MainWindow.xaml.cpp
- 캔버스 관련으로는 펜으로 그릴 수 있는 코드를 적었습니다.
- 슬라이더는 크기를 조절합니다.
- colorpicker는 색을 지정합니다.
- newFile은 canvas위의 내용을 지웁니다.
- Save는 그림을 파일에 저장합니다.
- Load는 파일에서 부터 그림을 들고옵니다.
- ColorPicker_hide_show는 ColorPicker의 가시화, 비가시화를 결정합니다.
- exit는 프로젝트의 실행을 정지시킬 수 있습니다.

## 동영상
https://youtu.be/s5_B4fnTDLw
