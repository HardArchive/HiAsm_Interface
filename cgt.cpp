//Project
#include "cgt.h"
#include "proxycgt.h"
#include "global.h"

//STL

//Qt
#include <QDebug>
#include <QFlags>

namespace fcgt
{
    bool isSelect(const ElementFlgs &flags)
    {
        return flags & ELEMENT_FLG_IS_SELECT;
    }

    bool isParent(const ElementFlgs &flags)
    {
        return flags & ELEMENT_FLG_IS_PARENT;
    }

    bool isCore(const ElementFlgs &flags)
    {
        return flags & ELEMENT_FLG_IS_CORE;
    }

    bool isNoDelete(const ElementFlgs &flags)
    {
        return flags & ELEMENT_FLG_IS_NODELETE;
    }

    bool isMulti(const ElementFlgs &flags)
    {
        return flags & ELEMENT_FLG_IS_MULTI;
    }

    bool isEdit(const ElementFlgs &flags)
    {
        return flags & ELEMENT_FLG_IS_EDIT;
    }

    bool isEditMultiEx(const ElementClass &eClass)
    {
        return eClass == CI_EditMultiEx;
    }

    bool isPolyMulti(const ElementClass &eClass)
    {
        return eClass == CI_PolyMulti;
    }
}



//!~~~~~~~~~~~~~~~~~~~~~ служебные функции ~~~~~~~~~~~~~~~~~~~~~~~

PCodeGenTools cgt::m_cgt = nullptr;
id_sdk cgt::m_sdk{};

//ru Устанавливаем параметры
void cgt::setParams(TBuildProcessRec &params)
{
    ProxyCgt::saveOriginalCgt(params.cgt);

#ifdef PROXYCGT
    params.cgt = ProxyCgt::getProxyCgt();
#endif

    m_cgt = params.cgt;
    m_sdk = params.sdk;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ контейнер ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает количество элементов в контейнере.

int cgt::sdkGetCount(id_sdk SDK)
{
    return m_cgt->sdkGetCount(SDK);
}

//ru Возвращает ID элемента по его Z-положению(индексу) в контейнере.
id_element cgt::sdkGetElement(id_sdk SDK, int Index)
{
    return m_cgt->sdkGetElement(SDK, Index);
}

//ru Возвращает ID элемента по имени элемента.
id_element cgt::sdkGetElementName(id_sdk SDK, char *Name)
{
    return m_cgt->sdkGetElementName(SDK, Name);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает флаги элемента.
ElementFlags cgt::elGetFlag(id_element e)
{
    return m_cgt->elGetFlag(e);
}

//ru Возвращает количество свойств элемента.
int cgt::elGetPropCount(id_element e)
{
    return m_cgt->elGetPropCount(e);
}

//ru Возвращает свойство элемента по индексу, с порядковым номером из INI.
id_prop cgt::elGetProperty(id_element e, int Index)
{
    return m_cgt->elGetProperty(e, Index);
}

//ru Возвращает True, если значение свойства совпадает с заданным в INI файле, иначе False.
bool cgt::elIsDefProp(id_element e, int Index)
{
    return m_cgt->elIsDefProp(e, Index);
}

//ru Присваиваем элементу уникальное имя и возвращаем ID этого элемента.
id_element cgt::elSetCodeName(id_element e, const char *Name)
{
    return m_cgt->elSetCodeName(e, Name);
}

//ru Возвращает уникальное имя элемента
const char *cgt::elGetCodeName(id_element e)
{
    return m_cgt->elGetCodeName(e);
}

//ru Возвращает имя класса элемента.
const char *cgt::elGetClassName(id_element e)
{
    return m_cgt->elGetClassName(e);
}

//ru Возвращает водержимое поля Sub из конфигурационного INI-файла элемента.
const char *cgt::elGetInfSub(id_element e)
{
    return m_cgt->elGetInfSub(e);
}

//ru Возвращает общее количество видимых точек у элемента.
int cgt::elGetPtCount(id_element e)
{
    return m_cgt->elGetPtCount(e);
}

//ru Возвращает ID точки по её индексу.
id_point cgt::elGetPt(id_element e, int i)
{
    return m_cgt->elGetPt(e, i);
}

//ru Возвращает ID точки по её имени.
//[deprecated]
id_point cgt::elGetPtName(id_element e, const char *Name)
{
    return m_cgt->elGetPtName(e, Name);
}

//ru Возвращает индекс класса элемента.
ElementClass cgt::elGetClassIndex(id_element e)
{
    return m_cgt->elGetClassIndex(e);
}

//ru Возвращает ID внутренней схемы для контейнеров,
//ru или ID родителя id_element для редактора контейнера (ELEMENT_FLG_IS_EDIT).
id_sdk cgt::elGetSDK(id_element e)
{
    return m_cgt->elGetSDK(e);
}

//ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются.
bool cgt::elLinkIs(id_element e)
{
    return m_cgt->elLinkIs(e);
}

//ru Возвращает ID главного элемента(тот, на который ссылаются другие).
id_element cgt::elLinkMain(id_element e)
{
    return m_cgt->elLinkMain(e);
}

//ru Помещает в переменные "X" и "Y", позицию элемента в редакторе схем.
void cgt::elGetPos(id_element e, int &X, int &Y)
{
    m_cgt->elGetPos(e, X, Y);
}

//ru Помещает в переменные "W" и "H", размеры элемента.
void cgt::elGetSize(id_element e, int &W, int &H)
{
    m_cgt->elGetSize(e, W, H);
}

//ru Возвращает внутренний ID элемента (отличается от внешнего).
//[deprecated]
int cgt::elGetEID(id_element e)
{
    return m_cgt->elGetEID(e);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID точки, с которой соединена указанная.
//TODO [deprecated?], в CodeGen.dpr не используется.
id_point cgt::ptGetLinkPoint(id_point p)
{
    return m_cgt->ptGetLinkPoint(p);
}

//ru Возвращает ID точки, с которой соединена указанная точка,
//ru без учета точек разрыва и хабов.
id_point cgt::ptGetRLinkPoint(id_point p)
{
    return m_cgt->ptGetRLinkPoint(p);
}

//ru Возвращает тип точек(константы PointTypes).
PointTypes cgt::ptGetType(id_point p)
{
    return m_cgt->ptGetType(p);
}

//ru Возвращает имя точки.
const char *cgt::ptGetName(id_point p)
{
    return m_cgt->ptGetName(p);
}

//ru Возвращает ID элемента, которому принадлежит точка.
id_element cgt::ptGetParent(id_point p)
{
    return m_cgt->ptGetParent(p);
}

//ru Возвращает тип точки (PointTypes).
PointTypes cgt::ptGetIndex(id_point p)
{
    return m_cgt->ptGetIndex(p);
}

//ru Возвращает базовую часть имени динамической точки(для CI_DPElement).
const char *cgt::pt_dpeGetName(id_point p)
{
    return m_cgt->pt_dpeGetName(p);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает тип свойства.
DataTypes cgt::propGetType(id_prop prop)
{
    return m_cgt->propGetType(prop);
}

//ru Возвращает имя свойства.
const char *cgt::propGetName(id_prop prop)
{
    return m_cgt->propGetName(prop);
}

//ru Возвращает значение свойства в виде указателя на данные.
quintptr cgt::propGetValue(id_prop prop)
{
    return m_cgt->propGetValue(prop);
}

//ru Возвращает значение свойства в формате unsigned char.
unsigned char cgt::propToByte(id_prop prop)
{
    return m_cgt->propToByte(prop);
}

//ru Возвращает значение свойства в формате int.
int cgt::propToInteger(id_prop prop)
{
    return m_cgt->propToInteger(prop);
}

//ru Возвращает значение свойства в формате float.
float cgt::propToReal(id_prop prop)
{
    return m_cgt->propToReal(prop);
}

//ru Возвращает значение свойства в виде C строки.
const char *cgt::propToString(id_prop prop)
{
    return m_cgt->propToString(prop);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~

//ru Добавляет имя файла в общий список временных файлов
//ru для последующего удаления файла.
int cgt::resAddFile(const char *Name)
{
    return m_cgt->resAddFile(Name);
}

//ru Добавляет иконку в ресурсы и в список временных файлов,
//ru и возвращают имя временного файла.
//TODO p - является свойством, которое содержит иконку?
const char *cgt::resAddIcon(id_prop p)
{
    return m_cgt->resAddIcon(p);
}

//ru Добавляет строку в ресурсы и в список временных файлов.
//TODO Что возвращает?
const char *cgt::resAddStr(const char *p)
{
    return m_cgt->resAddStr(p);
}

//ru Добавляет поток (данные) в ресурсы и в список временных файлов,
//ru и возвращает имя временного файла.
//ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
//ru работы с библиотекой.
const char *cgt::resAddStream(id_prop p)
{
    return m_cgt->resAddStream(p);
}

//ru Добавляет звук в ресурсы и в список временных файлов,
//ru и возвращает имя временного файла.
//ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
//ru работы с библиотекой.
const char *cgt::resAddWave(id_prop p)
{
    return m_cgt->resAddWave(p);
}

//ru Добавляет картинку в ресурсы и в список временных файлов,
//ru и возвращает имя временного файла.
//ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
//ru работы с библиотекой.
const char *cgt::resAddBitmap(id_prop p)
{
    return m_cgt->resAddBitmap(p);
}

//ru Добавляет меню в ресурсы и в список временных файлов.
//[deprecated]
const char *cgt::resAddMenu(id_prop p)
{
    return m_cgt->resAddMenu(p);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Выводит строку Text в окно Отладка цветом Color
//ru Всего возвращает 0.
int cgt::_Debug(const char *Text, int Color)
{
    return m_cgt->_Debug(Text, Color);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает значение параметра среды по его индексу
int cgt::GetParam(CgtParams index, void *value)
{
    return m_cgt->GetParam(index, value);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ массив ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает количество элементов в массиве.
int cgt::arrCount(id_array a)
{
    return m_cgt->arrCount(a);
}

//ru Возвращает тип элементов в массиве.
DataTypes cgt::arrType(id_array a)
{
    return m_cgt->arrType(a);
}

//ru Возвращает имя элемента с индексом Index.
const char *cgt::arrItemName(id_array a, int Index)
{
    return m_cgt->arrItemName(a, Index);
}

//ru Возвращает значение элемента с индексом Index
quintptr cgt::arrItemData(id_array a, int Index)
{
    return m_cgt->arrItemData(a, Index);
}

//ru Получаем элемент массива в виде свойства,
//ru для дальнейшей работы с ним cgt::prop* функциями.
id_data cgt::arrGetItem(id_array a, int Index)
{
    return m_cgt->arrGetItem(a, Index);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает true, если запускаем cборку и запуск схемы в режиме отладки,
//ru иначе false.
bool cgt::isDebug(id_sdk e)
{
    return m_cgt->isDebug(e);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ работа с данными ~~~~~~~~~~~~~~~~~~~~~~~~~~

//ru Возвращает тип данных.
DataTypes cgt::dtType(id_data d)
{
    return m_cgt->dtType(d);
}

//ru Возвращает данные в формате: строка в стиле C.
const char *cgt::dtStr(id_data d)
{
    return m_cgt->dtStr(d);
}

//ru Возвращает данные в формате: целое число.
int cgt::dtInt(id_data d)
{
    return m_cgt->dtInt(d);
}

//ru Возвращает данные в формате: число с плавающей запятой.
double cgt::dtReal(id_data d)
{
    return m_cgt->dtReal(d);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает название шрифта.
const char *cgt::fntName(id_font f)
{
    return m_cgt->fntName(f);
}
//ru Возвращает размер шрифта.
int cgt::fntSize(id_font f)
{
    return m_cgt->fntSize(f);
}
//ru Возвращает стиль шрифта.
unsigned char cgt::fntStyle(id_font f)
{
    return m_cgt->fntStyle(f);
}
//ru Возвращает цвет шрифта.
int cgt::fntColor(id_font f)
{
    return m_cgt->fntColor(f);
}
//ru Возвращает кодировку шрифта.
unsigned char cgt::fntCharSet(id_font f)
{
    return m_cgt->fntCharSet(f);
}

//!~~~~~~~~~~~~~~~~элемент | пользовательские данные ~~~~~~~~~~~~~
//!ru Судя по CodeGen.dpr, используется для хранения указателя (ID элемента) на самого себя.

//ru Возвращает пользовательские данные элемента.
//ru Коммент из hiasm5 - user data used in FTCG codegen.
//ru Судя по всему, данные могут быть любого типа, ибо хранит указатель..
quintptr cgt::elGetData(id_element e)
{
    return m_cgt->elGetData(e);
}

//ru Устанавливает пользовательские данные элементу.
//ru Коммент из hiasm5 - user data used in FTCG codegen.
//ru Судя по всему, данные могут быть любого типа, ибо хранит указатель.
void cgt::elSetData(id_element e, const quintptr data)
{
    m_cgt->elSetData(e, data);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает тип данных точки.
DataTypes cgt::ptGetDataType(id_point p)
{
    return m_cgt->ptGetDataType(p);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID родительского контейнера элемента.
id_sdk cgt::elGetParent(id_element e)
{
    return m_cgt->elGetParent(e);
}

//ru Возвращает количество свойств в списке свойств(из панели свойств).
//ru В RTCG используется аналогичная функция - elGetPropCount.
//[deprecated]
int cgt::elGetPropertyListCount(id_element e)
{
    return m_cgt->elGetPropertyListCount(e);
}

//ru Возвращает свойство из списка свойств (PropertyList).
//[deprecated]
id_proplist cgt::elGetPropertyListItem(id_element e, int i)
{
    return m_cgt->elGetPropertyListItem(e, i);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает имя свойства.
const char *cgt::plGetName(id_prop p)
{
    return m_cgt->plGetName(p);
}

//ru Возвращает описание свойства.
const char *cgt::plGetInfo(id_prop p)
{
    return m_cgt->plGetInfo(p);
}

//ru Возвращает группу свойсва.
const char *cgt::plGetGroup(id_prop p)
{
    return m_cgt->plGetGroup(p);
}

//ru Возвращает указатель на данные свойства.
quintptr cgt::plGetProperty(id_prop p)
{
    return m_cgt->plGetProperty(p);
}

//ru Возвращает ID родительского элемента указанного свойства.
id_element cgt::plGetOwner(id_prop p)
{
    return m_cgt->plGetOwner(p);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает описание точки.
const char *cgt::ptGetInfo(id_point p)
{
    return m_cgt->ptGetInfo(p);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID элемента, прилинкованного к указанному свойству.
id_element cgt::propGetLinkedElement(id_element e, const char *propName)
{
    return m_cgt->propGetLinkedElement(e, propName);
}

//ru Возвращает 1, если свойство помечено на перевод.
int cgt::propIsTranslate(id_element e, id_prop p)
{
    return m_cgt->propIsTranslate(e, p);
}

//ru Предназначение данной функции так и небыло найдено.
//ru Всегда возвращает 0.
//[deprecated]
id_element cgt::propGetLinkedElementInfo(id_element e, id_prop prop, char *_int)
{
    return m_cgt->propGetLinkedElementInfo(e, prop, _int);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент - CI_PolyMulti ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает SDK контейнера по его индексу.
id_sdk cgt::elGetSDKByIndex(id_element e, int index)
{
    return m_cgt->elGetSDKByIndex(e, index);
}

//ru Возвращает количаство контейнеров полиморфного элемента(CI_PolyMulti).
int cgt::elGetSDKCount(id_element e)
{
    return m_cgt->elGetSDKCount(e);
}

//ru Возвращает имя контейнера по индексу.
const char *cgt::elGetSDKName(id_element e, int index)
{
    return m_cgt->elGetSDKName(e, index);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает элемент родитель для данного SDK.
//ru Возвращает 0, если контейнер не имеет родителя.
id_element cgt::sdkGetParent(id_sdk SDK)
{
    return m_cgt->sdkGetParent(SDK);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает интерфейсы, предоставляемые элементом.
//ru Содержимое поля Interfaces= из конфигурации элемента.
const char *cgt::elGetInterface(id_element e)
{
    return m_cgt->elGetInterface(e);
}

//ru Возвращает список классов, от которых наследуется элемент
//ru Содержимое поля Inherit= из конфигурации элемента.
const char *cgt::elGetInherit(id_element e)
{
    return m_cgt->elGetInherit(e);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает 1, если список ресурсов пуст, и 0 в противном случае.
int cgt::resEmpty()
{
    return m_cgt->resEmpty();
}

//ru Устанавливает префикс для имен ресурсов.
int cgt::resSetPref(const char *pref)
{
    return m_cgt->resSetPref(pref);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Добавляет информацию в информационную панель
int cgt::_Error(int line, id_element e, const char *text)
{
    return m_cgt->_Error(line, e, text);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID группы, к которой принадлежит элемент и 0, если группа отсутствует
//[deprecated]
int cgt::elGetGroup(id_element e)
{
    return m_cgt->elGetGroup(e);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Сохраняет данные свойства в файл.
//[deprecated]
int cgt::propSaveToFile(id_prop p, const char *fileName)
{
    return m_cgt->propSaveToFile(p, fileName);
}

