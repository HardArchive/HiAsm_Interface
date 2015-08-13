#ifndef _CGTSHARE_H_
#define _CGTSHARE_H_

//STL

//Qt
#include <QBitArray>

//Project

#ifdef BUILDING_DLL
#ifndef HIASM_5
//!ru Флаги элемента
enum ElementFlags {
    //ru Элемент выбран
    ELEMENT_FLG_IS_SELECT = 0x100,

    //ru С элементом нельзя взаимодействовать с помощью мыши?
    //TODO Нужна дополнительная информация по этому флагу.
    ELEMENT_FLG_IS_NOMOUSE = 0x2000,

    //ru Родитель для элементов текущей SDK
    ELEMENT_FLG_IS_PARENT = 0x200,

    //ru Элемент является базовым
    ELEMENT_FLG_IS_CORE = 0x400,

    //ru Элемент заморожен (нельзя перемещать)
    ELEMENT_FLG_IS_FREEZE = 0x0,

    //ru Элемент нельзя удалить
    ELEMENT_FLG_IS_NODELETE = 0x2,

    //ru Элемент является контейнером
    ELEMENT_FLG_IS_MULTI = 0x40,

    //ru Элемент является графическим контром (виджетом)
    ELEMENT_FLG_ONE_WIDGET = 0x8,

    //ru Элемент является редактором контейнера
    //ru Например: EditMulti, EditMultiEx, EditPoliMulti
    ELEMENT_FLG_IS_EDIT = 0x20,

    //ru Элемент является системным
    //ru Например: CI_HubEx, CI_GetDataEx, ElementInfoTip, HCButton
    ELEMENT_FLG_IS_SYSTEM = 0x400,
};
typedef QFlags<ElementFlags> ElementFlgs;
#else
enum ElementFlags {
    ELEMENT_FLG_IS_SELECT = 0x01,
    ELEMENT_FLG_IS_NOMOUSE = 0x02,
    ELEMENT_FLG_IS_PARENT = 0x04,
    ELEMENT_FLG_IS_CORE = 0x08,
    ELEMENT_FLG_IS_FREEZE = 0x10,
    ELEMENT_FLG_IS_NODELETE = 0x20,
    ELEMENT_FLG_IS_MULTI = 0x40,
    ELEMENT_FLG_ONE_WIDGET = 0x80,
    ELEMENT_FLG_IS_EDIT = 0x100,
    ELEMENT_FLG_IS_SYSTEM = 0x400,
};
typedef QFlags<ElementFlags> ElementFlgs;
#endif
#else
enum ElementFlags {
    ELEMENT_FLG_IS_SELECT = 0x01,
    ELEMENT_FLG_IS_NOMOUSE = 0x02,
    ELEMENT_FLG_IS_PARENT = 0x04,
    ELEMENT_FLG_IS_CORE = 0x08,
    ELEMENT_FLG_IS_FREEZE = 0x10,
    ELEMENT_FLG_IS_NODELETE = 0x20,
    ELEMENT_FLG_ONE_WIDGET = 0x80,
    ELEMENT_FLG_IS_SYSTEM = 0x400,
};
typedef QFlags<ElementFlags> ElementFlgs;
#endif

//!ru Типы точек
enum PointsTypes {
    //ru Метод
    pt_Work = 1,

    //ru Событие
    pt_Event = 2,

    //ru Переменная
    pt_Var = 3,

    //ru Данные
    pt_Data = 4,
};

//!ru Типы данных
enum DataTypes {
    data_null = 0,
    data_int = 1,
    data_str = 2,
    data_data = 3,
    data_combo = 4,
    data_list = 5,
    data_icon = 6,
    data_real = 7,
    data_color = 8,
    data_script = 9,
    data_stream = 10,
    data_bitmap = 11,
    data_wave = 12,
    data_array = 13,
    data_comboEx = 14,
    data_font = 15,
    data_matr = 16,
    data_jpeg = 17,
    data_menu = 18,
    data_code = 19,
    data_element = 20,
    data_flags = 21,
};

//!ru Классы элемента (elGetClassIndex)
//TODO Дополнить описание.
enum ElementClasses {
    //ru Простой элемент
    CI_Element = 0,

    CI_DPElement = 1,

    CI_MultiElement = 2,

    //ru Простой контейнер
    CI_EditMulti = 3,

    //ru Динамический контейнер
    CI_EditMultiEx = 4,

    //ru Вставка кода
    CI_InlineCode = 5,

    CI_DrawElement = 6,

    CI_AS_Special = 7,

    CI_DPLElement = 8,

    CI_UseHiDLL = 9,

    CI_WinElement = 10,

    CI_PointHint = 11,

    CI_PointElement = 12,

    //ru Разрыв
    CI_LineBreak = 13,

    //ru Разрыв связи
    CI_LineBreakEx = 14,

    //ru Пользовательский элемент
    CI_UserElement = 15,

    //ru Полиморфный контейнер
    CI_PolyMulti = 17,
};

//!ru Индексы параметров среды
//TODO Что за индексы параметов среды? Дополнить описание.
enum ParamsIde {
    PARAM_CODE_PATH = 0,
    PARAM_DEBUG_MODE = 1,
    PARAM_DEBUG_SERVER_PORT = 2,
    PARAM_DEBUG_CLIENT_PORT = 3,
    PARAM_PROJECT_PATH = 4,
    PARAM_HIASM_VERSION = 5,
    PARAM_USER_NAME = 6,
    PARAM_USER_MAIL = 7,
    PARAM_PROJECT_NAME = 8,
    PARAM_SDE_WIDTH = 9,
    PARAM_SDE_HEIGHT = 10,
    PARAM_COMPILER = 11,
};

//!ru Ошибки при работе с библиотекой кодогенератора
enum CgResult {
    //ru Успешное завершение
    CG_SUCCESS = 0,

    //ru Кодогенератор не найден
    //TODO Что будет, если вернуть ?)
    CG_NOT_FOUND = 1,

    //ru Используемая версия среды не поддерживается
    CG_INVALID_VERSION = 2,

    //ru Точка входа в кодогенератор не найдена
    //TODO И этот статус тоже проверить.
    CG_ENTRY_POINT_NF = 3,

    //ru Файл модуля кода не найден
    //TODO Модуля кода? Тоже проверить.
    CG_MODULE_FILE_NF = 4,

    //ru Общая ошибка при сборке проекта
    CG_BUILD_FAILED = 10,

    //ru Результат компиляции не найден
    CG_APP_NOT_FOUND = 20,
};

//!ru Параметры проекта
enum ParamsProject {
    //ru Поддерживает сжатие
    //TODO Подробнее изучить этот параметр и дополнить описание.
    CGMP_COMPRESSED = 0x01,

    //ru Поддерживает запуск из среды
    CGMP_RUN = 0x02,

    //ru Поддерживает запуск из среды в отладочном режиме
    CGMP_RUN_DEBUG = 0x04,

    //ru Поддерживает внешний редактор форм
    CGMP_FORM_EDIT = 0x08,
};

//!ru Типы, используемые в интерфейсе
//ru Контейнер (уровень схемы)
typedef quintptr id_sdk;
//ru Элемент
typedef quintptr id_element;
//ru Точка
typedef quintptr id_point;
//ru Значение свойства
typedef quintptr id_prop;
typedef quintptr id_value;
//ru Свойство
typedef quintptr id_proplist;
//ru Массив
typedef quintptr id_array;
//ru Данные
typedef quintptr id_data;
//ru Шрифт
typedef quintptr id_font;

struct TCodeGenTools;

typedef TCodeGenTools *PCodeGenTools;

//!ru Структуры кодогенератора и интерфейсы точки входа
//!en CodeGen types and entry point interfaces
//TODO Составить описание для данных структур.

struct THiAsmVersion {
    short int major;
    short int minor;
    short int build;
};

struct TBuildPrepareRec {
    // none
};

struct TCGrec {
    char *MainForm{};
    quintptr Units{};
    quintptr IBody{};
};
typedef TCGrec *PCGrec;

struct TBuildProcessRec {
    PCodeGenTools cgt;
    id_sdk sdk;
    PCGrec result;
};

struct TBuildMakePrjRec {
    quintptr result;
    char *prjFilename;
    char *compiler;
};

struct TBuildCompliteRec {
    char *prjFilename;
    char *appFilename;
};

struct TBuildParams {
    int flags;
};

struct TBuildRunRec {
    char *FileName;
    int Mode;
    int ServerPort;
    int ClientPort;
    quintptr data;
};

//!ru Дополнительные структуры
//TODO Выяснить, для чего эти структуры нужны.

struct TSynParams {
    //ru Имя текущего элемента
    char *elName;

    //ru Имя объекта
    char *objName;

    //ru Список методов и полей для вставки в редактор
    char *inst_list;

    //ru Список, отображаемый во всплывающей подсказке
    char *disp_list;
};

struct THintParams {
    id_point point;
    id_sdk sdk;
    PCodeGenTools cgt;
    char *hint;
};

struct TRFD_Rec {
    char *name;
    char *className;
    char *inherit;
    char *interfaces;
    char *sub;
};

struct TCodeGenTools {
#define CALLBACK __stdcall

    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает количество элементов в схеме.
    //ru Элементы в контейнерах не считаются
    CALLBACK int (*sdkGetCount)(id_sdk SDK);

    //ru Возвращает идентификатор элемента по его Z-координате(индексу)
    CALLBACK id_element(*sdkGetElement)(id_sdk SDK, int Index);

    //ru Возвращает идентификатор элемента по имени его класса
    CALLBACK id_element(*sdkGetElementName)(id_sdk SDK, char *Name);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает флаги элемента по его идентификатору
    CALLBACK ElementFlags(*elGetFlag)(id_element e);

    //ru Возвращает кол-во св-в элемента
    CALLBACK int (*elGetPropCount)(id_element e);

    //ru Возвращает целую структуру для конкретного св-ва с порядковым номером из INI
    CALLBACK id_prop(*elGetProperty)(id_element e, int Index);

    //ru Возвращает True, если значение св-ва совпадает с заданным в INI файле, иначе False
    CALLBACK bool (*elIsDefProp)(id_element e, int Index);

    //ru Присваиваем элементу уникальное имя
    CALLBACK id_element(*elSetCodeName)(id_element e, char *Name);

    //ru Получаем уникальное имя элемента
    CALLBACK char *(*elGetCodeName)(id_element e);

    //ru Получаем имя класса элемента
    CALLBACK char *(*elGetClassName)(id_element e);

    //ru Просто содержимое поля Sub из INI-файла элемента
    //TODO Выяснить, что за "просто содержимое" поля Sub и дополнить описание.
    CALLBACK char *(*elGetInfSub)(id_element e);

    //ru Получаем общее количество точек у элемента
    CALLBACK int (*elGetPtCount)(id_element e);

    //ru Получаем идентификатор точки по её индексу
    CALLBACK id_point(*elGetPt)(id_element e, int i);

    //ru Получаем идентификатор точки по её имени
    CALLBACK id_point(*elGetPtName)(id_element e, const char *Name);

    //ru Получаем подкласс элемента
    CALLBACK ElementClasses(*elGetClassIndex)(id_element e);

    //ru Получаем идентификатор внутренней схемы для контейнеров
    //ru и идентификатор родителя id_element для редактора контейнера
    CALLBACK id_sdk(*elGetSDK)(id_element e);

    //ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются
    CALLBACK bool (*elLinkIs)(id_element e);

    //ru Возвращает идент главного элемента(тот, на который ссылаются другие)
    CALLBACK id_element(*elLinkMain)(id_element e);

    //ru Помещаем в переменные "X" и "Y", позицию элемента в редакторе схем
    CALLBACK void (*elGetPos)(id_element e, int &X, int &Y);

    //ru Помещаем в переменные "W" и "H", размеры элемента в редакторе схем
    CALLBACK void (*elGetSize)(id_element e, int &W, int &H);

    //ru Неизвестно для чего эта функция.
    //ru Возможно, возвращает уникальное число.
    //ru Можно считать её - deprecated.
    CALLBACK int (*elGetEID)(id_element e);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает идентификатор точки, с которой соеденена данная
    CALLBACK id_point(*ptGetLinkPoint)(id_point p);

    //ru Возвращает идентификатор точки, с которой соеденена данная точка,
    //ru без учета точек разрыва и хабов
    CALLBACK id_point(*ptGetRLinkPoint)(id_point p);

    //ru Возвращает тип точек(константы pt_XXX)
    CALLBACK PointsTypes(*ptGetType)(id_point p);

    //ru Возвращает имя точки
    CALLBACK char *(*ptGetName)(id_point p);

    //ru Возвращает идентификатор элемента, которому принадлежит точка
    CALLBACK id_element(*ptGetParent)(id_point p);

    //ru Возвращает относительный индекс точки по принадлежности к одной из 4х групп
    //TODO Выяснить, что представлять из себя "относительный индекс точки" и дополнить описание.
    CALLBACK int (*ptGetIndex)(id_point p);

    //ru Возвращает базовую часть имени динамических точек(для CI_DPElement)
    CALLBACK char *(*pt_dpeGetName)(id_point p);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип параметра
    CALLBACK DataTypes(*propGetType)(id_prop prop);

    //ru Возвращает имя параметра
    CALLBACK char *(*propGetName)(id_prop prop);

    //ru Возвращает значение параметра
    CALLBACK quintptr(*propGetValue)(id_prop prop);

    //TODO propTo функции, возвращают свойство в указанном типе? Дополнить описание.

    //ru ???
    CALLBACK unsigned char (*propToByte)(id_prop prop);

    //ru ???
    CALLBACK int (*propToInteger)(id_prop prop);

    //ru ???
    CALLBACK float (*propToReal)(id_prop prop);

    //ru ???
    CALLBACK char *(*propToString)(id_prop prop);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    /*
     *ru Функции resAdd* возвращают имя временного файла, в который сохраняется ресурс.
     *ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
     *ru работы с библиотекой.
     *
     */

    //ru Добавляет имя файла в общий список временных файлов для последующего удаления
    CALLBACK int (*resAddFile)(const char *Name);

    //ru Добавляет иконку в ресурсы и в список временных файлов
    CALLBACK char *(*resAddIcon)(id_prop p);

    //ru Добавляет строку в ресурсы и в список временных файлов
    CALLBACK char *(*resAddStr)(const char *p);

    //ru Добавляет поток в ресурсы и в список временных файлов
    CALLBACK char *(*resAddStream)(id_prop p);

    //ru Добавляет звук в ресурсы и в список временных файлов
    CALLBACK char *(*resAddWave)(id_prop p);

    //ru Добавляет картинку в ресурсы и в список временных файлов
    CALLBACK char *(*resAddBitmap)(id_prop p);

    //ru Добавляет меню в ресурсы и в список временных файлов
    CALLBACK char *(*resAddMenu)(id_prop p);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Выводит строку Text в окно Отладка цветом Color
    //TODO Что возвращается данной функцией? Выяснить и дополнить описание.
    CALLBACK int (*_Debug)(const char *Text, int Color);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //TODO Выяснить предназначение этой функции.
    //ru Возвращает значение параметра среды по его индексу
    CALLBACK int (*GetParam)(short int index, char *value);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ массивы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает кол-во элементов в массиве а
    CALLBACK int (*arrCount)(id_array a);

    //ru Возвращает тип элементов в массиве а
    CALLBACK DataTypes(*arrType)(id_array a);

    //ru Возвращает имя элемента с индексом Index
    CALLBACK char *(*arrItemName)(id_array a, int Index);

    //ru Возвращает значение элемента с индексом Index
    CALLBACK quintptr(*arrItemData)(id_array a, int Index);

    //ru ???
    //TODO Выяснить предназначение данной функции.
    //p.s. Возможно, тут производится работа со свойствов... чего?
    CALLBACK id_data(*arrGetItem)(id_array a, int Index);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru ???
    //TODO Выяснить предназначение данной функции.
    CALLBACK bool (*isDebug)(id_sdk e);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ данные ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //TODO Преобразование данные?
    //TODO Или просто возращаем в нужном типе?
    //TODO id_data? Где он берётся?

    CALLBACK unsigned char (*dtType)(id_data d);
    CALLBACK char *(*dtStr)(id_data d);
    CALLBACK int (*dtInt)(id_data d);
    CALLBACK double (*dtReal)(id_data d);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //TODO Возвращает название шрифта по идентификатору?
    //TODO id_font? Где он берётся?
    CALLBACK char *(*fntName)(id_font f);
    CALLBACK int (*fntSize)(id_font f);
    CALLBACK unsigned char (*fntStyle)(id_font f);
    CALLBACK int (*fntColor)(id_font f);
    CALLBACK unsigned char (*fntCharSet)(id_font f);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //TODO Пользовательские данные? Выяснить и дополнить описание.
    //ru Получает пользовательские данные элемента
    CALLBACK quintptr(*elGetData)(id_element e);

    //TODO Пользовательские данные? Выяснить и дополнить описание.
    //ru Устанавливает пользовательские данные элемента
    CALLBACK void (*elSetData)(id_element e, char *data);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип данных точки
    CALLBACK DataTypes(*ptGetDataType)(id_point p);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает идентификатор родителя
    CALLBACK id_sdk(*elGetParent)(id_element e);

    //ru Возвращает количество элементов в списке св-тв(из панели св-ва)
    //ru В RTCG используется аналогичный метод - elGetPropCount
    CALLBACK int (*elGetPropertyListCount)(id_element e);

    //ru Возвращает элемент списка св-тв (PropertyList)
    CALLBACK id_proplist(*elGetPropertyListItem)(id_element e, int i);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает имя св-ва
    CALLBACK char *(*plGetName)(id_proplist p);

    //ru Возвращает описание св-ва
    CALLBACK char *(*plGetInfo)(id_proplist p);

    //ru Возвращает группу св-ва
    CALLBACK char *(*plGetGroup)(id_proplist p);

    //ru Возвращает значение св-ва
    CALLBACK id_prop(*plGetProperty)(id_proplist p);

    //ru Возвращает родительский элемент даного св-ва
    CALLBACK id_element(*plGetOwner)(id_proplist p);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает описание точки
    CALLBACK char *(*ptGetInfo)(id_point p);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает идентификатор элемента, прилинкованного к указанному св-ву
    //TODO Как это? Выяснить и дополнить описание.
    CALLBACK id_element(*propGetLinkedElement)(id_element e, const char *propName);

    //ru Возвращает 1 если св-во помечено на перевод
    //TODO Выяснить, где в среде можно помечать свойства на перевод.
    CALLBACK int (*propIsTranslate)(id_element e, id_prop p);

    //ru ???
    //TODO Выяснить, для чего предназначена данная функция.
    CALLBACK id_element(*propGetLinkedElementInfo)(id_element e, id_prop prop, const char *_int);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает SDK полиморфного контейнера по его индексу
    CALLBACK id_sdk(*elGetSDKByIndex)(id_element e, int index);

    //ru Возвращает количаство сабклассов полиморфного контейнера
    CALLBACK int (*elGetSDKCount)(id_element e);

    //ru Возвращает имя контейнера?
    //TODO Выяснить, точно ли данная функция возвращает имя текущего(?) контейнера.
    CALLBACK char *(*elGetSDKName)(id_element e, int index);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает элемент родитель для данного SDK
    CALLBACK id_element(*sdkGetParent)(id_sdk SDK);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает интерфейсы, предоставляемые элементом
    CALLBACK char *(*elGetInterface)(id_element e);

    //ru Возвращает классы, от которых наследуется элемент
    CALLBACK char *(*elGetInherit)(id_element e);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает 1 если список ресурсов пуст, и 0 в противном случае
    CALLBACK int (*resEmpty)();

    //ru Устанавливает префикс для имен ресурсов
    CALLBACK int (*resSetPref)(const char *pref);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Добавляет информацию в панель ошибок
    CALLBACK int (*_Error)(int line, id_element e, const char *text);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID группы, к которой принадлежит элемент и 0, если группа отсутствует
    CALLBACK int (*elGetGroup)(id_element e);

    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru ???
    //TODO Выяснить, для чего предназначена данная функция.
    CALLBACK int (*propSaveToFile)(id_prop p, const char *fileName);

    //ru "MSDK" - определение вызовов, оптимизирующих производительность.
    //ru Вызовы реализованы в стороннем проекте HiAsm SDK.
    //ru http://forum.hiasm.com/forum.html?q=3&p=273676#p273676
    //TODO Нужно будет решить, что с ними делать.
#ifdef MSDK
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru ???
    CALLBACK id_prop(*elGetPropertyName)(id_element e, const char *name);

    //ru ???
    CALLBACK bool (*elIsDefProperty)(id_element e, id_prop p);
#endif
};

#endif // _CGTSHARE_H_
