/*
 * tasks.h
 *
 *  Created on: Mar 12, 2026
 *      Author: Prathibha
 */

#ifndef INC_TASKS_H_
#define INC_TASKS_H_
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Task prototypes */
void Task1(void *arg);
void Pedometer_Process(void *arg);
void Task3(void *arg);

/* Shared queue */
extern QueueHandle_t alertQueue;

/* Shared sensor data */
extern int16_t g_Ax, g_Ay, g_Az;
extern int16_t Gx, Gy, Gz;

extern int step_count;

/* MPU functions */
void MPU6050_Read(void);


#endif /* INC_TASKS_H_ */
