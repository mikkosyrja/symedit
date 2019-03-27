/home/mikko/Code/Qt5.12.2/5.12.2/gcc_64/bin/lrelease -idbased locale/symedit.*.ts

if [ $? -ne 0 ]; then
	lrelease-qt5 -idbased locale/symedit.*.ts
fi
