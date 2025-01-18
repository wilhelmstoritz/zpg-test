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
Naklonovat repositář a otevřít _src/ZPGproject.sln_. Nejjednodušší způsob je zvolit ve startovním menu MSVS ***Clone a repository*** a zadat url.

> [!NOTE]
> Ve složce _examples_ jsou rozchozené všechny jednotlivé příklady co jsme dostali během tutoriálů a ze kterých jsme měli vycházet. Co příklad to samostatně zkompilovatelný a spustitelný projekt. Pokud budete chtít nějaký z nich pustit, je potřeba příslušný projekt nastavit jako výchozí (pravé tlačítko na projektu a volba ***Set as Startup Project***).

> [!NOTE]
> Před první kompilací doporučuji unloadnout všechny projekty v adresáři examples (pravé tlačítko na _examples_ v _Solution Exploreru_ a volba ***Unload Projects in Solution Folder***). Vyhnete se tak zdlouhavé kompilaci všeho a taky nějakým těm warningům které tam jsou ve zdrojácích.

Pro spuštění je potřeba mít rozchozenou podporu OpenGL minimálně ve verzi Core 3.3; tzn na integrované kartě to možná pustíte ale rozhodně to nebude použitelné; je potřeba mít nějakou, ideálně dedikovanou, grafickou kartu a odpovídající ovladače. Verze shaderů je u mě nastavene na 4.30 protože VMWare VM kde to pouštím vyšší verzi nepodporuje, kdo to bude pouštět na moderním HW ať si nastaví v každém _.glsl_ zdrojáku k shaderu aktuální verzi 4.60.

### Co je co
Adresářová struktura:

| Adresář        | Co tam je                                                                                    |
|----------------|----------------------------------------------------------------------------------------------|
| _src/_         | Vlastní projekt; MSVS solution root                                                          |
| _3rd/_         | 3rd-party knihovny (GLM, GLFW, GLEW a další) a programy (FFMPEG) atd.                        |
| _3rd.src/_     | Zdrojové kódy k 3rd-party knihovnám                                                          |
| _blender.src/_ | Zdrojové soubory pro Blender                                                                 |
| __archive/_    | Archiv všeho co jsme dostali k dispozici v původní podobě; **přednášky** + **cvičení** z LMS |

Projektová struktura:

| Knihovna/Složka  | Co tam je                                                               |
|------------------|-------------------------------------------------------------------------|
| dir: _examples_  | Jednotlivé ukázkové příklady co jsme dostali během tutoriálů            |
| dir: _resources_ | Všechna ostatní data; modely, textury, fonty; **zdrojové kódy shaderů** |
|                  |                                                                         |
| _appcore_        | App core; sdílená knihovna nástrojů a utilit                            |
| _gl3rd_          | GL 3rd-party; dodané zdrojové kódy k zakomponování do projektu          |
| _gloo_           | GL object oriented; vlastní implementace projektu                       |
| _launcher_       | Launcher; vytváření scény                                               |

SOIL knihovna dodaná na tutoriálech je poměrně stará, při kompilaci docházelo k nějakým chybám a problémům; zkompiloval jsem vlastní ze zdrojáků z GitHubu - měla by fungovat v MSVS 2022, pro jiné platformy může být nutné zkompilovat si vlastní nebo použít původní - je tam, pouze přejmenovaná na _.zpgdefault_.

Prostředí je rozchozené a nakonfigurované pro 'Debug/Release' 'x86/x64', nicméně některé knihovny (GLFW) nejsou zjevně zkompilované s /MD flagem a proto při 'Release' překladu dojde k chybám a překlad nedopadne. Už jsem to neřešeil, kdo chce, ať si stáhne a zkompiluje vlastní verze knihoven.

> Obecně by mělo být možné editovat/kompilovat v podstatě jakýmkoliv C++ kompilátorem a na jakékoliv platformě; nutná správná konfigurace všech potřebných khihoven.

> [!CAUTION]
> _appcore/AppUtils_ používá platform-dependent interface _windows.h_ pro získání cesty k souborům ve Windows. Pro kompilaci na Linux/Mac nutno nahradit něčím jiným a upravit příslušné metody.

## Nějaké to info co mi přijde důležité
Alespoň základní znalost MSVS a nastavení C++ kompilátoru/linkeru nutná; hned na prvním tutoriálu, jinak si ani nestihnete rozchodit a nastavit prostředí, valí fakt rychle. Udržujte si v projektu pokud možno pořádek. Docela to narůstá a kdo si v tom udělá mrdník hned na začátku, bude ztracen ve vlastním kódu. Jednoznačně doporučuji použít nějaký verzovací systém a nějakou rozumnou správu (GitHub je ideální), jinak budete bojovat neustále s nějakým nastavením, chybějícíma souborama apod. Přenos mezi počítači doma/ve škole je pak výrazně snazší.

S tím souvisí i další věc - veškeré nastavení a cesty mějte relativní tak, aby se projekt dal zkompilovat ať je nakopírovaný v jakékoliv cestě. Všechno automatizujte v rámci překladu; některé knihovny je potřeba nakopírovat do cílového adresáře kam se Váš projekt zkompiluje (GLEW např.) a pokud to budete dělat ručně, budete pokaždé řešit doma/ve škole že jste na něco zapomněli a že to nejede protože tam chybí knihovna atd.

Doporučuju vybrat si jako cílovou platformu **Win32** ('Debug/x86') a té se držet a všechno nastavovat/kompilovat pro ní. Výsledná aplikace je viditelně rychlejší ale hlavně se zbavíte nepříjemných potenciálních problémů během vývoje s kompatibilitou knihoven apod. (```size_t``` je ```unsigned long``` pro win32 ale pro win64 je ```unsigned long long``` atd.)

### Projekt, DÚ
Projekt se vyvíjí a pořád mění - snažte se psát objektově a univerzálně ať doplnění další funkcionality neznamená refactoring poloviny kódu. Hlídejte si paměť (ideálně všude kde to dává smysl používat ```std::ptr``` místo ```*ptr``` pointerů; ušetří to dost časů a nervů) a typovou bezpečnost (```enum class``` místo ```enum```, ```GLint``` a obecně GL proměnné tam kde se očekávají apod.).

Nějak jsem se snažil ve zdrojácích udržet postupný progress ať se v tom vyznáte; co je pojmenováno s indexem [01, 02 .. 05a/05b, 06] apod. souvisí s daným tutoriálem a úkolem na něj navázaným. Takže scéna 03 "illuminated spheres" odpovídá tutoriálu 3 a používá zdrojové soubory k shaderům v adresáři _shaders.glsl/03/_ apod. Občas v kódu narazíte na zakomentovanou "implementaci něčeho" - většinou se jedná a nějaké řešení které bylo postupem nahrazeno jinou verzí; měl by tam být aspoň nějaká základní komentář "vo co go".

Přednášky a cvičení jsou očíslovány 1 - 10, my jsme měli 6 tutoriálů, proto číslování úkolů v kódu nemusí nutně korespondovat s číslem přednášky/cvičení které se daným tématem zabývá.

> [!IMPORTANT]
> Když něco v kódu změníte (v implementaci tříd, shaderů nebo v modelových datech), **udržujte zpětnou kompatibilitu s už hotovými úkoly**; tzn. upravte si dřívější DÚ tak, aby Vám běžely i s novým frameworkem. Minimálně na konci semestru chce nějaký náhodný úkol předvést a dost lidí s tím bojovalo. Prakticky u všech chtěl ukázat "4 koule" aby si ověřil Phongův osvětlovací model a občas náhodně i něco jiného.

### Proč je to tak a ne jinak?
Většinu projektu nám dal volnost a nechal nás ať si to uděláme jak chceme ale občas přišel s požadavkem že něco bude konkrétně implementováno "tak a ne jinak":
 - _ShaderProgram_ svoje ID nikdy neposkytne "ven"; veškerá implementace která s tím pracuje (vytvoření, smazání, bind/unbind) musí tudíž být implementována uvnitř této třídy.
 - Ačkoliv jsme už v tu dobu každý měl nějak naimplementované vytváření shaderů, dal nám svůj vlastní zdroják (u mě v _gl3rd/ShaderLoader_) a museli jsme ho zakomponovat a používat. To že je napsaný tak prasácky jak je odůvodnil "v praxi budete spolupracovat i s nechopnými/špatnými programátory a já jsem špatný programátor, takže si s tím musíte poradit".
 - Další podmínkou byla nějaká implementace návrhového vzoru **Singleton**, implementace interakce shaderů a osvětlení pomocí návrhového vzoru **Observer**; dál chtěl aspoň někde použít návrhové vzory **Composit** a **Factory**
 - Během semestru přišel s podmínkou že tam musí být třída _Drawable_; já už jsem měl většinu implementovanou ve třídě _Model_ a nechtělo se mi to předělávat, proto je u mě dědičnost z _Drawable_ čistě pro formu.

### Jak to používat
V _Launcheru_ zakomentovat/povolit scény které chcete pustit. Pokud je odkomentována scéna "main menu", můžete mezi scénama přepínat. Každá scéna má k dispozici nějaké ovládání, viz. info v titulku okna; všechny podporují přepínání pomocí **W** do wireframe vykreslování polygonů pro ladění (**+**/**-** toušťka), ukončení pomocí **ESC**. Většina scén umožňuje pohyb pomocí **myši** (**pravé tlačítko** = strafe), **kurzorových kláves** (**SHIFT** = sprint) a **F** pro vyp/zap baterky.
 
Veškerá smysluplná konfigurace by měla být dostupná skrze _appcore/Config_; hardcoded by mělo být naprosté minimum věcí.
 
Občas bude požadavek na obrázek nebo nahrát video z výstupu aplikace. Abyste nemuseli řešit nějaké zachytávání obrazovky/videa nějakým 3rd nástrojem, je implementováno nahrávání obsahu okna pomocí FFMPEG. Stačí v _appcore/Config_ nastavit
```
Config::SYSTEM_XTRA_RENDER_PROCESSING = true;
```
a aplikace začne po spuštění nahrávat video. Nahrávání se ukončí se zavřením okna/ukončením aplikace; výsledný soubor _output.mp4_ bude uložen v adresáři projektu.
 
> [!NOTE]
> Během nahrávání neměnte velikost okna; FFMPEG má na vstupu parametry výsledného videa a pokud budou rozdílné od velikosti okna nebo je během nahrávání změníte, nedopadne to. Ve výchozím nastavení je velikost okna 800x600 pixelů a stejně je nastavený i výstup FFMPEG do video souboru. V případě potřeby změnit parametry spouštění procesu FFMPEG v _gloo/Renderer_.
 
# !!! GOOD LUCK !!!
