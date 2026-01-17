# 2048 cli

![curses look](https://github.com/Patadass/2048/blob/main/photos/curses.png?raw=true)

## Build
### Terminal
on linux/macos/unix
```
make
```
### With curses
This version requires ```libncurses-dev```. Use your distros package manager to obtain it<br><br>

Debian/ubuntu
```
apt-get isntall libncurses-dev
```
<br>Arch
```
pacman -S ncurses
```
<br>Fedora
```
dnf install ncurses-devel
```
<br>Then
```
make curses
```

