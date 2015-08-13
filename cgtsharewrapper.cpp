//STL

//Qt
#include <QDebug>

//Project
#include "cgtsharewrapper.h"

namespace cgt
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

bool isSystem(const ElementFlgs &flags)
{
    return flags & ELEMENT_FLG_IS_SYSTEM;
}

bool isEditMultiEx(const ElementClasses &eClass)
{
    return eClass == CI_EditMultiEx;
}

bool isPolyMulti(const ElementClasses &eClass)
{
    return eClass == CI_PolyMulti;
}

}


namespace cgt
{
//Для хранения указателя на массив указателей на функции
static PCodeGenTools m_cgt = nullptr;

//Константы
const char CALL_STR[] = "  Call func:";
const char ARG_STR[] = "  Arg";
const char RESULT_STR[] = "  Result:";

//Дефайны
#define PRINT_FUNC_INFO qDebug() << CALL_STR << Q_FUNC_INFO;
#define EXPORT __stdcall

//Служебные функции
void printArgs(std::initializer_list<QVariant> args)
{
    uint i = 1;
    for(const QVariant &o : args) {
        qDebug().nospace() << "  Arg" << i << ": " << o.toString();
        i++;
    }
}

//~~~~~~~~~~~~~~~~~ Проксированные функции ~~~~~~~~~~~~~~~~~~~

//!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает количество элементов в схеме.
//ru Элементы в контейнерах не считаются
EXPORT int sdkGetCount(id_sdk SDK)
{
    PRINT_FUNC_INFO
    printArgs({SDK});
    int res = m_cgt->sdkGetCount(SDK);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает идентификатор элемента по его Z-координате(индексу)
EXPORT id_element sdkGetElement(id_sdk SDK, int Index)
{
    PRINT_FUNC_INFO
    printArgs({SDK});
    id_element res = m_cgt->sdkGetElement(SDK, Index);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает идентификатор элемента по имени его класса
EXPORT id_element sdkGetElementName(id_sdk SDK, char *Name)
{
    PRINT_FUNC_INFO
    printArgs({SDK});
    id_element res = m_cgt->sdkGetElementName(SDK, Name);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает флаги элемента по его идентификатору
EXPORT ElementFlags elGetFlag(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    ElementFlags res = m_cgt->elGetFlag(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает кол-во св-в элемента
EXPORT int elGetPropCount(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    int res = m_cgt->elGetPropCount(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает целую структуру для конкретного св-ва с порядковым номером из INI
EXPORT id_prop elGetProperty(id_element e, int Index)
{
    PRINT_FUNC_INFO
    printArgs({e, Index});
    id_prop res = m_cgt->elGetProperty(e, Index);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает True, если значение св-ва совпадает с заданным в INI файле, иначе False
EXPORT bool elIsDefProp(id_element e, int Index)
{
    PRINT_FUNC_INFO
    printArgs({e, Index});
    bool res = m_cgt->elIsDefProp(e, Index);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Присваиваем элементу уникальное имя
EXPORT id_element elSetCodeName(id_element e, char *Name)
{
    PRINT_FUNC_INFO
    printArgs({e, Name});
    id_element res = m_cgt->elSetCodeName(e, Name);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Получаем уникальное имя элемента
EXPORT char *elGetCodeName(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    char *res = m_cgt->elGetCodeName(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Получаем имя класса элемента
EXPORT char *elGetClassName(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    char *res = m_cgt->elGetClassName(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Просто содержимое поля Sub из INI-файла элемента
//TODO Выяснить, что за "просто содержимое" поля Sub и дополнить описание.
EXPORT char *elGetInfSub(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    char *res = m_cgt->elGetInfSub(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Получаем общее количество точек у элемента
EXPORT int elGetPtCount(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    int res = m_cgt->elGetPtCount(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Получаем идентификатор точки по её индексу
EXPORT id_point elGetPt(id_element e, int i)
{
    PRINT_FUNC_INFO
    printArgs({e, i});
    id_point res = m_cgt->elGetPt(e, i);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Получаем идентификатор точки по её имени
EXPORT id_point elGetPtName(id_element e, const char *Name)
{
    PRINT_FUNC_INFO
    printArgs({e, Name});
    id_point res = m_cgt->elGetPtName(e, Name);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Получаем подкласс элемента
EXPORT ElementClasses elGetClassIndex(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    ElementClasses res = m_cgt->elGetClassIndex(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Получаем идентификатор внутренней схемы для контейнеров
//ru и идентификатор родителя id_element для редактора контейнера
EXPORT id_sdk elGetSDK(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    id_sdk res = m_cgt->elGetSDK(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются
EXPORT bool elLinkIs(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    bool res = m_cgt->elLinkIs(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает идент главного элемента(тот, на который ссылаются другие)
EXPORT id_element elLinkMain(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    id_element res = m_cgt->elLinkMain(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Помещаем в переменные "X" и "Y", позицию элемента в редакторе схем
EXPORT void elGetPos(id_element e, int &X, int &Y)
{
    PRINT_FUNC_INFO
    printArgs({e, X, Y});
    m_cgt->elGetPos(e, X, Y);
}

//ru Помещаем в переменные "W" и "H", размеры элемента в редакторе схем
EXPORT void elGetSize(id_element e, int &W, int &H)
{
    PRINT_FUNC_INFO
    printArgs({e, W, H});
    m_cgt->elGetSize(e, W, H);
}

//ru Неизвестно для чего эта функция.
//ru Возможно, возвращает уникальное число.
//ru Можно считать её - deprecated.
EXPORT int elGetEID(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    int res = m_cgt->elGetEID(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает идентификатор точки, с которой соеденена данная
EXPORT id_point ptGetLinkPoint(id_point p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    id_point res = m_cgt->ptGetLinkPoint(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает идентификатор точки, с которой соеденена данная точка,
//ru без учета точек разрыва и хабов
EXPORT id_point ptGetRLinkPoint(id_point p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    id_point res = m_cgt->ptGetRLinkPoint(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает тип точек(константы pt_XXX)
EXPORT PointsTypes ptGetType(id_point p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    PointsTypes res = m_cgt->ptGetType(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает имя точки
EXPORT char *ptGetName(id_point p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    char *res = m_cgt->ptGetName(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает идентификатор элемента, которому принадлежит точка
EXPORT id_element ptGetParent(id_point p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    id_element res = m_cgt->ptGetParent(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает относительный индекс точки по принадлежности к одной из 4х групп
//TODO Выяснить, что представлять из себя "относительный индекс точки" и дополнить описание.
EXPORT int ptGetIndex(id_point p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    int res = m_cgt->ptGetIndex(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает базовую часть имени динамических точек(для CI_DPElement)
EXPORT char *pt_dpeGetName(id_point p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    char *res = m_cgt->pt_dpeGetName(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает тип параметра
EXPORT DataTypes propGetType(id_prop prop)
{
    PRINT_FUNC_INFO
    printArgs({prop});
    DataTypes res = m_cgt->propGetType(prop);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает имя параметра
EXPORT char *propGetName(id_prop prop)
{
    PRINT_FUNC_INFO
    printArgs({prop});
    char *res = m_cgt->propGetName(prop);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает значение параметра
EXPORT quintptr propGetValue(id_prop prop)
{
    PRINT_FUNC_INFO
    printArgs({prop});
    quintptr res = m_cgt->propGetValue(prop);
    qDebug() << RESULT_STR << res;

    return res;
}

//TODO propTo функции, возвращают свойство в указанном типе? Дополнить описание.

//ru ???
EXPORT unsigned char propToByte(id_prop prop)
{
    PRINT_FUNC_INFO
    printArgs({prop});
    unsigned char res = m_cgt->propToByte(prop);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru ???
EXPORT int propToInteger(id_prop prop)
{
    PRINT_FUNC_INFO
    printArgs({prop});
    int res = m_cgt->propToInteger(prop);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru ???
EXPORT float propToReal(id_prop prop)
{
    PRINT_FUNC_INFO
    printArgs({prop});
    float res = m_cgt->propToReal(prop);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru ???
EXPORT char *propToString(id_prop prop)
{
    PRINT_FUNC_INFO
    printArgs({prop});
    char *res = m_cgt->propToString(prop);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
 *ru Функции resAdd* возвращают имя временного файла, в который сохраняется ресурс.
 *ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
 *ru работы с библиотекой.
 *
 */

//ru Добавляет имя файла в общий список временных файлов для последующего удаления
EXPORT int resAddFile(const char *Name)
{
    PRINT_FUNC_INFO
    printArgs({Name});
    int res = m_cgt->resAddFile(Name);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Добавляет иконку в ресурсы и в список временных файлов
EXPORT char *resAddIcon(id_prop p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    char *res = m_cgt->resAddIcon(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Добавляет строку в ресурсы и в список временных файлов
EXPORT char *resAddStr(const char *p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    char *res = m_cgt->resAddStr(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Добавляет поток в ресурсы и в список временных файлов
EXPORT char *resAddStream(id_prop p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    char *res = m_cgt->resAddStream(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Добавляет звук в ресурсы и в список временных файлов
EXPORT char *resAddWave(id_prop p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    char *res = m_cgt->resAddWave(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Добавляет картинку в ресурсы и в список временных файлов
EXPORT char *resAddBitmap(id_prop p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    char *res = m_cgt->resAddBitmap(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Добавляет меню в ресурсы и в список временных файлов
EXPORT char *resAddMenu(id_prop p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    char *res = m_cgt->resAddMenu(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Выводит строку Text в окно Отладка цветом Color
//TODO Что возвращается данной функцией? Выяснить и дополнить описание.
EXPORT int _Debug(const char *Text, int Color)
{
    PRINT_FUNC_INFO
    printArgs({Text, Color});
    int res = m_cgt->_Debug(Text, Color);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает значение параметра среды по его индексу?
EXPORT int GetParam(short int index, char *value)
{
    PRINT_FUNC_INFO
    int res = m_cgt->GetParam(index, value);
    printArgs({index, value});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ массивы ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает кол-во элементов в массиве а
EXPORT int arrCount(id_array a)
{
    PRINT_FUNC_INFO
    printArgs({a});
    int res = m_cgt->arrCount(a);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает тип элементов в массиве а
EXPORT DataTypes arrType(id_array a)
{
    PRINT_FUNC_INFO
    printArgs({a});
    DataTypes res = m_cgt->arrType(a);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает имя элемента с индексом Index
EXPORT char *arrItemName(id_array a, int Index)
{
    PRINT_FUNC_INFO
    printArgs({a, Index});
    char *res = m_cgt->arrItemName(a, Index);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает значение элемента с индексом Index
EXPORT quintptr arrItemData(id_array a, int Index)
{
    PRINT_FUNC_INFO
    printArgs({a, Index});
    quintptr res = m_cgt->arrItemData(a, Index);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru ???
//TODO Выяснить предназначение данной функции.
//p.s. Возможно, тут производится работа со свойствов... чего?
EXPORT id_data arrGetItem(id_array a, int Index)
{
    PRINT_FUNC_INFO
    printArgs({a, Index});
    id_data res = m_cgt->arrGetItem(a, Index);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru ???
//TODO Выяснить предназначение данной функции.
EXPORT bool isDebug(id_sdk e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    bool res = m_cgt->isDebug(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ данные ~~~~~~~~~~~~~~~~~~~~~~~~~~
//TODO Преобразование данные?
//TODO Или просто возращаем в нужном типе?
//TODO id_data? Где он берётся?

EXPORT unsigned char dtType(id_data d)
{
    PRINT_FUNC_INFO
    printArgs({d});
    unsigned char res = m_cgt->dtType(d);
    qDebug() << RESULT_STR << res;

    return res;
}
EXPORT char *dtStr(id_data d)
{
    PRINT_FUNC_INFO
    printArgs({d});
    char *res = m_cgt->dtStr(d);
    qDebug() << RESULT_STR << res;

    return res;
}
EXPORT int dtInt(id_data d)
{
    PRINT_FUNC_INFO
    printArgs({d});
    int res = m_cgt->dtInt(d);
    qDebug() << RESULT_STR << res;

    return res;
}
EXPORT double dtReal(id_data d)
{
    PRINT_FUNC_INFO
    printArgs({d});
    double res = m_cgt->dtReal(d);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
//TODO Возвращает название шрифта по идентификатору?
//TODO id_font? Где он берётся?
EXPORT char *fntName(id_font f)
{
    PRINT_FUNC_INFO
    printArgs({f});
    char *res = m_cgt->fntName(f);
    qDebug() << RESULT_STR << res;

    return res;
}
EXPORT int fntSize(id_font f)
{
    PRINT_FUNC_INFO
    printArgs({f});
    int res = m_cgt->fntSize(f);
    qDebug() << RESULT_STR << res;

    return res;
}
EXPORT unsigned char fntStyle(id_font f)
{
    PRINT_FUNC_INFO
    printArgs({f});
    unsigned char res = m_cgt->fntStyle(f);
    qDebug() << RESULT_STR << res;

    return res;
}
EXPORT int fntColor(id_font f)
{
    PRINT_FUNC_INFO
    printArgs({f});
    int res = m_cgt->fntColor(f);
    qDebug() << RESULT_STR << res;

    return res;
}
EXPORT unsigned char fntCharSet(id_font f)
{
    PRINT_FUNC_INFO
    printArgs({f});
    unsigned char res = m_cgt->fntCharSet(f);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//TODO Пользовательские данные? Выяснить и дополнить описание.
//ru Получает пользовательские данные элемента
EXPORT quintptr elGetData(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    quintptr res = m_cgt->elGetData(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//TODO Пользовательские данные? Выяснить и дополнить описание.
//ru Устанавливает пользовательские данные элемента
EXPORT void elSetData(id_element e, char *data)
{
    PRINT_FUNC_INFO
    m_cgt->elSetData(e, data);
    printArgs({e, data});
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает тип данных точки
EXPORT DataTypes ptGetDataType(id_point p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    DataTypes res = m_cgt->ptGetDataType(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает идентификатор родителя
EXPORT id_sdk elGetParent(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    id_sdk res = m_cgt->elGetParent(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает количество элементов в списке св-тв(из панели св-ва)
//ru В RTCG используется аналогичный метод - elGetPropCount
EXPORT int elGetPropertyListCount(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    int res = m_cgt->elGetPropertyListCount(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает элемент списка св-тв (PropertyList)
EXPORT id_proplist elGetPropertyListItem(id_element e, int i)
{
    PRINT_FUNC_INFO
    printArgs({e, i});
    id_proplist res = m_cgt->elGetPropertyListItem(e, i);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает имя св-ва
EXPORT char *plGetName(id_proplist p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    char *res = m_cgt->plGetName(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает описание св-ва
EXPORT char *plGetInfo(id_proplist p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    char *res = m_cgt->plGetInfo(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает группу св-ва
EXPORT char *plGetGroup(id_proplist p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    char *res = m_cgt->plGetGroup(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает значение св-ва
EXPORT id_prop plGetProperty(id_proplist p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    id_prop res = m_cgt->plGetProperty(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает родительский элемент даного св-ва
EXPORT id_element plGetOwner(id_proplist p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    id_element res = m_cgt->plGetOwner(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает описание точки
EXPORT char *ptGetInfo(id_point p)
{
    PRINT_FUNC_INFO
    printArgs({p});
    char *res = m_cgt->ptGetInfo(p);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает идентификатор элемента, прилинкованного к указанному св-ву
//TODO Как это? Выяснить и дополнить описание.
EXPORT id_element propGetLinkedElement(id_element e, const char *propName)
{
    PRINT_FUNC_INFO
    printArgs({e, propName});
    id_element res = m_cgt->propGetLinkedElement(e, propName);
    //id_element res = cgt::getOriginalCgt()->propGetLinkedElement(e, propName);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает 1 если св-во помечено на перевод
//TODO Выяснить, где в среде можно помечать свойства на перевод.
EXPORT int propIsTranslate(id_element e, id_prop p)
{
    PRINT_FUNC_INFO
    printArgs({e, p});
    int res = m_cgt->propIsTranslate(e, p);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru ???
//TODO Выяснить, для чего предназначена данная функция.
EXPORT id_element propGetLinkedElementInfo(id_element e, id_prop prop, const char *_int)
{
    PRINT_FUNC_INFO
    printArgs({e, prop, _int});
    id_element res = m_cgt->propGetLinkedElementInfo(e, prop, _int);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает SDK полиморфного контейнера по его индексу
EXPORT id_sdk elGetSDKByIndex(id_element e, int index)
{
    PRINT_FUNC_INFO
    printArgs({e, index});
    id_sdk res = m_cgt->elGetSDKByIndex(e, index);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает количаство сабклассов полиморфного контейнера
EXPORT int elGetSDKCount(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    int res = m_cgt->elGetSDKCount(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает имя контейнера?
//TODO Выяснить, точно ли данная функция возвращает имя текущего(?) контейнера.
EXPORT char *elGetSDKName(id_element e, int index)
{
    PRINT_FUNC_INFO
    printArgs({e, index});
    char *res = m_cgt->elGetSDKName(e, index);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает элемент родитель для данного SDK
EXPORT id_element sdkGetParent(id_sdk SDK)
{
    PRINT_FUNC_INFO
    printArgs({SDK});
    id_element res = m_cgt->sdkGetParent(SDK);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает интерфейсы, предоставляемые элементом
EXPORT char *elGetInterface(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    char *res = m_cgt->elGetInterface(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает классы, от которых наследуется элемент
EXPORT char *elGetInherit(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    char *res = m_cgt->elGetInherit(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает 1 если список ресурсов пуст, и 0 в противном случае
EXPORT int resEmpty()
{
    PRINT_FUNC_INFO
    int res = m_cgt->resEmpty();
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Устанавливает префикс для имен ресурсов
EXPORT int resSetPref(const char *pref)
{
    PRINT_FUNC_INFO
    printArgs({pref});
    int res = m_cgt->resSetPref(pref);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Добавляет информацию в панель ошибок
EXPORT int _Error(int line, id_element e, const char *text)
{
    PRINT_FUNC_INFO
    printArgs({line, e, text});
    int res = m_cgt->_Error(line, e, text);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID группы, к которой принадлежит элемент и 0, если группа отсутствует
EXPORT int elGetGroup(id_element e)
{
    PRINT_FUNC_INFO
    printArgs({e});
    int res = m_cgt->elGetGroup(e);
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru ???
//TODO Выяснить, для чего предназначена данная функция.
EXPORT int propSaveToFile(id_prop p, const char *fileName)
{
    PRINT_FUNC_INFO
    printArgs({p, fileName});
    int res = m_cgt->propSaveToFile(p, fileName);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru "MSDK" - определение вызовов, оптимизирующих производительность.
//ru Вызовы реализованы в стороннем проекте HiAsm SDK.
//ru http://forum.hiasm.com/forum.html?q=3&p=273676#p273676
//TODO Нужно будет решить, что с ними делать.
#ifdef MSDK
//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru ???
EXPORT id_prop elGetPropertyName(id_element e, const char *name)
{
    PRINT_FUNC_INFO
    printResult({e, name});
    int id_prop = m_cgt->elGetPropertyName(e, name);
    qDebug() << RESULT_STR << res;

    return res;
}

//ru ???
EXPORT bool elIsDefProperty(id_element e, id_prop p)
{
    PRINT_FUNC_INFO
    printResult({e, p});
    int bool = m_cgt->elIsDefProperty(e, p);
    qDebug() << RESULT_STR << res;

    return res;
}
#endif

//Заполняем массив указателей
quintptr arrayPointers[] {
    (quintptr) &sdkGetCount,
    (quintptr) &sdkGetElement,
    (quintptr) &sdkGetElementName,
    (quintptr) &elGetFlag,
    (quintptr) &elGetPropCount,
    (quintptr) &elGetProperty,
    (quintptr) &elIsDefProp,
    (quintptr) &elSetCodeName,
    (quintptr) &elGetCodeName,
    (quintptr) &elGetClassName,
    (quintptr) &elGetInfSub,
    (quintptr) &elGetPtCount,
    (quintptr) &elGetPt,
    (quintptr) &elGetPtName,
    (quintptr) &elGetClassIndex,
    (quintptr) &elGetSDK,
    (quintptr) &elLinkIs,
    (quintptr) &elLinkMain,
    (quintptr) &elGetPos,
    (quintptr) &elGetSize,
    (quintptr) &elGetEID,
    (quintptr) &ptGetLinkPoint,
    (quintptr) &ptGetRLinkPoint,
    (quintptr) &ptGetType,
    (quintptr) &ptGetName,
    (quintptr) &ptGetParent,
    (quintptr) &ptGetIndex,
    (quintptr) &pt_dpeGetName,
    (quintptr) &propGetType,
    (quintptr) &propGetName,
    (quintptr) &propGetValue,
    (quintptr) &propToByte,
    (quintptr) &propToInteger,
    (quintptr) &propToReal,
    (quintptr) &propToString,
    (quintptr) &resAddFile,
    (quintptr) &resAddIcon,
    (quintptr) &resAddStr,
    (quintptr) &resAddStream,
    (quintptr) &resAddWave,
    (quintptr) &resAddBitmap,
    (quintptr) &resAddMenu,
    (quintptr) &_Debug,
    (quintptr) &GetParam,
    (quintptr) &arrCount,
    (quintptr) &arrType,
    (quintptr) &arrItemName,
    (quintptr) &arrItemData,
    (quintptr) &arrGetItem,
    (quintptr) &isDebug,
    (quintptr) &dtType,
    (quintptr) &dtStr,
    (quintptr) &dtInt,
    (quintptr) &dtReal,
    (quintptr) &fntName,
    (quintptr) &fntSize,
    (quintptr) &fntStyle,
    (quintptr) &fntColor,
    (quintptr) &fntCharSet,
    (quintptr) &elGetData,
    (quintptr) &elSetData,
    (quintptr) &ptGetDataType,
    (quintptr) &elGetParent,
    (quintptr) &elGetPropertyListCount,
    (quintptr) &elGetPropertyListItem,
    (quintptr) &plGetName,
    (quintptr) &plGetInfo,
    (quintptr) &plGetGroup,
    (quintptr) &plGetProperty,
    (quintptr) &plGetOwner,
    (quintptr) &ptGetInfo,
    (quintptr) &propGetLinkedElement,
    (quintptr) &propIsTranslate,
    (quintptr) &propGetLinkedElementInfo,
    (quintptr) &elGetSDKByIndex,
    (quintptr) &elGetSDKCount,
    (quintptr) &elGetSDKName,
    (quintptr) &sdkGetParent,
    (quintptr) &elGetInterface,
    (quintptr) &elGetInherit,
    (quintptr) &resEmpty,
    (quintptr) &resSetPref,
    (quintptr) &_Error,
    (quintptr) &elGetGroup,
    (quintptr) &propSaveToFile,
#ifdef MSDK
    (quintptr) &elGetPropertyName,
    (quintptr) &elIsDefProperty
#endif
};

/*!  Служебные функции   */

//Сохранение указателя для дальнейшей работы с оным
void saveOriginalCgt(PCodeGenTools cgt)
{
    m_cgt = cgt;
}

PCodeGenTools getOriginalCgt()
{
    return m_cgt;
}

//Получаем массив указателей на функции
PCodeGenTools getProxyCgt()
{
    return (PCodeGenTools)arrayPointers;
}
}
