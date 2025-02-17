## Linux
> [!CAUTION]
> Wayland platforma není podporována z důvodu omezení GLEW knihovny; **je nutné použít X11**. Ujistěte se, že vaše prostředí běží pod X11, jinak aplikaci nebude možné spustit.

### Nastavení prostředí
Je nutné mít nainstalované všechny potřebné vývojové nástroje (```gcc```, ```cmake``` + ```make```, atd.), všechny odpovídající systémové OpenGL/X11 knihovny a 3rd-party knihovny používané v projektu (jejich "debug" verze); také balíčky pro přístup na GitHub a balíček FFmpeg (používá se k nahrávání videa z obsahu okna aplikace).

> [!NOTE]
> Doporučuji nainstalovat balíček ```gh``` (navíc k univerzálnímu ```git```) pro pohodlnější práci s GitHub repozitáři; umožňuje pohodlné přihlašování klíčem apod.

#### RHEL, Fedora a odvozené distribuce
```
# development tools
sudo dnf update
sudo dnf -y install gcc-c++ cmake make

# libraries for OpenGL and related development; additional libraries and dependencies
sudo dnf -y install mesa-libGL-devel mesa-libEGL-devel libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel
sudo dnf -y install glm-devel glfw-devel glew-devel assimp-devel SOIL-devel

# GitHub tools
sudo dnf -y install git gh

# FFmpeg
sudo dnf -y install https://download1.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm # enable RPM Fusion repository
sudo dnf -y install ffmpeg --allowerasing
```

#### Debian, Ubuntu a odvozené distribuce
```
# development tools
sudo apt update
sudo apt install -y g++ cmake make

# libraries for OpenGL and related development; additional libraries and dependencies
sudo apt install -y libgl1-mesa-dev libegl1-mesa-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
sudo apt install -y libglm-dev libglfw3-dev libglew-dev libassimp-dev libsoil-dev

# GitHub tools
sudo apt install -y git gh

# FFmpeg
sudo apt install -y ffmpeg
```

> Pro jiné distra to bude podobné, Google/ChatGPT případně napoví přesné názvy balíčků...

### Jak to rozchodit
a) Nakonfigurovat přístup na GitHub (pokud ještě nemáte):
```
gh auth login
git config --global user.email "you@mail.com"
git config --global user.name "your name"
```

b) Stáhnout projekt a zkompilovat:
```
cd; mkdir src; cd src/
git clone https://github.com/wilhelmstoritz/zpg-projekt

cd zpg-projekt/src/
cmake ./
make
```

c) Binární soubory jsou v _build/_ adresáři; kvůli relativním cestám je nutné spouštět z adresáře, kde se nachází spustitelný soubor a knihovny:
```
cd build/
./ZPGproject
```
