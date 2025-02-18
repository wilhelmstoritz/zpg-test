## macOS
Pro správu závislostí je použitý balíčkovací systém **Homebrew**, který zajišťuje konzistentní a snadnou instalaci potřebných externích knihoven; je preferován, protože poskytuje aktuální verze balíků, umožňuje jednoduchou správu závislostí a je široce podporován komunitou.

> Instalace Homebrew automaticky nainstaluje **Xcode Command Line Tools**, které obsahují nezbytné kompilátory a nástroje pro vývoj na macOS.

### Nastavení prostředí
Je nutné mít nainstalované všechny potřebné vývojové nástroje (c++ kompilátor ```gcc / clang++```, ```cmake``` + ```make```, atd.), všechny odpovídající systémové OpenGL/X11 knihovny a 3rd-party knihovny používané v projektu; také balíčky pro přístup na GitHub a balíček FFmpeg (používá se k nahrávání videa z obsahu okna aplikace).

> [!NOTE]
> Doporučuji nainstalovat balíček ```gh``` (navíc k univerzálnímu ```git```) pro pohodlnější práci s GitHub repozitáři; umožňuje pohodlné přihlašování klíčem apod.

```
# Homebrew; also installs Xcode Command Line Tools
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# development tools
brew install gcc cmake make
PATH="/usr/local/opt/make/libexec/gnubin:$PATH"

# libraries for OpenGL and related development; additional libraries and dependencies
brew install mesa libx11 libxrandr libxinerama libxcursor libxi
brew install glm glfw glew assimp

# GitHub tools
brew install git gh

# FFmpeg
brew install ffmpeg
```

### Jak to rozchodit
a) Nakonfigurovat přístup na GitHub (pokud ještě nemáte) **PRO VYZKOUŠENÍ A KOMPILACI NENÍ POTŘEBA A MOŽNO VYNECHAT**:
```
gh auth login
git config --global user.email "you@mail.com"
git config --global user.name "your name"
```

b) Stáhnout, zkompilovat a nainstalovat SOIL knihovnu:
```
cd; mkdir src; cd src/
git clone https://github.com/childhood/libSOIL.git

cd libSOIL/
make
sudo make install
```

c) Stáhnout projekt a zkompilovat:
```
cd; cd src/
git clone https://github.com/wilhelmstoritz/zpg-test

cd zpg-test/src/
cmake ./
make
```

d) Binární soubory jsou v _build/_ adresáři; kvůli relativním cestám je nutné spouštět z adresáře, kde se nachází spustitelný soubor a knihovny:
```
cd build/
./ZPGproject
```
