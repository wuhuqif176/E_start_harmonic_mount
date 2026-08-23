# E_start_harmonic_mount

Low-cost open-source harmonic equatorial mount. Hybrid CNC + 3D-printed structure, 2× S14 harmonic reducers, 2× 42mm steppers, OnStepX, custom ESP32 PD-powered controller. BOM under 1500 CNY.

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
│   └── drawings/     # 装配图纸（可先空着，放 README 说明）
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
