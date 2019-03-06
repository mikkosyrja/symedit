/home/mikko/Code/Qt5.12.1/5.12.1/gcc_64/bin/lrelease -idbased locale/symedit.*.ts

if [ $? -ne 0 ]; then
	lrelease-qt5 -idbased locale/symedit.*.ts
fi
