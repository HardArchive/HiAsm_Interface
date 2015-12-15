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
    bool isLink(const ElementFlgs &flags);

    bool isEditMultiEx(const ElementClass &eClass);
    bool isPolyMulti(const ElementClass &eClass);
}

namespace cgt
{
    //!~~~~~~~~~~~~~~~~~~~~~ служебные функции ~~~~~~~~~~~~~~~~~~~~~~~
    //ru Устанавливаем параметры
    void init(TBuildProcessRec &params);
    void setProxyCgt(PCodeGenTools proxyCgt);
    quintptr getMainSDK();

    //!~~~~~~~~~~~~~~~~~~~~~~~~ контейнер ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает количество элементов в контейнере.
    int sdkGetCount(quintptr SDK);
    //ru Возвращает ID элемента по его Z-положению(индексу) в контейнере.
    quintptr sdkGetElement(quintptr SDK, int Index);
    //ru Возвращает ID элемента по имени элемента.
    quintptr sdkGetElementName(quintptr SDK, char *Name);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает флаги элемента.
    ElementFlags elGetFlag(quintptr e);
    //ru Возвращает количество свойств элемента.
    int elGetPropCount(quintptr e);
    //ru Возвращает свойство элемента по индексу, с порядковым номером из INI.
    quintptr elGetProperty(quintptr e, int Index);
    //ru Возвращает True, если значение свойства совпадает с заданным в INI файле, иначе False.
    bool elIsDefProp(quintptr id_element, int index);
    //ru Присваиваем элементу уникальное имя и возвращаем ID этого элемента.
    quintptr elSetCodeName(quintptr e, const char *Name);
    //ru Возвращает уникальное имя элемента
    const char *elGetCodeName(quintptr e);
    //ru Возвращает имя класса элемента.
    const char *elGetClassName(quintptr e);
    //ru Возвращает водержимое поля Sub из конфигурационного INI-файла элемента.
    const char *elGetInfSub(quintptr e);
    //ru Возвращает общее количество видимых точек у элемента.
    int elGetPtCount(quintptr e);
    //ru Возвращает ID точки по её индексу.
    quintptr elGetPt(quintptr e, int i);
    //ru Возвращает ID точки по её имени.
    //[deprecated]
    quintptr elGetPtName(quintptr e, const char *Name);
    //ru Возвращает индекс класса элемента.
    ElementClass elGetClassIndex(quintptr e);
    //ru Возвращает ID внутренней схемы для контейнеров,
    //ru или ID родителя id_element для редактора контейнера (ELEMENT_FLG_IS_EDIT).
    quintptr elGetSDK(quintptr e);
    //ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются.
    bool elLinkIs(quintptr e);
    //ru Возвращает ID главного элемента(тот, на который ссылаются другие).
    quintptr elLinkMain(quintptr e);
    //ru Помещает в переменные "X" и "Y", позицию элемента в редакторе схем.
    void elGetPos(quintptr e, int &X, int &Y);
    //ru Помещает в переменные "W" и "H", размеры элемента.
    void elGetSize(quintptr e, int &W, int &H);
    //ru Возвращает внутренний ID элемента (отличается от внешнего).
    //[deprecated]
    int elGetEID(quintptr e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID точки, с которой соединена указанная.
    //TODO [deprecated?], в CodeGen.dpr не используется.
    quintptr ptGetLinkPoint(quintptr p);
    //ru Возвращает ID точки, с которой соединена указанная точка,
    //ru без учета точек разрыва и хабов.
    quintptr ptGetRLinkPoint(quintptr p);
    //ru Возвращает тип точек(константы PointTypes).
    PointTypes ptGetType(quintptr p);
    //ru Возвращает имя точки.
    const char *ptGetName(quintptr p);
    //ru Возвращает ID элемента, которому принадлежит точка.
    quintptr ptGetParent(quintptr p);
    //ru Возвращает тип точки (PointTypes).
    PointTypes ptGetIndex(quintptr p);
    //ru Возвращает базовую часть имени динамической точки(для CI_DPElement).
    const char *pt_dpeGetName(quintptr p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип свойства.
    DataTypes propGetType(quintptr prop);
    //ru Возвращает имя свойства.
    const char *propGetName(quintptr prop);
    //ru Возвращает значение свойства в виде указателя на данные.
    quintptr propGetValue(quintptr prop);
    //ru Возвращает значение свойства в формате uchar.
    uchar propToByte(quintptr prop);
    //ru Возвращает значение свойства в формате int.
    int propToInteger(quintptr prop);
    //ru Возвращает значение свойства в формате float.
    qreal propToReal(quintptr prop);
    //ru Возвращает значение свойства в виде C строки.
    const char *propToString(quintptr prop);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Добавляет имя файла в общий список временных файлов
    //ru для последующего удаления файла.
    int resAddFile(const char *Name);
    //ru Добавляет иконку в ресурсы и в список временных файлов.
    //ru Возвращают имя временного файла.
    const char *resAddIcon(quintptr p);
    //ru Добавляет строку в ресурсы и в список временных файлов.
    //ru Возвращают имя временного файла.
    const char *resAddStr(const char *p);
    //ru Добавляет поток (данные) в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    const char *resAddStream(quintptr p);
    //ru Добавляет звук в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    const char *resAddWave(quintptr p);
    //ru Добавляет картинку в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    const char *resAddBitmap(quintptr p);
    //ru Добавляет меню в ресурсы и в список временных файлов.
    //[deprecated]
    const char *resAddMenu(quintptr p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Выводит строку Text в окно Отладка цветом Color
    //ru Всего возвращает 0.
    int _Debug(const char *Text, int Color);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает значение параметра среды по его индексу
    int GetParam(CgtParams index, void *value);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ массив ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает количество элементов в массиве.
    int arrCount(quintptr a);
    //ru Возвращает тип элементов в массиве.
    DataTypes arrType(quintptr a);
    //ru Возвращает имя элемента с индексом Index.
    const char *arrItemName(quintptr a, int Index);
    //ru Возвращает значение элемента с индексом Index
    quintptr arrItemData(quintptr a, int Index);
    //ru Получаем элемент массива в виде свойства,
    //ru для дальнейшей работы с ним cgt::prop* функциями.
    quintptr arrGetItem(quintptr a, int Index);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает >0, если запускаем cборку и запуск схемы в режиме отладки,
    //ru иначе 0.
    int isDebug(quintptr e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ работа с данными ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип данных.
    DataTypes dtType(quintptr d);
    //ru Возвращает данные в формате: строка в стиле C.
    const char *dtStr(quintptr d);
    //ru Возвращает данные в формате: целое число.
    int dtInt(quintptr d);
    //ru Возвращает данные в формате: число с плавающей запятой.
    double dtReal(quintptr d);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает название шрифта.
    const char *fntName(quintptr f);
    //ru Возвращает размер шрифта.
    int fntSize(quintptr f);
    //ru Возвращает стиль шрифта.
    uchar fntStyle(quintptr f);
    //ru Возвращает цвет шрифта.
    uint fntColor(quintptr f);
    //ru Возвращает кодировку шрифта.
    uchar fntCharSet(quintptr f);
    //!~~~~~~~~~~~~~~~~элемент | пользовательские данные ~~~~~~~~~~~~~
    //!ru Судя по CodeGen.dpr, используется для хранения указателя (ID элемента) на самого себя.
    //ru Возвращает пользовательские данные элемента.
    //ru Коммент из hiasm5 - user data used in FTCG codegen.
    //ru Судя по всему, данные могут быть любого типа, ибо хранит указатель..
    quintptr elGetData(quintptr e);
    //ru Устанавливает пользовательские данные элементу.
    //ru Коммент из hiasm5 - user data used in FTCG codegen.
    //ru Судя по всему, данные могут быть любого типа, ибо хранит указатель.
    void elSetData(quintptr e, quintptr data);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип данных точки.
    DataTypes ptGetDataType(quintptr p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID родительского контейнера элемента.
    quintptr elGetParent(quintptr e);
    //ru Возвращает количество свойств в списке свойств(из панели свойств).
    //ru В RTCG используется аналогичная функция - elGetPropCount.
    //[deprecated]
    int elGetPropertyListCount(quintptr e);
    //ru Возвращает свойство из списка свойств (PropertyList).
    //[deprecated]
    quintptr elGetPropertyListItem(quintptr e, int i);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает имя свойства.
    const char *plGetName(quintptr p);
    //ru Возвращает описание свойства.
    const char *plGetInfo(quintptr p);
    //ru Возвращает группу свойсва.
    const char *plGetGroup(quintptr p);
    //ru Возвращает указатель на данные свойства.
    quintptr plGetProperty(quintptr p);
    //ru Возвращает ID родительского элемента указанного свойства.
    quintptr plGetOwner(quintptr p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает описание точки.
    const char *ptGetInfo(quintptr p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID элемента, прилинкованного к указанному свойству.
    quintptr propGetLinkedElement(quintptr e, const char *propName);
    //ru Возвращает 1, если свойство помечено на перевод.
    int propIsTranslate(quintptr e, quintptr p);
    //ru Предназначение данной функции так и небыло найдено.
    //ru Всегда возвращает 0.
    //[deprecated]
    quintptr propGetLinkedElementInfo(quintptr e, quintptr prop, char *buf);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент - CI_PolyMulti ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает SDK контейнера по его индексу.
    quintptr elGetSDKByIndex(quintptr e, int index);
    //ru Возвращает количаство контейнеров полиморфного элемента(CI_PolyMulti).
    int elGetSDKCount(quintptr e);
    //ru Возвращает имя контейнера по индексу.
    const char *elGetSDKName(quintptr e, int index);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает элемент родитель для данного SDK.
    //ru Возвращает 0, если контейнер не имеет родителя.
    quintptr sdkGetParent(quintptr SDK);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает интерфейсы, предоставляемые элементом.
    //ru Содержимое поля Interfaces= из конфигурации элемента.
    const char *elGetInterface(quintptr e);
    //ru Возвращает список классов, от которых наследуется элемент
    //ru Содержимое поля Inherit= из конфигурации элемента.
    const char *elGetInherit(quintptr e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает 1, если список ресурсов пуст, и 0 в противном случае.
    int resEmpty();
    //ru Устанавливает префикс для имен ресурсов.
    int resSetPref(const char *pref);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Добавляет информацию в информационную панель
    int _Error(int line, quintptr e, const char *text);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID группы, к которой принадлежит элемент и 0, если группа отсутствует
    //[deprecated]
    int elGetGroup(quintptr e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Сохраняет данные свойства в файл.
    //[deprecated]
    int propSaveToFile(quintptr p, const char *fileName);
}
