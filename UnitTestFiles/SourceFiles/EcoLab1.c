/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"
#include "IEcoLab1Events.h"
#include "IEcoConnectionPointContainer.h"
#include "CEcoLab1Sink.h"
#include "IdEcoList1.h"

#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Генерация случайного int в диапазоне [min, max]
int rand_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Генерация случайного long в диапазоне [min, max]
long rand_long(long min, long max) {
    return min + rand() % (max - min + 1);
}

// Генерация случайного float в диапазоне [min, max]
float rand_float(float min, float max) {
    float scale = (float)rand() / (float)RAND_MAX;
    return min + scale * (max - min);
}

// Генерация случайного double в диапазоне [min, max]
double rand_double(double min, double max) {
    double scale = (double)rand() / (double)RAND_MAX;
    return min + scale * (max - min);
}

// Генерация случайного long double в диапазоне [min, max]
long double rand_long_double(long double min, long double max) {
    long double scale = (long double)rand() / (long double)RAND_MAX;
    return min + scale * (max - min);
}
/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;
	/* Указатель на интерфейс контейнера точек подключения */
    IEcoConnectionPointContainer* pICPC = 0;
    /* Указатель на интерфейс точки подключения */
    IEcoConnectionPoint* pICP = 0;
    /* Указатель на обратный интерфейс */
    IEcoLab1Events* pIEcoLab1Sink = 0;
    IEcoUnknown* pISinkUnk = 0;
    uint32_t cAdvise = 0;
	IEcoList1* pIList = 0;

	int32_t* testIntArray = 0;
	long* testLongArray = 0;
	float* testFloatArray = 0;
	double* testDoubleArray = 0;
	long double* testLongDoubleArray = 0;
	uint32_t printSize = 20;
	uint32_t smallSize = 100;
	uint32_t mediumSize = 500;
	uint32_t largeSize = 1000;
	uint32_t i = 0;

	clock_t begin;
    clock_t end;

	IEcoCalculatorX* pIEcoCalculatorX = 0;
    IEcoCalculatorY* pIEcoCalculatorY = 0;
    int16_t i32A = 36, i32B = 2;
    char_t c;

    srand(time(0));

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация компонента коллекций */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoList1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_53884AFC93C448ECAA929C8D3A562281);
    if (result != 0) {
        goto Release;
    }

	/* Регистрация компонента A */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorA, (IEcoUnknown*)GetIEcoComponentFactoryPtr_4828F6552E4540E78121EBD220DC360E);
    if (result != 0) {
        goto Release;
    }

    /* Регистрация компонента B */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorB, (IEcoUnknown*)GetIEcoComponentFactoryPtr_AE202E543CE54550899603BD70C62565);
    if (result != 0) {
        goto Release;
    }

    /* Регистрация компонента D */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorD, (IEcoUnknown*)GetIEcoComponentFactoryPtr_3A8E44677E82475CB4A3719ED8397E61);
    if (result != 0) {
        goto Release;
    }

    /* Регистрация компонента E */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorE, (IEcoUnknown*)GetIEcoComponentFactoryPtr_872FEF1DE3314B87AD44D1E7C232C2F0);
    if (result != 0) {
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

	result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**) &pIEcoCalculatorX);
    if (result != 0 || pIEcoCalculatorX == 0) {
        goto Release;
    }

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**) &pIEcoCalculatorY);
    if (result != 0 || pIEcoCalculatorY == 0) {
        goto Release;
    }

	///* Проверка поддержки подключений обратного интерфейса */
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void**) &pICPC);
    if (result != 0 || pICPC == 0) {
        goto Release;
    }

 //   /* Запрос на получения интерфейса точки подключения */
    result = pICPC->pVTbl->FindConnectionPoint(pICPC, &IID_IEcoLab1Events, &pICP);
    pICPC->pVTbl->Release(pICPC);
    pICPC = 0;
    if (result != 0 || pICP == 0) {
        goto Release;
    }

 //   /* Создание экземпляра обратного интерфейса */
    result = createCEcoLab1Sink(pIMem, (IEcoLab1Events**)&pIEcoLab1Sink);
    if (result != 0 || pIEcoLab1Sink == 0) {
        goto Release;
    }

    result = pIEcoLab1Sink->pVTbl->QueryInterface(pIEcoLab1Sink, &IID_IEcoUnknown, (void**)&pISinkUnk);
    if (result != 0 || pISinkUnk == 0) {
        goto Release;
    }

    result = pICP->pVTbl->Advise(pICP, pISinkUnk, &cAdvise);
    pISinkUnk->pVTbl->Release(pISinkUnk);
    pISinkUnk = 0;
    if (result != 0 || cAdvise == 0) {
        goto Release;
    }

    printf("\n========== Демонстрация работы Comb Sort ==========\n");
    {
        int demoArray[] = { 64, 34, 25, 12, 22, 11, 90, 5 };
        int demoSize = sizeof(demoArray) / sizeof(demoArray[0]);
        printf("Исходный массив: ");
        for (i = 0; i < demoSize; ++i) {
            printf("%d ", demoArray[i]);
        }
        printf("\n\nПроцесс сортировки:\n");
        pIEcoLab1->pVTbl->combSortInt(pIEcoLab1, demoArray, demoSize);
        printf("\nРезультат: ");
        for (i = 0; i < demoSize; ++i) {
            printf("%d ", demoArray[i]);
        }
        printf("\n================================================\n\n");
    }

    if (pICP != 0 && cAdvise != 0) {
        pICP->pVTbl->Unadvise(pICP, cAdvise);
        cAdvise = 0;
    }
    if (pIEcoLab1Sink != 0) {
        pIEcoLab1Sink->pVTbl->Release(pIEcoLab1Sink);
        pIEcoLab1Sink = 0;
    }
    if (pICP != 0) {
        pICP->pVTbl->Release(pICP);
        pICP = 0;
    }

	printf("A/B components tests:\n");
    printf("%d + %d = %d\n", i32A, i32B, pIEcoCalculatorX->pVTbl->Addition(pIEcoCalculatorX, i32A, i32B));
    printf("%d - %d = %d\n\n", i32A, i32B, pIEcoCalculatorX->pVTbl->Subtraction(pIEcoCalculatorX, i32A, i32B));

    printf("D/E components tests:\n");
    printf("%d * %d = %d\n", i32A, i32B, pIEcoCalculatorY->pVTbl->Multiplication(pIEcoCalculatorY, i32A, i32B));
    printf("%d / %d = %d\n\n", i32A, i32B, pIEcoCalculatorY->pVTbl->Division(pIEcoCalculatorY, i32A, i32B));

	pIEcoCalculatorX->pVTbl->Release(pIEcoCalculatorX);
    pIEcoCalculatorY->pVTbl->Release(pIEcoCalculatorY);

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIEcoCalculatorX);
    if (result == 0) {
        pIEcoCalculatorX->pVTbl->Release(pIEcoCalculatorX);
        printf("IEcoLab1 -> pIEcoCalculatorX [OK]\n");
    }
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIEcoCalculatorY);
    if (result == 0) {
        pIEcoCalculatorY->pVTbl->Release(pIEcoCalculatorY);
        printf("IEcoLab1 -> pIEcoCalculatorY [OK]\n");
    }
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoLab1, (void**)&pIEcoLab1);
    if (result == 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
        printf("IEcoLab1 -> IEcoLab1 [OK]\n");
    }
    result = pIEcoCalculatorX->pVTbl->QueryInterface(pIEcoCalculatorX, &IID_IEcoCalculatorY, (void**)&pIEcoCalculatorY);
    if (result == 0) {
        pIEcoCalculatorY->pVTbl->Release(pIEcoCalculatorY);
        printf("pIEcoCalculatorX -> pIEcoCalculatorY [OK]\n");
    }
    result = pIEcoCalculatorX->pVTbl->QueryInterface(pIEcoCalculatorX, &IID_IEcoLab1, (void**)&pIEcoLab1);
    if (result == 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
        printf("pIEcoCalculatorX -> IEcoLab1 [OK]\n");
    }
    result = pIEcoCalculatorX->pVTbl->QueryInterface(pIEcoCalculatorX, &IID_IEcoCalculatorX, (void**)&pIEcoCalculatorX);
    if (result == 0) {
        pIEcoCalculatorX->pVTbl->Release(pIEcoCalculatorX);
        printf("pIEcoCalculatorX -> pIEcoCalculatorX [OK]\n");
    }
    result = pIEcoCalculatorY->pVTbl->QueryInterface(pIEcoCalculatorY, &IID_IEcoCalculatorX, (void**)&pIEcoCalculatorX);
    if (result == 0) {
        pIEcoCalculatorX->pVTbl->Release(pIEcoCalculatorX);
        printf("pIEcoCalculatorY -> pIEcoCalculatorX [OK]\n");
    }
    result = pIEcoCalculatorY->pVTbl->QueryInterface(pIEcoCalculatorY, &IID_IEcoCalculatorY, (void**)&pIEcoCalculatorY);
    if (result == 0) {
        pIEcoCalculatorY->pVTbl->Release(pIEcoCalculatorY);
        printf("pIEcoCalculatorY -> pIEcoCalculatorY [OK]\n");
    }
    result = pIEcoCalculatorY->pVTbl->QueryInterface(pIEcoCalculatorY, &IID_IEcoLab1, (void**)&pIEcoLab1);
    if (result == 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
        printf("pIEcoCalculatorY -> IEcoLab1 [OK]\n");
    }

	printf("\n\n");
    printf("Next are sort tests. Wanna see? (y/n)\n");
    c = getchar();
    while (c != 'y') {
        switch (c) {
        case 'n':
            goto Release;
            break;
        default:
            printf("Next are sort tests. Wanna see? (y/n)\n");
            fflush(stdin);
            c = getchar();
            continue;
        }
    }
    printf("\n");

	printf("/// int32_t test ///\n");
	{
		{
			printf("Test #1: ");
			testIntArray = (int32_t*) pIMem->pVTbl->Alloc(pIMem, sizeof(int32_t) * smallSize);
			for (i = 0; i < smallSize; ++i) {
				testIntArray[i] = rand_int(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%i ", testIntArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortInt(pIEcoLab1, testIntArray, smallSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #1: ");
			for (i = 0; i < printSize; ++i) {
				printf("%i ", testIntArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testIntArray);

			printf("...\n\n");
		}

		{
			printf("Test #2: ");
			testIntArray = (int32_t*) pIMem->pVTbl->Alloc(pIMem, sizeof(int32_t) * mediumSize);
			for (i = 0; i < mediumSize; ++i) {
				testIntArray[i] = rand_int(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%i ", testIntArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortInt(pIEcoLab1, testIntArray, mediumSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #2: ");
			for (i = 0; i < printSize; ++i) {
				printf("%i ", testIntArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testIntArray);

			printf("...\n\n");
		}

		{
			printf("Test #3: ");
			testIntArray = (int32_t*) pIMem->pVTbl->Alloc(pIMem, sizeof(int32_t) * largeSize);
			for (i = 0; i < largeSize; ++i) {
				testIntArray[i] = rand_int(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%i ", testIntArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortInt(pIEcoLab1, testIntArray, largeSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #3: ");
			for (i = 0; i < printSize; ++i) {
				printf("%i ", testIntArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testIntArray);

			printf("...\n\n");
		}
	}


	printf("/// long test ///\n");
	{
		{
			printf("Test #1: ");
			testLongArray = (long*) pIMem->pVTbl->Alloc(pIMem, sizeof(long) * smallSize);
			for (i = 0; i < smallSize; ++i) {
				testLongArray[i] = rand_long(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%ld ", testLongArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortLong(pIEcoLab1, testLongArray, smallSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #1: ");
			for (i = 0; i < printSize; ++i) {
				printf("%ld ", testLongArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testLongArray);

			printf("...\n\n");
		}

		{
			printf("Test #2: ");
			testLongArray = (long*) pIMem->pVTbl->Alloc(pIMem, sizeof(long) * mediumSize);
			for (i = 0; i < mediumSize; ++i) {
				testLongArray[i] = rand_long(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%ld ", testLongArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortLong(pIEcoLab1, testLongArray, mediumSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #2: ");
			for (i = 0; i < printSize; ++i) {
				printf("%ld ", testLongArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testLongArray);

			printf("...\n\n");
		}

		{
			printf("Test #3: ");
			testLongArray = (long*) pIMem->pVTbl->Alloc(pIMem, sizeof(long) * largeSize);
			for (i = 0; i < largeSize; ++i) {
				testLongArray[i] = rand_long(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%ld ", testLongArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortLong(pIEcoLab1, testLongArray, largeSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #2: ");
			for (i = 0; i < printSize; ++i) {
				printf("%ld ", testLongArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testLongArray);

			printf("...\n\n");
		}
	}

	printf("/// float test ///\n");
	{
		{
			printf("Test #1: ");
			testFloatArray = (float*) pIMem->pVTbl->Alloc(pIMem, sizeof(float) * smallSize);
			for (i = 0; i < smallSize; ++i) {
				testFloatArray[i] = rand_float(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%.2f ", testFloatArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortFloat(pIEcoLab1, testFloatArray, smallSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #1: ");
			for (i = 0; i < printSize; ++i) {
				printf("%.2f ", testFloatArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testFloatArray);

			printf("...\n\n");
		}

		{
			printf("Test #2: ");
			testFloatArray = (float*) pIMem->pVTbl->Alloc(pIMem, sizeof(float) * mediumSize);
			for (i = 0; i < mediumSize; ++i) {
				testFloatArray[i] = rand_float(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%.2f ", testFloatArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortFloat(pIEcoLab1, testFloatArray, mediumSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #2: ");
			for (i = 0; i < printSize; ++i) {
				printf("%.2f ", testFloatArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testFloatArray);

			printf("...\n\n");
		}

		{
			printf("Test #3: ");
			testFloatArray = (float*) pIMem->pVTbl->Alloc(pIMem, sizeof(float) * largeSize);
			for (i = 0; i < largeSize; ++i) {
				testFloatArray[i] = rand_float(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%.2f ", testFloatArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortFloat(pIEcoLab1, testFloatArray, largeSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #2: ");
			for (i = 0; i < printSize; ++i) {
				printf("%.2f ", testFloatArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testFloatArray);

			printf("...\n\n");
		}
	}

	printf("/// double test ///\n");
	{
		{
			printf("Test #1: ");
			testDoubleArray = (double*) pIMem->pVTbl->Alloc(pIMem, sizeof(double) * smallSize);
			for (i = 0; i < smallSize; ++i) {
				testDoubleArray[i] = rand_double(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%.2f ", testDoubleArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortDouble(pIEcoLab1, testDoubleArray, smallSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #1: ");
			for (i = 0; i < printSize; ++i) {
				printf("%.2f ", testDoubleArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testDoubleArray);

			printf("...\n\n");
		}

		{
			printf("Test #2: ");
			testDoubleArray = (double*) pIMem->pVTbl->Alloc(pIMem, sizeof(double) * mediumSize);
			for (i = 0; i < mediumSize; ++i) {
				testDoubleArray[i] = rand_double(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%.2f ", testDoubleArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortDouble(pIEcoLab1, testDoubleArray, mediumSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #2: ");
			for (i = 0; i < printSize; ++i) {
				printf("%.2f ", testDoubleArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testDoubleArray);

			printf("...\n\n");
		}

		{
			printf("Test #3: ");
			testDoubleArray = (double*) pIMem->pVTbl->Alloc(pIMem, sizeof(double) * largeSize);
			for (i = 0; i < largeSize; ++i) {
				testDoubleArray[i] = rand_double(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%.2f ", testDoubleArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortDouble(pIEcoLab1, testDoubleArray, largeSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #2: ");
			for (i = 0; i < printSize; ++i) {
				printf("%.2f ", testDoubleArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testDoubleArray);

			printf("...\n\n");
		}
	}
	
	printf("/// long double test ///\n");
	{
		{
			printf("Test #1: ");
			testLongDoubleArray = (long double*) pIMem->pVTbl->Alloc(pIMem, sizeof(long double) * smallSize);
			for (i = 0; i < smallSize; ++i) {
				testLongDoubleArray[i] = rand_long_double(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%.3Lf ", testLongDoubleArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortLongDouble(pIEcoLab1, testLongDoubleArray, smallSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #1: ");
			for (i = 0; i < printSize; ++i) {
				printf("%.3Lf ", testLongDoubleArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testLongDoubleArray);

			printf("...\n\n");
		}

		{
			printf("Test #2: ");
			testLongDoubleArray = (long double*) pIMem->pVTbl->Alloc(pIMem, sizeof(long double) * mediumSize);
			for (i = 0; i < mediumSize; ++i) {
				testLongDoubleArray[i] = rand_long_double(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%.3Lf ", testLongDoubleArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortLongDouble(pIEcoLab1, testLongDoubleArray, mediumSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #2: ");
			for (i = 0; i < printSize; ++i) {
				printf("%.3Lf ", testLongDoubleArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testLongDoubleArray);

			printf("...\n\n");
		}

		{
			printf("Test #3: ");
			testLongDoubleArray = (long double*) pIMem->pVTbl->Alloc(pIMem, sizeof(long double) * largeSize);
			for (i = 0; i < largeSize; ++i) {
				testLongDoubleArray[i] = rand_long_double(-1000,1000);
			}
			for (i = 0; i < printSize; ++i) {
				printf("%.3Lf ", testLongDoubleArray[i]);
			}
			printf("...\n");
			begin = clock();
			result = pIEcoLab1->pVTbl->combSortLongDouble(pIEcoLab1, testLongDoubleArray, largeSize); 
			end = clock();
			printf("Test took %f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
			printf("Result #2: ");
			for (i = 0; i < printSize; ++i) {
				printf("%.3Lf ", testLongDoubleArray[i]);
			}
			/* Освобождение блока памяти */
			pIMem->pVTbl->Free(pIMem, testLongDoubleArray);

			printf("...\n\n");
		}
	}

Release:

    if (pICP != 0 && cAdvise != 0) {
        pICP->pVTbl->Unadvise(pICP, cAdvise);
        cAdvise = 0;
    }
    if (pIEcoLab1Sink != 0) {
        pIEcoLab1Sink->pVTbl->Release(pIEcoLab1Sink);
        pIEcoLab1Sink = 0;
    }
    if (pICP != 0) {
        pICP->pVTbl->Release(pICP);
        pICP = 0;
    }
    if (pICPC != 0) {
        pICPC->pVTbl->Release(pICPC);
        pICPC = 0;
    }

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

