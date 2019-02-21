# Symbol editor

Simple symbol editor for use with 3D-Win.

https://gentleface.com/free_icon_set.html

krita:
	icons:
		48x48
		transparent
		line width: 6px
		brush: basic-1

Windows deployment:

c:\Local\Qt\5.12.0\msvc2017_64\bin\windeployqt.exe
	--release
	--qmldir ../../symedit
	--no-translations
	--no-compiler-runtime
	--no-webkit2
	--no-angle
	--no-opengl-sw
	.

