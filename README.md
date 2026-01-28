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
```bash
apt-get install libncurses-dev
```
<br>Arch
```bash
pacman -Sy ncurses
```
<br>Fedora
```bash
dnf install ncurses-devel
```
<br>Then
```bash
make curses
```

