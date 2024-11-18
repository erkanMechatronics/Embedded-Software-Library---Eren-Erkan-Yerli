/*
 * sensortest.h
 *
 *  Created on: Mar 16, 2024
 *      Author: erkan
 */

#ifndef INC_SENSORTEST_H_
#define INC_SENSORTEST_H_

#include "MPU6050_driver.h"
#include "sensordriver.h"


void sensorTest_init(void);
void sensorTest_print_sensor_values(void);


#endif /* INC_SENSORTEST_H_ */
