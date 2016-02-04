#!/bin/bash

destDir=$(eval echo ~${SUDO_USER})/Jamtaba2

#create the directory and set permissions
install -d -m 0777 $destDir


echo "Installing Jamtaba 2 in " $destDir

#copy the files to $destDir and erase the original permission
cp Jamtaba2 $destDir
cp VstScanner $destDir

#copy the .desktop file to Desktop and Applications folder
cp Jamtaba2.desktop ~/Desktop/
cp Jamtaba2.desktop /usr/share/applications/

#copy the uninstaller script
cp uninstaller.sh $destDir

#copy the icon
cp Jamtaba2.png /usr/share/pixmaps/

#permissions
chmod 777 $destDir/Jamtaba2
chmod 777 $destDir/VstScanner
chmod 777 $destDir/uninstaller.sh
chmod 777 ~/Desktop/Jamtaba2.desktop
chmod 777 /usr/share/applications/Jamtaba2.desktop
chmod 777 /usr/share/pixmaps/Jamtaba2.png
