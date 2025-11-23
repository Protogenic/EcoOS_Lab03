# EcoLab03

## 1. Постановка задачи

Цель: в ранее созданный компонент добавить точки подключения с интерфейсом событий демонстрирующих пошаговую работу алгоритма выполненного задания.

## 2. Реализация

### Логирование

1. **OnCombSortCall** — событие начала итерации сортировки. Передаёт информацию о текущем шаге сравнения (gap) и порядковом номере прохода. Позволяет отслеживать динамику уменьшения расстояния между сравниваемыми элементами.

2. **OnCombSortSwap** — событие обмена элементов. Срабатывает при каждой перестановке, фиксируя индексы перемещаемых элементов. Это событие отражает активные действия алгоритма по упорядочиванию данных.

3. **OnCombSortCompleted** — событие завершения сортировки. Содержит итоговую информацию: тип обработанных данных, размер массива и образец отсортированной последовательности.

### Интерфейс событий

```c
typedef enum tagECO_COMB_SORT_TYPE {
    ECO_COMB_SORT_INT32 = 0,
    ECO_COMB_SORT_LONG,
    ECO_COMB_SORT_FLOAT,
    ECO_COMB_SORT_DOUBLE,
    ECO_COMB_SORT_LONG_DOUBLE
} ECO_COMB_SORT_TYPE;
```

```c
int16_t ECOCALLMETHOD CEcoLab1Sink_OnCombSortCall(/* in */ struct IEcoLab1Events* me,
                                                    /* in */ int32_t gap,
                                                    /* in */ uint32_t pass,
                                                    /* in */ ECO_COMB_SORT_TYPE typeId) {
    if (me == 0) {
        return -1;
    }

    printf("Проход #%u: gap=%d (тип: %s)\n", pass, gap, combTypeToString(typeId));

    return 0;
}
```


## Интеграция Connection Point

### Настройка точки подключения

Компонент `CEcoLab1` реализует интерфейс `IEcoConnectionPointContainer`, что позволяет внешним объектам подписываться на события. Инициализация точки подключения происходит в функции `initCEcoLab1`:

```c
/* Создание точки подключения */
result = createCEcoLab1ConnectionPoint((IEcoUnknown*)pCMe->m_pISys,
                                       (IEcoConnectionPointContainer*)&pCMe->m_pVTblICPC,
                                       &IID_IEcoLab1Events,
                                       (IEcoConnectionPoint**)&pCMe->m_pISinkCP);
```

Это обеспечивает возможность подключения нескольких подписчиков одновременно, что расширяет возможности системы мониторинга.

### Генерация событий в алгоритме

Алгоритм Comb Sort реализован в виде набора вспомогательных функций для каждого типа данных. Основная логика:

1. Инициализация: `gap = size`, `swapped = 1`
2. Цикл продолжается пока `gap > 1` или были обмены
3. На каждой итерации gap уменьшается: `gap = (gap * 10) / 13`
4. Проход по массиву с текущим gap и сравнение элементов
5. При необходимости выполняется обмен с генерацией события

**Фрагмент реализации:**

```c
static void combSortHelperInt(CEcoLab1* pCMe, int* arr, int size) {
    int gap = size;
    int swapped = 1;
    int i;
    uint32_t pass = 0;
    
    while (gap > 1 || swapped) {
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
```

Функции генерации событий (`CEcoLab1_Fire_OnCombSortCall`, `CEcoLab1_Fire_OnCombSortSwap`, `CEcoLab1_Fire_OnCombSortCompleted`) используют механизм перечисления подключений для доставки событий всем зарегистрированным подписчикам.

## Результат работы

<img width="336" height="981" alt="image" src="https://github.com/user-attachments/assets/168edcb3-fbc4-4e8a-ac87-3d320bce2a36" />

<img width="832" height="129" alt="image" src="https://github.com/user-attachments/assets/8b3160f7-7684-4530-bc58-b76b5bf4dd6f" />
