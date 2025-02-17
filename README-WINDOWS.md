## Windows
### Nastavení IDE
Projekt je nakonfigurovaný pro MS Visual Studio 2022; předpokládá nainstalovanou podporu pro C++. Nemělo by být potřeba nic doinstalovávat mimo vlastní MSVS, všechny potřebné 3rd-party knihovny, software a další data jsou součástí projektu.

V nastavení Visual Studia doporučuju v ***Tools/Options/Text Editor/File Extension*** přidat následující nastavení pro editory:

| Extension | Editor               |
|-----------|----------------------|
| glsl	    | Microsoft Visual C++ |
| mtl       | XML (Text) Editor    |
| tpp       | Microsoft Visual C++ |

### Jak to rozchodit
Stáhnout projekt z GitHubu a otevřít _src/ZPGproject.sln_. Nejjednodušší způsob je zvolit ve startovním menu MSVS ***Clone a repository*** a zadat url.

> [!NOTE]
> Před první kompilací doporučuju všechny projekty ve složce _examples_ unloadnout (pravé tlačítko na _examples_ a volba ***Unload Projects in Solution Folder***). Vyhnete se tak zdlouhavé kompilaci všeho a taky nějakým těm warningům které tam jsou ve zdrojácích.

SOIL knihovna dodaná na tutoriálech je poměrně stará, při kompilaci docházelo k nějakým chybám a problémům; zkompiloval jsem aktuální ze zdrojáků z GitHubu (zdrojové kódy nalinkovány, viz. adresářová struktura) - měla by fungovat v MSVS 2022, pro jinou verzi může být potřeba znova zkompilovat nebo použít původní; ta je v adresáři _3rd/_ také, jen přejmenovaná na _.zpgdefault_.

Prostředí je rozchozené a nakonfigurované pro všechny 'Debug/Release' + 'x86/x64' kombinace, nicméně některé knihovny (GLFW) nejsou zjevně zkompilované s /MD flagem a proto při 'Release' překladu dojde k chybám a překlad nedopadne. Už jsem to neřešil, kdo chce, ať si stáhne a zkompiluje vlastní verze knihoven.
