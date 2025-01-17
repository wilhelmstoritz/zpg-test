# 03zpg-01---projekt
semestr 03 | Základy počítačové grafiky; projekt

## Nastavení IDE
Projekt je nakonfigurován pro MS Visual Studio 2022; předpokládá nainstalovanou podporu pro C++. Nemělo by být potřeba nic doinstalovávat mimo vlastní MSVS, všechny potřebné 3rd-party knihovny, utility a další data jsou součástí projektu.

V nastavení Visual Studia doporučuji v ***Tools/Options/Text Editor/File Extension*** přidat následující nastavení pro editory:
| Extension | Editor               |
|-----------|----------------------|
| glsl	    | Microsoft Visual C++ |
| mtl       | XML (Text) Editor    |
| tpp       | Microsoft Visual C++ |

### Jak to rozchodit
Naklonovat repositář a otevřít _src/ZPGproject.sln_. Nejjednodušší způsob je zvolit ve startovním menu MSVS _Clone a repository_ a zadat url.

> [!NOTE]
> V adresáři 'examples' jsou rozchozené všechny jednotlivé příklady co jsme dostali během tutoriálů a ze kterých jsme měli vycházet. Co příklad to samostatně zkompilovatelný a spustitelný projekt. Pokud budete chtít nějaký z nich pustit, je potřeba příslušný projekt nastavit jako výchozí (pravé tlačítko na projektu a volba **Set as Startup Project**).

> [!NOTE]
Před první kompilací doporučuji unloadnout všechny projekty v adresáři examples (pravé tlačítko na _examples_ v _Solution Exploreru_ a volba **Unload Projects in Solution Folder**). Vyhnete se tak jednak zbytečně delší kompilaci a nějakým těm warningům které tam má Němec ve zdrojácích.

### Co je co
| Adresář      | Co tam je                                                             |
|--------------|-----------------------------------------------------------------------|
| src/	       | Vlastní projekt obsahuijící MSVS .sln solution                        |
| 3rd/         | 3rd-party knihovny (GLM, GLFW, GLEW a další) a programy (FFMPEG) atd. |
| 3rd.src/     | Zdrojové kódy k 3rd-party knihovnám                                   |
| blender.src/ | Zdrojové soubory pro Blender                                          |
| _archive/    | Archiv všeho co jsme dostali k dispozici v původní podobě             |

> Mělo být možné editovat/kompilovat v podstatě jakýmkoliv C++ kompilátorem a na jakékoliv platformě; nutná správná konfigurace všech potřebných khihoven.

> [!CAUTION]
> appcore/AppUtils používá platform-dependent interface _windows.h_ pro získání cesty k souborům ve Windows. Pro kompilaci na Linux/Mac nutno nahradit něčím jiným a upravit příslušné metody.