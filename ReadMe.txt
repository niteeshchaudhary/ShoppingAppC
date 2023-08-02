Please stop your anti virus before running project,as it may result in crash.
execute E-CommerceSite.exe to run project.
different exe are different frames(parts) of the project which will be called by E-CommerceSite.exe
when needed.

Requirement to Run the code:

1.location of project folder csProject should be in D derive.(D:/csProject/E-CommerceSite.exe).
   (if location not matched it may result in loss of images in some frames).
2. OS:Windows
3. need to put folloowing libraries into linker settings of your IDE, to inform compiler about them.
    > -user32.lib  
    > -lgdi32  
    > D:\Programs\ming\mingw64\x86_64-w64-mingw32\lib\libcomdlg32.a (path may differ according to your mingw location)
4. it uses 3 user define header file which should be in same folder of source code.
5. windows.h is included so it will be supported on windows based machine only.


*******************************************************************************
Console_version.exe is simple console form of this whole project,
it don't require any additional features.:-).
