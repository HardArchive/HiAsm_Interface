//STL

//Qt
#include <QDebug>
#include <QFlags>

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
const char CALL_STR[] = "  Call:";
const char ARG_STR[] = "  Arg";
const char RESULT_STR[] = "  Result:";

//Дефайны
#define PRINT_FUNC_INFO qDebug() << CALL_STR << Q_FUNC_INFO;
#define PRINT_RESULT_STR(X) \
        qDebug().noquote() << RESULT_STR << '"'+QString::fromLocal8Bit(X)+'"';
#define EXPORT __stdcall

//Служебные функции
void printArgs(std::initializer_list<QVariant> args)
{
    uint i = 1;
    for(const QVariant &v : args) {
        if(v.type() == QVariant::String)
            qDebug().nospace() << "  Arg" << i << ": " << v.toString();
        else
            qDebug().nospace().noquote() << "  Arg" << i << ": " << v.toString();

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
    int res = m_cgt->sdkGetCount(SDK);
    printArgs({SDK});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает идентификатор элемента по его Z-координате(индексу)
EXPORT id_element sdkGetElement(id_sdk SDK, int Index)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->sdkGetElement(SDK, Index);
    printArgs({SDK, Index});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает идентификатор элемента по имени его класса
EXPORT id_element sdkGetElementName(id_sdk SDK, char *Name)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->sdkGetElementName(SDK, Name);
    printArgs({SDK, Name});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает флаги элемента по его идентификатору
EXPORT ElementFlags elGetFlag(id_element e)
{
    PRINT_FUNC_INFO
    ElementFlags res = m_cgt->elGetFlag(e);
    printArgs({e});
    qDebug() << RESULT_STR << ElementFlgs(res);

    return res;
}

//ru Возвращает кол-во св-в элемента
EXPORT int elGetPropCount(id_element e)
{
    PRINT_FUNC_INFO
    int res = m_cgt->elGetPropCount(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает целую структуру для конкретного св-ва с порядковым номером из INI
EXPORT id_prop elGetProperty(id_element e, int Index)
{
    PRINT_FUNC_INFO
    id_prop res = m_cgt->elGetProperty(e, Index);
    printArgs({e, Index});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает True, если значение св-ва совпадает с заданным в INI файле, иначе False
EXPORT bool elIsDefProp(id_element e, int Index)
{
    PRINT_FUNC_INFO
    bool res = m_cgt->elIsDefProp(e, Index);
    printArgs({e, Index});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Присваиваем элементу уникальное имя
EXPORT id_element elSetCodeName(id_element e, char *Name)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->elSetCodeName(e, Name);
    printArgs({e, Name});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Получаем уникальное имя элемента
EXPORT char *elGetCodeName(id_element e)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->elGetCodeName(e);
    printArgs({e});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Получаем имя класса элемента
EXPORT char *elGetClassName(id_element e)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->elGetClassName(e);
    printArgs({e});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Просто содержимое поля Sub из INI-файла элемента
//TODO Выяснить, что за "просто содержимое" поля Sub и дополнить описание.
EXPORT char *elGetInfSub(id_element e)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->elGetInfSub(e);
    printArgs({e});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Получаем общее количество точек у элемента
EXPORT int elGetPtCount(id_element e)
{
    PRINT_FUNC_INFO
    int res = m_cgt->elGetPtCount(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Получаем идентификатор точки по её индексу
EXPORT id_point elGetPt(id_element e, int i)
{
    PRINT_FUNC_INFO
    id_point res = m_cgt->elGetPt(e, i);
    printArgs({e, i});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Получаем идентификатор точки по её имени
EXPORT id_point elGetPtName(id_element e, const char *Name)
{
    PRINT_FUNC_INFO
    id_point res = m_cgt->elGetPtName(e, Name);
    printArgs({e, Name});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Получаем подкласс элемента
EXPORT ElementClasses elGetClassIndex(id_element e)
{
    PRINT_FUNC_INFO
    ElementClasses res = m_cgt->elGetClassIndex(e);
    printArgs({e});
    qDebug().noquote() << RESULT_STR << ElementClassesMap[res];

    return res;
}

//ru Получаем идентификатор внутренней схемы для контейнеров
//ru и идентификатор родителя id_element для редактора контейнера
EXPORT id_sdk elGetSDK(id_element e)
{
    PRINT_FUNC_INFO
    id_sdk res = m_cgt->elGetSDK(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются
EXPORT bool elLinkIs(id_element e)
{
    PRINT_FUNC_INFO
    bool res = m_cgt->elLinkIs(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает идент главного элемента(тот, на который ссылаются другие)
EXPORT id_element elLinkMain(id_element e)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->elLinkMain(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Помещаем в переменные "X" и "Y", позицию элемента в редакторе схем
EXPORT void elGetPos(id_element e, int &X, int &Y)
{
    PRINT_FUNC_INFO
    m_cgt->elGetPos(e, X, Y);
    printArgs({e, X, Y});
}

//ru Помещаем в переменные "W" и "H", размеры элемента в редакторе схем
EXPORT void elGetSize(id_element e, int &W, int &H)
{
    PRINT_FUNC_INFO
    m_cgt->elGetSize(e, W, H);
    printArgs({e, W, H});
}

//ru Неизвестно для чего эта функция.
//ru Возможно, возвращает уникальное число.
//ru Можно считать её - deprecated.
EXPORT int elGetEID(id_element e)
{
    PRINT_FUNC_INFO
    int res = m_cgt->elGetEID(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает идентификатор точки, с которой соеденена данная
EXPORT id_point ptGetLinkPoint(id_point p)
{
    PRINT_FUNC_INFO
    id_point res = m_cgt->ptGetLinkPoint(p);
    printArgs({p});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает идентификатор точки, с которой соеденена данная точка,
//ru без учета точек разрыва и хабов
EXPORT id_point ptGetRLinkPoint(id_point p)
{
    PRINT_FUNC_INFO
    id_point res = m_cgt->ptGetRLinkPoint(p);
    printArgs({p});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает тип точек(константы pt_XXX)
EXPORT PointsTypes ptGetType(id_point p)
{
    PRINT_FUNC_INFO
    PointsTypes res = m_cgt->ptGetType(p);
    printArgs({p});
    qDebug().noquote() << RESULT_STR << PointsTypesMap[res];

    return res;
}

//ru Возвращает имя точки
EXPORT char *ptGetName(id_point p)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->ptGetName(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает идентификатор элемента, которому принадлежит точка
EXPORT id_element ptGetParent(id_point p)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->ptGetParent(p);
    printArgs({p});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает относительный индекс точки по принадлежности к одной из 4х групп
//TODO Выяснить, что представлять из себя "относительный индекс точки" и дополнить описание.
EXPORT int ptGetIndex(id_point p)
{
    PRINT_FUNC_INFO
    int res = m_cgt->ptGetIndex(p);
    printArgs({p});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает базовую часть имени динамических точек(для CI_DPElement)
EXPORT char *pt_dpeGetName(id_point p)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->pt_dpeGetName(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает тип параметра
EXPORT DataTypes propGetType(id_prop prop)
{
    PRINT_FUNC_INFO
    DataTypes res = m_cgt->propGetType(prop);
    printArgs({prop});
    qDebug().noquote() << RESULT_STR << DataTypesMap[res];

    return res;
}

//ru Возвращает имя параметра
EXPORT char *propGetName(id_prop prop)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->propGetName(prop);
    printArgs({prop});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает значение параметра
EXPORT quintptr propGetValue(id_prop prop)
{
    PRINT_FUNC_INFO
    quintptr res = m_cgt->propGetValue(prop);
    printArgs({prop});
    qDebug() << RESULT_STR << res;

    return res;
}

//TODO propTo функции, возвращают свойство в указанном типе? Дополнить описание.

//ru ???
EXPORT unsigned char propToByte(id_prop prop)
{
    PRINT_FUNC_INFO
    unsigned char res = m_cgt->propToByte(prop);
    printArgs({prop});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru ???
EXPORT int propToInteger(id_prop prop)
{
    PRINT_FUNC_INFO
    int res = m_cgt->propToInteger(prop);
    printArgs({prop});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru ???
EXPORT float propToReal(id_prop prop)
{
    PRINT_FUNC_INFO
    float res = m_cgt->propToReal(prop);
    printArgs({prop});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru ???
EXPORT char *propToString(id_prop prop)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->propToString(prop);
    printArgs({prop});
    PRINT_RESULT_STR(res)

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
    int res = m_cgt->resAddFile(Name);
    printArgs({Name});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Добавляет иконку в ресурсы и в список временных файлов
EXPORT char *resAddIcon(id_prop p)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->resAddIcon(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Добавляет строку в ресурсы и в список временных файлов
EXPORT char *resAddStr(const char *p)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->resAddStr(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Добавляет поток в ресурсы и в список временных файлов
EXPORT char *resAddStream(id_prop p)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->resAddStream(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Добавляет звук в ресурсы и в список временных файлов
EXPORT char *resAddWave(id_prop p)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->resAddWave(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Добавляет картинку в ресурсы и в список временных файлов
EXPORT char *resAddBitmap(id_prop p)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->resAddBitmap(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Добавляет меню в ресурсы и в список временных файлов
EXPORT char *resAddMenu(id_prop p)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->resAddMenu(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Выводит строку Text в окно Отладка цветом Color
//TODO Что возвращается данной функцией? Выяснить и дополнить описание.
EXPORT int _Debug(const char *Text, int Color)
{
    PRINT_FUNC_INFO
    int res = m_cgt->_Debug(Text, Color);
    printArgs({Text, Color});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает значение параметра среды по его индексу?
EXPORT int GetParam(short int index, char *value)
{
    PRINT_FUNC_INFO
    int res = m_cgt->GetParam(index, value);
    printArgs({ParamsIdeMap[index], value});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ массивы ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает кол-во элементов в массиве а
EXPORT int arrCount(id_array a)
{
    PRINT_FUNC_INFO
    int res = m_cgt->arrCount(a);
    printArgs({a});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает тип элементов в массиве а
EXPORT DataTypes arrType(id_array a)
{
    PRINT_FUNC_INFO
    DataTypes res = m_cgt->arrType(a);
    printArgs({a});
    qDebug().noquote() << RESULT_STR << DataTypesMap[res];

    return res;
}

//ru Возвращает имя элемента с индексом Index
EXPORT char *arrItemName(id_array a, int Index)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->arrItemName(a, Index);
    printArgs({a, Index});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает значение элемента с индексом Index
EXPORT quintptr arrItemData(id_array a, int Index)
{
    PRINT_FUNC_INFO
    quintptr res = m_cgt->arrItemData(a, Index);
    printArgs({a, Index});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru ???
//TODO Выяснить предназначение данной функции.
//p.s. Возможно, тут производится работа со свойствов... чего?
EXPORT id_data arrGetItem(id_array a, int Index)
{
    PRINT_FUNC_INFO
    id_data res = m_cgt->arrGetItem(a, Index);
    printArgs({a, Index});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru ???
//TODO Выяснить предназначение данной функции.
EXPORT bool isDebug(id_sdk e)
{
    PRINT_FUNC_INFO
    bool res = m_cgt->isDebug(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ данные ~~~~~~~~~~~~~~~~~~~~~~~~~~
//TODO Преобразование данные?
//TODO Или просто возращаем в нужном типе?
//TODO id_data? Где он берётся?

EXPORT DataTypes dtType(id_data d)
{
    PRINT_FUNC_INFO
    DataTypes res = m_cgt->dtType(d);
    printArgs({d});
    qDebug().noquote() << RESULT_STR << DataTypesMap[res];

    return res;
}
EXPORT char *dtStr(id_data d)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->dtStr(d);
    printArgs({d});
    PRINT_RESULT_STR(res)

    return res;
}
EXPORT int dtInt(id_data d)
{
    PRINT_FUNC_INFO
    int res = m_cgt->dtInt(d);
    printArgs({d});
    qDebug() << RESULT_STR << res;

    return res;
}
EXPORT double dtReal(id_data d)
{
    PRINT_FUNC_INFO
    double res = m_cgt->dtReal(d);
    printArgs({d});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
//TODO Возвращает название шрифта по идентификатору?
//TODO id_font? Где он берётся?
EXPORT char *fntName(id_font f)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->fntName(f);
    printArgs({f});
    PRINT_RESULT_STR(res)

    return res;
}
EXPORT int fntSize(id_font f)
{
    PRINT_FUNC_INFO
    int res = m_cgt->fntSize(f);
    printArgs({f});
    qDebug() << RESULT_STR << res;

    return res;
}
EXPORT unsigned char fntStyle(id_font f)
{
    printArgs({f});
    PRINT_FUNC_INFO
    unsigned char res = m_cgt->fntStyle(f);
    qDebug() << RESULT_STR << res;

    return res;
}
EXPORT int fntColor(id_font f)
{
    PRINT_FUNC_INFO
    int res = m_cgt->fntColor(f);
    printArgs({f});
    qDebug() << RESULT_STR << res;

    return res;
}
EXPORT unsigned char fntCharSet(id_font f)
{
    PRINT_FUNC_INFO
    unsigned char res = m_cgt->fntCharSet(f);
    printArgs({f});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//TODO Пользовательские данные? Выяснить и дополнить описание.
//ru Получает пользовательские данные элемента
EXPORT quintptr elGetData(id_element e)
{
    PRINT_FUNC_INFO
    quintptr res = m_cgt->elGetData(e);
    printArgs({e});
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
    DataTypes res = m_cgt->ptGetDataType(p);
    printArgs({p});
    qDebug().noquote() << RESULT_STR << DataTypesMap[res];

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает идентификатор родителя
EXPORT id_sdk elGetParent(id_element e)
{
    PRINT_FUNC_INFO
    id_sdk res = m_cgt->elGetParent(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает количество элементов в списке св-тв(из панели св-ва)
//ru В RTCG используется аналогичный метод - elGetPropCount
EXPORT int elGetPropertyListCount(id_element e)
{
    PRINT_FUNC_INFO
    int res = m_cgt->elGetPropertyListCount(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает элемент списка св-тв (PropertyList)
EXPORT id_proplist elGetPropertyListItem(id_element e, int i)
{
    PRINT_FUNC_INFO
    id_proplist res = m_cgt->elGetPropertyListItem(e, i);
    printArgs({e, i});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает имя св-ва
EXPORT char *plGetName(id_proplist p)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->plGetName(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает описание св-ва
EXPORT char *plGetInfo(id_proplist p)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->plGetInfo(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает группу св-ва
EXPORT char *plGetGroup(id_proplist p)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->plGetGroup(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает значение св-ва
EXPORT id_prop plGetProperty(id_proplist p)
{
    PRINT_FUNC_INFO
    id_prop res = m_cgt->plGetProperty(p);
    printArgs({p});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает родительский элемент даного св-ва
EXPORT id_element plGetOwner(id_proplist p)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->plGetOwner(p);
    printArgs({p});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает описание точки
EXPORT char *ptGetInfo(id_point p)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->ptGetInfo(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает идентификатор элемента, прилинкованного к указанному св-ву
//TODO Как это? Выяснить и дополнить описание.
EXPORT id_element propGetLinkedElement(id_element e, const char *propName)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->propGetLinkedElement(e, propName);
    printArgs({e, propName});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает 1 если св-во помечено на перевод
//TODO Выяснить, где в среде можно помечать свойства на перевод.
EXPORT int propIsTranslate(id_element e, id_prop p)
{
    PRINT_FUNC_INFO
    int res = m_cgt->propIsTranslate(e, p);
    printArgs({e, p});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru ???
//TODO Выяснить, для чего предназначена данная функция.
EXPORT id_element propGetLinkedElementInfo(id_element e, id_prop prop, const char *_int)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->propGetLinkedElementInfo(e, prop, _int);
    printArgs({e, prop, _int});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает SDK полиморфного контейнера по его индексу
EXPORT id_sdk elGetSDKByIndex(id_element e, int index)
{
    PRINT_FUNC_INFO
    id_sdk res = m_cgt->elGetSDKByIndex(e, index);
    printArgs({e, index});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает количаство сабклассов полиморфного контейнера
EXPORT int elGetSDKCount(id_element e)
{
    PRINT_FUNC_INFO
    int res = m_cgt->elGetSDKCount(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает имя контейнера?
//TODO Выяснить, точно ли данная функция возвращает имя текущего(?) контейнера.
EXPORT char *elGetSDKName(id_element e, int index)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->elGetSDKName(e, index);
    printArgs({e, index});
    PRINT_RESULT_STR(res)

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает элемент родитель для данного SDK
EXPORT id_element sdkGetParent(id_sdk SDK)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->sdkGetParent(SDK);
    printArgs({SDK});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает интерфейсы, предоставляемые элементом
EXPORT char *elGetInterface(id_element e)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->elGetInterface(e);
    printArgs({e});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает классы, от которых наследуется элемент
EXPORT char *elGetInherit(id_element e)
{
    PRINT_FUNC_INFO
    char *res = m_cgt->elGetInherit(e);
    printArgs({e});
    PRINT_RESULT_STR(res)

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
    int res = m_cgt->resSetPref(pref);
    printArgs({pref});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Добавляет информацию в панель ошибок
EXPORT int _Error(int line, id_element e, const char *text)
{
    PRINT_FUNC_INFO
    int res = m_cgt->_Error(line, e, text);
    printArgs({line, e, text});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID группы, к которой принадлежит элемент и 0, если группа отсутствует
EXPORT int elGetGroup(id_element e)
{
    PRINT_FUNC_INFO
    int res = m_cgt->elGetGroup(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru ???
//TODO Выяснить, для чего предназначена данная функция.
EXPORT int propSaveToFile(id_prop p, const char *fileName)
{
    PRINT_FUNC_INFO
    int res = m_cgt->propSaveToFile(p, fileName);
    printArgs({p, fileName});
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
    int id_prop = m_cgt->elGetPropertyName(e, name);
    printResult({e, name});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru ???
EXPORT bool elIsDefProperty(id_element e, id_prop p)
{
    PRINT_FUNC_INFO
    int bool = m_cgt->elIsDefProperty(e, p);
    printResult({e, p});
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
