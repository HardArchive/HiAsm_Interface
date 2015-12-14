//Project
#include "proxycgt.h"

//STL

//Qt
#include <QDebug>
#include <QFlags>

namespace ProxyCgt
{
    //Дефайны
#define PRINT_FUNC_INFO qDebug() << CALL_STR << Q_FUNC_INFO;
#define PRINT_RESULT_STR(X) \
    qDebug().noquote() << RESULT_STR << '"'+QString::fromLocal8Bit(X)+'"';
#define EXPORT static __stdcall

    //Константы
    const char CALL_STR[] = "  Call:";
    const char ARG_STR[] = "  Arg";
    const char RESULT_STR[] = "  Return:";


    //Для хранения указателя на массив указателей на callback функции
    static PCodeGenTools m_cgt = nullptr;

    //Служебные функции
    void printArgs(std::initializer_list<QVariant> args, bool noquote = false)
    {
        uint i = 1;
        for (const QVariant &v : args) {
            if (v.type() == QVariant::String) {
                if (noquote)
                    qDebug().nospace().noquote() << "  Arg" << i << ": " << v.toString();
                else
                    qDebug().nospace() << "  Arg" << i << ": " << v.toString();

            } else {
                qDebug().nospace().noquote() << "  Arg" << i << ": " << v.toString();
            }
            i++;
        }
    }
    void printArgs(CgtParams index, const QVariant value)
    {
        qDebug().nospace().noquote() << "  Arg1: " << CgtParamsMap[index];
        if (value.type() == QVariant::String) {
            qDebug().nospace() << "  Arg2: " << value.toString();
        } else {
            qDebug().nospace().noquote() << "  Arg2: " << value.toString();
        }
    }

    //~~~~~~~~~~~~~~~~~ Проксированные функции ~~~~~~~~~~~~~~~~~~~

    //!~~~~~~~~~~~~~~~~~~~~~~~~ контейнер ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает количество элементов в контейнере.
    EXPORT int sdkGetCount(quintptr SDK)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->sdkGetCount(SDK);
        printArgs({SDK});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает ID элемента по его Z-положению(индексу) в контейнере.
    EXPORT quintptr sdkGetElement(quintptr SDK, int Index)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->sdkGetElement(SDK, Index);
        printArgs({SDK, Index});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает ID элемента по имени элемента.
    EXPORT quintptr sdkGetElementName(quintptr SDK, char *Name)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->sdkGetElementName(SDK, Name);
        printArgs({SDK, Name});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает флаги элемента.
    EXPORT ElementFlags elGetFlag(quintptr e)
    {
        PRINT_FUNC_INFO
        ElementFlags res = m_cgt->elGetFlag(e);
        printArgs({e});

        qDebug() << RESULT_STR << ElementFlgs(res);

        return res;
    }

    //ru Возвращает количество свойств элемента.
    EXPORT int elGetPropCount(quintptr e)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->elGetPropCount(e);
        printArgs({e});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает свойство элемента по индексу, с порядковым номером из INI.
    EXPORT quintptr elGetProperty(quintptr e, int Index)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->elGetProperty(e, Index);
        printArgs({e, Index});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает True, если значение свойства совпадает с заданным в INI файле, иначе False.
    EXPORT bool elIsDefProp(quintptr e, int Index)
    {
        PRINT_FUNC_INFO
        bool res = m_cgt->elIsDefProp(e, Index);
        printArgs({e, Index});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Присваиваем элементу уникальное имя и возвращаем ID этого элемента.
    EXPORT quintptr elSetCodeName(quintptr e, const char *Name)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->elSetCodeName(e, Name);
        printArgs({e, Name});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает уникальное имя элемента
    EXPORT const char *elGetCodeName(quintptr e)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->elGetCodeName(e);
        printArgs({e});
        PRINT_RESULT_STR(res)

        return res;
    }

    //ru Возвращает имя класса элемента.
    EXPORT const char *elGetClassName(quintptr e)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->elGetClassName(e);
        printArgs({e});
        PRINT_RESULT_STR(res)

        return res;
    }

    //ru Возвращает водержимое поля Sub из конфигурационного INI-файла элемента.
    EXPORT const char *elGetInfSub(quintptr e)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->elGetInfSub(e);
        printArgs({e});
        PRINT_RESULT_STR(res)

        return res;
    }

    //ru Возвращает общее количество видимых точек у элемента.
    EXPORT int elGetPtCount(quintptr e)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->elGetPtCount(e);
        printArgs({e});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает ID точки по её индексу.
    EXPORT quintptr elGetPt(quintptr e, int i)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->elGetPt(e, i);
        printArgs({e, i});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает ID точки по её имени.
    //[deprecated]
    EXPORT quintptr elGetPtName(quintptr e, const char *Name)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->elGetPtName(e, Name);
        printArgs({e, Name});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает индекс класса элемента.
    EXPORT ElementClass elGetClassIndex(quintptr e)
    {
        PRINT_FUNC_INFO
        ElementClass res = m_cgt->elGetClassIndex(e);
        printArgs({e});
        qDebug().noquote() << RESULT_STR << ElementClassMap[res];

        return res;
    }

    //ru Возвращает ID внутренней схемы для контейнеров,
    //ru или ID родителя id_element для редактора контейнера (ELEMENT_FLG_IS_EDIT).
    EXPORT quintptr elGetSDK(quintptr e)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->elGetSDK(e);
        printArgs({e});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются.
    EXPORT bool elLinkIs(quintptr e)
    {
        PRINT_FUNC_INFO
        bool res = m_cgt->elLinkIs(e);
        printArgs({e});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает ID главного элемента(тот, на который ссылаются другие).
    EXPORT quintptr elLinkMain(quintptr e)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->elLinkMain(e);
        printArgs({e});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Помещает в переменные "X" и "Y", позицию элемента в редакторе схем.
    EXPORT void elGetPos(quintptr e, int &X, int &Y)
    {
        PRINT_FUNC_INFO
        m_cgt->elGetPos(e, X, Y);
        printArgs({e, X, Y});
    }

    //ru Помещает в переменные "W" и "H", размеры элемента.
    EXPORT void elGetSize(quintptr e, int &W, int &H)
    {
        PRINT_FUNC_INFO
        m_cgt->elGetSize(e, W, H);
        printArgs({e, W, H});
    }

    //ru Возвращает внутренний ID элемента (отличается от внешнего).
    //[deprecated]
    EXPORT int elGetEID(quintptr e)
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
    EXPORT quintptr ptGetLinkPoint(quintptr p)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->ptGetLinkPoint(p);
        printArgs({p});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает ID точки, с которой соединена указанная точка,
    //ru без учета точек разрыва и хабов.
    EXPORT quintptr ptGetRLinkPoint(quintptr p)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->ptGetRLinkPoint(p);
        printArgs({p});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает тип точек(константы PointTypes).
    EXPORT PointTypes ptGetType(quintptr p)
    {
        PRINT_FUNC_INFO
        PointTypes res = m_cgt->ptGetType(p);
        printArgs({p});
        qDebug().noquote() << RESULT_STR << PointTypesMap[res];

        return res;
    }

    //ru Возвращает имя точки.
    EXPORT const char *ptGetName(quintptr p)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->ptGetName(p);
        printArgs({p});
        PRINT_RESULT_STR(res)

        return res;
    }

    //ru Возвращает ID элемента, которому принадлежит точка.
    EXPORT quintptr ptGetParent(quintptr p)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->ptGetParent(p);
        printArgs({p});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает тип точки (PointTypes).
    EXPORT PointTypes ptGetIndex(quintptr p)
    {
        PRINT_FUNC_INFO
        PointTypes res = m_cgt->ptGetIndex(p);
        printArgs({p}, true);
        qDebug().noquote() << RESULT_STR << PointTypesMap[res];

        return res;
    }

    //ru Возвращает базовую часть имени динамической точки(для CI_DPElement).
    EXPORT const char *pt_dpeGetName(quintptr p)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->pt_dpeGetName(p);
        printArgs({p});
        PRINT_RESULT_STR(res)

        return res;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип свойства.
    EXPORT DataTypes propGetType(quintptr prop)
    {
        PRINT_FUNC_INFO
        DataTypes res = m_cgt->propGetType(prop);
        printArgs({prop});
        qDebug().noquote() << RESULT_STR << DataTypesMap[res];

        return res;
    }

    //ru Возвращает имя свойства.
    EXPORT const char *propGetName(quintptr prop)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->propGetName(prop);
        printArgs({prop});
        PRINT_RESULT_STR(res)

        return res;
    }

    //ru Возвращает значение свойства в виде указателя на данные.
    EXPORT quintptr propGetValue(quintptr prop)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->propGetValue(prop);
        printArgs({prop});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает значение свойства в формате uchar.
    EXPORT uchar propToByte(quintptr prop)
    {
        PRINT_FUNC_INFO
        uchar res = m_cgt->propToByte(prop);
        printArgs({prop});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает значение свойства в формате int.
    EXPORT int propToInteger(quintptr prop)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->propToInteger(prop);
        printArgs({prop});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает значение свойства в формате float.
    EXPORT qreal propToReal(quintptr prop)
    {
        PRINT_FUNC_INFO
        float res = m_cgt->propToReal(prop);
        printArgs({prop});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает значение свойства в виде C строки.
    EXPORT const char *propToString(quintptr prop)
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
    EXPORT const char *resAddIcon(quintptr p)
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
    EXPORT const char *resAddStream(quintptr p)
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
    EXPORT const char *resAddWave(quintptr p)
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
    EXPORT const char *resAddBitmap(quintptr p)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->resAddBitmap(p);
        printArgs({p});
        PRINT_RESULT_STR(res)

        return res;
    }

    //ru Добавляет меню в ресурсы и в список временных файлов.
    //[deprecated]
    EXPORT const char *resAddMenu(quintptr p)
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
    EXPORT int GetParam(CgtParams index, void *value)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->GetParam(index, value);

        switch (index) {
        case PARAM_CODE_PATH :
            printArgs(index, reinterpret_cast<const char *>(value));
            break;
        case PARAM_DEBUG_MODE:
            printArgs(index, *reinterpret_cast<const int *>(value));
            break;
        case PARAM_DEBUG_SERVER_PORT:
            printArgs(index, *reinterpret_cast<const int *>(value));
            break;
        case PARAM_DEBUG_CLIENT_PORT:
            printArgs(index, *reinterpret_cast<const int *>(value));
            break;
        case PARAM_PROJECT_PATH:
            printArgs(index, reinterpret_cast<const char *>(value));
            break;
        case PARAM_HIASM_VERSION:
            printArgs(index, reinterpret_cast<const char *>(value));
            break;
        case PARAM_USER_NAME:
            printArgs(index, reinterpret_cast<const char *>(value));
            break;
        case PARAM_USER_MAIL:
            printArgs(index, reinterpret_cast<const char *>(value));
            break;
        case PARAM_PROJECT_NAME:
            printArgs(index, reinterpret_cast<const char *>(value));
            break;
        case PARAM_SDE_WIDTH:
            printArgs(index, *reinterpret_cast<const int *>(value));
            break;
        case PARAM_SDE_HEIGHT:
            printArgs(index, *reinterpret_cast<const int *>(value));
            break;
        case PARAM_COMPILER:
            printArgs(index, reinterpret_cast<const char *>(value));
            break;
        }

        qDebug() << RESULT_STR << res;

        return res;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ массив ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает количество элементов в массиве.
    EXPORT int arrCount(quintptr a)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->arrCount(a);
        printArgs({a});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает тип элементов в массиве.
    EXPORT DataTypes arrType(quintptr a)
    {
        PRINT_FUNC_INFO
        DataTypes res = m_cgt->arrType(a);
        printArgs({a});
        qDebug().noquote() << RESULT_STR << DataTypesMap[res];

        return res;
    }

    //ru Возвращает имя элемента с индексом Index.
    EXPORT const char *arrItemName(quintptr a, int Index)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->arrItemName(a, Index);
        printArgs({a, Index});
        PRINT_RESULT_STR(res)

        return res;
    }

    //ru Возвращает значение элемента с индексом Index
    EXPORT quintptr arrItemData(quintptr a, int Index)
    {
        PRINT_FUNC_INFO
        const quintptr res = m_cgt->arrItemData(a, Index);
        printArgs({a, Index});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Получаем элемент массива в виде свойства,
    //ru для дальнейшей работы с ним cgt::prop* функциями.
    EXPORT quintptr arrGetItem(quintptr a, int Index)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->arrGetItem(a, Index);
        printArgs({a, Index});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает >0, если запускаем cборку и запуск схемы в режиме отладки,
    //ru иначе 0.
    EXPORT int isDebug(quintptr e)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->isDebug(e);
        printArgs({e});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ работа с данными ~~~~~~~~~~~~~~~~~~~~~~~~~~

    //ru Возвращает тип данных.
    EXPORT DataTypes dtType(quintptr d)
    {
        PRINT_FUNC_INFO
        DataTypes res = m_cgt->dtType(d);
        printArgs({d});
        qDebug().noquote() << RESULT_STR << DataTypesMap[res];

        return res;
    }

    //ru Возвращает данные в формате: строка в стиле C.
    EXPORT const char *dtStr(quintptr d)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->dtStr(d);
        printArgs({d});
        PRINT_RESULT_STR(res)

        return res;
    }

    //ru Возвращает данные в формате: целое число.
    EXPORT int dtInt(quintptr d)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->dtInt(d);
        printArgs({d});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает данные в формате: число с плавающей запятой.
    EXPORT double dtReal(quintptr d)
    {
        PRINT_FUNC_INFO
        double res = m_cgt->dtReal(d);
        printArgs({d});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает название шрифта.
    EXPORT const char *fntName(quintptr f)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->fntName(f);
        printArgs({f});
        PRINT_RESULT_STR(res)

        return res;
    }
    //ru Возвращает размер шрифта.
    EXPORT int fntSize(quintptr f)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->fntSize(f);
        printArgs({f});
        qDebug() << RESULT_STR << res;

        return res;
    }
    //ru Возвращает стиль шрифта.
    EXPORT uchar fntStyle(quintptr f)
    {
        printArgs({f});
        PRINT_FUNC_INFO
        uchar res = m_cgt->fntStyle(f);
        qDebug() << RESULT_STR << res;

        return res;
    }
    //ru Возвращает цвет шрифта.
    EXPORT uint fntColor(quintptr f)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->fntColor(f);
        printArgs({f});
        qDebug() << RESULT_STR << res;

        return res;
    }
    //ru Возвращает кодировку шрифта.
    EXPORT uchar fntCharSet(quintptr f)
    {
        PRINT_FUNC_INFO
        uchar res = m_cgt->fntCharSet(f);
        printArgs({f});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //!~~~~~~~~~~~~~~~~элемент | пользовательские данные ~~~~~~~~~~~~~
    //!ru Судя по CodeGen.dpr, используется для хранения указателя (ID элемента) на самого себя.

    //ru Возвращает пользовательские данные элемента.
    //ru Коммент из hiasm5 - user data used in FTCG codegen.
    //ru Судя по всему, данные могут быть любого типа, ибо хранит указатель..
    EXPORT quintptr elGetData(quintptr e)
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
    EXPORT void elSetData(quintptr e, quintptr data)
    {
        PRINT_FUNC_INFO
        m_cgt->elSetData(e, data);
        printArgs({e, data});
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип данных точки.
    EXPORT DataTypes ptGetDataType(quintptr p)
    {
        PRINT_FUNC_INFO
        DataTypes res = m_cgt->ptGetDataType(p);
        printArgs({p});
        qDebug().noquote() << RESULT_STR << DataTypesMap[res];

        return res;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID родительского контейнера элемента.
    EXPORT quintptr elGetParent(quintptr e)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->elGetParent(e);
        printArgs({e});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает количество свойств в списке свойств(из панели свойств).
    //ru В RTCG используется аналогичная функция - elGetPropCount.
    //[deprecated]
    EXPORT int elGetPropertyListCount(quintptr e)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->elGetPropertyListCount(e);
        printArgs({e});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает свойство из списка свойств (PropertyList).
    //[deprecated]
    EXPORT quintptr elGetPropertyListItem(quintptr e, int i)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->elGetPropertyListItem(e, i);
        printArgs({e, i});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает имя свойства.
    EXPORT const char *plGetName(quintptr p)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->plGetName(p);
        printArgs({p});
        PRINT_RESULT_STR(res)

        return res;
    }

    //ru Возвращает описание свойства.
    EXPORT const char *plGetInfo(quintptr p)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->plGetInfo(p);
        printArgs({p});
        PRINT_RESULT_STR(res)

        return res;
    }

    //ru Возвращает группу свойсва.
    EXPORT const char *plGetGroup(quintptr p)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->plGetGroup(p);
        printArgs({p});
        PRINT_RESULT_STR(res)

        return res;
    }

    //ru Возвращает указатель на данные свойства.
    EXPORT quintptr plGetProperty(quintptr p)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->plGetProperty(p);
        printArgs({p});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает ID родительского элемента указанного свойства.
    EXPORT quintptr plGetOwner(quintptr p)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->plGetOwner(p);
        printArgs({p});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает описание точки.
    EXPORT const char *ptGetInfo(quintptr p)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->ptGetInfo(p);
        printArgs({p});
        PRINT_RESULT_STR(res)

        return res;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID элемента, прилинкованного к указанному свойству.
    EXPORT quintptr propGetLinkedElement(quintptr e, const char *propName)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->propGetLinkedElement(e, propName);
        printArgs({e, propName});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает 1, если свойство помечено на перевод.
    EXPORT int propIsTranslate(quintptr e, quintptr p)
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
    EXPORT quintptr propGetLinkedElementInfo(quintptr e, quintptr prop, char *_int)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->propGetLinkedElementInfo(e, prop, _int);
        printArgs({e, prop, _int});
        qDebug() << RESULT_STR << res;

        return 0;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент - CI_PolyMulti ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает SDK контейнера по его индексу.
    EXPORT quintptr elGetSDKByIndex(quintptr e, int index)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->elGetSDKByIndex(e, index);
        printArgs({e, index});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает количаство контейнеров полиморфного элемента(CI_PolyMulti).
    EXPORT int elGetSDKCount(quintptr e)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->elGetSDKCount(e);
        printArgs({e});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //ru Возвращает имя контейнера по индексу.
    EXPORT const char *elGetSDKName(quintptr e, int index)
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
    EXPORT quintptr sdkGetParent(quintptr SDK)
    {
        PRINT_FUNC_INFO
        quintptr res = m_cgt->sdkGetParent(SDK);
        printArgs({SDK});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает интерфейсы, предоставляемые элементом.
    //ru Содержимое поля Interfaces= из конфигурации элемента.
    EXPORT const char *elGetInterface(quintptr e)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->elGetInterface(e);
        printArgs({e});
        PRINT_RESULT_STR(res)

        return res;
    }

    //ru Возвращает список классов, от которых наследуется элемент
    //ru Содержимое поля Inherit= из конфигурации элемента.
    EXPORT const char *elGetInherit(quintptr e)
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
    EXPORT int _Error(int line, quintptr e, const char *text)
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
    EXPORT int elGetGroup(quintptr e)
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
    EXPORT int propSaveToFile(quintptr p, const char *fileName)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->propSaveToFile(p, fileName);
        printArgs({p, fileName});
        qDebug() << RESULT_STR << res;

        return res;
    }

    //Заполняем массив указателей
    static uintptr_t arrayPointers[] {
        reinterpret_cast<quintptr>(sdkGetCount),
        reinterpret_cast<quintptr>(sdkGetElement),
        reinterpret_cast<quintptr>(sdkGetElementName),
        reinterpret_cast<quintptr>(elGetFlag),
        reinterpret_cast<quintptr>(elGetPropCount),
        reinterpret_cast<quintptr>(elGetProperty),
        reinterpret_cast<quintptr>(elIsDefProp),
        reinterpret_cast<quintptr>(elSetCodeName),
        reinterpret_cast<quintptr>(elGetCodeName),
        reinterpret_cast<quintptr>(elGetClassName),
        reinterpret_cast<quintptr>(elGetInfSub),
        reinterpret_cast<quintptr>(elGetPtCount),
        reinterpret_cast<quintptr>(elGetPt),
        reinterpret_cast<quintptr>(elGetPtName),
        reinterpret_cast<quintptr>(elGetClassIndex),
        reinterpret_cast<quintptr>(elGetSDK),
        reinterpret_cast<quintptr>(elLinkIs),
        reinterpret_cast<quintptr>(elLinkMain),
        reinterpret_cast<quintptr>(elGetPos),
        reinterpret_cast<quintptr>(elGetSize),
        reinterpret_cast<quintptr>(elGetEID),
        reinterpret_cast<quintptr>(ptGetLinkPoint),
        reinterpret_cast<quintptr>(ptGetRLinkPoint),
        reinterpret_cast<quintptr>(ptGetType),
        reinterpret_cast<quintptr>(ptGetName),
        reinterpret_cast<quintptr>(ptGetParent),
        reinterpret_cast<quintptr>(ptGetIndex),
        reinterpret_cast<quintptr>(pt_dpeGetName),
        reinterpret_cast<quintptr>(propGetType),
        reinterpret_cast<quintptr>(propGetName),
        reinterpret_cast<quintptr>(propGetValue),
        reinterpret_cast<quintptr>(propToByte),
        reinterpret_cast<quintptr>(propToInteger),
        reinterpret_cast<quintptr>(propToReal),
        reinterpret_cast<quintptr>(propToString),
        reinterpret_cast<quintptr>(resAddFile),
        reinterpret_cast<quintptr>(resAddIcon),
        reinterpret_cast<quintptr>(resAddStr),
        reinterpret_cast<quintptr>(resAddStream),
        reinterpret_cast<quintptr>(resAddWave),
        reinterpret_cast<quintptr>(resAddBitmap),
        reinterpret_cast<quintptr>(resAddMenu),
        reinterpret_cast<quintptr>(_Debug),
        reinterpret_cast<quintptr>(GetParam),
        reinterpret_cast<quintptr>(arrCount),
        reinterpret_cast<quintptr>(arrType),
        reinterpret_cast<quintptr>(arrItemName),
        reinterpret_cast<quintptr>(arrItemData),
        reinterpret_cast<quintptr>(arrGetItem),
        reinterpret_cast<quintptr>(isDebug),
        reinterpret_cast<quintptr>(dtType),
        reinterpret_cast<quintptr>(dtStr),
        reinterpret_cast<quintptr>(dtInt),
        reinterpret_cast<quintptr>(dtReal),
        reinterpret_cast<quintptr>(fntName),
        reinterpret_cast<quintptr>(fntSize),
        reinterpret_cast<quintptr>(fntStyle),
        reinterpret_cast<quintptr>(fntColor),
        reinterpret_cast<quintptr>(fntCharSet),
        reinterpret_cast<quintptr>(elGetData),
        reinterpret_cast<quintptr>(elSetData),
        reinterpret_cast<quintptr>(ptGetDataType),
        reinterpret_cast<quintptr>(elGetParent),
        reinterpret_cast<quintptr>(elGetPropertyListCount),
        reinterpret_cast<quintptr>(elGetPropertyListItem),
        reinterpret_cast<quintptr>(plGetName),
        reinterpret_cast<quintptr>(plGetInfo),
        reinterpret_cast<quintptr>(plGetGroup),
        reinterpret_cast<quintptr>(plGetProperty),
        reinterpret_cast<quintptr>(plGetOwner),
        reinterpret_cast<quintptr>(ptGetInfo),
        reinterpret_cast<quintptr>(propGetLinkedElement),
        reinterpret_cast<quintptr>(propIsTranslate),
        reinterpret_cast<quintptr>(propGetLinkedElementInfo),
        reinterpret_cast<quintptr>(elGetSDKByIndex),
        reinterpret_cast<quintptr>(elGetSDKCount),
        reinterpret_cast<quintptr>(elGetSDKName),
        reinterpret_cast<quintptr>(sdkGetParent),
        reinterpret_cast<quintptr>(elGetInterface),
        reinterpret_cast<quintptr>(elGetInherit),
        reinterpret_cast<quintptr>(resEmpty),
        reinterpret_cast<quintptr>(resSetPref),
        reinterpret_cast<quintptr>(_Error),
        reinterpret_cast<quintptr>(elGetGroup),
        reinterpret_cast<quintptr>(propSaveToFile),
    };

    /*!  Служебные функции   */

    void setProxiedCgt(PCodeGenTools cgt)
    {
        m_cgt = cgt;
    }

    //Получаем массив указателей на функции
    PCodeGenTools getCgt()
    {
        return reinterpret_cast<PCodeGenTools>(arrayPointers);
    }
}
