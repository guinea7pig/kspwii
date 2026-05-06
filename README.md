## Build

Prerequisites:

* devkitPro
  * devkitPPC (release 47 or later)
  * libogc
  * libfat
* Port libs
  * Mini-XML
  * libpng
  * FreeType

To compile:

```text
pacman --sync --needed --noconfirm ppc-mxml ppc-libpng ppc-freetype
cmake --workflow wii
```
