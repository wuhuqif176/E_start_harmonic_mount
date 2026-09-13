// CH224K PD 诱骗芯片插件
#include "CH224K.h"

#if CH224K_ENABLE == ON

#include "../../Common.h"
#include "../../lib/tasks/OnTask.h"
#include "../../lib/nv/Nv.h"
#include <Wire.h>

#ifndef CH224K_SDA_PIN
  #define CH224K_SDA_PIN 5
#endif

#ifndef CH224K_SCL_PIN
  #define CH224K_SCL_PIN 18
#endif

#ifndef CH224K_DEFAULT_VOLTAGE
  #define CH224K_DEFAULT_VOLTAGE 12
#endif

#ifndef CH224K_I2C_ADDRESS
  #define CH224K_I2C_ADDRESS 0x22
#endif

CH224KPlugin ch224k;

// 包装函数，用于任务调度器调用
void ch224kWrapper() { ch224k.loop(); }

void CH224KPlugin::init() {
  VLF("MSG: Plugins, starting: CH224K PD 诱骗芯片");
  VF("CH224K: 硬件连接 SDA=");
  V((int)CH224K_SDA_PIN);
  VF(", SCL=");
  V((int)CH224K_SCL_PIN);
  VLF(" (等待 CH224K 独立上电)");
  VF("CH224K: 使用 Wire1 (独立I2C总线)，I2C地址=0x");
  if (DEBUG != OFF) { SERIAL_DEBUG.print(CH224K_I2C_ADDRESS, HEX); }
  VLF("");

  // 从 NV 加载保存的电压设置
  load();

  // 使用 Wire1 (I2C1) 而非 Wire (I2C0)，避免与主 I2C 设备 (AHT20/DS3231) 冲突
  // 主 I2C 总线 (SDA=22, SCL=23) 用于 AHT20/DS3231 等设备
  // CH224K 连接在独立 I2C 引脚 (SDA=5, SCL=18)，使用 Wire1 独立控制
  
  // 释放旧的 CH224Q 对象，防止内存泄漏
  if (ch224q != nullptr) {
    delete ch224q;
    ch224q = nullptr;
  }
  
  if (!Wire1.begin((int)CH224K_SDA_PIN, (int)CH224K_SCL_PIN)) {
    VLF("CH224K: [错误] Wire1 初始化失败！请检查引脚配置");
    errorState = true;
    initState = CH224K_STATE_ERROR;
    return;
  }
  Wire1.setClock(100000);  // 100kHz 标准模式
  ch224q = new CH224Q(&Wire1);

  // 初始化状态机
  initialized = false;
  errorState = false;
  initState = CH224K_STATE_WAIT_POWER_ON;
  stateStartTime = millis();
  lastRetryTime = 0;

  // 注册后台任务，每 100ms 执行一次，优先级 7
  tasks.add(100, 0, true, 7, ch224kWrapper, "CH224K");

  VLF("CH224K: 插件已启动，等待 CH224K 独立上电...");
  VLF("CH224K: 注意: MCU 先上电，CH224K 后上电（独立电源）");
}

void CH224KPlugin::reset() {
  VLF("CH224K: 手动重置连接...");
  initialized = false;
  errorState = false;
  initState = CH224K_STATE_WAIT_POWER_ON;
  stateStartTime = millis();
  lastRetryTime = 0;
  VLF("CH224K: 状态机已重置，开始重新连接...");
}

void CH224KPlugin::loop() {
  // 如果已完全初始化完成，无需处理
  if (initialized && !errorState && initState == CH224K_STATE_RUNNING) return;

  uint32_t now = millis();

  switch (initState) {

    // ========== 阶段 1: 等待 CH224K 上电就绪 ==========
    case CH224K_STATE_WAIT_POWER_ON: {
      // 空指针保护
      if (ch224q == nullptr) return;
      
      // 检查是否超时
      if (now - stateStartTime > WAIT_CH224K_TIMEOUT) {
        VLF("CH224K: [警告] 等待 CH224K 上电超时 (10秒)！");
        VLF("CH224K:         5秒后将自动重试...");
        initState = CH224K_STATE_RETRY;
        stateStartTime = now;
        return;
      }

      // 每 100ms 尝试连接
      if (now - lastRetryTime < 100) return;
      lastRetryTime = now;

      // 尝试连接 CH224K
      int8_t result = ch224q->begin(CH224K_I2C_ADDRESS);
      if (result < 0) {
        return; // 连接失败，下次重试
      }

      // 连接成功
      VLF("CH224K: 设备已连接 (I2C 通信正常)");
      VLF("CH224K: 等待 500ms 确保 CH224K 完全初始化...");

      // 进入阶段 2
      initState = CH224K_STATE_WAIT_PD_READY;
      stateStartTime = now;
      break;
    }

    // ========== 阶段 2: 等待 PD 协议握手完成 ==========
    case CH224K_STATE_WAIT_PD_READY: {
      // 先等待 500ms 确保 CH224K 完全初始化
      if (now - stateStartTime < 500) {
        return;
      }

      // 检查是否超时 (从进入此阶段开始计时)
      if (now - stateStartTime > WAIT_PD_TIMEOUT + 500) {
        VLF("CH224K: [警告] 等待 PD 协议握手超时 (10秒)！");
        VLF("CH224K:         5秒后将自动重试...");
        VLF("CH224K:         请检查 PD 电源是否已连接");
        initState = CH224K_STATE_RETRY;
        stateStartTime = now;
        return;
      }

      // 每 100ms 轮询状态
      if (now - lastRetryTime < 100) return;
      lastRetryTime = now;

      uint8_t status = ch224q->getStatus();

      // 检查是否有任意协议激活
      if (status == CH224Q_STATUS_NONE_ACTIVATED) {
        return; // 尚未就绪，继续等待
      }

      // PD 协议已激活
      VLF("CH224K: PD 协议已激活!");

      // 输出检测到的协议
      if (status & CH224Q_STATUS_BC_ACTIVATED)  VLF("CH224K:   检测到 BC 1.2");
      if (status & CH224Q_STATUS_QC2_ACTIVATED) VLF("CH224K:   检测到 QC 2.0");
      if (status & CH224Q_STATUS_QC3_ACTIVATED) VLF("CH224K:   检测到 QC 3.0");
      if (status & CH224Q_STATUS_PD_ACTIVATED)  VLF("CH224K:   检测到 USB-PD");
      if (status & CH224Q_STATUS_EPR_ACTIVATED) VLF("CH224K:   检测到 EPR (PD 3.1)");

      // 如果是 PD 协议，输出 PDO 详情
      if (status & (CH224Q_STATUS_PD_ACTIVATED | CH224Q_STATUS_EPR_ACTIVATED)) {
        uint8_t num = ch224q->getNumberPDOs();
        VF("CH224K:   PDO 数量: "); VL((int)num);
        for (uint8_t i = 0; i < num; i++) {
          String s;
          PDO2String(decodePDO(ch224q->getPDORawValue(i)), &s);
          VF("CH224K:     PDO ");
          V((int)i);
          VF(": ");
          VLF(s.c_str());
        }
      }

      // 进入阶段 3
      initState = CH224K_STATE_SET_VOLTAGE;
      stateStartTime = now;
      break;
    }

    // ========== 阶段 3: 设置目标电压 ==========
    case CH224K_STATE_SET_VOLTAGE: {
      // 等待 200ms 确保状态稳定
      if (now - stateStartTime < 200) {
        return;
      }

      // 设置保存的电压
      VF("CH224K: 设置目标电压 "); V((int)currentVoltage); VLF("V...");
      setVoltage(currentVoltage);

      // 标记初始化完成
      initialized = true;
      errorState = false;
      initState = CH224K_STATE_RUNNING;

      VF("CH224K: 插件就绪，电压 "); V((int)currentVoltage); VLF(" V");
      break;
    }

    // ========== 重试状态 ==========
    case CH224K_STATE_RETRY: {
      // 等待 RETRY_DELAY 后自动重试
      if (now - stateStartTime < RETRY_DELAY) {
        return;
      }

      VLF("CH224K: 自动重试连接...");
      initialized = false;
      errorState = false;
      initState = CH224K_STATE_WAIT_POWER_ON;
      stateStartTime = now;
      lastRetryTime = 0;
      break;
    }

    // ========== 错误状态 ==========
    case CH224K_STATE_ERROR: {
      errorState = true;
      initialized = true;
      break;
    }

    // ========== 运行状态 ==========
    case CH224K_STATE_RUNNING:
    default:
      initialized = true;
      errorState = false;
      break;
  }
}

bool CH224KPlugin::setVoltage(uint8_t voltage) {
  uint8_t mode = voltageToMode(voltage);
  if (mode == CH224Q_MODE_UNKNOWN) {
    VLF("CH224K: 不支持的电压值");
    return false;
  }

  // 始终记录用户选择的目标电压（由 save() 持久化到 NV，下次开机自动应用）
  currentVoltage = voltage;

  if (ch224q == nullptr) {
    VLF("CH224K: 无法立即应用电压 - CH224Q 对象未创建，已保存目标电压待初始化后应用");
    return false;
  }

  int8_t result = ch224q->setMode(mode);
  if (result < 0) {
    VLF("CH224K: 电压设置失败 (I2C 错误)，已保存目标电压待下次初始化应用");
    return false;
  }

  VF("CH224K: 电压已设置为 "); V((int)voltage); VLF("V");
  return true;
}

uint8_t CH224KPlugin::getVoltage() {
  // 如果未初始化，返回 0 而不是保存的目标电压，避免显示误导性数据
  if (!initialized || errorState) {
    return 0;
  }
  return currentVoltage;
}

uint8_t CH224KPlugin::getTargetVoltage() {
  return currentVoltage;
}

uint8_t CH224KPlugin::getStatus() {
  if (!initialized || errorState || ch224q == nullptr) {
    return CH224K_STATUS_NONE;
  }
  return ch224q->getStatus();
}

uint16_t CH224KPlugin::getMaxCurrent() {
  if (!initialized || errorState || ch224q == nullptr) {
    return 0;
  }
  uint16_t current = ch224q->getMaxCurrent_mA();
  // 过滤异常值：CH224K 最大支持 5A (5000mA)，PD 3.1 EPR 最大 5A
  // 寄存器读取失败时可能返回 0xFFFF 或乱码
  if (current > 5000) {
    return 0;
  }
  return current;
}

uint16_t CH224KPlugin::getPDOMaxCurrent() {
  if (!initialized || errorState || ch224q == nullptr) {
    return 0;
  }

  int8_t count = getPDOCount();
  if (count <= 0) return 0;

  uint32_t target_mV = (uint32_t)currentVoltage * 1000;

  for (uint8_t i = 0; i < (uint8_t)count; i++) {
    PDOInfo info = getPDOInfo(i);
    if (!info.valid()) continue;

    // 对于 Fixed PDO: 电压为单一值
    if (info.type == PDOType::Fixed) {
      // Fixed PDO 的标称电压在 min/max/nominal 中相同
      if (info.max_voltage_mV == target_mV) {
        return (uint16_t)info.max_current_mA;
      }
    } else {
      // 对于 Variable/Battery PDO: 检查目标电压是否在范围内
      if (info.min_voltage_mV <= target_mV && target_mV <= info.max_voltage_mV) {
        if (info.max_current_mA > 0) {
          return (uint16_t)info.max_current_mA;
        }
        if (info.max_power_mW > 0 && info.max_voltage_mV > 0) {
          // 从功率计算电流: I = P / V
          uint32_t current_mA = (info.max_power_mW * 10) / (info.max_voltage_mV / 100);
          if (current_mA < 5000) return (uint16_t)current_mA;
        }
      }
    }
  }

  return 0;
}

PDOInfo CH224KPlugin::getPDOInfo(uint8_t index) {
  PDOInfo info;
  if (!initialized || errorState || ch224q == nullptr) {
    return info;
  }

  uint32_t raw = getPDORaw(index);
  if (raw == 0) return info;

  info = decodePDO(raw);
  return info;
}

int8_t CH224KPlugin::getPDOCount() {
  if (!initialized || errorState || ch224q == nullptr) {
    return 0;
  }
  return ch224q->getNumberPDOs();
}

uint32_t CH224KPlugin::getPDORaw(uint8_t index) {
  if (!initialized || errorState || ch224q == nullptr) {
    return 0;
  }
  return ch224q->getPDORawValue(index);
}

bool CH224KPlugin::isInitialized() {
  return initialized;
}

bool CH224KPlugin::isError() {
  return errorState;
}

bool CH224KPlugin::save() {
  if (!nv().ok()) {
    return false;
  }

  KvPartition::Status status = nv().kv().put(CH224K_NV_KEY, currentVoltage);
  return status == KvPartition::Status::Ok;
}

bool CH224KPlugin::load() {
  if (!nv().ok()) {
    currentVoltage = CH224K_DEFAULT_VOLTAGE;
    return false;
  }

  uint8_t savedVoltage = CH224K_DEFAULT_VOLTAGE;
  KvPartition::Status status = nv().kv().get(CH224K_NV_KEY, savedVoltage);

  if (status == KvPartition::Status::Ok && savedVoltage >= 5 && savedVoltage <= 28) {
    currentVoltage = savedVoltage;
    return true;
  }

  currentVoltage = CH224K_DEFAULT_VOLTAGE;
  return false;
}

uint8_t CH224KPlugin::voltageToMode(uint8_t voltage) {
  switch (voltage) {
    case 5:  return CH224Q_MODE_5V;
    case 9:  return CH224Q_MODE_9V;
    case 12: return CH224Q_MODE_12V;
    case 15: return CH224Q_MODE_15V;
    case 20: return CH224Q_MODE_20V;
    case 28: return CH224Q_MODE_28V;
    default: return CH224Q_MODE_UNKNOWN;
  }
}

const char* CH224KPlugin::statusToString(uint8_t status) {
  switch (status) {
    case CH224K_STATUS_BC:   return "BC";
    case CH224K_STATUS_QC2:  return "QC2";
    case CH224K_STATUS_QC3:  return "QC3";
    case CH224K_STATUS_PD:   return "PD";
    case CH224K_STATUS_EPR:  return "EPR";
    default:                 return "NONE";
  }
}

#endif