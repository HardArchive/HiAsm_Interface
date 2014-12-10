#ifndef _CGTSHARE_H_
#define _CGTSHARE_H_

#include <QBitArray>

//TODO Подробно изучить флаги и составить описание.
#ifdef BUILDING_DLL
#ifndef HIASM_5
enum ElementFlags {
    ELEMENT_FLG_IS_SELECT   = 0x100,
    ELEMENT_FLG_IS_NOMOUSE  = 0x2000,
    ELEMENT_FLG_IS_PARENT   = 0x200,
    ELEMENT_FLG_IS_CORE	    = 0x400,
    ELEMENT_FLG_IS_FREEZE   = 0x0,
    ELEMENT_FLG_IS_NODELETE = 0x2,
    ELEMENT_FLG_IS_MULTI	= 0x40,
    ELEMENT_FLG_ONE_WIDGET	= 0x1,
    ELEMENT_FLG_IS_EDIT 	= 0x20,
    ELEMENT_FLG_IS_SYSTEM	= 0x400,
};
typedef QFlags<ElementFlags> ElementFlgs;
#else
enum ElementFlags {
    ELEMENT_FLG_IS_SELECT	= 0x01,
    ELEMENT_FLG_IS_NOMOUSE	= 0x02,
    ELEMENT_FLG_IS_PARENT	= 0x04,
    ELEMENT_FLG_IS_CORE		= 0x08,
    ELEMENT_FLG_IS_FREEZE	= 0x10,
    ELEMENT_FLG_IS_NODELETE = 0x20,
    ELEMENT_FLG_IS_MULTI	= 0x40,
    ELEMENT_FLG_ONE_WIDGET	= 0x80,
    ELEMENT_FLG_IS_EDIT 	= 0x100,
    ELEMENT_FLG_IS_SYSTEM	= 0x400,
};
typedef QFlags<ElementFlags> ElementFlgs;
#endif
#else
enum ElementFlags {
    ELEMENT_FLG_IS_SELECT	= 0x01,
    ELEMENT_FLG_IS_NOMOUSE	= 0x02,
    ELEMENT_FLG_IS_PARENT	= 0x04,
    ELEMENT_FLG_IS_CORE		= 0x08,
    ELEMENT_FLG_IS_FREEZE	= 0x10,
    ELEMENT_FLG_IS_NODELETE = 0x20,
    ELEMENT_FLG_ONE_WIDGET	= 0x80,
    ELEMENT_FLG_IS_SYSTEM	= 0x400,
};
typedef QFlags<ElementFlags> ElementFlgs;
#endif

//ru Типы точек
enum PointsTypes {
    pt_Work  = 1, //ru Метод
    pt_Event = 2, //ru Событие
    pt_Var   = 3, //ru Переменная
    pt_Data  = 4, //ru Данные
};

//ru Типы данных
enum DataTypes {
    data_null    = 0,
    data_int     = 1,
    data_str     = 2,
    data_data    = 3,
    data_combo   = 4,
    data_list    = 5,
    data_icon    = 6,
    data_real    = 7,
    data_color   = 8,
    data_script  = 9,
    data_stream  = 10,
    data_bitmap  = 11,
    data_wave    = 12,
    data_array   = 13,
    data_comboEx = 14,
    data_font    = 15,
    data_matr    = 16,
    data_jpeg    = 17,
    data_menu    = 18,
    data_code    = 19,
    data_element = 20,
    data_flags   = 21,
};

//ru Классы элемента (elGetClassIndex)
enum ElementClasses {
    CI_DPElement    = 1,
    CI_MultiElement = 2,
    CI_EditMulti    = 3,
    CI_EditMultiEx  = 4,
    CI_InlineCode   = 5,
    CI_DrawElement  = 6,
    CI_AS_Special   = 7,
    CI_DPLElement   = 8,
    CI_UseHiDLL     = 9,
    CI_WinElement   = 10,
    CI_PointHint    = 11,
    CI_PointElement = 12,
    CI_LineBreak    = 13,
    CI_LineBreakEx  = 14,
    CI_UserElement  = 15,
};

//ru Индексы параметров среды
//TODO Что за индексы параметов среды? Дополнить описание.
enum ParamsIde {
    PARAM_CODE_PATH         = 0,
    PARAM_DEBUG_MODE        = 1,
    PARAM_DEBUG_SERVER_PORT = 2,
    PARAM_DEBUG_CLIENT_PORT = 3,
    PARAM_PROJECT_PATH      = 4,
    PARAM_HIASM_VERSION     = 5,
    PARAM_USER_NAME         = 6,
    PARAM_USER_MAIL         = 7,
    PARAM_PROJECT_NAME      = 8,
    PARAM_SDE_WIDTH         = 9,
    PARAM_SDE_HEIGHT        = 10,
    PARAM_COMPILER          = 11,
};

//ru Ошибки при работе с библиотекой кодогенератора
enum CgResult {
    //ru Успешное завершение
    CG_SUCCESS          = 0,  
    
    //ru Кодогенератор не найден
    //TODO Что будет, если вернуть ?)
    CG_NOT_FOUND        = 1,  
    
    //ru Используемая версия среды не поддерживается
    CG_INVALID_VERSION  = 2,  
    
    //ru Точка входа в кодогенератор не найдена
    //TODO И этот статус тоже проверить.
    CG_ENTRY_POINT_NF   = 3,  // точка входа в кодогенератор не найдена
    
    //ru Файл модуля кода не найден
    //TODO Модуля кода? Тоже проверить.
    CG_MODULE_FILE_NF   = 4,  
    
    //ru Общая ошибка при сборке проекта
    CG_BUILD_FAILED     = 10, 
    
    //ru Результат компиляции не найден
    CG_APP_NOT_FOUND    = 20, 
};

//ru Параметры проекта
enum ParamsProject {
    //ru Поддерживает сжатие
    //TODO Подробнее изучить этот параметр и дополнить описание.
    CGMP_COMPRESSED = 0x01,
    
    //ru Поддерживает запуск из среды
    CGMP_RUN        = 0x02, 
    
    //ru Поддерживает запуск из среды в отладочном режиме
    CGMP_RUN_DEBUG  = 0x04, 
    
    //ru Поддерживает внешний редактор форм
    CGMP_FORM_EDIT  = 0x08, 
};

//ru Типы, используемые в интерфейсе
typedef void* id_sdk;
typedef void* id_element;
typedef void* id_point;
typedef void* id_prop;
typedef void* id_array;
typedef void* id_data;
typedef void* id_font;
typedef void* id_proplist;

struct TCodeGenTools;

typedef TCodeGenTools *PCodeGenTools;

//!ru Структуры кодогенератора и интерфейсы точки входа
//!en CodeGen types and entry point interfaces
//TODO Составить описание для данных структур.

typedef struct{
    short int major;
    short int minor;
    short int build;
} THiAsmVersion;

typedef struct {
	// none
} TBuildPrepareRec;

typedef struct {
	PCodeGenTools cgt;
	id_sdk sdk;
	void *result;
} TBuildProcessRec;

typedef struct {
	void *result;
	char *prjFilename;
	char *compiler;
} TBuildMakePrjRec;

typedef struct {
	char *prjFilename;
	char *appFilename;
} TBuildCompliteRec;

typedef struct {
	int flags;
} TBuildParams;

typedef struct {
	char *FileName;
	int Mode;
	int ServerPort;
	int ClientPort;
	void *data;
} TBuildRunRec;

//!ru Дополнительные структуры
//TODO Выяснить, для чего эти структуры нужны.

typedef struct {
    //ru Имя текущего элемента
	char *elName;
    
    //ru Имя объекта
	char *objName;
    
    //ru Список методов и полей для вставки в редактор
	char *inst_list;
    
    //ru Список, отображаемый во всплывающей подсказке
	char *disp_list; 
} TSynParams;

typedef struct {
	id_point point;
	id_sdk sdk;
	PCodeGenTools cgt;
	char *hint;
} THintParams;

struct TCodeGenTools {
    #define call __stdcall
    
    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает общее количество элементов в схеме
    call int (*sdkGetCount)(id_sdk SDK);
    
    //ru Возвращает идентификатор элемента по его Z-координате(индексу)
    call id_element (*sdkGetElement)(id_sdk SDK, int Index);
    
    //ru Возвращает идентификатор элемента по имени его класса
    call id_element (*sdkGetElementName)(id_sdk SDK, char *Name);
    
    //ru Возвращает элемент родитель для данного SDK
    call id_element (*sdkGetParent)(id_sdk SDK);
    
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает флаги элемента по его идентификатору
    call ElementFlgs (*elGetFlag)(id_element e);
    
    //ru Возвращает кол-во св-в элемента
    call int (*elGetPropCount)(id_element e);
    
    //ru Возвращает целую структуру для конкретного св-ва с порядковым номером из INI
    call id_prop (*elGetProperty)(id_element e, int Index);
    
    //ru Возвращает True, если значение св-ва совпадает с заданным в INI файле, иначе False
    call bool (*elIsDefProp)(id_element e, int Index);
    
    //ru Присваиваем элементу уникальное имя
    call id_element (*elSetCodeName)(id_element e, char *Name);
    
    //ru Получаем уникальное имя элемента
    call char* (*elGetCodeName)(id_element e);
    
    //ru Получаем имя класса элемента
    call char* (*elGetClassName)(id_element e);
    
    //ru Просто содержимое поля Sub из INI-файла элемента
    //TODO Выяснить, что за "просто содержимое" поля Sub и дополнить описание.
    call char* (*elGetInfSub)(id_element e);
    
    //ru Получаем количество точек у элемента
    //TODO Общее к-во точек? Дополнить описание.
    call int (*elGetPtCount)(id_element e);
    
    //ru Получаем идентификатор точки по её индексу
    call id_point (*elGetPt)(id_element e, int i);
    
    //ru Получаем идентификатор точки по её имени
    call id_point (*elGetPtName)(id_element e, const char *Name);
    
    //ru Получаем подкласс элемента
    call ElementClasses (*elGetClassIndex)(id_element e);
    
    //ru Получаем идент внутренней схемы для контейнеров и идентификатор родителя(id_element)
    //ru для редактора контейнера
    call id_sdk (*elGetSDK)(id_element e);
    
    //ru Возвращает SDK полиморфного контейнера по его индексу
    call id_sdk (*elGetSDKByIndex)(id_element e, int index);
    
    //ru Возвращает количаство сабклассов полиморфного контейнера
    call int (*elGetSDKCount)(id_element e);
    
    //ru Возвращает имя контейнера?
    //TODO Выяснить, точно ли данная функция возвращает имя текущего(?) контейнера.
    call char* (*elGetSDKName)(id_element e, int index);
    
    //ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются
    call bool (*elLinkIs)(id_element e);
    
    //ru Возвращает идент главного элемента(тот, на который ссылаются другие)
    call id_element (*elLinkMain)(id_element e);
    
    //ru Помещаем в переменные "X" и "Y", позицию элемента в редакторе схем
    call void (*elGetPos)(id_element e, int &X, int &Y);
    
    //ru Помещаем в переменные "W" и "H", размеры элемента в редакторе схем
    call void (*elGetSize)(id_element e, int &W, int &H);
    
    //??
    //TODO Что возвращает данная функция? Дополнить описание.
    call int (*elGetEID)(id_element e);
    
    //ru Возвращает идентификатор родителя
    call id_sdk (*elGetParent)(id_element e);

    //TODO Пользовательские данные? Выяснить и дополнить описание.
    //ru Устанавливает пользовательские данные элемента
    call void (*elSetData)(id_element e, void *data);
    
    //ru Возвращает интерфейсы, предоставляемые элементом
    call char* (*elGetInterface)(id_element e);
    
    //ru Возвращает классы, от которых наследуется элемент
    call char* (*elGetInherit)(id_element e);
    
    //ru Возвращает ID группы, к которой принадлежит элемент и 0, если группа отсутствует
    call int (*elGetGroup)(id_element e);
    
    //ru Возвращает количество элементов в списке св-тв(из панели св-ва)
    call int (*elGetPropertyListCount)(id_element e);
    
    //ru Возвращает элемент списка св-тв (PropertyList)
    call id_proplist (*elGetPropertyListItem)(id_element e, int i);    
    
    
    //!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает имя св-ва
    call char* (*plGetName)(id_proplist p);
    
    //ru Возвращает описание св-ва
    call char* (*plGetInfo)(id_proplist p);
    
    //ru Возвращает группу св-ва
    call char* (*plGetGroup)(id_proplist p);
    
    //ru Возвращает значение св-ва
    call id_prop (*plGetProperty)(id_proplist p);
    
    //ru Возвращает родительский элемент даного св-ва
    call id_element (*plGetOwner)(id_proplist p);    
    
    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента? ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип параметра
    call int (*propGetType)(id_prop prop);
    
    //ru Возвращает имя параметра
    call char* (*propGetName)(id_prop prop);
    
    //ru Возвращает значение параметра
    call void* (*propGetValue)(id_prop prop);
    
    //TODO propTo функции, возвращают свойство в указанном типе? Дополнить описание.
    
    //ru ???
    call unsigned char (*propToByte)(id_prop prop);
    
    //ru ???
    call int (*propToInteger)(id_prop prop);
    
    //ru ???
    call float (*propToReal)(id_prop prop);
    
    //ru ???
    call char* (*propToString)(id_prop prop);
    
    //ru Возвращает идентификатор элемента, прилинкованного к указанному св-ву
    //TODO Как это? Выяснить и дополнить описание.
    call id_element (*propGetLinkedElement)(id_element e, const char *propName);
    
    //ru Возвращает 1 если св-во помечено на перевод
    //TODO Выяснить, где в среде можно помечать свойства на перевод.
    call int (*propIsTranslate)(id_element e, id_prop p);
    
    //ru ???
    //TODO Выяснить, для чего предназначена данная функция.
    call id_element (*propGetLinkedElementInfo)(id_element e, id_prop prop, const char *_int);  

    //ru ???
    //TODO Выяснить, для чего предназначена данная функция.
    call int (*propSaveToFile)(id_prop p, const char *fileName);
    
    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает идентификатор точки, с которой соеденена данная
    call id_point (*ptGetLinkPoint)(id_point p);
    
    //ru Возвращает идентификатор точки, с которой соеденена данная точка,
    //ru без учета точек разрыва и хабов
    call id_point (*ptGetRLinkPoint)(id_point p);
    
    //ru Возвращает тип точек(константы pt_XXX)
    call PointsTypes (*ptGetType)(id_point p);
    
    //ru Возвращает имя точки
    call char* (*ptGetName)(id_point p);
    
    //ru Возвращает идентификатор элемента, которому принадлежит точка
    call id_element (*ptGetParent)(id_point p);
    
    //ru Возвращает относительный индекс точки по принадлежности к одной из 4х групп
    //TODO Выяснить, что представлять из себя "относительный индекс точки" и дополнить описание.
    call int (*ptGetIndex)(id_point p);
    
    //ru Возвращает базовую часть имени динамических точек(для CI_DPElement)
    call char* (*pt_dpeGetName)(id_point p);
    
    //TODO Пользовательские данные? Выяснить и дополнить описание.
    //ru Получает пользовательские данные элемента
    call void* (*elGetData)(id_element e);
    
    //TODO Нужно выяснить, какие типы данных возвращаются и реализовать enum, или использовать существующий.
    //ru Возвращает тип данных точки
    call int (*ptGetDataType)(id_point p);
    
    //ru Возвращает описание точки
    call char* (*ptGetInfo)(id_point p);
    
    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //TODO Что возвращается данными функциями? Выяснить и дополнить описание.
    
    //ru Добавляет имя файла в общий список временных файлов для последующего удаления
    call int (*resAddFile)(const char *Name);
    
    //ru Добавляет иконку в ресурсы и в список временных файлов
    call char* (*resAddIcon)(id_prop p);
    
    //ru Добавляет строку в ресурсы и в список временных файлов
    call char* (*resAddStr)(const char *p);
    
    //ru Добавляет поток в ресурсы и в список временных файлов
    call char* (*resAddStream)(id_prop p);
    
    //ru Добавляет звук в ресурсы и в список временных файлов
    call char* (*resAddWave)(id_prop p);
    
    //ru Добавляет картинку в ресурсы и в список временных файлов
    call char* (*resAddBitmap)(id_prop p);
    
    //ru Добавляет меню в ресурсы и в список временных файлов
    call char* (*resAddMenu)(id_prop p);
    
    //ru Возвращает 1 если список ресурсов пуст, и 0 в противном случае
    call int (*resEmpty)();
    
    //ru Устанавливает префикс для имен ресурсов
    call int (*resSetPref)(const char *pref);
    
    //!~~~~~~~~~~~~~~~~~~~~~~~~ массивы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает кол-во элементов в массиве а
    call int (*arrCount)(id_array a);
    
    //ru Возвращает тип элементов в массиве а
    call int (*arrType)(id_array a);
    
    //ru Возвращает имя элемента с индексом Index
    call char* (*arrItemName)(id_array a, int Index);
    
    //ru Возвращает значение элемента с индексом Index
    call void* (*arrItemData)(id_array a, int Index);
    
    //ru ???
    //TODO Выяснить предназначение данной функции.
    //p.s. Возможно, тут производится работа со свойствов... чего?
    call id_prop (*arrGetItem)(id_array a, int Index);
    
    //ru ???
    //TODO Выяснить предназначение данной функции.
    call bool (*isDebug)(id_sdk e);
    
    //!~~~~~~~~~~~~~~~~~~~~~~~~ данные ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //TODO Преобразование данные?
    //TODO Или просто возращаем в нужном типе?
    //TODO id_data? Где он берётся?
    
    call unsigned char (*dtType)(id_data d);
    call char* (*dtStr)(id_data d);
    call int (*dtInt)(id_data d);
    call double (*dtReal)(id_data d);
    
    //!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //TODO Возвращает название шрифта по идентификатору?
    //TODO id_font? Где он берётся?
    call char* (*fntName)(id_font f);
    call int (*fntSize)(id_font f);
    call unsigned char (*fntStyle)(id_font f);
    call int (*fntColor)(id_font f);
    call unsigned char (*fntCharSet)(id_font f);
    
    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //TODO Что возвращается данными функциями? Выяснить и дополнить описание.
    
    //ru Выводит строку Text в окно Отладка цветом Color
    call int (*_Debug)(const char *Text, int Color);
    
    //ru Добавляет информацию в панель ошибок
    call int (*_Error)(int line, id_element e, const char *text);    
    
    //!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //TODO Выяснить предназначение этой функции.
    //ru Возвращает значение параметра среды по его индексу
    call int (*GetParam)(short int index, void *value);
    
    //TODO Что за "MSDK"? Стоит порыться в исходниках HiAsm 5, может оттуда.
#ifdef MSDK
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru ???
    call id_prop (*elGetPropertyName)(id_element e, const char *name);
    
    //ru ???
    call bool (*elIsDefProperty)(id_element e, id_prop p);
#endif

    //!~~~~~~~~~~~~~~~~~~~~~~~~~ пользовательские ф-ции ~~~~~~~~~~~~~~~~~~~~~~~~~
	//ru ???
	int ReadIntParam(int Index) {
		int i = 0;
		GetParam(Index, &i);
		return i;
	}
    
    //ru ???
	char *ReadStrParam(int Index, id_element e = NULL) {
		char *c;
		c = new char[256];
		*((id_element*)c) = e;
		GetParam(Index, c);
		return c;
	}

	//!------------------------- DEBUG TOOLS ----------------------
    
	id_point getPointByType(id_element e, int type, int index) {
		int c = 0;
		for(int i = 0; i < elGetPtCount(e); i++) {
			id_point point = elGetPt(e, i);
			if(ptGetType(point) == type) {
				if(c == index)
					return point;
				c++;
			}
		}
		return NULL;
	}

	id_prop getPropByName(id_element e, const char *name) {
#ifdef MSDK
		return elGetPropertyName(e, name);
#else
		for(int i = 0; i < elGetPropCount(e); i++) {
			id_prop p = elGetProperty(e, i);
			if(strcasecmp(name, propGetName(p)) == 0)
				return p;
		}
		return NULL;
#endif
	}

	bool isDefProp(id_element e, id_prop p) {
#ifdef MSDK
		return elIsDefProperty(e, p);
#else
		for(int i = 0; i < elGetPropCount(e); i++) {
			if(elGetProperty(e, i) == p) {
				if(propGetType(p) == data_array) {
					if(arrCount((id_array)propGetValue(p)))
						return false;
					else
						return true;
				}
				return elIsDefProp(e, i);
			}
		}
		return false;
#endif
	}
};

#endif
