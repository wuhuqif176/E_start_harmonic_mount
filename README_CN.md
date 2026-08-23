# E_start_harmonic_mount

[English](README.md) | **简体中文**

> ⚠️ **项目状态：早期开发 / 初步验证已完成。**
>
> 硬件已经搭建并通过基础测试，但详细的装配文档、技术文档和图纸仍在准备中。欢迎贡献与建议。

低成本开源谐波赤道仪。混合 CNC + 3D 打印结构，2× S14 谐波减速器，2× 17HM15 步进电机，OnStepX，自研 ESP32 PD 供电控制器。BOM 预算低于 1500 元。

## 项目目录结构

```
E_start/
├── README.md
├── LICENSE
├── hardware/
│   ├── cad/          # STEP、Fusion 360 等源文件
│   ├── stl/          # 3D 打印文件
│   ├── pcb/          # 控制板 PCB 文件
│   ├── bom/          # BOM 表格
│   └── drawings/     # 装配图纸（当前为占位，目录内有 README 说明）
├── firmware/
│   ├── onstepx/      # OnStepX 配置
│   └── custom/       # 自研 ESP32 固件
├── docs/
│   ├── assembly.md
│   ├── technical.md
│   └── images/
└── images/
```

## 快速链接

- [装配说明](docs/assembly.md)
- [技术说明](docs/technical.md)
- [English](README.md)
