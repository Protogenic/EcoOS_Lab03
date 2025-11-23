/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1.h"
#include "CEcoLab1EnumConnectionPoints.h"
#include "CEcoLab1EnumConnections.h"
#include "IEcoConnectionPointContainer.h"
#include "IEcoConnectionPoint.h"

#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab1
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_QueryInterface(/* in */ IEcoLab1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoConnectionPointContainer)) {
        *ppv = &pCMe->m_pVTblICPC;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    } 
	else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX) && pCMe->m_pInnerUnknown != 0) {
        return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
    } 
	else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorX;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    } 
	else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorY;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    } 
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_Release(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

static int16_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorX_QueryInterface(/* in */ struct IEcoCalculatorX* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoLab1*) * 2);

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if (IsEqualUGUID(riid, &IID_IEcoLab1)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    } 
    else if (IsEqualUGUID(riid, &IID_IEcoConnectionPointContainer)) {
        *ppv = &pCMe->m_pVTblICPC;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    }
	else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    } 
	else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX) && pCMe->m_pInnerUnknown != 0) {
        return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
    } 
	else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorX;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    } 
	else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorY;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    } else {
        *ppv = 0;
        return -1;
    }
    return 0;
}



/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
static uint32_t CEcoLab1_IEcoCalculatorX_AddRef(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoLab1*) * 2);

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoCalculatorY
 * </описание>
 *
 */
static uint32_t CEcoLab1_IEcoCalculatorX_Release(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoLab1*) * 2);

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0) {
        deleteCEcoLab1((IEcoLab1*) pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция Addition
 * </сводка>
 *
 * <описание>
 *   Функция сложения
 * </описание>
 *
 */
static int32_t ECOCALLMETHOD CEcoLab1_Addition(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoLab1*) * 2);

    /* Проверка указателей */
    if (me == 0 || pCMe->m_pIEcoCalculatorX == 0) {
        return -1;
    }

    return pCMe->m_pIEcoCalculatorX->pVTbl->Addition(pCMe->m_pIEcoCalculatorX, a, b);
}


/*
 *
 * <сводка>
 *   Функция Subtraction
 * </сводка>
 *
 * <описание>
 *   Функция вычитания
 * </описание>
 *
 */
static int16_t CEcoLab1_Subtraction(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoLab1*) * 2);

    /* Проверка указателей */
    if (me == 0 || pCMe->m_pIEcoCalculatorX == 0) {
        return -1;
    }

    return pCMe->m_pIEcoCalculatorX->pVTbl->Subtraction(pCMe->m_pIEcoCalculatorX, a, b);
}


static int16_t CEcoLab1_IEcoCalculatorY_QueryInterface(/* in */ struct IEcoCalculatorY* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoLab1*) * 3);

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if (IsEqualUGUID(riid, &IID_IEcoLab1)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    } 
    else if (IsEqualUGUID(riid, &IID_IEcoConnectionPointContainer)) {
        *ppv = &pCMe->m_pVTblICPC;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    } 
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX) && pCMe->m_pInnerUnknown != 0) {
        return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
    } 
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorX;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    } else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorY;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*) pCMe);
    } else {
        *ppv = 0;
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoCalculatorY
 * </описание>
 *
 */
static uint32_t CEcoLab1_IEcoCalculatorY_AddRef(/* in */ struct IEcoCalculatorY* me) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoLab1*) * 3);

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoCalculatorY
 * </описание>
 *
 */
static uint32_t CEcoLab1_IEcoCalculatorY_Release(/* in */ struct IEcoCalculatorY* me) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoLab1*) * 3);

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0) {
        deleteCEcoLab1((IEcoLab1*) pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

static int16_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_QueryInterface(/* in */ struct IEcoConnectionPointContainer* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoUnknown*));

    if (me == 0 || ppv == 0) {
        return -1;
    }

    if (IsEqualUGUID(riid, &IID_IEcoLab1)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoConnectionPointContainer)) {
        *ppv = &pCMe->m_pVTblICPC;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX) && pCMe->m_pInnerUnknown != 0) {
        return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorX;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorY;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }

    return 0;
}

static uint32_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_AddRef(/* in */ struct IEcoConnectionPointContainer* me) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoUnknown*));

    if (me == 0) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_Release(/* in */ struct IEcoConnectionPointContainer* me) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoUnknown*));

    if (me == 0) {
        return -1;
    }

    --pCMe->m_cRef;

    if (pCMe->m_cRef == 0) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }

    return pCMe->m_cRef;
}

static int16_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_EnumConnectionPoints(/* in */ struct IEcoConnectionPointContainer* me, /* out */ struct IEcoEnumConnectionPoints** ppEnum) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoUnknown*));
    int16_t result = 0;

    if (me == 0 || ppEnum == 0) {
        return -1;
    }

    if (pCMe->m_pISinkCP == 0) {
        *ppEnum = 0;
        return -1;
    }

    result = createCEcoLab1EnumConnectionPoints((IEcoUnknown*)pCMe->m_pISys, (IEcoConnectionPoint*)pCMe->m_pISinkCP, ppEnum);
    return result;
}

static int16_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_FindConnectionPoint(/* in */ struct IEcoConnectionPointContainer* me, /* in */ const UGUID* riid, /* out */ struct IEcoConnectionPoint** ppCP) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoUnknown*));

    if (me == 0 || ppCP == 0 || riid == 0) {
        return -1;
    }

    if (!IsEqualUGUID(riid, &IID_IEcoLab1Events) || pCMe->m_pISinkCP == 0) {
        *ppCP = 0;
        return -1;
    }

    ((IEcoConnectionPoint*)pCMe->m_pISinkCP)->pVTbl->AddRef((IEcoConnectionPoint*)pCMe->m_pISinkCP);
    *ppCP = (IEcoConnectionPoint*)pCMe->m_pISinkCP;

    return 0;
}


/*
 *
 * <сводка>
 *   Функция Multiplication
 * </сводка>
 *
 * <описание>
 *   Функция умножения
 * </описание>
 *
 */
static int32_t CEcoLab1_Multiplication(/* in */ struct IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoLab1*) * 3);

    /* Проверка указателей */
    if (me == 0 || pCMe->m_pIEcoCalculatorY == 0) {
        return -1;
    }

    return pCMe->m_pIEcoCalculatorY->pVTbl->Multiplication(pCMe->m_pIEcoCalculatorY, a, b);
}


/*
 *
 * <сводка>
 *   Функция Division
 * </сводка>
 *
 * <описание>
 *   Функция деления
 * </описание>
 *
 */
static int16_t CEcoLab1_Division(/* in */ struct IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*) ((uint64_t) me - sizeof(struct IEcoLab1*) * 3);

    /* Проверка указателей */
    if (me == 0 || pCMe->m_pIEcoCalculatorY == 0) {
        return -1;
    }

    return pCMe->m_pIEcoCalculatorY->pVTbl->Division(pCMe->m_pIEcoCalculatorY, a, b);
}

static int16_t CEcoLab1_Fire_OnCombSortCall(/* in */ IEcoLab1Ptr_t me,
                                             /* in */ int32_t gap,
                                             /* in */ uint32_t pass,
                                             /* in */ ECO_COMB_SORT_TYPE typeId) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    int16_t result = 0;
    IEcoEnumConnections* pEnum = 0;
    IEcoLab1Events* pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0 || pCMe->m_pISinkCP == 0) {
        return 0;
    }

    result = ((IEcoConnectionPoint*)pCMe->m_pISinkCP)->pVTbl->EnumConnections((IEcoConnectionPoint*)pCMe->m_pISinkCP, &pEnum);
    if ((result == 0) && (pEnum != 0)) {
        while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
            result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void**)&pIEvents);
            if ((result == 0) && (pIEvents != 0)) {
                pIEvents->pVTbl->OnCombSortCall(pIEvents, gap, pass, typeId);
                pIEvents->pVTbl->Release(pIEvents);
            }
            cd.pUnk->pVTbl->Release(cd.pUnk);
        }
        pEnum->pVTbl->Release(pEnum);
    }

    return result;
}

static int16_t CEcoLab1_Fire_OnCombSortSwap(/* in */ IEcoLab1Ptr_t me,
                                             /* in */ int32_t indexSrc,
                                             /* in */ int32_t indexDst,
                                             /* in */ ECO_COMB_SORT_TYPE typeId) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    int16_t result = 0;
    IEcoEnumConnections* pEnum = 0;
    IEcoLab1Events* pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0 || pCMe->m_pISinkCP == 0) {
        return 0;
    }

    result = ((IEcoConnectionPoint*)pCMe->m_pISinkCP)->pVTbl->EnumConnections((IEcoConnectionPoint*)pCMe->m_pISinkCP, &pEnum);
    if ((result == 0) && (pEnum != 0)) {
        while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
            result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void**)&pIEvents);
            if ((result == 0) && (pIEvents != 0)) {
                pIEvents->pVTbl->OnCombSortSwap(pIEvents, indexSrc, indexDst, typeId);
                pIEvents->pVTbl->Release(pIEvents);
            }
            cd.pUnk->pVTbl->Release(cd.pUnk);
        }
        pEnum->pVTbl->Release(pEnum);
    }

    return result;
}

static int16_t CEcoLab1_Fire_OnCombSortCompleted(/* in */ IEcoLab1Ptr_t me,
                                                  /* in */ const void* pArray,
                                                  /* in */ int32_t size,
                                                  /* in */ ECO_COMB_SORT_TYPE typeId) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    int16_t result = 0;
    IEcoEnumConnections* pEnum = 0;
    IEcoLab1Events* pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0 || pCMe->m_pISinkCP == 0) {
        return 0;
    }

    result = ((IEcoConnectionPoint*)pCMe->m_pISinkCP)->pVTbl->EnumConnections((IEcoConnectionPoint*)pCMe->m_pISinkCP, &pEnum);
    if ((result == 0) && (pEnum != 0)) {
        while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
            result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void**)&pIEvents);
            if ((result == 0) && (pIEvents != 0)) {
                pIEvents->pVTbl->OnCombSortCompleted(pIEvents, pArray, size, typeId);
                pIEvents->pVTbl->Release(pIEvents);
            }
            cd.pUnk->pVTbl->Release(cd.pUnk);
        }
        pEnum->pVTbl->Release(pEnum);
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ struct IEcoLab1* me, /* in */ struct IEcoUnknown* pIUnkSystem) {
    CEcoLab1* pCMe = (CEcoLab1*) me;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoUnknown* pOuterUnknown = (IEcoUnknown*) me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*) pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void**) &pIBus);

    /* Проверка указателей */
    if (me == 0) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*) pIUnkSystem;

	/* Создание точки подключения */
    result = createCEcoLab1ConnectionPoint((IEcoUnknown*)pCMe->m_pISys,
                                           (IEcoConnectionPointContainer*)&pCMe->m_pVTblICPC,
                                           &IID_IEcoLab1Events,
                                           (IEcoConnectionPoint**)&pCMe->m_pISinkCP);
    if (result != 0 || pCMe->m_pISinkCP == 0) {
        goto release;
    }

	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIEcoCalculatorY);
    if (result != 0 || pCMe->m_pIEcoCalculatorY == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIEcoCalculatorY);
    }
    if (result != 0) {
        goto release;
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, pOuterUnknown, &IID_IEcoUnknown, (void**) &pCMe->m_pInnerUnknown);
    if (result != 0 || pCMe->m_pInnerUnknown == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIEcoCalculatorX);
    }

release:
	/* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*) pIUnkSystem;
    /* Освобождение */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Initialization should not fail just because optional calculators are absent */
    return 0;
}


/*
 * Вспомогательные функции для Comb sort
 */
static void combSortHelperInt(CEcoLab1* pCMe, int* arr, int size) {
    int gap = size;
    int swapped = 1;
    int i;
    uint32_t pass = 0;
    
    while (gap > 1 || swapped) {
        /* Уменьшаем gap */
        gap = (gap * 10) / 13;
        if (gap < 1) {
            gap = 1;
        }
        
        swapped = 0;
        CEcoLab1_Fire_OnCombSortCall((IEcoLab1*)pCMe, gap, pass, ECO_COMB_SORT_INT32);
        
        for (i = 0; i < size - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                int temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = 1;
                CEcoLab1_Fire_OnCombSortSwap((IEcoLab1*)pCMe, i, i + gap, ECO_COMB_SORT_INT32);
            }
        }
        pass++;
    }
}

static void combSortHelperLong(CEcoLab1* pCMe, long* arr, int size) {
    int gap = size;
    int swapped = 1;
    int i;
    uint32_t pass = 0;
    
    while (gap > 1 || swapped) {
        /* Уменьшаем gap */
        gap = (gap * 10) / 13;
        if (gap < 1) {
            gap = 1;
        }
        
        swapped = 0;
        CEcoLab1_Fire_OnCombSortCall((IEcoLab1*)pCMe, gap, pass, ECO_COMB_SORT_LONG);
        
        for (i = 0; i < size - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                long temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = 1;
                CEcoLab1_Fire_OnCombSortSwap((IEcoLab1*)pCMe, i, i + gap, ECO_COMB_SORT_LONG);
            }
        }
        pass++;
    }
}

static void combSortHelperFloat(CEcoLab1* pCMe, float* arr, int size) {
    int gap = size;
    int swapped = 1;
    int i;
    uint32_t pass = 0;
    
    while (gap > 1 || swapped) {
        /* Уменьшаем gap */
        gap = (gap * 10) / 13;
        if (gap < 1) {
            gap = 1;
        }
        
        swapped = 0;
        CEcoLab1_Fire_OnCombSortCall((IEcoLab1*)pCMe, gap, pass, ECO_COMB_SORT_FLOAT);
        
        for (i = 0; i < size - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                float temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = 1;
                CEcoLab1_Fire_OnCombSortSwap((IEcoLab1*)pCMe, i, i + gap, ECO_COMB_SORT_FLOAT);
            }
        }
        pass++;
    }
}

static void combSortHelperDouble(CEcoLab1* pCMe, double* arr, int size) {
    int gap = size;
    int swapped = 1;
    int i;
    uint32_t pass = 0;
    
    while (gap > 1 || swapped) {
        /* Уменьшаем gap */
        gap = (gap * 10) / 13;
        if (gap < 1) {
            gap = 1;
        }
        
        swapped = 0;
        CEcoLab1_Fire_OnCombSortCall((IEcoLab1*)pCMe, gap, pass, ECO_COMB_SORT_DOUBLE);
        
        for (i = 0; i < size - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                double temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = 1;
                CEcoLab1_Fire_OnCombSortSwap((IEcoLab1*)pCMe, i, i + gap, ECO_COMB_SORT_DOUBLE);
            }
        }
        pass++;
    }
}

static void combSortHelperLongDouble(CEcoLab1* pCMe, long double* arr, int size) {
    int gap = size;
    int swapped = 1;
    int i;
    uint32_t pass = 0;
    
    while (gap > 1 || swapped) {
        /* Уменьшаем gap */
        gap = (gap * 10) / 13;
        if (gap < 1) {
            gap = 1;
        }
        
        swapped = 0;
        CEcoLab1_Fire_OnCombSortCall((IEcoLab1*)pCMe, gap, pass, ECO_COMB_SORT_LONG_DOUBLE);
        
        for (i = 0; i < size - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                long double temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = 1;
                CEcoLab1_Fire_OnCombSortSwap((IEcoLab1*)pCMe, i, i + gap, ECO_COMB_SORT_LONG_DOUBLE);
            }
        }
        pass++;
    }
}

/*
 *
 * <сводка>
 *   Функция combSortInt
 * </сводка>
 *
 * <описание>
 *   Функция сортирует массив целых чисел с помощью алгоритма Comb sort
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_combSortInt(/* in */ IEcoLab1Ptr_t me, /* in */ int* array, /* in */ int size) {
	CEcoLab1* pCMe = (CEcoLab1*)me;
    /* Проверка указателей */
    if (me == 0 || array == 0 || size <= 0) {
        return ERR_ECO_POINTER;
    }
    combSortHelperInt(pCMe, array, size);
    CEcoLab1_Fire_OnCombSortCompleted(me, array, size, ECO_COMB_SORT_INT32);

	return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция combSortLong
 * </сводка>
 *
 * <описание>
 *   Функция сортирует массив длинных целых чисел с помощью алгоритма Comb sort
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_combSortLong(/* in */ IEcoLab1Ptr_t me, /* in */ long* array, /* in */ int size) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    /* Проверка указателей */
    if (me == 0 || array == 0 || size <= 0) {
        return ERR_ECO_POINTER;
    }
    combSortHelperLong(pCMe, array, size);
    CEcoLab1_Fire_OnCombSortCompleted(me, array, size, ECO_COMB_SORT_LONG);

	return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция combSortFloat
 * </сводка>
 *
 * <описание>
 *   Функция сортирует массив чисел с плавающей точкой с помощью алгоритма Comb sort
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_combSortFloat(/* in */ IEcoLab1Ptr_t me, /* in */ float* array, /* in */ int size) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    /* Проверка указателей */
    if (me == 0 || array == 0 || size <= 0) {
       return ERR_ECO_POINTER;
    }
    combSortHelperFloat(pCMe, array, size);
    CEcoLab1_Fire_OnCombSortCompleted(me, array, size, ECO_COMB_SORT_FLOAT);

	return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция combSortDouble
 * </сводка>
 *
 * <описание>
 *   Функция сортирует массив чисел с плавающей точкой двойной точности с помощью алгоритма Comb sort
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_combSortDouble(/* in */ IEcoLab1Ptr_t me, /* in */ double* array, /* in */ int size) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    /* Проверка указателей */
    if (me == 0 || array == 0 || size <= 0) {
        return ERR_ECO_POINTER;
    }
    combSortHelperDouble(pCMe, array, size);
    CEcoLab1_Fire_OnCombSortCompleted(me, array, size, ECO_COMB_SORT_DOUBLE);

	return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция combSortLongDouble
 * </сводка>
 *
 * <описание>
 *   Функция сортирует массив чисел с плавающей точкой повышенной точности с помощью алгоритма Comb sort
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_combSortLongDouble(/* in */ IEcoLab1Ptr_t me, /* in */ long double* array, /* in */ int size) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    /* Проверка указателей */
    if (me == 0 || array == 0 || size <= 0) {
        return ERR_ECO_POINTER;
    }
    combSortHelperLongDouble(pCMe, array, size);
    CEcoLab1_Fire_OnCombSortCompleted(me, array, size, ECO_COMB_SORT_LONG_DOUBLE);

	return ERR_ECO_SUCCESES;
}


/* Create Virtual Table IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab1_QueryInterface,
    CEcoLab1_AddRef,
    CEcoLab1_Release,
	CEcoLab1_combSortInt,
	CEcoLab1_combSortLong,
	CEcoLab1_combSortFloat,
	CEcoLab1_combSortDouble,
	CEcoLab1_combSortLongDouble
};

/* Create Virtual Table IEcoConnectionPointContainer */
IEcoConnectionPointContainerVTbl g_x0000000500000000C000000000000046VTblCPC = {
    CEcoLab1_IEcoConnectionPointContainer_QueryInterface,
    CEcoLab1_IEcoConnectionPointContainer_AddRef,
    CEcoLab1_IEcoConnectionPointContainer_Release,
    CEcoLab1_IEcoConnectionPointContainer_EnumConnectionPoints,
    CEcoLab1_IEcoConnectionPointContainer_FindConnectionPoint
};

IEcoCalculatorXVTbl g_x9322111622484742AE0682819447843DVTblD = {
    CEcoLab1_IEcoCalculatorX_QueryInterface,
    CEcoLab1_IEcoCalculatorX_AddRef,
    CEcoLab1_IEcoCalculatorX_Release,
    CEcoLab1_Addition,
    CEcoLab1_Subtraction
};

IEcoCalculatorYVTbl g_xBD6414C29096423EA90C04D77AFD1CADVTblD = {
    CEcoLab1_IEcoCalculatorY_QueryInterface,
    CEcoLab1_IEcoCalculatorY_AddRef,
    CEcoLab1_IEcoCalculatorY_Release,
    CEcoLab1_Multiplication,
    CEcoLab1_Division
};
/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab1* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab1 */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;

    /* Создание таблицы функций интерфейса IEcoConnectionPointContainer */
    pCMe->m_pVTblICPC = &g_x0000000500000000C000000000000046VTblCPC;

	pCMe->m_pVTblIEcoCalculatorX = &g_x9322111622484742AE0682819447843DVTblD;
    pCMe->m_pVTblIEcoCalculatorY = &g_xBD6414C29096423EA90C04D77AFD1CADVTblD;
    /* Инициализация данных */
    pCMe->m_Name = 0;
    pCMe->m_pISinkCP = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab1 = (IEcoLab1*)pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1) {
    CEcoLab1* pCMe = (CEcoLab1*)pIEcoLab1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if (pCMe->m_pISinkCP != 0) {
            deleteCEcoLab1ConnectionPoint((IEcoConnectionPoint*)pCMe->m_pISinkCP);
            pCMe->m_pISinkCP = 0;
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
