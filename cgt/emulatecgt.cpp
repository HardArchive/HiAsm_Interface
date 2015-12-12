//Project
#include "emulatecgt.h"
#include "scenemodel/container.h"
#include "scenemodel/element.h"
#include "scenemodel/point.h"
#include "scenemodel/property.h"

//STL

//Qt


namespace EmulateCgt
{
#define EXPORT static __stdcall

    //ru Храним указатель на модель схемы
    static SceneModel *m_model = nullptr;

    //~~~~~~~~~~~~~~~~~ Проксированные функции ~~~~~~~~~~~~~~~~~~~

    //!~~~~~~~~~~~~~~~~~~~~~~~~ контейнер ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает количество элементов в контейнере.
    EXPORT uint sdkGetCount(quintptr id_sdk)
    {
        return m_model->getCountContainers(id_sdk);
    }

    //ru Возвращает ID элемента по его Z-положению(индексу) в контейнере.
    EXPORT quintptr sdkGetElement(quintptr id_sdk, int index)
    {
        return m_model->getIdElementFromSDKByIndex(id_sdk, index);
    }

    //ru Возвращает ID элемента по имени элемента.
    EXPORT quintptr sdkGetElementName(quintptr id_sdk, char *name)
    {
        const PContainer c = m_model->getContainerById(id_sdk);
        if (!c)
            return 0;

        return c->getIdElementByName(QString::fromLocal8Bit(name));
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает флаги элемента.
    EXPORT ElementFlags elGetFlag(quintptr e)
    {

        return ELEMENT_FLG_IS_FREEZE;
    }

    //ru Возвращает количество свойств элемента.
    EXPORT int elGetPropCount(quintptr e)
    {

        return 0;
    }

    //ru Возвращает свойство элемента по индексу, с порядковым номером из INI.
    EXPORT quintptr elGetProperty(quintptr e, int Index)
    {

        return 0;
    }

    //ru Возвращает True, если значение свойства совпадает с заданным в INI файле, иначе False.
    EXPORT bool elIsDefProp(quintptr e, int Index)
    {

        return false;
    }

    //ru Присваиваем элементу уникальное имя и возвращаем ID этого элемента.
    EXPORT quintptr elSetCodeName(quintptr e, const char *Name)
    {

        return 0;
    }

    //ru Возвращает уникальное имя элемента
    EXPORT const char *elGetCodeName(quintptr e)
    {
        return new char[5] {};
    }

    //ru Возвращает имя класса элемента.
    EXPORT const char *elGetClassName(quintptr e)
    {
        return new char[5] {};
    }

    //ru Возвращает водержимое поля Sub из конфигурационного INI-файла элемента.
    EXPORT const char *elGetInfSub(quintptr e)
    {
        return new char[5] {};
    }

    //ru Возвращает общее количество видимых точек у элемента.
    EXPORT int elGetPtCount(quintptr e)
    {

        return 0;
    }

    //ru Возвращает ID точки по её индексу.
    EXPORT quintptr elGetPt(quintptr e, int i)
    {

        return 0;
    }

    //ru Возвращает ID точки по её имени.
    //[deprecated]
    EXPORT quintptr elGetPtName(quintptr e, const char *Name)
    {

        return 0;
    }

    //ru Возвращает индекс класса элемента.
    EXPORT ElementClass elGetClassIndex(quintptr e)
    {

        return CI_Element;
    }

    //ru Возвращает ID внутренней схемы для контейнеров,
    //ru или ID родителя id_element для редактора контейнера (ELEMENT_FLG_IS_EDIT).
    EXPORT quintptr elGetSDK(quintptr e)
    {

        return 0;
    }

    //ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются.
    EXPORT bool elLinkIs(quintptr e)
    {
        return false;
    }

    //ru Возвращает ID главного элемента(тот, на который ссылаются другие).
    EXPORT quintptr elLinkMain(quintptr e)
    {
        return 0;
    }

    //ru Помещает в переменные "X" и "Y", позицию элемента в редакторе схем.
    EXPORT void elGetPos(quintptr e, int &X, int &Y)
    {
        X = 0;
        Y = 0;
    }

    //ru Помещает в переменные "W" и "H", размеры элемента.
    EXPORT void elGetSize(quintptr e, int &W, int &H)
    {
        W = 0;
        H = 0;
    }

    //ru Возвращает внутренний ID элемента (отличается от внешнего).
    //[deprecated]
    EXPORT int elGetEID(quintptr e)
    {

        return 0;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID точки, с которой соединена указанная.
    //TODO [deprecated?], в CodeGen.dpr не используется.
    EXPORT quintptr ptGetLinkPoint(quintptr p)
    {
        return 0;
    }

    //ru Возвращает ID точки, с которой соединена указанная точка,
    //ru без учета точек разрыва и хабов.
    EXPORT quintptr ptGetRLinkPoint(quintptr p)
    {
        return 0;
    }

    //ru Возвращает тип точек(константы PointTypes).
    EXPORT PointTypes ptGetType(quintptr p)
    {
        return pt_Work;
    }

    //ru Возвращает имя точки.
    EXPORT const char *ptGetName(quintptr p)
    {

        return new char[5] {};
    }

    //ru Возвращает ID элемента, которому принадлежит точка.
    EXPORT quintptr ptGetParent(quintptr p)
    {


        return 0;
    }

    //ru Возвращает тип точки (PointTypes).
    EXPORT PointTypes ptGetIndex(quintptr p)
    {

        return pt_Work;
    }

    //ru Возвращает базовую часть имени динамической точки(для CI_DPElement).
    EXPORT const char *pt_dpeGetName(quintptr p)
    {

        return new char[5] {};
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип свойства.
    EXPORT DataTypes propGetType(quintptr prop)
    {
        return data_null;
    }

    //ru Возвращает имя свойства.
    EXPORT const char *propGetName(quintptr prop)
    {

        return new char[5] {};
    }

    //ru Возвращает значение свойства в виде указателя на данные.
    EXPORT quintptr propGetValue(quintptr prop)
    {

        return 0;
    }

    //ru Возвращает значение свойства в формате uchar.
    EXPORT uchar propToByte(quintptr prop)
    {

        return 0;
    }

    //ru Возвращает значение свойства в формате int.
    EXPORT int propToInteger(quintptr prop)
    {

        return 0;
    }

    //ru Возвращает значение свойства в формате float.
    EXPORT float propToReal(quintptr prop)
    {

        return 0.0;
    }

    //ru Возвращает значение свойства в виде C строки.
    EXPORT const char *propToString(quintptr prop)
    {

        return new char[5] {};
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~

    //ru Добавляет имя файла в общий список временных файлов
    //ru для последующего удаления файла.
    EXPORT int resAddFile(const char *Name)
    {

        return 0;
    }

    //ru Добавляет иконку в ресурсы и в список временных файлов,
    //ru и возвращают имя временного файла.
    //TODO p - является свойством, которое содержит иконку?
    EXPORT const char *resAddIcon(quintptr p)
    {


        return new char[5] {};
    }

    //ru Добавляет строку в ресурсы и в список временных файлов.
    //TODO Что возвращает?
    EXPORT const char *resAddStr(const char *p)
    {

        return new char[5] {};
    }

    //ru Добавляет поток (данные) в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    EXPORT const char *resAddStream(quintptr p)
    {

        return new char[5] {};
    }

    //ru Добавляет звук в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    EXPORT const char *resAddWave(quintptr p)
    {

        return new char[5] {};
    }

    //ru Добавляет картинку в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    EXPORT const char *resAddBitmap(quintptr p)
    {

        return new char[5] {};
    }

    //ru Добавляет меню в ресурсы и в список временных файлов.
    //[deprecated]
    EXPORT const char *resAddMenu(quintptr p)
    {

        return new char[5] {};
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Выводит строку Text в окно Отладка цветом Color
    //ru Всего возвращает 0.
    EXPORT int _Debug(const char *Text, int Color)
    {

        return 0;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru На основе индекса параметра, записываем данные в память value
    EXPORT int GetParam(CgtParams index, quintptr value)
    {
        m_model->getCgtParam(index, value);

        return 1;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ массив ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает количество элементов в массиве.
    EXPORT int arrCount(quintptr a)
    {

        return 0;
    }

    //ru Возвращает тип элементов в массиве.
    EXPORT DataTypes arrType(quintptr a)
    {

        return data_null;
    }

    //ru Возвращает имя элемента с индексом Index.
    EXPORT const char *arrItemName(quintptr a, int Index)
    {

        return new char[5] {};
    }

    //ru Возвращает значение элемента с индексом Index
    EXPORT quintptr arrItemData(quintptr a, int Index)
    {

        return 0;
    }

    //ru Получаем элемент массива в виде свойства,
    //ru для дальнейшей работы с ним cgt::prop* функциями.
    EXPORT quintptr arrGetItem(quintptr a, int Index)
    {

        return 0;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращаем >0, если запускаем схемы в режиме отладки,
    //ru иначе 0.
    EXPORT int isDebug(quintptr e)
    {
        Q_UNUSED(e)
        return m_model->isDebug();
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ работа с данными ~~~~~~~~~~~~~~~~~~~~~~~~~~

    //ru Возвращает тип данных.
    EXPORT DataTypes dtType(quintptr d)
    {

        return data_null;
    }

    //ru Возвращает данные в формате: строка в стиле C.
    EXPORT const char *dtStr(quintptr d)
    {

        return new char[5] {};
    }

    //ru Возвращает данные в формате: целое число.
    EXPORT int dtInt(quintptr d)
    {

        return 0;
    }

    //ru Возвращает данные в формате: число с плавающей запятой.
    EXPORT double dtReal(quintptr d)
    {


        return 0.0;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает название шрифта.
    EXPORT const char *fntName(quintptr f)
    {


        return new char[5] {};
    }
    //ru Возвращает размер шрифта.
    EXPORT int fntSize(quintptr f)
    {

        return 0;
    }
    //ru Возвращает стиль шрифта.
    EXPORT uchar fntStyle(quintptr f)
    {

        return 0;
    }
    //ru Возвращает цвет шрифта.
    EXPORT uint fntColor(quintptr f)
    {

        return 0;
    }
    //ru Возвращает кодировку шрифта.
    EXPORT uchar fntCharSet(quintptr f)
    {

        return 0;
    }

    //!~~~~~~~~~~~~~~~~элемент | пользовательские данные ~~~~~~~~~~~~~
    //!ru Судя по CodeGen.dpr, используется для хранения указателя (ID элемента) на самого себя.

    //ru Возвращает пользовательские данные элемента.
    //ru Коммент из hiasm5 - user data used in FTCG codegen.
    //ru Судя по всему, данные могут быть любого типа, ибо хранит указатель..
    EXPORT quintptr elGetData(quintptr e)
    {

        return 0;
    }

    //ru Устанавливает пользовательские данные элементу.
    //ru Коммент из hiasm5 - user data used in FTCG codegen.
    //ru Судя по всему, данные могут быть любого типа, ибо хранит указатель.
    EXPORT void elSetData(quintptr e, const quintptr data)
    {

    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип данных точки.
    EXPORT DataTypes ptGetDataType(quintptr p)
    {

        return data_null;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID родительского контейнера элемента.
    EXPORT quintptr elGetParent(quintptr e)
    {

        return 0;
    }

    //ru Возвращает количество свойств в списке свойств(из панели свойств).
    //ru В RTCG используется аналогичная функция - elGetPropCount.
    //[deprecated]
    EXPORT int elGetPropertyListCount(quintptr e)
    {

        return 0;
    }

    //ru Возвращает свойство из списка свойств (PropertyList).
    //[deprecated]
    EXPORT quintptr elGetPropertyListItem(quintptr e, int i)
    {

        return 0;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает имя свойства.
    EXPORT const char *plGetName(quintptr p)
    {

        return new char[5] {};
    }

    //ru Возвращает описание свойства.
    EXPORT const char *plGetInfo(quintptr p)
    {

        return new char[5] {};
    }

    //ru Возвращает группу свойсва.
    EXPORT const char *plGetGroup(quintptr p)
    {

        return new char[5] {};
    }

    //ru Возвращает указатель на данные свойства.
    EXPORT quintptr plGetProperty(quintptr p)
    {

        return 0;
    }

    //ru Возвращает ID родительского элемента указанного свойства.
    EXPORT quintptr plGetOwner(quintptr p)
    {

        return 0;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает описание точки.
    EXPORT const char *ptGetInfo(quintptr p)
    {

        return new char[5] {};
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID элемента, прилинкованного к указанному свойству.
    EXPORT quintptr propGetLinkedElement(quintptr e, const char *propName)
    {

        return 0;
    }

    //ru Возвращает 1, если свойство помечено на перевод.
    EXPORT int propIsTranslate(quintptr e, quintptr p)
    {

        return 0;
    }

    //ru Предназначение данной функции так и небыло найдено.
    //ru Всегда возвращает 0.
    //[deprecated]
    EXPORT quintptr propGetLinkedElementInfo(quintptr e, quintptr prop, char *_int)
    {

        return 0;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент - CI_PolyMulti ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает SDK контейнера по его индексу.
    EXPORT quintptr elGetSDKByIndex(quintptr e, int index)
    {

        return 0;
    }

    //ru Возвращает количаство контейнеров полиморфного элемента(CI_PolyMulti).
    EXPORT int elGetSDKCount(quintptr e)
    {

        return 0;
    }

    //ru Возвращает имя контейнера по индексу.
    EXPORT const char *elGetSDKName(quintptr e, int index)
    {

        return new char[5] {};
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает элемент родитель для данного SDK.
    //ru Возвращает 0, если контейнер не имеет родителя.
    EXPORT quintptr sdkGetParent(quintptr SDK)
    {

        return 0;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает интерфейсы, предоставляемые элементом.
    //ru Содержимое поля Interfaces= из конфигурации элемента.
    EXPORT const char *elGetInterface(quintptr e)
    {

        return new char[5] {};
    }

    //ru Возвращает список классов, от которых наследуется элемент
    //ru Содержимое поля Inherit= из конфигурации элемента.
    EXPORT const char *elGetInherit(quintptr e)
    {

        return new char[5] {};
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает 1, если список ресурсов пуст, и 0 в противном случае.
    EXPORT int resEmpty()
    {

        return 0;
    }

    //ru Устанавливает префикс для имен ресурсов.
    EXPORT int resSetPref(const char *pref)
    {

        return 0;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Добавляет информацию в информационную панель
    EXPORT int _Error(int line, quintptr e, const char *text)
    {

        return 0;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID группы, к которой принадлежит элемент и 0, если группа отсутствует
    //[deprecated]
    EXPORT int elGetGroup(quintptr e)
    {

        return 0;
    }

    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Сохраняет данные свойства в файл.
    //[deprecated]
    EXPORT int propSaveToFile(quintptr p, const char *fileName)
    {

        return 0;
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

    //Сохранение указателя для дальнейшей работы с оным
    void setSceneModel(SceneModel &collector)
    {
        m_model = &collector;
    }

    //Получаем массив указателей на функции
    PCodeGenTools getCgt()
    {
        return reinterpret_cast<PCodeGenTools>(arrayPointers);
    }
}
