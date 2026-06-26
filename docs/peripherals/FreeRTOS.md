# FreeRTOS — Real-Time Operating System

> STM32F401RE · HAL + CMSIS-RTOS v2 Reference · [Back to README](../../README.md)

---

## Overview

FreeRTOS is a lightweight RTOS for microcontrollers. STM32CubeIDE integrates it via **CMSIS-RTOS v2** wrapper (standard API over FreeRTOS kernel).

---

## Key Concepts

| Concept | Description |
|---------|-------------|
| **Task** | Independent thread of execution with its own stack |
| **Scheduler** | Decides which task runs based on priority |
| **Queue** | Safe inter-task communication buffer |
| **Semaphore** | Synchronization primitive |
| **Mutex** | Mutual exclusion for shared resources |
| **Timer** | Software timer (does not need TIM peripheral) |

---

## CubeMX Setup

1. **Middleware** → **FreeRTOS** → Enable, select **CMSIS_V2**
2. Create tasks in **Tasks and Queues** tab
3. Adjust **Stack Size** per task (default 128 words = 512 bytes)

---

## CMSIS-RTOS v2 API

```c
#include "cmsis_os.h"

/* ---- Task creation ---- */
osThreadId_t myTaskHandle;
const osThreadAttr_t myTask_attr = {
    .name       = "myTask",
    .stack_size = 256 * 4,  // bytes
    .priority   = osPriorityNormal,
};

void myTask(void *argument) {
    for (;;) {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        osDelay(500);  // Non-blocking delay (yields CPU)
    }
}

/* In main, before osKernelStart() */
myTaskHandle = osThreadNew(myTask, NULL, &myTask_attr);
osKernelStart();  // Start the scheduler (does not return)
```

---

## Queue (Inter-Task Communication)

```c
/* Create a queue that holds 10 uint32_t values */
osMessageQueueId_t queue = osMessageQueueNew(10, sizeof(uint32_t), NULL);

/* Producer task */
void producerTask(void *arg) {
    uint32_t value = 42;
    for (;;) {
        osMessageQueuePut(queue, &value, 0, osWaitForever);
        osDelay(100);
    }
}

/* Consumer task */
void consumerTask(void *arg) {
    uint32_t received;
    for (;;) {
        osMessageQueueGet(queue, &received, NULL, osWaitForever);
        // Process received value
    }
}
```

---

## Binary Semaphore (ISR → Task)

```c
osSemaphoreId_t btnSemaphore = osSemaphoreNew(1, 0, NULL);

/* ISR gives semaphore */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == B1_Pin) {
        osSemaphoreRelease(btnSemaphore);
    }
}

/* Task waits on semaphore */
void buttonTask(void *arg) {
    for (;;) {
        osSemaphoreAcquire(btnSemaphore, osWaitForever);
        // Button was pressed — handle here
    }
}
```

---

## Priority Levels (CMSIS-RTOS v2)

| Level | Value |
|-------|-------|
| `osPriorityIdle` | 1 |
| `osPriorityLow` | 8 |
| `osPriorityNormal` | 24 |
| `osPriorityAboveNormal` | 32 |
| `osPriorityHigh` | 40 |
| `osPriorityRealtime` | 48 |

---

## References

- [FreeRTOS Documentation](https://www.freertos.org/Documentation/RTOS_book.html)
- [CMSIS-RTOS v2 API Reference](https://arm-software.github.io/CMSIS_5/RTOS2/html/)
- HAL: `cmsis_os.h`, `FreeRTOSConfig.h`

> 📝 *Detailed notes will be added when FreeRTOS lab is completed.*
