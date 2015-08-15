//Project
#include "cgtsharewrapper.h"
#include "global.h"

//STL

//Qt
#include <QDebug>
#include <QFlags>

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

bool isEditMultiEx(const ClassesElements &eClass)
{
    return eClass == CI_EditMultiEx;
}

bool isPolyMulti(const ClassesElements &eClass)
{
    return eClass == CI_PolyMulti;
}
}

namespace cgt
{
//Для хранения указателя на массив указателей на callback функции
static PCodeGenTools m_cgt = nullptr;

//Константы
const char CALL_STR[] = "  Call:";
const char ARG_STR[] = "  Arg";
const char RESULT_STR[] = "  Return:";

//Дефайны
#define PRINT_RESULT_STR(X) \
        qDebug().noquote() << RESULT_STR << '"'+QString::fromLocal8Bit(X)+'"';
#define EXPORT __stdcall

//Служебные функции
void printArgs(std::initializer_list<QVariant> args, bool noquote = false)
{
    uint i = 1;
    for(const QVariant &v : args) {
        if(v.type() == QVariant::String) {
            if(noquote)
                qDebug().nospace().noquote() << "  Arg" << i << ": " << v.toString();
            else
                qDebug().nospace() << "  Arg" << i << ": " << v.toString();

        } else {
            qDebug().nospace().noquote() << "  Arg" << i << ": " << v.toString();
        }
        i++;
    }
}

//~~~~~~~~~~~~~~~~~ Проксированные функции ~~~~~~~~~~~~~~~~~~~

//!~~~~~~~~~~~~~~~~~~~~~~~~ контейнер ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает количество элементов в контейнере.
EXPORT int sdkGetCount(id_sdk SDK)
{
    PRINT_FUNC_INFO
    int res = m_cgt->sdkGetCount(SDK);
    printArgs({SDK});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает ID элемента по его Z-положению(индексу) в контейнере.
EXPORT id_element sdkGetElement(id_sdk SDK, int Index)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->sdkGetElement(SDK, Index);
    printArgs({SDK, Index});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает ID элемента по имени элемента.
EXPORT id_element sdkGetElementName(id_sdk SDK, char *Name)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->sdkGetElementName(SDK, Name);
    printArgs({SDK, Name});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает флаги элемента.
EXPORT ElementFlags elGetFlag(id_element e)
{
    PRINT_FUNC_INFO
    ElementFlags res = m_cgt->elGetFlag(e);
    printArgs({e});

    qDebug() << RESULT_STR << ElementFlgs(res);

    return res;
}

//ru Возвращает количество свойств элемента.
EXPORT int elGetPropCount(id_element e)
{
    PRINT_FUNC_INFO
    int res = m_cgt->elGetPropCount(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает свойство элемента по индексу, с порядковым номером из INI.
EXPORT id_prop elGetProperty(id_element e, int Index)
{
    PRINT_FUNC_INFO
    id_prop res = m_cgt->elGetProperty(e, Index);
    printArgs({e, Index});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает True, если значение свойства совпадает с заданным в INI файле, иначе False.
EXPORT bool elIsDefProp(id_element e, int Index)
{
    PRINT_FUNC_INFO
    bool res = m_cgt->elIsDefProp(e, Index);
    printArgs({e, Index});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Присваиваем элементу уникальное имя и возвращаем ID этого элемента.
EXPORT id_element elSetCodeName(id_element e, const char *Name)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->elSetCodeName(e, Name);
    printArgs({e, Name});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает уникальное имя элемента
EXPORT const char *elGetCodeName(id_element e)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetCodeName(e);
    printArgs({e});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает имя класса элемента.
EXPORT const char *elGetClassName(id_element e)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetClassName(e);
    printArgs({e});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает водержимое поля Sub из конфигурационного INI-файла элемента.
EXPORT const char *elGetInfSub(id_element e)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetInfSub(e);
    printArgs({e});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает общее количество видимых точек у элемента.
EXPORT int elGetPtCount(id_element e)
{
    PRINT_FUNC_INFO
    int res = m_cgt->elGetPtCount(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает ID точки по её индексу.
EXPORT id_point elGetPt(id_element e, int i)
{
    PRINT_FUNC_INFO
    id_point res = m_cgt->elGetPt(e, i);
    printArgs({e, i});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает ID точки по её имени.
//[deprecated]
EXPORT id_point elGetPtName(id_element e, const char *Name)
{
    PRINT_FUNC_INFO
    id_point res = m_cgt->elGetPtName(e, Name);
    printArgs({e, Name});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает индекс класса элемента.
EXPORT ClassesElements elGetClassIndex(id_element e)
{
    PRINT_FUNC_INFO
    ClassesElements res = m_cgt->elGetClassIndex(e);
    printArgs({e});
    qDebug().noquote() << RESULT_STR << ClassesElementMap[res];

    return res;
}

//ru Возвращает ID внутренней схемы для контейнеров,
//ru или ID родителя id_element для редактора контейнера (ELEMENT_FLG_IS_EDIT).
EXPORT id_sdk elGetSDK(id_element e)
{
    PRINT_FUNC_INFO
    id_sdk res = m_cgt->elGetSDK(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются.
EXPORT bool elLinkIs(id_element e)
{
    PRINT_FUNC_INFO
    bool res = m_cgt->elLinkIs(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает ID главного элемента(тот, на который ссылаются другие).
EXPORT id_element elLinkMain(id_element e)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->elLinkMain(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Помещает в переменные "X" и "Y", позицию элемента в редакторе схем.
EXPORT void elGetPos(id_element e, int &X, int &Y)
{
    PRINT_FUNC_INFO
    m_cgt->elGetPos(e, X, Y);
    printArgs({e, X, Y});
}

//ru Помещает в переменные "W" и "H", размеры элемента.
EXPORT void elGetSize(id_element e, int &W, int &H)
{
    PRINT_FUNC_INFO
    m_cgt->elGetSize(e, W, H);
    printArgs({e, W, H});
}

//ru Возвращает внутренний ID элемента (отличается от внешнего).
//[deprecated]
EXPORT int elGetEID(id_element e)
{
    PRINT_FUNC_INFO
    int res = m_cgt->elGetEID(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID точки, с которой соединена указанная.
//TODO [deprecated?], в CodeGen.dpr не используется.
EXPORT id_point ptGetLinkPoint(id_point p)
{
    PRINT_FUNC_INFO
    id_point res = m_cgt->ptGetLinkPoint(p);
    printArgs({p});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает ID точки, с которой соединена указанная точка,
//ru без учета точек разрыва и хабов.
EXPORT id_point ptGetRLinkPoint(id_point p)
{
    PRINT_FUNC_INFO
    id_point res = m_cgt->ptGetRLinkPoint(p);
    printArgs({p});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает тип точек(константы PointTypes).
EXPORT PointTypes ptGetType(id_point p)
{
    PRINT_FUNC_INFO
    PointTypes res = m_cgt->ptGetType(p);
    printArgs({p});
    qDebug().noquote() << RESULT_STR << PointTypesMap[res];

    return res;
}

//ru Возвращает имя точки.
EXPORT const char *ptGetName(id_point p)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->ptGetName(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает ID элемента, которому принадлежит точка.
EXPORT id_element ptGetParent(id_point p)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->ptGetParent(p);
    printArgs({p});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает тип точки (PointTypes).
EXPORT PointTypes ptGetIndex(id_point p)
{
    PRINT_FUNC_INFO
    PointTypes res = m_cgt->ptGetIndex(p);
    printArgs({p}, true);
    qDebug().noquote() << RESULT_STR << PointTypesMap[res];

    return res;
}

//ru Возвращает базовую часть имени динамической точки(для CI_DPElement).
EXPORT const char *pt_dpeGetName(id_point p)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->pt_dpeGetName(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает тип свойства.
EXPORT DataTypes propGetType(id_prop prop)
{
    PRINT_FUNC_INFO
    DataTypes res = m_cgt->propGetType(prop);
    printArgs({prop});
    qDebug().noquote() << RESULT_STR << DataTypesMap[res];

    return res;
}

//ru Возвращает имя свойства.
EXPORT const char *propGetName(id_prop prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->propGetName(prop);
    printArgs({prop});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает значение свойства в виде указателя на данные.
EXPORT quintptr propGetValue(id_prop prop)
{
    PRINT_FUNC_INFO
    quintptr res = m_cgt->propGetValue(prop);
    printArgs({prop});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает значение свойства в формате unsigned char.
EXPORT unsigned char propToByte(id_prop prop)
{
    PRINT_FUNC_INFO
    unsigned char res = m_cgt->propToByte(prop);
    printArgs({prop});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает значение свойства в формате int.
EXPORT int propToInteger(id_prop prop)
{
    PRINT_FUNC_INFO
    int res = m_cgt->propToInteger(prop);
    printArgs({prop});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает значение свойства в формате float.
EXPORT float propToReal(id_prop prop)
{
    PRINT_FUNC_INFO
    float res = m_cgt->propToReal(prop);
    printArgs({prop});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает значение свойства в виде C строки.
EXPORT const char *propToString(id_prop prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->propToString(prop);
    printArgs({prop});
    PRINT_RESULT_STR(res)

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~

//ru Добавляет имя файла в общий список временных файлов
//ru для последующего удаления файла.
EXPORT int resAddFile(const char *Name)
{
    PRINT_FUNC_INFO
    int res = m_cgt->resAddFile(Name);
    printArgs({Name});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Добавляет иконку в ресурсы и в список временных файлов,
//ru и возвращают имя временного файла.
//TODO p - является свойством, которое содержит иконку?
EXPORT const char *resAddIcon(id_prop p)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddIcon(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Добавляет строку в ресурсы и в список временных файлов.
//TODO Что возвращает?
EXPORT const char *resAddStr(const char *p)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddStr(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Добавляет поток (данные) в ресурсы и в список временных файлов,
//ru и возвращает имя временного файла.
//ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
//ru работы с библиотекой.
EXPORT const char *resAddStream(id_prop p)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddStream(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Добавляет звук в ресурсы и в список временных файлов,
//ru и возвращает имя временного файла.
//ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
//ru работы с библиотекой.
EXPORT const char *resAddWave(id_prop p)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddWave(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Добавляет картинку в ресурсы и в список временных файлов,
//ru и возвращает имя временного файла.
//ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
//ru работы с библиотекой.
EXPORT const char *resAddBitmap(id_prop p)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddBitmap(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Добавляет меню в ресурсы и в список временных файлов.
//[deprecated]
EXPORT const char *resAddMenu(id_prop p)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddMenu(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Выводит строку Text в окно Отладка цветом Color
//ru Всего возвращает 0.
EXPORT int _Debug(const char *Text, int Color)
{
    PRINT_FUNC_INFO
    int res = m_cgt->_Debug(Text, Color);
    printArgs({Text, Color});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает значение параметра среды по его индексу
EXPORT int GetParam(CgtParams index, const void *value)
{
    PRINT_FUNC_INFO
    int res = m_cgt->GetParam(index, value);

    switch(index) {
    case PARAM_CODE_PATH :
        printArgs({CgtParamsMap[index], reinterpret_cast<const char *>(value)}, true);
        break;
    case PARAM_DEBUG_MODE:
        printArgs({CgtParamsMap[index], *reinterpret_cast<const int *>(value)});
        break;
    case PARAM_DEBUG_SERVER_PORT:
        printArgs({CgtParamsMap[index], *reinterpret_cast<const int *>(value)});
        break;
    case PARAM_DEBUG_CLIENT_PORT:
        printArgs({CgtParamsMap[index], *reinterpret_cast<const int *>(value)});
        break;
    case PARAM_PROJECT_PATH:
        printArgs({CgtParamsMap[index], reinterpret_cast<const char *>(value)}, true);
        break;
    case PARAM_HIASM_VERSION:
        printArgs({CgtParamsMap[index], reinterpret_cast<const char *>(value)}, true);
        break;
    case PARAM_USER_NAME:
        printArgs({CgtParamsMap[index], reinterpret_cast<const char *>(value)}, true);
        break;
    case PARAM_USER_MAIL:
        printArgs({CgtParamsMap[index], reinterpret_cast<const char *>(value)}, true);
        break;
    case PARAM_PROJECT_NAME:
        printArgs({CgtParamsMap[index], reinterpret_cast<const char *>(value)}, true);
        break;
    case PARAM_SDE_WIDTH:
        printArgs({CgtParamsMap[index], *reinterpret_cast<const int *>(value)});
        break;
    case PARAM_SDE_HEIGHT:
        printArgs({CgtParamsMap[index], *reinterpret_cast<const int *>(value)});
        break;
    case PARAM_COMPILER:
        printArgs({CgtParamsMap[index], reinterpret_cast<const char *>(value)}, true);
        break;
    }

    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ массив ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает количество элементов в массиве.
EXPORT int arrCount(id_array a)
{
    PRINT_FUNC_INFO
    int res = m_cgt->arrCount(a);
    printArgs({a});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает тип элементов в массиве.
EXPORT DataTypes arrType(id_array a)
{
    PRINT_FUNC_INFO
    DataTypes res = m_cgt->arrType(a);
    printArgs({a});
    qDebug().noquote() << RESULT_STR << DataTypesMap[res];

    return res;
}

//ru Возвращает имя элемента с индексом Index.
EXPORT const char *arrItemName(id_array a, int Index)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->arrItemName(a, Index);
    printArgs({a, Index});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает значение элемента с индексом Index
EXPORT quintptr arrItemData(id_array a, int Index)
{
    PRINT_FUNC_INFO
    const quintptr res = m_cgt->arrItemData(a, Index);
    printArgs({a, Index});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Получаем элемент массива в виде свойства,
//ru для дальнейшей работы с ним cgt::prop* функциями.
EXPORT id_data arrGetItem(id_array a, int Index)
{
    PRINT_FUNC_INFO
    id_data res = m_cgt->arrGetItem(a, Index);
    printArgs({a, Index});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает true, если запускаем cборку и запуск схемы в режиме отладки,
//ru иначе false.
EXPORT bool isDebug(id_sdk e)
{
    PRINT_FUNC_INFO
    bool res = m_cgt->isDebug(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ работа с данными ~~~~~~~~~~~~~~~~~~~~~~~~~~

//ru Возвращает тип данных.
EXPORT DataTypes dtType(id_data d)
{
    PRINT_FUNC_INFO
    DataTypes res = m_cgt->dtType(d);
    printArgs({d});
    qDebug().noquote() << RESULT_STR << DataTypesMap[res];

    return res;
}

//ru Возвращает данные в формате: строка в стиле C.
EXPORT const char *dtStr(id_data d)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->dtStr(d);
    printArgs({d});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает данные в формате: целое число.
EXPORT int dtInt(id_data d)
{
    PRINT_FUNC_INFO
    int res = m_cgt->dtInt(d);
    printArgs({d});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает данные в формате: число с плавающей запятой.
EXPORT double dtReal(id_data d)
{
    PRINT_FUNC_INFO
    double res = m_cgt->dtReal(d);
    printArgs({d});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает название шрифта.
EXPORT const char *fntName(id_font f)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->fntName(f);
    printArgs({f});
    PRINT_RESULT_STR(res)

    return res;
}
//ru Возвращает размер шрифта.
EXPORT int fntSize(id_font f)
{
    PRINT_FUNC_INFO
    int res = m_cgt->fntSize(f);
    printArgs({f});
    qDebug() << RESULT_STR << res;

    return res;
}
//ru Возвращает стиль шрифта.
EXPORT unsigned char fntStyle(id_font f)
{
    printArgs({f});
    PRINT_FUNC_INFO
    unsigned char res = m_cgt->fntStyle(f);
    qDebug() << RESULT_STR << res;

    return res;
}
//ru Возвращает цвет шрифта.
EXPORT int fntColor(id_font f)
{
    PRINT_FUNC_INFO
    int res = m_cgt->fntColor(f);
    printArgs({f});
    qDebug() << RESULT_STR << res;

    return res;
}
//ru Возвращает кодировку шрифта.
EXPORT unsigned char fntCharSet(id_font f)
{
    PRINT_FUNC_INFO
    unsigned char res = m_cgt->fntCharSet(f);
    printArgs({f});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~элемент | пользовательские данные ~~~~~~~~~~~~~
//!ru Судя по CodeGen.dpr, используется для хранения указателя (ID элемента) на самого себя.

//ru Возвращает пользовательские данные элемента.
//ru Коммент из hiasm5 - user data used in FTCG codegen.
//ru Судя по всему, данные могут быть любого типа, ибо хранит указатель..
EXPORT quintptr elGetData(id_element e)
{
    PRINT_FUNC_INFO
    const quintptr res = m_cgt->elGetData(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Устанавливает пользовательские данные элементу.
//ru Коммент из hiasm5 - user data used in FTCG codegen.
//ru Судя по всему, данные могут быть любого типа, ибо хранит указатель.
EXPORT void elSetData(id_element e, const quintptr data)
{
    PRINT_FUNC_INFO
    m_cgt->elSetData(e, data);
    printArgs({e, data});
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает тип данных точки.
EXPORT DataTypes ptGetDataType(id_point p)
{
    PRINT_FUNC_INFO
    DataTypes res = m_cgt->ptGetDataType(p);
    printArgs({p});
    qDebug().noquote() << RESULT_STR << DataTypesMap[res];

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID родительского контейнера элемента.
EXPORT id_sdk elGetParent(id_element e)
{
    PRINT_FUNC_INFO
    id_sdk res = m_cgt->elGetParent(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает количество свойств в списке свойств(из панели свойств).
//ru В RTCG используется аналогичная функция - elGetPropCount.
//[deprecated]
EXPORT int elGetPropertyListCount(id_element e)
{
    PRINT_FUNC_INFO
    int res = m_cgt->elGetPropertyListCount(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает свойство из списка свойств (PropertyList).
//[deprecated]
EXPORT id_proplist elGetPropertyListItem(id_element e, int i)
{
    PRINT_FUNC_INFO
    id_proplist res = m_cgt->elGetPropertyListItem(e, i);
    printArgs({e, i});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает имя свойства.
EXPORT const char *plGetName(id_prop p)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->plGetName(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает описание свойства.
EXPORT const char *plGetInfo(id_prop p)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->plGetInfo(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает группу свойсва.
EXPORT const char *plGetGroup(id_prop p)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->plGetGroup(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает указатель на данные свойства.
EXPORT quintptr plGetProperty(id_prop p)
{
    PRINT_FUNC_INFO
    quintptr res = m_cgt->plGetProperty(p);
    printArgs({p});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает ID родительского элемента указанного свойства.
EXPORT id_element plGetOwner(id_prop p)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->plGetOwner(p);
    printArgs({p});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает описание точки.
EXPORT const char *ptGetInfo(id_point p)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->ptGetInfo(p);
    printArgs({p});
    PRINT_RESULT_STR(res)

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID элемента, прилинкованного к указанному свойству.
EXPORT id_element propGetLinkedElement(id_element e, const char *propName)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->propGetLinkedElement(e, propName);
    printArgs({e, propName});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает 1, если свойство помечено на перевод.
EXPORT int propIsTranslate(id_element e, id_prop p)
{
    PRINT_FUNC_INFO
    int res = m_cgt->propIsTranslate(e, p);
    printArgs({e, p});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Предназначение данной функции так и небыло найдено.
//ru Всегда возвращает 0.
//[deprecated]
EXPORT id_element propGetLinkedElementInfo(id_element e, id_prop prop, char *_int)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->propGetLinkedElementInfo(e, prop, _int);
    printArgs({e, prop, _int});
    qDebug() << RESULT_STR << res;

    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент - CI_PolyMulti ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает SDK контейнера по его индексу.
EXPORT id_sdk elGetSDKByIndex(id_element e, int index)
{
    PRINT_FUNC_INFO
    id_sdk res = m_cgt->elGetSDKByIndex(e, index);
    printArgs({e, index});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает количаство контейнеров полиморфного элемента(CI_PolyMulti).
EXPORT int elGetSDKCount(id_element e)
{
    PRINT_FUNC_INFO
    int res = m_cgt->elGetSDKCount(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Возвращает имя контейнера по индексу.
EXPORT const char *elGetSDKName(id_element e, int index)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetSDKName(e, index);
    printArgs({e, index});
    PRINT_RESULT_STR(res)

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает элемент родитель для данного SDK.
//ru Возвращает 0, если контейнер не имеет родителя.
EXPORT id_element sdkGetParent(id_sdk SDK)
{
    PRINT_FUNC_INFO
    id_element res = m_cgt->sdkGetParent(SDK);
    printArgs({SDK});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает интерфейсы, предоставляемые элементом.
//ru Содержимое поля Interfaces= из конфигурации элемента.
EXPORT const char *elGetInterface(id_element e)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetInterface(e);
    printArgs({e});
    PRINT_RESULT_STR(res)

    return res;
}

//ru Возвращает список классов, от которых наследуется элемент
//ru Содержимое поля Inherit= из конфигурации элемента.
EXPORT const char *elGetInherit(id_element e)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetInherit(e);
    printArgs({e});
    PRINT_RESULT_STR(res)

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает 1, если список ресурсов пуст, и 0 в противном случае.
EXPORT int resEmpty()
{
    PRINT_FUNC_INFO
    int res = m_cgt->resEmpty();
    qDebug() << RESULT_STR << res;

    return res;
}

//ru Устанавливает префикс для имен ресурсов.
EXPORT int resSetPref(const char *pref)
{
    PRINT_FUNC_INFO
    int res = m_cgt->resSetPref(pref);
    printArgs({pref});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Добавляет информацию в информационную панель
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
//[deprecated]
EXPORT int elGetGroup(id_element e)
{
    PRINT_FUNC_INFO
    int res = m_cgt->elGetGroup(e);
    printArgs({e});
    qDebug() << RESULT_STR << res;

    return res;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Сохраняет данные свойства в файл.
//[deprecated]
EXPORT int propSaveToFile(id_prop p, const char *fileName)
{
    PRINT_FUNC_INFO
    int res = m_cgt->propSaveToFile(p, fileName);
    printArgs({p, fileName});
    qDebug() << RESULT_STR << res;

    return res;
}

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
