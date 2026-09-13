# Firmware 固件使用说明

## 目录结构

```
firmware/
├── README.md          # 本说明文件
├── onstepx/           # 项目修改过的 OnStepX 源码
├── firmware.bin       # 编译好的应用固件
├── bootloader.bin     # Bootloader
└── partitions.bin     # 分区表
```

## 使用方法

### 使用编译好的二进制文件

- 使用 **Flash Download Tool** 烧录
- 配置烧录参数：
    - Development Mode：选择 Develop
    - WorkMode：选择 UART
    - SPI SPEED：选择 80MHz
    - SPI MODE：选择 DIO 或 QIO
- 地址：
    - `bootloader.bin` -> `0x1000`
    - `partitions.bin` -> `0x8000`
    - `firmware.bin` -> `0x10000`
- 选择 COM 口，波特率建议 `460800` 或 `921600`
- 点击 **START** 开始烧录
