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

SOIL knihovna dodaná na tutoriálech je poměrně stará, při kompilaci docházelo k nějakým chybám a problémům; zkompiloval jsem vlastní ze zdroj8k; z GitHubu - m2la by fungovat v MSVS 2022, pro jiné platformy může být nutné zkompilovat si vlastní nebo použít původní - je tam, pouze přejmenovaná na _.zpfdefault_.

Je rozchozené a nakonfigurované prostředí pro všechny varianty Debug/Release x86/x64, nicméně některé knihovny (GLFW) nejsou zjevně zkompilované s /MD flagem a proto při 'Release' překladu dojde k chybám a překlad nedopadne. Už jsem to neřešeil, kdo chce, ať si stáhne a zkompiluje vlastní verze knohoven.

> Obecně by mělo být možné editovat/kompilovat v podstatě jakýmkoliv C++ kompilátorem a na jakékoliv platformě; nutná správná konfigurace všech potřebných khihoven.

> [!CAUTION]
> appcore/AppUtils používá platform-dependent interface _windows.h_ pro získání cesty k souborům ve Windows. Pro kompilaci na Linux/Mac nutno nahradit něčím jiným a upravit příslušné metody.

### Nějaké to info co mi přijde důležité
Alespoň základní znalost MSVS studia a nastavení C++ kompilátoru/linkeru nutná. Udržujte si v projektu pokud možno pořádek. Docela to narůstá a kdo si v tom udělá mrdník hned na začátku, bude ztracen ve vlastním kódu. Jednoznačně doporučuji použít nějaký verzovací systém a nějakou rozumnou správu (GitHub je ideální), jinak budete bojovat neustále s nějakým nastavením, chybějícíma souborama apod. Přenos mezi počítači doma/ve škole je pak výrazně snazší.

S tím souvisí i další věc - veškeré nastavení a cesty mějte relativní tak, aby se projekt dal zkopilovat ať je nakopírovaný v jakékoliv cestě. Všechno automatizujte v rámci překladu - některé knihovny je potřeba nakopírovat do cílového adresáře kam se Váš projekt zkompiluje aby šel vůbec pustit (GLEW např.) a pokud to budete dělat ručně, budete pokaždé řešit doma/ve škole že jste na něco zapomněli a že to nejede protože tam chybí knohovna atd.

Doporučuju vybrat si jako cílovou platformu Win32 a té se držet a všechno nastavovat/kompilovat pro ní. Výsledná aplikace je viditelně rychlejší ale hlavně se zbavíte nepříjemných potenciálních problémů (size_t je unsigned long pro win32 a bez problémů funguje automatické přetypování na int ale pro win64 je size_t unsigned long long a budete muset řešit přetypovávání pro volání GL knihoven které očekávají GLint/GLuint např. apod.)

## Projekt, DÚ
Projekt se vyvíjí a pořád mění - co uděláte v hodině, doma přepíšete když budete něco doplňovat a řešit DÚ.

> [!IMPORTANT]
> Když něco změníte - třeba doplníte/rozšíříte podporu pro nějakou třídu nebo shader, **udržujte zpětnou kompatibilitu s už hotovými úkoly**; tzn. upravte si dřívější DÚ tak, aby Vám běžely i s novým frameworkem. Minimálně na konci semestru chce nějaký náhodný úkol předvést a dost lidí s tím bojovalo. Prakticky u všech chtěl ukázat "4 koule" aby si ověřil Phongov osvětlovací model.