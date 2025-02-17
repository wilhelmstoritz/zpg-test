# ZPG projekt
### semestr 03 | Základy počítačové grafiky; projekt
Předmět kde se reálně (za účelem dosažení výsledku; ne jen kvůli vyzkoušení nějakého konceptu) programuje. Jedná se "větší" (ve srovnání s jinými dosavadními úkoly) projekt a celkově ucelenější koncept a je _vhodné_ k tomu tak přistupovat.

## Nastavení prostředí a jak to rozchodit
- [Windows](README-WINDOWS.md)
- [macOS](README-MACOS.md)
- [Linux](README-LINUX.md)

> Testováno na **Windows 11**, **macOS 14 Sonoma** a na Linux distribucích **Fedora 41** a **Ubuntu 24.04.1 LTS**.

> [!CAUTION]
> _appcore/AppUtils_ používá platformově závislý interface _windows.h/direct.h_, resp. _limits.h/unistd.h_, pro získání cesty k souborům ve Windows, resp. macOS / Linuxu. Pro kompilaci na jiných platformách nutno nahradit odpovídajícím řešením a upravit příslušné metody.
>
> _gloo/Renderer_ používá platformově závislé funkce ```localtime_s()``` ve Windows, resp. ```localtime_r()``` v macOS / Linuxu.

## Co je co
Adresářová struktura:

| Adresář        | Co tam je                                                                                    |
|----------------|----------------------------------------------------------------------------------------------|
| _src/_         | Vlastní projekt; MSVS solution root                                                          |
| _3rd/_         | 3rd-party knihovny (GLM, GLFW, GLEW a další) a programy (FFmpeg) atd.                        |
| _3rd.src/_     | Zdrojové kódy k 3rd-party knihovnám                                                          |
| _blender.src/_ | Zdrojové soubory pro Blender                                                                 |
| _ARCHIVE/_     | Archiv všeho co jsme dostali k dispozici v původní podobě; **přednášky** + **cvičení** z LMS |

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

Ve složce _examples_ jsou rozchozené všechny jednotlivé příklady co jsme dostali během tutoriálů a ze kterých jsme měli vycházet. Co příklad, to samostatně zkompilovatelný a spustitelný projekt.

> [!NOTE]
> Pokud budete chtít nějaký z příkladů spustit v MSVS, je potřeba příslušný projekt nastavit jako výchozí (pravé tlačítko na projektu a volba ***Set as Startup Project***).

## Nějaké info co mi přijde důležité
> Pro spuštění je potřeba mít ovladače podporující OpenGL v4.x; na integrované kartě to (možná) pustíte ale rozhodně to nebude použitelné; ideální je dedikovaná grafická karta a odpovídající ovladače. Verze shaderů je u mě nastavená na 4.30 protože VMWare VM (které pro vývoj používám) vyšší verzi nepodporuje; kdo to bude spouštět na moderním HW ať si nastaví v každém _.glsl_ zdrojáku k shaderu aktuální verzi 4.60.

Projekt se dá psát na jakékoliv platformě; doporučuji se držet MSVS a Windows. Je to jediná platforma kde použité knihovny fungují bez problémů; na většině moderních Linux distribucích a/nebo macOS jsou nějaká omezení (na Linuxu GLEW nepodporuje Wayland, na macOS jsou různé funkce z GL knihoven označeny jako _deprecated_ a nahrazeny Metal API apod.)

Základní **znalost MSVS a nastavení C++ kompilátoru/linkeru nutná**; hned na prvním tutoriálu, jinak si ani nestihnete rozchodit a nastavit prostředí, valí fakt rychle. Udržujte si v projektu pokud možno pořádek. Docela to narůstá a kdo si v tom udělá mrdník hned na začátku, bude ztracen ve vlastním kódu. Jednoznačně doporučuji použít nějaký verzovací systém a nějakou rozumnou správu (GitHub je ideální), jinak budete bojovat neustále s nějakým nastavením, chybějícíma souborama apod. Přenos mezi počítači doma/ve škole je pak výrazně snazší.

S tím souvisí i další věc - veškeré nastavení a cesty mějte relativní tak, aby se projekt dal zkompilovat ať je nakopírovaný v jakékoliv cestě. Všechno automatizujte v rámci překladu; některé knihovny je potřeba nakopírovat do cílového adresáře kam se Váš projekt zkompiluje (GLEW např.) a pokud to budete dělat ručně, budete pokaždé řešit doma/ve škole že jste na něco zapomněli a že to nejede protože tam chybí knihovna atd.

Doporučuju vybrat si jako cílovou platformu **win32** ('Debug/x86') a té se držet a všechno nastavovat/kompilovat pro ní. Výsledná aplikace nijak pomalejší není a hlavně předejdete potenciálním nepříjemným problémům během vývoje s kompatibilitou knihoven apod. (```size_t``` je ```unsigned long``` pro win32 ale ```unsigned long long``` pro win64 apod.)

> Není problém, když si pomůžete (Ctrl+C/Ctrl+V, Copilot, ChatGPT apod.) ale když přijde na věc, chce abyste tomu rozuměli a uměli to vysvětlit; na tutoriálu náhodně vybere jednoho/dva z davu a kouká do zdrojáků (projektor) a ptá se.

### Projekt; DÚ
Projekt se rychle rozrůstá a pořád mění - snažte se psát objektově a univerzálně ať doplnění další funkcionality neznamená refactoring poloviny stávajícího kódu. Zdrojové kódy a všechna ostatní data rozumně strukturujte. Dodržujte principy OOP, hlídejte si paměť (všude kde to dává smysl používejte 'smart' ```std::unique/shared_ptr``` místo ```*ptr``` pointerů; ušetří to dost času a nervů) a typovou bezpečnost (```enum class``` místo ```enum```, ```GLint``` a obecně GL proměnné tam kde se očekávají apod.).

Nějak jsem se snažil ve zdrojácích udržet postupný progress ať se v tom vyznáte; co je pojmenováno s indexem (01, 02 .. 05a/05b, 06 apod.) souvisí s daným tutoriálem a úkolem na něj navázaným. Takže scéna 03 "illuminated spheres" odpovídá tutoriálu 3 a používá zdrojové soubory k shaderům ve složce _resources/shaders.glsl/03/_ atd. Občas v kódu narazíte na zakomentovanou "implementaci něčeho" - většinou se jedná o nějaké řešení které bylo nahrazeno jinou verzí; měl by tam být aspoň nějaký základní komentář o co jde.

Přednášky a cvičení jsou očíslováné 1 - 10, my jsme měli 6 tutoriálů, proto číslování úkolů v kódu nemusí nutně korespondovat s číslem přednášky/cvičení které se daným tématem zabývá.

> [!IMPORTANT]
> Když něco v kódu změníte (v implementaci tříd, shaderů nebo v modelových datech), **udržujte zpětnou kompatibilitu s už hotovými úkoly**; tzn. upravte si dřívější DÚ tak, aby Vám běžely i s novým frameworkem. Minimálně na konci semestru chce nějaký náhodný úkol předvést a dost lidí s tím bojovalo. Po všech chtěl ukázat scénu s nasvícenýma koulema (03 "illuminated spheres") aby si ověřil Phongův osvětlovací model a občas náhodně i něco jiného.

### Proč je to zrovna takhle ?
Většinu projektu jsme měli volnost a mohli si implementaci řešit podle sebe, občas ale přišel požadavek že něco bude implementováno "právě tak a ne jinak":
 - _ShaderProgram_ svoje ID nikdy "neposkytne ven"; veškerá implementace která s ním pracuje (vytvoření, smazání, bind/unbind) musí tudíž být uvnitř této třídy.
 - Ačkoliv jsme už v tu dobu každý měl nějak naimplementované vytváření shaderů, dal nám svůj vlastní zdroják (u mě v _gl3rd/ShaderLoader_) a museli jsme ho zakomponovat a používat "tak jak je". To že je napsaný tak prasácky jak je odůvodnil "v praxi budete spolupracovat i s nechopnými/špatnými programátory a já jsem špatný programátor, takže si s tím musíte poradit".
 - Další podmínkou byla nějaká implementace návrhového vzoru **Singleton**, implementace interakce shaderů a osvětlení pomocí návrhového vzoru **Observer**; dál chtěl aspoň někde použít návrhové vzory **Composit** a **Factory**
 - Během semestru přišel s podmínkou že tam musí být třída _Drawable_; já už jsem měl většinu implementovanou ve třídě _Model_ a nechtělo se mi to předělávat, proto je u mě dědičnost z _Drawable_ čistě pro formu.

### Jak to používat
V _Launcheru_ zakomentovat/povolit scény které chcete pustit. Pokud je odkomentována scéna "main menu", můžete mezi scénama přepínat. Každá scéna má k dispozici nějaké ovládání; viz. info v titulku okna.

> Všechny podporují:
>  - **X** pro přepínání celoobrazovkového (fullscreen) režimu,
>  - **W** pro přepínání vykreslování polygonů (wireframe) pro ladění (**+**/**-** toušťka čáry),
>  - **ESC** pro ukončení.

> Většina scén dále podporuje:
>  - pohyb pomocí **myši** (**pravé tlačítko** = strafe),
>  - pohyb pomocí **kurzorových kláves** (**SHIFT** = sprint),
>  - **F** pro vyp/zap baterky.

> Poslední scéna "dark magic woods:fireballs" pak navíc umožňuje hodit 'ohnivou kouli':
>  - **1-4** tradiční ohnivá / ledová / temná / mystická,
>  - **0** zhasnutí/ostranění.

#### Konfigurace
Veškerá konfigurace by měla být dostupná skrze _appcore/Config_; hardcoded by mělo být naprosté minimum věcí.

#### Nahrávání videa z výstupu
Občas se objeví požadavek na video z výstupu aplikace. Aby se zachytávání obrazovky/okna nemuselo řešit extra, je implementováno nahrávání obsahu okna pomocí FFmpeg. Stačí v _appcore/Config_ nastavit
```
Config::SYSTEM_XTRA_RENDER_PROCESSING = true;
```
a aplikace začne po spuštění nahrávat video - každou scénu (včetně "main menu") do samostatného souboru. Nahrávání se ukončí se zavřením okna/ukončením aplikace; výsledné soubory _output.TIMESTAMP.mp4_ budou uloženy v adresáři, ze kterého byl program spuštěn.

> [!IMPORTANT]
> Během nahrávání by se neměla měnit velikost okna; FFmpeg má na vstupu parametry výsledného videa a pokud budou rozdílné od velikosti okna nebo se velikost okna během nahrávání změní, nedopadne to. Ve výchozím nastavení je velikost okna 800x600 pixelů a stejně je nastavený i výstup FFmpeg. V případě potřeby změnit parametry spouštění procesu FFmpeg v _gloo/Renderer_.

# 🍀 Good Luck!
