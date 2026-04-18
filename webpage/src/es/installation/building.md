# Construir QOwnNotes

## Construyendo desde GitHub

También puede crear QOwnNotes usted mismo a partir del código fuente.

Obtenga el código del último lanzamiento directamente desde el repositorio de git:

```bash
git clone https://github.com/pbek/QOwnNotes.git -b release
cd QOwnNotes
git submodule update --init
```

Para la depuración, es más fácil usar QtCreator. Al descargar [Qt Creator](https://www.qt.io/download-qt-installer-oss), también necesitará el paquete `qtwebsockets` para construir QOwnNotes con Qt6. Si lo construye en Windows, querrá ceñirse a _MinGw de 64-bits_. En Linux, lo más probable es que tenga un paquete para QtCreator en su repositorio.

Posteriormente, abra el archivo de proyecto `src/QOwnNotes.pro` y haga clic en **Construir** / **Construir Proyecto QOwnNotes**.

Si sabe lo que está haciendo, también puede construir QOwnNotes directamente desde su terminal:

```bash
cd src

# build binary translation files if you want another language than English
lrelease QOwnNotes.pro

# prepare build process and build the application
qmake
make
```

No dude en contribuir con el código fuente a este proyecto, realizar sugerencias o informar problemas en la [página de incidencias de QOwnNotes](https://github.com/pbek/QOwnNotes/issues).

Visitar [QOwnNotes en GitHub](https://github.com/pbek/QOwnNotes).

::: tip
Si desea contribuir código fuente al proyecto, por favor haga sus solicitudes de incorporación de cambios (pull requests) en la rama `main`. But please make sure to read the [code contribution guidelines](../contributing/code-contributions.md) first.
:::

## Archivo fuente

Encontrará los archivos fuente de QOwnNotes en el [archivo fuente de QOwnNotes](https://github.com/pbek/QOwnNotes/releases).

Los archivos fuente serán accesibles de esta forma:

`https://github.com/pbek/QOwnNotes/releases/download/v23.7.0/qownnotes-23.7.0.tar.xz`

## Construir con Nix

Si tienes instalado el gestor de paquetes [Nix](https://nixos.org/download/) y [Devenv](https://devenv.sh/getting-started/), puedes clonar el repositorio con git, como se explicó anteriormente, y construilro con:

```bash
# Open a shell with all the tools you need
devenv shell

# Build the application
just nix-build

# Run the built application
just nix-run
```
