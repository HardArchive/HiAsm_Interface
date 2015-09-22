#pragma once

//Project
#include "CGTShare.h"

//STL

//Qt

namespace fcgt
{
bool isSelect(const ElementFlgs &flags);
bool isParent(const ElementFlgs &flags);
bool isCore(const ElementFlgs &flags);
bool isNoDelete(const ElementFlgs &flags);
bool isMulti(const ElementFlgs &flags);
bool isEdit(const ElementFlgs &flags);
bool isSystem(const ElementFlgs &flags);


bool isEditMultiEx(const ClassesElements &eClass);
bool isPolyMulti(const ClassesElements &eClass);
}

class cgt
{
    static PCodeGenTools m_cgt;
    static id_sdk m_sdk;

public:
    //!~~~~~~~~~~~~~~~~~~~~~ служебные функции ~~~~~~~~~~~~~~~~~~~~~~~
    //ru Устанавливаем параметры
    static void setParams(TBuildProcessRec &params);
    inline static id_sdk getMainSDK()
    {
        return m_sdk;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ контейнер ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает количество элементов в контейнере.
    static int sdkGetCount(id_sdk SDK);
    //ru Возвращает ID элемента по его Z-положению(индексу) в контейнере.
    static id_element sdkGetElement(id_sdk SDK, int Index);
    //ru Возвращает ID элемента по имени элемента.
    static id_element sdkGetElementName(id_sdk SDK, char *Name);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает флаги элемента.
    static ElementFlags elGetFlag(id_element e);
    //ru Возвращает количество свойств элемента.
    static int elGetPropCount(id_element e);
    //ru Возвращает свойство элемента по индексу, с порядковым номером из INI.
    static id_prop elGetProperty(id_element e, int Index);
    //ru Возвращает True, если значение свойства совпадает с заданным в INI файле, иначе False.
    static bool elIsDefProp(id_element e, int Index);
    //ru Присваиваем элементу уникальное имя и возвращаем ID этого элемента.
    static id_element elSetCodeName(id_element e, const char *Name);
    //ru Возвращает уникальное имя элемента
    static const char *elGetCodeName(id_element e);
    //ru Возвращает имя класса элемента.
    static const char *elGetClassName(id_element e);
    //ru Возвращает водержимое поля Sub из конфигурационного INI-файла элемента.
    static const char *elGetInfSub(id_element e);
    //ru Возвращает общее количество видимых точек у элемента.
    static int elGetPtCount(id_element e);
    //ru Возвращает ID точки по её индексу.
    static id_point elGetPt(id_element e, int i);
    //ru Возвращает ID точки по её имени.
    //[deprecated]
    static id_point elGetPtName(id_element e, const char *Name);
    //ru Возвращает индекс класса элемента.
    static ClassesElements elGetClassIndex(id_element e);
    //ru Возвращает ID внутренней схемы для контейнеров,
    //ru или ID родителя id_element для редактора контейнера (ELEMENT_FLG_IS_EDIT).
    static id_sdk elGetSDK(id_element e);
    //ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются.
    static bool elLinkIs(id_element e);
    //ru Возвращает ID главного элемента(тот, на который ссылаются другие).
    static id_element elLinkMain(id_element e);
    //ru Помещает в переменные "X" и "Y", позицию элемента в редакторе схем.
    static void elGetPos(id_element e, int &X, int &Y);
    //ru Помещает в переменные "W" и "H", размеры элемента.
    static void elGetSize(id_element e, int &W, int &H);
    //ru Возвращает внутренний ID элемента (отличается от внешнего).
    //[deprecated]
    static int elGetEID(id_element e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID точки, с которой соединена указанная.
    //TODO [deprecated?], в CodeGen.dpr не используется.
    static id_point ptGetLinkPoint(id_point p);
    //ru Возвращает ID точки, с которой соединена указанная точка,
    //ru без учета точек разрыва и хабов.
    static id_point ptGetRLinkPoint(id_point p);
    //ru Возвращает тип точек(константы PointTypes).
    static PointTypes ptGetType(id_point p);
    //ru Возвращает имя точки.
    static const char *ptGetName(id_point p);
    //ru Возвращает ID элемента, которому принадлежит точка.
    static id_element ptGetParent(id_point p);
    //ru Возвращает тип точки (PointTypes).
    static PointTypes ptGetIndex(id_point p);
    //ru Возвращает базовую часть имени динамической точки(для CI_DPElement).
    static const char *pt_dpeGetName(id_point p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип свойства.
    static DataTypes propGetType(id_prop prop);
    //ru Возвращает имя свойства.
    static const char *propGetName(id_prop prop);
    //ru Возвращает значение свойства в виде указателя на данные.
    static quintptr propGetValue(id_prop prop);
    //ru Возвращает значение свойства в формате unsigned char.
    static unsigned char propToByte(id_prop prop);
    //ru Возвращает значение свойства в формате int.
    static int propToInteger(id_prop prop);
    //ru Возвращает значение свойства в формате float.
    static float propToReal(id_prop prop);
    //ru Возвращает значение свойства в виде C строки.
    static const char *propToString(id_prop prop);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Добавляет имя файла в общий список временных файлов
    //ru для последующего удаления файла.
    static int resAddFile(const char *Name);
    //ru Добавляет иконку в ресурсы и в список временных файлов,
    //ru и возвращают имя временного файла.
    //TODO p - является свойством, которое содержит иконку?
    static const char *resAddIcon(id_prop p);
    //ru Добавляет строку в ресурсы и в список временных файлов.
    //TODO Что возвращает?
    static const char *resAddStr(const char *p);
    //ru Добавляет поток (данные) в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    static const char *resAddStream(id_prop p);
    //ru Добавляет звук в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    static const char *resAddWave(id_prop p);
    //ru Добавляет картинку в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    static const char *resAddBitmap(id_prop p);
    //ru Добавляет меню в ресурсы и в список временных файлов.
    //[deprecated]
    static const char *resAddMenu(id_prop p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Выводит строку Text в окно Отладка цветом Color
    //ru Всего возвращает 0.
    static int _Debug(const char *Text, int Color);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает значение параметра среды по его индексу
    static int GetParam(CgtParams index, void *value);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ массив ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает количество элементов в массиве.
    static int arrCount(id_array a);
    //ru Возвращает тип элементов в массиве.
    static DataTypes arrType(id_array a);
    //ru Возвращает имя элемента с индексом Index.
    static const char *arrItemName(id_array a, int Index);
    //ru Возвращает значение элемента с индексом Index
    static quintptr arrItemData(id_array a, int Index);
    //ru Получаем элемент массива в виде свойства,
    //ru для дальнейшей работы с ним cgt::prop* функциями.
    static id_data arrGetItem(id_array a, int Index);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает true, если запускаем cборку и запуск схемы в режиме отладки,
    //ru иначе false.
    static bool isDebug(id_sdk e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ работа с данными ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип данных.
    static DataTypes dtType(id_data d);
    //ru Возвращает данные в формате: строка в стиле C.
    static const char *dtStr(id_data d);
    //ru Возвращает данные в формате: целое число.
    static int dtInt(id_data d);
    //ru Возвращает данные в формате: число с плавающей запятой.
    static double dtReal(id_data d);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает название шрифта.
    static const char *fntName(id_font f);
    //ru Возвращает размер шрифта.
    static int fntSize(id_font f);
    //ru Возвращает стиль шрифта.
    static unsigned char fntStyle(id_font f);
    //ru Возвращает цвет шрифта.
    static int fntColor(id_font f);
    //ru Возвращает кодировку шрифта.
    static unsigned char fntCharSet(id_font f);
    //!~~~~~~~~~~~~~~~~элемент | пользовательские данные ~~~~~~~~~~~~~
    //!ru Судя по CodeGen.dpr, используется для хранения указателя (ID элемента) на самого себя.
    //ru Возвращает пользовательские данные элемента.
    //ru Коммент из hiasm5 - user data used in FTCG codegen.
    //ru Судя по всему, данные могут быть любого типа, ибо хранит указатель..
    static quintptr elGetData(id_element e);
    //ru Устанавливает пользовательские данные элементу.
    //ru Коммент из hiasm5 - user data used in FTCG codegen.
    //ru Судя по всему, данные могут быть любого типа, ибо хранит указатель.
    static void elSetData(id_element e, const quintptr data);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип данных точки.
    static DataTypes ptGetDataType(id_point p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID родительского контейнера элемента.
    static id_sdk elGetParent(id_element e);
    //ru Возвращает количество свойств в списке свойств(из панели свойств).
    //ru В RTCG используется аналогичная функция - elGetPropCount.
    //[deprecated]
    static int elGetPropertyListCount(id_element e);
    //ru Возвращает свойство из списка свойств (PropertyList).
    //[deprecated]
    static id_proplist elGetPropertyListItem(id_element e, int i);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает имя свойства.
    static const char *plGetName(id_prop p);
    //ru Возвращает описание свойства.
    static const char *plGetInfo(id_prop p);
    //ru Возвращает группу свойсва.
    static const char *plGetGroup(id_prop p);
    //ru Возвращает указатель на данные свойства.
    static quintptr plGetProperty(id_prop p);
    //ru Возвращает ID родительского элемента указанного свойства.
    static id_element plGetOwner(id_prop p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает описание точки.
    static const char *ptGetInfo(id_point p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID элемента, прилинкованного к указанному свойству.
    static id_element propGetLinkedElement(id_element e, const char *propName);
    //ru Возвращает 1, если свойство помечено на перевод.
    static int propIsTranslate(id_element e, id_prop p);
    //ru Предназначение данной функции так и небыло найдено.
    //ru Всегда возвращает 0.
    //[deprecated]
    static id_element propGetLinkedElementInfo(id_element e, id_prop prop, char *_int);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент - CI_PolyMulti ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает SDK контейнера по его индексу.
    static id_sdk elGetSDKByIndex(id_element e, int index);
    //ru Возвращает количаство контейнеров полиморфного элемента(CI_PolyMulti).
    static int elGetSDKCount(id_element e);
    //ru Возвращает имя контейнера по индексу.
    static const char *elGetSDKName(id_element e, int index);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает элемент родитель для данного SDK.
    //ru Возвращает 0, если контейнер не имеет родителя.
    static id_element sdkGetParent(id_sdk SDK);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает интерфейсы, предоставляемые элементом.
    //ru Содержимое поля Interfaces= из конфигурации элемента.
    static const char *elGetInterface(id_element e);
    //ru Возвращает список классов, от которых наследуется элемент
    //ru Содержимое поля Inherit= из конфигурации элемента.
    static const char *elGetInherit(id_element e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает 1, если список ресурсов пуст, и 0 в противном случае.
    static int resEmpty();
    //ru Устанавливает префикс для имен ресурсов.
    static int resSetPref(const char *pref);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Добавляет информацию в информационную панель
    static int _Error(int line, id_element e, const char *text);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID группы, к которой принадлежит элемент и 0, если группа отсутствует
    //[deprecated]
    static int elGetGroup(id_element e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Сохраняет данные свойства в файл.
    //[deprecated]
    static int propSaveToFile(id_prop p, const char *fileName);
};
