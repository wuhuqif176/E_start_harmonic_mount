// CH224K PD 诱骗芯片插件
#pragma once

#include <Arduino.h>
#include <CH224Q_Arduino.h>
#include <CH224Q_PDO_Decoder.h>

// CH224K 协议状态常量
#define CH224K_STATUS_NONE 0
#define CH224K_STATUS_BC   (1<<0)
#define CH224K_STATUS_QC2  (1<<1)
#define CH224K_STATUS_QC3  (1<<2)
#define CH224K_STATUS_PD   (1<<3)
#define CH224K_STATUS_EPR  (1<<4)

// 状态机超时常量 (毫秒)
#define WAIT_CH224K_TIMEOUT  10000UL  // 等待 CH224K 上电超时
#define WAIT_PD_TIMEOUT      10000UL  // 等待 PD 协议握手超时
#define RETRY_DELAY          5000UL   // 自动重试等待时间

// NV 存储键
#define CH224K_NV_KEY "CHV"

// CH224K 状态机状态
enum CH224KInitState {
  CH224K_STATE_WAIT_POWER_ON,    // 等待 CH224K 独立上电
  CH224K_STATE_WAIT_PD_READY,    // 等待 PD 协议握手完成
  CH224K_STATE_SET_VOLTAGE,      // 设置目标电压
  CH224K_STATE_RUNNING,          // 正常运行
  CH224K_STATE_RETRY,            // 超时重试
  CH224K_STATE_ERROR             // 错误
};

class CH224KPlugin {
  public:
    // 初始化
    void init();

    // 主循环 (由任务调度器定时调用)
    void loop();

    // 重置连接状态机，允许重新尝试连接
    void reset();

    // 设置目标电压
    bool setVoltage(uint8_t voltage);

    // 获取当前电压 (未初始化时返回 0)
    uint8_t getVoltage();

    // 获取协议状态
    uint8_t getStatus();

    // 获取最大电流 (从寄存器读取协商值，单位 mA)
    uint16_t getMaxCurrent();

    // 获取当前电压对应的 PDO 最大电流 (单位 mA)
    // 例如 12V Fixed PDO 返回 3000 (3A)
    uint16_t getPDOMaxCurrent();

    // 获取 PDO 数量
    int8_t getPDOCount();

    // 获取指定索引的 PDO 原始值
    uint32_t getPDORaw(uint8_t index);

    // 获取指定索引的 PDO 信息
    PDOInfo getPDOInfo(uint8_t index);

    // 状态查询
    bool isInitialized();
    bool isError();

    // NV 存储
    bool save();
    bool load();

    // 获取当前目标电压 (无论是否完成初始化都返回已保存/设置的目标值)
    uint8_t getTargetVoltage();

    // 电压值到 CH224Q 模式的转换
    uint8_t voltageToMode(uint8_t voltage);

  private:
    // CH224Q 底层驱动对象
    CH224Q* ch224q = nullptr;

    // 状态机变量
    CH224KInitState initState = CH224K_STATE_WAIT_POWER_ON;
    bool initialized = false;
    bool errorState = false;
    uint32_t stateStartTime = 0;
    uint32_t lastRetryTime = 0;

    // 当前目标电压
    uint8_t currentVoltage = 0;

    // 状态文本
    const char* statusToString(uint8_t status);
};

extern CH224KPlugin ch224k;