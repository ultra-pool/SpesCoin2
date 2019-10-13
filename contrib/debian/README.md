
Debian
====================
This directory contains files used to package spescoind/spescoin-qt
for Debian-based Linux systems. If you compile spescoind/spescoin-qt yourself, there are some useful files here.

## spescoin: URI support ##


spescoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install spescoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your spescoinqt binary to `/usr/bin`
and the `../../share/pixmaps/spescoin128.png` to `/usr/share/pixmaps`

spescoin-qt.protocol (KDE)
