# E_start_harmonic_mount

**English** | [简体中文](README_CN.md)

> ⚠️ **Project status: Early development / Initial validation completed.**
>
> Hardware has been built and basic testing passed, but detailed assembly docs, technical docs, and drawings are still being prepared. Contributions and suggestions are welcome.

Low-cost open-source harmonic equatorial mount. Hybrid CNC + 3D-printed structure, 2× S14 harmonic reducers, 2× 17HM15 steppers, OnStepX, custom ESP32 PD-powered controller. BOM under 1500 CNY.

## Project Structure

```
E_start/
├── README.md
├── LICENSE
├── hardware/
│   ├── cad/          # STEP, Fusion 360, and other source files
│   ├── stl/          # 3D-printable files
│   ├── pcb/          # Controller PCB files
│   ├── bom/          # BOM tables
│   └── drawings/     # Assembly drawings (placeholder, see README inside)
├── firmware/
│   ├── onstepx/      # OnStepX configuration
│   └── custom/       # Custom ESP32 firmware
├── docs/
│   ├── assembly.md
│   ├── technical.md
│   └── images/
└── images/
```

## Quick Links

- [Assembly Guide](docs/assembly.md)
- [Technical Notes](docs/technical.md)
- [简体中文](README_CN.md)
