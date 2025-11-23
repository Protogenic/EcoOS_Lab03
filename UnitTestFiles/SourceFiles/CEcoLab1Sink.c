/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1Sink
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1Sink
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CEcoLab1Sink.h"
#include "IEcoConnectionPointContainer.h"

#include <stdio.h>

static const char_t* combTypeToString(ECO_COMB_SORT_TYPE typeId) {
    switch (typeId) {
    case ECO_COMB_SORT_INT32:
        return "int32";
    case ECO_COMB_SORT_LONG:
        return "long";
    case ECO_COMB_SORT_FLOAT:
        return "float";
    case ECO_COMB_SORT_DOUBLE:
        return "double";
    case ECO_COMB_SORT_LONG_DOUBLE:
        return "long double";
    default:
        return "unknown";
    }
}

static void printArrayPreview(const void* pArray, int32_t size, ECO_COMB_SORT_TYPE typeId) {
    int32_t limit = size < 10 ? size : 10;
    int32_t i = 0;

    printf("Sorted preview: ");
    for (i = 0; i < limit; ++i) {
        switch (typeId) {
        case ECO_COMB_SORT_INT32:
            printf("%d ", ((const int32_t*)pArray)[i]);
            break;
        case ECO_COMB_SORT_LONG:
            printf("%ld ", ((const long*)pArray)[i]);
            break;
        case ECO_COMB_SORT_FLOAT:
            printf("%.3f ", ((const float*)pArray)[i]);
            break;
        case ECO_COMB_SORT_DOUBLE:
            printf("%.3f ", ((const double*)pArray)[i]);
            break;
        case ECO_COMB_SORT_LONG_DOUBLE:
            printf("%.3Lf ", ((const long double*)pArray)[i]);
            break;
        default:
            printf("? ");
            break;
        }
    }
    if (size > limit) {
        printf("...");
    }
    printf("\n");
}

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink_QueryInterface(/* in */ struct IEcoLab1Events* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoLab1Events ) ) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    }

    *ppv = 0;

    return -1;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1Sink_AddRef(/* in */ struct IEcoLab1Events* me) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;

    if (me == 0 ) {
        return -1;
    }

    pCMe->m_cRef++;
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1Sink_Release(/* in */ struct IEcoLab1Events* me) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;

    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1Sink((IEcoLab1Events*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

int16_t ECOCALLMETHOD CEcoLab1Sink_OnCombSortCall(/* in */ struct IEcoLab1Events* me,
                                                    /* in */ int32_t gap,
                                                    /* in */ uint32_t pass,
                                                    /* in */ ECO_COMB_SORT_TYPE typeId) {
    if (me == 0) {
        return -1;
    }

    printf("[Comb:%s] pass=%u gap=%d\n", combTypeToString(typeId), pass, gap);

    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1Sink_OnCombSortSwap(/* in */ struct IEcoLab1Events* me,
                                                   /* in */ int32_t indexSrc,
                                                   /* in */ int32_t indexDst,
                                                   /* in */ ECO_COMB_SORT_TYPE typeId) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)me;

    if (me == 0) {
        return -1;
    }

    pCMe->m_iStep++;
    printf("Step %u [%s]: swap %d <-> %d\n", pCMe->m_iStep, combTypeToString(typeId), indexSrc, indexDst);

    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1Sink_OnCombSortCompleted(/* in */ struct IEcoLab1Events* me,
                                                         /* in */ const void* pArray,
                                                         /* in */ int32_t size,
                                                         /* in */ ECO_COMB_SORT_TYPE typeId) {
    if (me == 0 || pArray == 0) {
        return -1;
    }

    printf("[Comb:%s] completed. Total elements: %d\n", combTypeToString(typeId), size);
    printArrayPreview(pArray, size, typeId);
    printf("\n");

    return 0;
}


/*
 *
 * <сводка>
 *   Функция Advise
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink_Advise(/* in */ struct CEcoLab1Sink* me, /* in */IEcoLab1 *pIEcoLab1) {
    IEcoConnectionPointContainer* pCPC = 0;
    IEcoConnectionPoint* pCP = 0;
    int16_t result = 0;

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void**)&pCPC);

    if (result == 0 && pCPC != 0) {
        result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab1Events, &pCP);
        pCPC->pVTbl->Release(pCPC);
        pCPC = 0;
        if (result == 0 && pCP != 0) {

            result = pCP->pVTbl->Advise(pCP, (IEcoUnknown*)me, &me->m_cCookie);
            pCP->pVTbl->Release(pCP);
            pCP = 0;
        }
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция Unadvise
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink_Unadvise(/* in */ struct CEcoLab1Sink* me, /* in */IEcoLab1 *pIEcoLab1) {
    IEcoConnectionPointContainer* pCPC = 0;
    IEcoConnectionPoint * pCP = 0;
    int16_t result = 0;

    if (me->m_cCookie) {
        result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void**)&pCPC);
        if (result == 0) {
            result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab1Events, &pCP);
            pCPC->pVTbl->Release(pCPC);
            pCPC = 0;
            if (result == 0) {
                result = pCP->pVTbl->Unadvise(pCP, me->m_cCookie);
                pCP->pVTbl->Release(pCP);
                pCP = 0;
            }
        }
    }
    return result;
}

/* Create Virtual Table IEcoLab1VTblEvents */
IEcoLab1VTblEvents g_x2D2E3B9214F248A6A09ECB494B59C795VTblEvents = {
    CEcoLab1Sink_QueryInterface,
    CEcoLab1Sink_AddRef,
    CEcoLab1Sink_Release,
    CEcoLab1Sink_OnCombSortCall,
    CEcoLab1Sink_OnCombSortSwap,
    CEcoLab1Sink_OnCombSortCompleted
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
int16_t ECOCALLMETHOD createCEcoLab1Sink(/* in */ IEcoMemoryAllocator1* pIMem, /* out */ IEcoLab1Events** ppIEcoLab1Events) {
    int16_t result = -1;
    CEcoLab1Sink* pCMe = 0;

    /* Проверка указателей */
    if (ppIEcoLab1Events == 0 || pIMem == 0 ) {
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1Sink*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1Sink));

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;
    pCMe->m_pIMem->pVTbl->AddRef(pCMe->m_pIMem);

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;
    pCMe->m_cCookie = 0;
    pCMe->m_iStep = 0;

    /* Создание таблицы функций интерфейса IEcoP2PEvents */
    pCMe->m_pVTblIEcoLab1Events = &g_x2D2E3B9214F248A6A09ECB494B59C795VTblEvents;

    *ppIEcoLab1Events = (IEcoLab1Events*)pCMe;

    return 0;
};

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
void ECOCALLMETHOD deleteCEcoLab1Sink(IEcoLab1Events* pIEcoLab1Events) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*)pIEcoLab1Events;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1Events != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
};
