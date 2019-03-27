/home/mikko/Code/Qt5.12.2/5.12.2/gcc_64/bin/lupdate -locations none . -ts locale/symedit.ts locale/symedit.en_GB.ts locale/symedit.fi_FI.ts

if [ $? -ne 0 ]; then
	lupdate-qt5 -locations none . -ts locale/symedit.ts locale/symedit.en_GB.ts locale/symedit.fi_FI.ts
fi
