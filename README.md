# Symbol editor

Simple symbol editor for use with 3D-Win.

https://gentleface.com/free_icon_set.html

krita icons:
	48x48
	transparent
	line width: 6px
	brush: basic-1

Windows icon creation with ImageMagick:

convert icon16.png icon24.png icon32.png icon48.png icon256.png icon.ico

Build html help in Windows:

sphinx-build -M html . _build

Windows deployment:

C:\Users\Mikko\Code\Qt\5.12.4\msvc2017_64\bin\windeployqt.exe
	--debug --qmldir ../../symedit
	--no-translations --no-compiler-runtime --no-webkit2 --no-angle --no-opengl-sw
	.

C:\Users\Mikko\Code\Qt\5.12.4\msvc2017_64\bin\windeployqt.exe
	--release --qmldir ../../symedit
	--no-translations --no-compiler-runtime --no-webkit2 --no-angle --no-opengl-sw
	.

