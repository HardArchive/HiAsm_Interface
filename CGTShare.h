#pragma once

//Project

//STL

//Qt
#include <QtCore>
#include <QBitArray>

//!!! ========== Поддерживается только HiAsm 4, пакет Delphi ==========

//!ru Флаги элемента
enum ElementFlags {
    //ru Элемент заморожен (нельзя перемещать).
    ELEMENT_FLG_IS_FREEZE = 0x0,

    //ru Элемент нельзя удалить.
    ELEMENT_FLG_IS_NODELETE = 0x2,

    //ru Элемент является частью интерфейса.
    ELEMENT_FLG_ONE_WIDGET = 0x8,

    //ru Элемент является редактором контейнера.
    //ru Например: EditMulti, EditMultiEx, EditPoliMulti.
    ELEMENT_FLG_IS_EDIT = 0x20,

    //ru Элемент является контейнером.
    ELEMENT_FLG_IS_MULTI = 0x40,

    //ru Элемент выбран в редакторе схем.
    ELEMENT_FLG_IS_SELECT = 0x100,

    //ru Родитель для элементов текущей SDK.
    ELEMENT_FLG_IS_PARENT = 0x200,

    //ru Элемент является базовым.
    //ru Например: CI_HubEx, CI_GetDataEx, ElementInfoTip, HCButton.
    ELEMENT_FLG_IS_CORE = 0x400,

    //ru Элемент является ссылкой, либо на него ссылаются.
    ELEMENT_FLG_IS_LINK = 0x800,

    //ru С элементом нельзя взаимодействовать с помощью мыши?
    //TODO Нужна дополнительная информация по этому флагу.
    ELEMENT_FLG_IS_NOMOUSE = 0x2000,
};
typedef QFlags<ElementFlags> ElementFlgs;

//!ru Типы точек
enum PointTypes {
    //ru Метод
    pt_Work = 1,

    //ru Событие
    pt_Event,

    //ru Переменная
    pt_Var,

    //ru Данные
    pt_Data
};
const static QMap<int, QString> PointTypesMap{
    {pt_Work, "pt_Work"},
    {pt_Event, "pt_Event"},
    {pt_Var, "pt_Var"},
    {pt_Data, "pt_Data"}
};

//!ru Типы данных
enum DataTypes {
    data_null = 0,
    data_int,
    data_str,
    data_data,
    data_combo,
    data_list,
    data_icon,
    data_real,
    data_color,
    data_script,
    data_stream,
    data_bitmap,
    data_wave,
    data_array,
    data_comboEx,
    data_font,
    data_matr,
    data_jpeg,
    data_menu,
    data_code,
    data_element,
    data_flags,
    data_object
};
const static QMap<int, QString> DataTypesMap{
    {data_null, "data_null"},
    {data_int, "data_int"},
    {data_str, "data_str"},
    {data_data, "data_data"},
    {data_combo, "data_combo"},
    {data_list, "data_list"},
    {data_icon, "data_icon"},
    {data_real, "data_real"},
    {data_color, "data_color"},
    {data_script, "data_color"},
    {data_stream, "data_stream"},
    {data_bitmap, "data_bitmap"},
    {data_wave, "data_wave"},
    {data_array, "data_array"},
    {data_comboEx, "data_comboEx"},
    {data_font, "data_font"},
    {data_matr, "data_matr"},
    {data_jpeg, "data_jpeg"},
    {data_menu, "data_menu"},
    {data_code, "data_code"},
    {data_element, "data_element"},
    {data_flags, "data_flags"},
    {data_object, "data_object"}
};

//!ru Классы элементов (elGetClassIndex)
enum ElementClass {
    //ru Просто элемент.
    CI_Element = 0,
    //ru Элемент с динамическими точками (автонумерация), например - IndexToChanel.
    //D - Dynamic, P - Point.
    CI_DPElement,
    //ru Контейнер
    CI_MultiElement,
    //ru Редактор контейнера MultiElement.
    CI_EditMulti,
    //ru Редактор динамического контейнера.
    CI_EditMultiEx,
    //ru Элемент для встраивания кода.
    CI_InlineCode,
    //ru Ручная отрисовка элемента интерфейса.
    CI_DrawElement,
    //ru Специальный класс, который используется для реализации ActionSkin.
    //ru Элемент AS_Control.
    CI_AS_Special,
    //ru Элемент со списком динамических точек.
    //ru Например элемент - VBScript.
    //D - Dynamic, P - Point, L - List
    CI_DPLElement,
    //ru Упрощённое подключение внешних библиотек.
    CI_UseHiDLL,
    //ru Элемент интерфейса, которым можно управлять в дизайнере форм.
    CI_WinElement,
    //ru Сноска.
    //ru PointHint - элемент базового пакета (_base).
    CI_PointHint,
    //ru Эмулятор элемента.
    //ru PointElement - элемент базового пакета (_base).
    CI_PointElement,
    //ru Разрыв линии.
    //ru LineBreak - элемент базового пакета (_base).
    CI_LineBreak,
    //ru Разрыв линии.
    //ru LineBreakEx - элемент базового пакета (_base).
    CI_LineBreakEx,
    //ru Пользовательский элемент.
    CI_UserElement,
    //ru Элемент для работы с переводом.
    //ru В пакете Windows, именуется как Class=Translator.
    CI_Translate,
    //ru Полиморфный контейнер.
    //ru Элемент может содержать более одного контейнера.
    CI_PolyMulti,
    //ru Шаблон документа.
    CI_DocumentTemplate
};
const static QMap<int, QString> ElementClassMap{
    {CI_Element, "CI_Element"},
    {CI_DPElement, "CI_DPElement"},
    {CI_MultiElement, "CI_MultiElement"},
    {CI_EditMulti, "CI_EditMulti"},
    {CI_EditMultiEx, "CI_EditMultiEx"},
    {CI_InlineCode, "CI_InlineCode"},
    {CI_DrawElement, "CI_DrawElement"},
    {CI_AS_Special, "CI_AS_Special"},
    {CI_DPLElement, "CI_DPLElement"},
    {CI_UseHiDLL, "CI_UseHiDLL"},
    {CI_WinElement, "CI_WinElement"},
    {CI_PointHint, "CI_PointHint"},
    {CI_PointElement, "CI_PointElement"},
    {CI_LineBreak, "CI_LineBreak"},
    {CI_LineBreakEx, "CI_LineBreakEx"},
    {CI_UserElement, "CI_UserElement"},
    {CI_Translate, "CI_Translate"},
    {CI_PolyMulti, "CI_PolyMulti"},
    {CI_DocumentTemplate, "CI_DocumentTemplate"}
};

//!ru Индексы параметров среды - GetParam()
enum CgtParams {
    PARAM_CODE_PATH = 0,
    PARAM_DEBUG_MODE,
    PARAM_DEBUG_SERVER_PORT,
    PARAM_DEBUG_CLIENT_PORT,
    PARAM_PROJECT_PATH,
    PARAM_HIASM_VERSION,
    PARAM_USER_NAME,
    PARAM_USER_MAIL,
    PARAM_PROJECT_NAME,
    PARAM_SDE_WIDTH,
    PARAM_SDE_HEIGHT,
    PARAM_COMPILER
};
const static QMap<int, QString> CgtParamsMap{
    {PARAM_CODE_PATH, "PARAM_CODE_PATH"},
    {PARAM_DEBUG_MODE, "PARAM_DEBUG_MODE"},
    {PARAM_DEBUG_SERVER_PORT, "PARAM_DEBUG_SERVER_PORT"},
    {PARAM_DEBUG_CLIENT_PORT, "PARAM_DEBUG_CLIENT_PORT"},
    {PARAM_PROJECT_PATH, "PARAM_PROJECT_PATH"},
    {PARAM_HIASM_VERSION, "PARAM_HIASM_VERSION"},
    {PARAM_USER_NAME, "PARAM_USER_NAME"},
    {PARAM_USER_MAIL, "PARAM_USER_MAIL"},
    {PARAM_PROJECT_NAME, "PARAM_PROJECT_NAME"},
    {PARAM_SDE_WIDTH, "PARAM_SDE_WIDTH"},
    {PARAM_SDE_HEIGHT, "PARAM_SDE_HEIGHT"},
    {PARAM_COMPILER, "PARAM_COMPILER"}
};
struct TCgtParams {
    QString PARAM_CODE_PATH{};
    int PARAM_DEBUG_MODE{};
    int PARAM_DEBUG_SERVER_PORT{};
    int PARAM_DEBUG_CLIENT_PORT{};
    QString PARAM_PROJECT_PATH{};
    QString PARAM_HIASM_VERSION{};
    QString PARAM_USER_NAME{};
    QString PARAM_USER_MAIL{};
    QString PARAM_PROJECT_NAME{};
    uint PARAM_SDE_WIDTH{};
    uint PARAM_SDE_HEIGHT{};
    QString PARAM_COMPILER{};
};

//!ru Ошибки при работе с библиотекой кодогенератора
enum CgResult {
    //ru Успешное завершение.
    CG_SUCCESS = 0,

    //ru Кодогенератор не найден.
    CG_NOT_FOUND = 1,

    //ru Используемая версия среды не поддерживается.
    CG_INVALID_VERSION = 2,

    //ru Точка входа в кодогенератор не найдена.
    CG_ENTRY_POINT_NF = 3,

    //ru Общая ошибка при сборке проекта.
    CG_BUILD_FAILED = 10,

    //ru Результат компиляции не найден.
    CG_APP_NOT_FOUND = 20
};

//!ru Параметры проекта
enum ProjectFlags {
    //ru Поддерживает сжатие.
    CGMP_COMPRESSED = 0x01,

    //ru Поддерживает запуск из среды.
    CGMP_RUN = 0x02,

    //ru Поддерживает запуск из среды в отладочном режиме.
    CGMP_RUN_DEBUG = 0x04,

    //ru Поддерживает внешний редактор форм.
    CGMP_FORM_EDIT = 0x08
};
typedef QFlags<ProjectFlags> ProjectFlgs;

//!ru Типы используемые в CodeGenTools.
//ru Контейнер
typedef quintptr id_sdk;
//ru Элемент
typedef quintptr id_element;
//ru Точка
typedef quintptr id_point;
//ru Cвойство
typedef quintptr id_prop;
//ru Список свойств
typedef quintptr id_proplist;
//ru Массив
typedef quintptr id_array;
//ru Данные
typedef quintptr id_data;
//ru Шрифт
typedef quintptr id_font;

//!ru Структуры необходимые для работы кодогенератора и интерфейса.

struct TCodeGenTools;
typedef TCodeGenTools *PCodeGenTools;

//Требуется для export функции - CheckVersionProc.
struct THiAsmVersion {
    short int major{};
    short int minor{};
    short int build{};
};

//Требуется для export функции - buildPrepareProc.
struct TBuildPrepareRec {
    // none
};

//Требуется для export функции - buildProcessProc.
struct TCGrec {
    char *MainForm{};
    //char *Units;
    //char *IBody;
};
typedef TCGrec *PTCGrep;

struct TBuildProcessRec {
    PCodeGenTools cgt{};
    id_sdk sdk{};
    PTCGrep result{};
};

//Требуется для export функции - synReadFuncList.
struct TSynParams {
    //ru Имя текущего элемента.
    char *elName{};

    //ru Имя объекта.
    char *objName{};

    //ru Список методов и полей для вставки в редактор.
    char *inst_list{};

    //ru Список, отображаемый во всплывающей подсказке.
    char *disp_list{};
};

//Требуется для export функции - hintForElement.
struct THintParams {
    id_point point{};
    id_sdk sdk{};
    PCodeGenTools cgt{};
    char *hint{};
};

//Требуется для export функции - isReadyForAdd.
struct TRFD_Rec {
    char *name{};
    char *className{};
    char *inherit{};
    char *interfaces{};
    char *sub{};
};

struct TCodeGenTools {
#define CALLBACK __stdcall
    //!~~~~~~~~~~~~~~~~~~~~~~~~ контейнер ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает количество элементов в контейнере.
    CALLBACK int (*sdkGetCount)(id_sdk SDK);
    //ru Возвращает ID элемента по его Z-положению(индексу) в контейнере.
    CALLBACK id_element(*sdkGetElement)(id_sdk SDK, int Index);
    //ru Возвращает ID элемента по имени элемента.
    CALLBACK id_element(*sdkGetElementName)(id_sdk SDK, char *Name);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает флаги элемента.
    CALLBACK ElementFlags(*elGetFlag)(id_element e);
    //ru Возвращает количество свойств элемента.
    CALLBACK int (*elGetPropCount)(id_element e);
    //ru Возвращает свойство элемента по индексу, с порядковым номером из INI.
    CALLBACK id_prop(*elGetProperty)(id_element e, int Index);
    //ru Возвращает True, если значение свойства совпадает с заданным в INI файле, иначе False.
    CALLBACK bool (*elIsDefProp)(id_element e, int Index);
    //ru Присваиваем элементу уникальное имя и возвращаем ID этого элемента.
    CALLBACK id_element(*elSetCodeName)(id_element e, const char *Name);
    //ru Возвращает уникальное имя элемента
    CALLBACK const char *(*elGetCodeName)(id_element e);
    //ru Возвращает имя класса элемента.
    CALLBACK const char *(*elGetClassName)(id_element e);
    //ru Возвращает водержимое поля Sub из конфигурационного INI-файла элемента.
    CALLBACK const char *(*elGetInfSub)(id_element e);
    //ru Возвращает общее количество видимых точек у элемента.
    CALLBACK int (*elGetPtCount)(id_element e);
    //ru Возвращает ID точки по её индексу.
    CALLBACK id_point(*elGetPt)(id_element e, int i);
    //ru Возвращает ID точки по её имени.
    //[deprecated]
    CALLBACK id_point(*elGetPtName)(id_element e, const char *Name);
    //ru Возвращает индекс класса элемента.
    CALLBACK ElementClass(*elGetClassIndex)(id_element e);
    //ru Возвращает ID внутренней схемы для контейнеров
    //ru или ID родителя id_element для редактора контейнера (ELEMENT_FLG_IS_EDIT).
    CALLBACK id_sdk(*elGetSDK)(id_element e);
    //ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются.
    CALLBACK bool (*elLinkIs)(id_element e);
    //ru Возвращает ID главного элемента(тот, на который ссылаются другие).
    CALLBACK id_element(*elLinkMain)(id_element e);
    //ru Помещает в переменные "X" и "Y", позицию элемента в редакторе схем.
    CALLBACK void (*elGetPos)(id_element e, int &X, int &Y);
    //ru Помещает в переменные "W" и "H", размеры элемента
    CALLBACK void (*elGetSize)(id_element e, int &W, int &H);
    //ru Возвращает внутренний ID элемента (отличается от внешнего).
    //[deprecated]
    CALLBACK int (*elGetEID)(id_element e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID точки, с которой соединена указанная.
    //TODO [deprecated?], в CodeGen.dpr не используется.
    CALLBACK id_point(*ptGetLinkPoint)(id_point p);
    //ru Возвращает ID точки, с которой соединена указанная точка,
    //ru без учета точек разрыва и хабов.
    CALLBACK id_point(*ptGetRLinkPoint)(id_point p);
    //ru Возвращает тип точек(константы PointTypes).
    CALLBACK PointTypes(*ptGetType)(id_point p);
    //ru Возвращает имя точки.
    CALLBACK const char *(*ptGetName)(id_point p);
    //ru Возвращает ID элемента, которому принадлежит точка.
    CALLBACK id_element(*ptGetParent)(id_point p);
    //ru Возвращает тип точки (PointTypes).
    CALLBACK PointTypes(*ptGetIndex)(id_point p);
    //ru Возвращает базовую часть имени динамической точки(для CI_DPElement).
    CALLBACK const char *(*pt_dpeGetName)(id_point p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип свойства.
    CALLBACK DataTypes(*propGetType)(id_prop prop);
    //ru Возвращает имя свойства.
    CALLBACK const char *(*propGetName)(id_prop prop);
    //ru Возвращает значение свойства в виде указателя на данные.
    CALLBACK quintptr(*propGetValue)(id_prop prop);
    //ru Возвращает значение свойства в формате uchar.
    CALLBACK uchar (*propToByte)(id_prop prop);
    //ru Возвращает значение свойства в формате int.
    CALLBACK int (*propToInteger)(id_prop prop);
    //ru Возвращает значение свойства в формате float.
    CALLBACK float (*propToReal)(id_prop prop);
    //ru Возвращает значение свойства в виде C строки.
    CALLBACK const char *(*propToString)(id_prop prop);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Добавляет имя файла в общий список временных файлов
    //ru для последующего удаления файла.
    CALLBACK int (*resAddFile)(const char *Name);
    //ru Добавляет иконку в ресурсы и в список временных файлов,
    //ru и возвращают имя временного файла.
    //TODO p - является свойством, которое содержит иконку?
    CALLBACK const char *(*resAddIcon)(id_prop p);
    //ru Добавляет строку в ресурсы и в список временных файлов.
    //TODO Что возвращает?
    CALLBACK const char *(*resAddStr)(const char *p);
    //ru Добавляет поток (данные) в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    CALLBACK const char *(*resAddStream)(id_prop p);
    //ru Добавляет звук в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    CALLBACK const char *(*resAddWave)(id_prop p);
    //ru Добавляет картинку в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    CALLBACK const char *(*resAddBitmap)(id_prop p);
    //ru Добавляет меню в ресурсы и в список временных файлов.
    //[deprecated]
    CALLBACK const char *(*resAddMenu)(id_prop p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Выводит строку Text в окно Отладка цветом Color
    //ru Всего возвращает 0.
    CALLBACK int (*_Debug)(const char *Text, int Color);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает значение параметра среды по его индексу
    CALLBACK int (*GetParam)(CgtParams index, void *value);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ массив ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает количество элементов в массиве.
    CALLBACK int (*arrCount)(id_array a);
    //ru Возвращает тип элементов в массиве.
    CALLBACK DataTypes(*arrType)(id_array a);
    //ru Возвращает имя элемента с индексом Index.
    CALLBACK const char *(*arrItemName)(id_array a, int Index);
    //ru Возвращает значение элемента с индексом Index
    CALLBACK quintptr(*arrItemData)(id_array a, int Index);
    //ru Получаем элемент массива в виде свойства,
    //ru для дальнейшей работы с ним cgt::prop* функциями.
    CALLBACK id_data(*arrGetItem)(id_array a, int Index);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает >0, если запускаем cборку и запуск схемы в режиме отладки,
    //ru иначе 0.
    CALLBACK int (*isDebug)(id_sdk e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ работа с данными ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип данных.
    CALLBACK DataTypes(*dtType)(id_data d);
    //ru Возвращает данные в формате: строка в стиле C.
    CALLBACK const char *(*dtStr)(id_data d);
    //ru Возвращает данные в формате: целое число.
    CALLBACK int (*dtInt)(id_data d);
    //ru Возвращает данные в формате: число с плавающей запятой.
    CALLBACK double (*dtReal)(id_data d);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает название шрифта.
    CALLBACK const char *(*fntName)(id_font f);
    //ru Возвращает размер шрифта.
    CALLBACK int (*fntSize)(id_font f);
    //ru Возвращает стиль шрифта.
    CALLBACK uchar (*fntStyle)(id_font f);
    //ru Возвращает цвет шрифта.
    CALLBACK uint (*fntColor)(id_font f);
    //ru Возвращает кодировку шрифта.
    CALLBACK uchar (*fntCharSet)(id_font f);
    //!~~~~~~~~~~~~~~~~элемент | пользовательские данные ~~~~~~~~~~~~~
    //!ru Судя по CodeGen.dpr, используется для хранения указателя (ID элемента) на самого себя.
    //ru Возвращает пользовательские данные элемента.
    //ru Коммент из hiasm5 - user data used in FTCG codegen.
    //ru Судя по всему, данные могут быть любого типа, ибо хранит указатель..
    CALLBACK quintptr(*elGetData)(id_element e);
    //ru Устанавливает пользовательские данные элементу.
    //ru Коммент из hiasm5 - user data used in FTCG codegen.
    //ru Судя по всему, данные могут быть любого типа, ибо хранит указатель.
    CALLBACK void (*elSetData)(id_element e, const quintptr data);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип данных точки.
    CALLBACK DataTypes(*ptGetDataType)(id_point p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID родительского контейнера элемента.
    CALLBACK id_sdk(*elGetParent)(id_element e);
    //ru Возвращает количество свойств в списке свойств(из панели свойств).
    //ru В RTCG используется аналогичная функция - elGetPropCount.
    //[deprecated]
    CALLBACK int (*elGetPropertyListCount)(id_element e);
    //ru Возвращает свойство из списка свойств (PropertyList).
    //[deprecated]
    CALLBACK id_proplist(*elGetPropertyListItem)(id_element e, int i);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает имя свойства.
    CALLBACK const char *(*plGetName)(id_prop p);
    //ru Возвращает описание свойства.
    CALLBACK const char *(*plGetInfo)(id_prop p);
    //ru Возвращает группу свойсва.
    CALLBACK const char *(*plGetGroup)(id_prop p);
    //ru Возвращает указатель на данные свойства.
    CALLBACK quintptr(*plGetProperty)(id_prop p);
    //ru Возвращает ID родительского элемента указанного свойства.
    CALLBACK id_element(*plGetOwner)(id_prop p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает описание точки.
    CALLBACK const char *(*ptGetInfo)(id_point p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID элемента, прилинкованного к указанному свойству.
    CALLBACK id_element(*propGetLinkedElement)(id_element e, const char *propName);
    //ru Возвращает 1, если свойство помечено на перевод.
    CALLBACK int (*propIsTranslate)(id_element e, id_prop p);
    //ru Предназначение данной функции так и небыло найдено.
    //ru Всегда возвращает 0.
    //[deprecated]
    CALLBACK id_element(*propGetLinkedElementInfo)(id_element e, id_prop prop, char *_int);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент - CI_PolyMulti ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает SDK контейнера по его индексу.
    CALLBACK id_sdk(*elGetSDKByIndex)(id_element e, int index);
    //ru Возвращает количаство контейнеров полиморфного элемента(CI_PolyMulti).
    CALLBACK int (*elGetSDKCount)(id_element e);
    //ru Возвращает имя контейнера по индексу.
    CALLBACK const char *(*elGetSDKName)(id_element e, int index);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает элемент родитель для данного SDK.
    //ru Возвращает 0, если контейнер не имеет родителя.
    CALLBACK id_element(*sdkGetParent)(id_sdk SDK);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает интерфейсы, предоставляемые элементом.
    //ru Содержимое поля Interfaces= из конфигурации элемента.
    CALLBACK const char *(*elGetInterface)(id_element e);
    //ru Возвращает список классов, от которых наследуется элемент
    //ru Содержимое поля Inherit= из конфигурации элемента.
    CALLBACK const char *(*elGetInherit)(id_element e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает 1, если список ресурсов пуст, и 0 в противном случае.
    CALLBACK int (*resEmpty)();
    //ru Устанавливает префикс для имен ресурсов.
    CALLBACK int (*resSetPref)(const char *pref);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Добавляет информацию в информационную панель
    CALLBACK int (*_Error)(int line, id_element e, const char *text);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID группы, к которой принадлежит элемент и 0, если группа отсутствует
    //[deprecated]
    CALLBACK int (*elGetGroup)(id_element e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Сохраняет данные свойства в файл.
    //[deprecated]
    CALLBACK int (*propSaveToFile)(id_prop p, const char *fileName);
};
