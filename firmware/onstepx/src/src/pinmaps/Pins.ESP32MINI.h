// -------------------------------------------------------------------------------------------------
// ESP32MINI 板卡引脚映射
// 说明: 自定义 ESP32 小型化板卡，使用共享 UART 控制 TMC 步进驱动器
// 日期: 2025-06-08
// 
// 硬件设计:
//   - 轴1: DIR=32, STEP=33
//   - 轴2: DIR=25, STEP=26
//   - 轴3: DIR=27, STEP=14
//   - 共用 ENABLE: GPIO13
//   - 共享 UART: GPIO19 (所有 TMC 驱动器)
//   - I2C: SDA=22, SCL=23
//   - 电磁制动器: GPIO21 (DRV103H, 低电平制动，通过 FEATURE1 控制)
//
// 电磁制动器使用说明:
//   在 Config.h 中添加以下配置来控制制动器:
//   #define FEATURE1_PURPOSE        SWITCH
//   #define FEATURE1_NAME           "BRAKE1"
//   #define FEATURE1_PIN            21
//   #define FEATURE1_VALUE_DEFAULT  OFF
//   #define FEATURE1_ON_STATE       LOW         // 低电平制动
//
#pragma once

#if defined(ESP32)

// =================================================================================================
// 串口配置
// =================================================================================================
// Serial0: RX=GPIO3, TX=GPIO1 (USB 串口)
// Serial1: 用于 TMC UART 通信
// Serial2: RX=GPIO16, TX=GPIO17 (辅助串口/可配置为GPS)

#if SERIAL_A_BAUD_DEFAULT != OFF
  #define SERIAL_A              Serial      // 串口A - 主命令通道 (USB)
#endif
#if SERIAL_B_BAUD_DEFAULT != OFF
  #define SERIAL_B              Serial2     // 串口B - 辅助通道
#endif

// =================================================================================================
// GPS 串口配置
// =================================================================================================
// GPS模块连接到 IO17(RX) 和 IO15(TX)，使用硬件 Serial2
// 注意: 需要禁用 SERIAL_B (在Config.h中设置 SERIAL_B_BAUD_DEFAULT = OFF) 才能使用Serial2给GPS
// 波特率使用默认值 9600 (在 Config.defaults.h 中定义)
#if defined(TIME_LOCATION_SOURCE) && TIME_LOCATION_SOURCE == GPS
  #define SERIAL_GPS                    Serial2
  #define SERIAL_GPS_RX                 17      // IO17 - 接收GPS数据
  #define SERIAL_GPS_TX                 15      // IO15 - 发送数据到GPS
#endif

// =================================================================================================
// TMC UART 驱动器配置 (共享 UART 总线)
// =================================================================================================
// 所有 TMC 驱动器共享同一个 UART 端口，通过不同地址区分各个驱动器
// 硬件连接: 将所有驱动器的 UART 引脚并联到 GPIO19
// 驱动器地址通过 MS1/MS2 引脚设置:
//   - 轴1: MS1=LOW,  MS2=LOW  → 地址 0
//   - 轴2: MS1=HIGH, MS2=LOW  → 地址 1
//   - 轴3: MS1=LOW,  MS2=HIGH → 地址 2
#if defined(STEP_DIR_TMC_UART_PRESENT) || defined(SERVO_TMC2209_PRESENT)
  #define SERIAL_TMC_HARDWARE_UART
  #define SERIAL_TMC            Serial1     // 使用 Serial1 进行 TMC UART 通信
  #define SERIAL_TMC_BAUD       115200      // UART 波特率
  #define SERIAL_TMC_RX         19          // 共享 UART 接收/发送引脚
  #ifndef SERIAL_TMC_TX
    #define SERIAL_TMC_TX       19          // 单线模式，TX 与 RX 相同
  #endif
  // TMC 驱动器地址映射: 轴1=0, 轴2=1, 轴3=2
  #define SERIAL_TMC_ADDRESS_MAP(x) (x)
#endif

// =================================================================================================
// I2C 配置
// =================================================================================================
// 使用自定义 I2C 引脚 (非默认引脚)
#define I2C_SDA_PIN                 22          // I2C 数据引脚
#define I2C_SCL_PIN                 23          // I2C 时钟引脚

// =================================================================================================
// 辅助引脚定义
// =================================================================================================
// 注意: GPIO34, 35, 36, 39 是 ESP32 的仅输入引脚，不能用作输出!
#define AUX1_PIN                21          // 电磁制动器 (DRV103H)
#define AUX2_PIN                OFF         // 可用扩展引脚
#define AUX3_PIN                OFF         // 可用扩展引脚
#define AUX4_PIN                OFF         // 可用扩展引脚
#define AUX5_PIN                OFF         // 可用扩展引脚
#define AUX6_PIN                OFF         // 可用扩展引脚
#define AUX7_PIN                OFF         // 可用扩展引脚
#define AUX8_PIN                OFF         // 可用扩展引脚

// =================================================================================================
// 杂项引脚定义
// =================================================================================================
#ifndef ONE_WIRE_PIN
  #define ONE_WIRE_PIN          OFF         // 单总线引脚 (DS18B20 温度传感器)
#endif

#ifndef PEC_SENSE_PIN
  #define PEC_SENSE_PIN         OFF         // PEC 感应引脚
#endif

// =================================================================================================
// 状态 LED 配置 (可选)
// =================================================================================================
#ifdef STATUS_LED_ON_STATE
  #undef STATUS_LED_ON_STATE
#endif
#define STATUS_LED_ON_STATE     HIGH
#ifndef STATUS_LED_PIN
  #define STATUS_LED_PIN        OFF         // 状态 LED 引脚 (如不需要设为 OFF)
#endif

#ifdef MOUNT_LED_ON_STATE
  #undef MOUNT_LED_ON_STATE
#endif
#define MOUNT_LED_ON_STATE      HIGH
#define MOUNT_LED_PIN           STATUS_LED_PIN

#ifndef RETICLE_LED_PIN
  #define RETICLE_LED_PIN       OFF         // 十字丝 LED 引脚
#endif

// =================================================================================================
// 蜂鸣器配置 (可选)
// =================================================================================================
#ifndef STATUS_BUZZER_PIN
  #define STATUS_BUZZER_PIN     OFF         // 蜂鸣器引脚 (如不需要设为 OFF)
#endif

// =================================================================================================
// PPS (秒脉冲) 时间同步引脚 (可选，用于 GPS 时间同步)
// =================================================================================================
#ifndef PPS_SENSE_PIN
  #define PPS_SENSE_PIN         OFF         // PPS 输入引脚
#endif

// =================================================================================================
// 限位开关引脚 (可选)
// =================================================================================================
#ifndef LIMIT_SENSE_PIN
  #define LIMIT_SENSE_PIN       OFF         // 限位开关输入引脚
#endif

// =================================================================================================
// 共享引脚配置
// =================================================================================================
#define SHARED_DIRECTION_PINS                 // 方向引脚独立 (不共享)
#ifndef SHARED_ENABLE_PIN
  #define SHARED_ENABLE_PIN     13            // 共用 ENABLE 引脚 - 所有轴共享
#endif

// =================================================================================================
// Axis1 - RA/方位角 步进/方向驱动器
// =================================================================================================
// 引脚分配: DIR=GPIO32, STEP=GPIO33
// 
//          如果编译报错或功能异常，请更换为支持输出的 GPIO (如 16, 17 等)
#define AXIS1_ENABLE_PIN        SHARED        // 使能引脚 (共享)
#define AXIS1_M0_PIN            OFF           // M0 - 由 UART 地址配置代替
#define AXIS1_M1_PIN            OFF           // M1 - 由 UART 地址配置代替
#define AXIS1_M2_PIN            OFF           // M2 - 由 UART 地址配置代替
#define AXIS1_M3_PIN            OFF           // M3 - UART 通信由 SERIAL_TMC 处理
#define AXIS1_STEP_PIN          33            // 步进脉冲引脚 
#define AXIS1_DIR_PIN           32            // 方向引脚 
#ifndef AXIS1_SENSE_HOME_PIN
  #define AXIS1_SENSE_HOME_PIN  OFF           // 归零开关引脚 (如不需要设为 OFF)
#endif

// =================================================================================================
// Axis2 - DEC/高度角 步进/方向驱动器
// =================================================================================================
// 引脚分配: DIR=GPIO33, STEP=GPIO25
#define AXIS2_ENABLE_PIN        SHARED        // 使能引脚 (共享)
#define AXIS2_M0_PIN            OFF           // M0 - 由 UART 地址配置代替
#define AXIS2_M1_PIN            OFF           // M1 - 由 UART 地址配置代替
#define AXIS2_M2_PIN            OFF           // M2 - 由 UART 地址配置代替
#define AXIS2_M3_PIN            OFF           // M3 - UART 通信由 SERIAL_TMC 处理
#define AXIS2_STEP_PIN          26            // 步进脉冲引脚 ✓
#define AXIS2_DIR_PIN           25            // 方向引脚 ✓
#ifndef AXIS2_SENSE_HOME_PIN
  #define AXIS2_SENSE_HOME_PIN  OFF           // 归零开关引脚
#endif
#ifndef AXIS2_ENCODER_B_PIN
  #define AXIS2_ENCODER_B_PIN   OFF           // 编码器 B 相引脚
#endif

// =================================================================================================
// Axis3 - 旋转器/调焦器 步进/方向驱动器
// =================================================================================================
// 引脚分配: DIR=GPIO27, STEP=GPIO14
#define AXIS3_ENABLE_PIN        SHARED        // 使能引脚 (共享)
#define AXIS3_M0_PIN            OFF           // M0 - 由 UART 地址配置代替
#define AXIS3_M1_PIN            OFF           // M1 - 由 UART 地址配置代替
#define AXIS3_M2_PIN            OFF           // M2 - 由 UART 地址配置代替
#define AXIS3_M3_PIN            OFF           // M3 - UART 通信由 SERIAL_TMC 处理
#define AXIS3_STEP_PIN          14            // 步进脉冲引脚 ✓
#define AXIS3_DIR_PIN           27            // 方向引脚 ✓

// =================================================================================================
// Axis4 - 调焦器1 (未使用，可后续扩展)
// =================================================================================================
#define AXIS4_ENABLE_PIN        OFF
#define AXIS4_M0_PIN            OFF
#define AXIS4_M1_PIN            OFF
#define AXIS4_M2_PIN            OFF
#define AXIS4_M3_PIN            OFF
#define AXIS4_STEP_PIN          OFF
#define AXIS4_DIR_PIN           OFF

// =================================================================================================
// Axis5 - 调焦器2 (未使用，可后续扩展)
// =================================================================================================
#define AXIS5_ENABLE_PIN        OFF
#define AXIS5_M0_PIN            OFF
#define AXIS5_M1_PIN            OFF
#define AXIS5_M2_PIN            OFF
#define AXIS5_M3_PIN            OFF
#define AXIS5_STEP_PIN          OFF
#define AXIS5_DIR_PIN           OFF

// =================================================================================================
// ST4 导星接口引脚 (未使用，可后续扩展)
// =================================================================================================
#define ST4_RA_W_PIN            OFF
#define ST4_DEC_S_PIN           OFF
#define ST4_DEC_N_PIN           OFF
#define ST4_RA_E_PIN            OFF

#else
#error "处理器错误！此配置仅适用于 ESP32！"

#endif