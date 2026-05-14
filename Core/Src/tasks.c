/*
 * tasks.c
 *
 *  Created on: Mar 12, 2026
 *      Author:Prathibha
 */
#include "tasks.h"
#include <math.h>
#include <stdio.h>

/* External variables from main.c */
extern QueueHandle_t alertQueue;
extern int step_count;

/* Sensor values */
extern int16_t g_Ax, g_Ay, g_Az;
extern int16_t Gx, Gy, Gz;

/* Thresholds */
#define THRESHOLD 19660
#define GYRO_SCALE_FACTOR 131.0
#define SWING_THRESHOLD 15.0


/*================ SENSOR TASK =================*/
void Task1(void *arg)
{
    while(1)
    {
        MPU6050_Read();
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}


/*================ PEDOMETER TASK =================*/
void Pedometer_Process(void *arg)
{
    float prev_magnitude = 0.0f;
    float gyro_y_dps;
    int swing_detected;

    while(1)
    {
        float aTotal = sqrtf((float)g_Ax*g_Ax +
                             (float)g_Ay*g_Ay +
                             (float)g_Az*g_Az);

        gyro_y_dps = (float)Gy / GYRO_SCALE_FACTOR;

        if(fabs(gyro_y_dps) > SWING_THRESHOLD)
            swing_detected = 1;
        else
            swing_detected = 0;

        if((aTotal >= THRESHOLD) &&
           (prev_magnitude < THRESHOLD) &&
           (swing_detected))
        {
            step_count++;

            xQueueSend(alertQueue, &step_count, portMAX_DELAY);

            vTaskDelay(pdMS_TO_TICKS(250));
        }
        else
        {
            vTaskDelay(pdMS_TO_TICKS(20));
        }

        prev_magnitude = aTotal;
    }
}


/*================ ALERT TASK =================*/
void Task3(void *arg)
{
    int received_step;

    while(1)
    {
        xQueueReceive(alertQueue, &received_step, portMAX_DELAY);

        printf("Step count = %d\r\n", received_step);

        HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
    }
}

