# SAD Extractor

Projeto em C que extrai informações chave de PDF's de patrimônios e as organiza em uma planilha excel, ultilizando a biblioteca [libxlsxwriter](https://github.com/jmcnamara/libxlsxwriter).

## Como compilar

### Requisitos
- [MSYS2](https://www.msys2.org)
- CMake
- MinGW64
- Zlib (`pacman -S mingw-w64-x86_64-zlib`)

### Compilação
```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
./sad_extractor_github.exe
