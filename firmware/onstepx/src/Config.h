/* ---------------------------------------------------------------------------------------------------------------------------------
 * Configuration for OnStepX
 *
 *          For more information on setting OnStep up see http://www.stellarjourney.com/index.php?r=site/equipment_onstep 
 *                      and join the OnStep Groups.io at https://groups.io/g/onstep
 * 
 *           *** Read the compiler warnings and errors, they are there to help guard against invalid configurations ***
 *
 * ---------------------------------------------------------------------------------------------------------------------------------
 * ADJUST THE FOLLOWING TO CONFIGURE YOUR CONTROLLER FEATURES ----------------------------------------------------------------------
 * <-Req'd = always must set, <-Often = usually must set, Option = optional, Adjust = adjust as req'd, Infreq = infrequently changed
*/
//      Parameter Name              Value   Default  Notes                                                                      Hint

// =================================================================================================================================
// CONTROLLER ======================================================================================================================
#define HOST_NAME                "ESP32-ONSTEP" // nStep", Hostname for this device up to 16 chars.                                 Adjust

// CH224K PD 诱骗芯片配置 --------------------------------------------------------------------------------------------
#define CH224K_ENABLE                 ON    //    OFF, 启用/禁用 CH224K PD 诱骗芯片功能                               Option
#define CH224K_SDA_PIN                5     //         SDA 引脚 (GPIO5)                                              Adjust
#define CH224K_SCL_PIN                18    //         SCL 引脚 (GPIO18)                                             Adjust
#define CH224K_DEFAULT_VOLTAGE        12    //         默认电压 (V): 5/9/12/15/20/28                                 Adjust
#define CH224K_I2C_ADDRESS            0x22  //         I2C 地址                                                      Adjust

// PINMAP ------------------------------------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Controller#PINMAP
#define PINMAP                        ESP32MINI //    OFF, Choose from: MiniPCB, MiniPCB2, MaxPCB4, MaxESP4, MaxSTM3, FYSETC_E4,   <-Req'd
                                          //         BTT_SKR_PRO, etc.  Other boards and more info. in ~/src/Constants.h

// SERIAL PORT COMMAND CHANNELS --------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Controller#SERIAL_PORTS
#define SERIAL_A_BAUD_DEFAULT        230400 //   9600, n. Where n=9600,19200,57600,115200,230400,460800 (common baud rates.)    Infreq
#define SERIAL_B_BAUD_DEFAULT        OFF //   9600, n. Baud rate as above. See (src/pinmaps/) for Serial port assignments.   Infreq
#define SERIAL_B_ESP_FLASHING         OFF //    OFF, ON Upload ESP8266 WiFi firmware through SERIAL_B with :ESPFLASH# cmd.    Option
#define SERIAL_C_BAUD_DEFAULT         OFF //    OFF, n. Baud rate as above. See (src/pinmaps/) for Serial port assignments.   Infreq
#define SERIAL_D_BAUD_DEFAULT         OFF //    OFF, n. Baud rate as above. See (src/pinmaps/) for Serial port assignments.   Infreq
#define SERIAL_E_BAUD_DEFAULT         OFF //    OFF, n. Baud rate as above. See (src/pinmaps/) for Serial port assignments.   Infreq
#define SERIAL_RADIO                  WIFI_STATION    //    关闭，使用蓝牙或WiFi接入点或WiFi站（仅ESP32）  WIFI_STATION   #elif SERIAL_RADIO == WIFI_ACCESS_POINT   Option

// STATUS --------------------------------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Controller#STATUS_LED
#define STATUS_LED                    OFF //    OFF, Steady illumination if no error, blinks w/error code otherwise.          Option

// RETICLE CONTROL ------------------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Controller#RETICLE_CONTROL
#define RETICLE_LED_DEFAULT           OFF //    OFF, n. Where n=0..255 (0..100%) activates feature sets default brightness.   Option
#define RETICLE_LED_MEMORY            OFF //    OFF, ON Remember reticle brightness across power cycles.                      Option
#define RETICLE_LED_INVERT            OFF //    OFF, ON Inverts control for cases where 0V is max brightness.                 Option

// WEATHER SENSOR --------------------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Controller#WEATHER_SENSOR
#define WEATHER                       AHT20 //    OFF, BME280 (I2C 0x77,) BME280_0x76, BME280_SPI (see pinmap for CS.)          Option
                                          //         BMP280 (I2C 0x77,) BMP280_0x76, BMP280_SPI (see pinmap for CS.)
                                          //         AHT20 (I2C 0x38) for temperature and humidity (no pressure).
                                          //         BME280 or BMP280 for temperature, pressure.  BME280/AHT20 for humidity also.

// SIGNALING ------------------------------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Controller#SIGNALING
#define STEP_WAVE_FORM             SQUARE // SQUARE, PULSE Step signal wave form faster rates. SQUARE best signal integrity.  Adjust
                                          //         Applies to all axes.

// NON-VOLATILE MEMORY ---------------------------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Controller#NV
#define NV_DRIVER              NV_DEFAULT // NV_DEF, Use platforms default non-volatile device to remember runtime settings.  Option

// =================================================================================================================================
// MOUNT ===========================================================================================================================

// 电机驱动型号 (步进/方向 和 伺服) 许多驱动有特定要求，请参考以下链接了解详细信息
// 常用驱动: A4988, DRV8825, LV8729, S109, TMC2130, TMC5160, TMC2209 等

// 轴1 - 赤经/方位角 -------------------------------------------------------- 参见 https://onstep.groups.io/g/main/wiki/Configuration_Axes
#define AXIS1_DRIVER_MODEL            TMC2209 //    OFF, 填写电机驱动型号(如上)以激活望远镜，两个轴都必须填写    <-常用

// 如果启用了运行时轴设置，以下部分的更改将被忽略（在SWS网页中禁用或清除NV/EEPROM）：
// \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ 
#define AXIS1_STEPS_PER_DEGREE      1333 //  12800, n. 每度的步数：                                                          <-必填
                                          //         n = (电机步数 × 微步数 × 总减速比)/360.0
#define AXIS1_REVERSE                 OFF //    OFF, ON 反转运动方向，或反转接线来纠正    <-常用
#define AXIS1_LIMIT_MIN              -180 //   -180, n. n= -90..-360 (度) 最小"时角"或方位角        调整
#define AXIS1_LIMIT_MAX               180 //    180, n. n=  90.. 360 (度) 最大"时角"或方位角        调整
#define AXIS1_LIMIT_SYNC              OFF //    OFF, n. n= 0..90 (度) 仅允许在此+/-范围内同步/重置  选项

#define AXIS1_DRIVER_MICROSTEPS       8 //    OFF, n. 默认微步模式（跟踪时）                                              <-必填
#define AXIS1_DRIVER_MICROSTEPS_GOTO  OFF //    OFF, n. Goto微步模式覆盖。OFF使用上述_DRIVER_MICROSTEPS的值            选项

// 适用于 TMC2130, TMC5160, TMC2209, TMC2226 步进/方向驱动型号：
#define AXIS1_DRIVER_IHOLD            300 //    OFF, n, (mA) 静止时的保持电流。OFF使用IRUN/2.0                    选项
#define AXIS1_DRIVER_IRUN             500 //    OFF, n, (mA) 默认运行电流，根据电机/驱动等设置        选项
#define AXIS1_DRIVER_IGOTO            500 //    OFF, n, (mA) 快速转动时的运行电流覆盖。OFF使用IRUN                  选项
// /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /

#define AXIS1_DRIVER_STATUS           ON //    OFF, ON, HIGH或LOW。用于驱动状态信息/故障检测               选项

#define AXIS1_DRIVER_DECAY            OFF //    OFF, 跟踪衰减模式默认覆盖。TMC默认是STEALTHCHOP(静音模式)        少用
#define AXIS1_DRIVER_DECAY_GOTO       OFF //    OFF, Goto衰减模式默认覆盖。TMC默认是SPREADCYCLE(扩频模式)            少用

#define AXIS1_POWER_DOWN              OFF //    OFF, ON 运动停止后30秒或最后一次<=1x导星后10分钟关闭电源  少用

#define AXIS1_SENSE_HOME              OFF //    OFF, HIGH或LOW启用并设置顺时针归零位置（从正面看） 选项
#define AXIS1_SENSE_LIMIT_MIN LIMIT_SENSE // ...NSE, HIGH或LOW状态限位开关停止运动                  选项
#define AXIS1_SENSE_LIMIT_MAX LIMIT_SENSE // ...NSE, HIGH或LOW状态限位开关停止运动                  选项
                                          //         数字输入，可添加：|HYST(n) n=0..1023 稳定时间(ms)
                                          //         模拟输入还可添加：
                                          //         |THLD(n) n=1..1023 (ADU) 模拟阈值
                                          //         |HYST(n) n=0..1023 (ADU) +/- 迟滞范围

// 轴2 - 赤纬/高度角 ------------------------------------------------------- 参见 https://onstep.groups.io/g/main/wiki/Configuration_Axes
#define AXIS2_DRIVER_MODEL            TMC2209 //    OFF, 填写电机驱动型号(如上)以激活望远镜，两个轴都必须填写    <-常用

// 如果启用了运行时轴设置，以下部分的更改将被忽略（在SWS网页中禁用或清除NV/EEPROM）：
// \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/
#define AXIS2_STEPS_PER_DEGREE      1333 //  12800, n. 每度的步数：                                                          <-必填
                                          //         n = (电机步数 × 微步数 × 总减速比)/360.0
#define AXIS2_REVERSE                 OFF //    OFF, ON 反转运动方向，或反转接线来纠正    <-常用
#define AXIS2_LIMIT_MIN               -90 //    -90, n. n=-90..0 (度) 允许的最小赤纬或高度角    少用
#define AXIS2_LIMIT_MAX                90 //     90, n. n= 0..90 (度) 允许的最大赤纬或高度角    少用
#define AXIS2_LIMIT_SYNC              OFF //    OFF, n. n= 0..90 (度) 仅允许在此+/-范围内同步/重置  选项

#define AXIS2_DRIVER_MICROSTEPS       8 //    OFF, n. 默认微步模式（跟踪时）                                              <-必填
#define AXIS2_DRIVER_MICROSTEPS_GOTO  OFF //    OFF, n. Goto微步模式覆盖。OFF使用上述_DRIVER_MICROSTEPS的值            选项

// 适用于 TMC2130, TMC5160, TMC2209, TMC2226 步进/方向驱动型号：
#define AXIS2_DRIVER_IHOLD            300 //    OFF, n, (mA) 静止时的保持电流。OFF使用IRUN/2.0                    选项
#define AXIS2_DRIVER_IRUN             500 //    OFF, n, (mA) 默认运行电流，根据电机/驱动等设置        选项
#define AXIS2_DRIVER_IGOTO            500 //    OFF, n, (mA) 快速转动时的运行电流覆盖。OFF使用IRUN                  选项
// /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /

#define AXIS2_DRIVER_STATUS           ON //    OFF, ON, HIGH或LOW。轮询驱动状态信息/故障检测       选项

#define AXIS2_DRIVER_DECAY            OFF //    OFF, 跟踪衰减模式默认覆盖。TMC默认是STEALTHCHOP(静音模式)        少用
#define AXIS2_DRIVER_DECAY_GOTO       OFF //    OFF, Goto衰减模式默认覆盖。TMC默认是SPREADCYCLE(扩频模式)            少用

#define AXIS2_POWER_DOWN              OFF //    OFF, ON 运动停止后30秒或最后一次<=1x导星后10分钟关闭电源  选项

#define AXIS2_SENSE_HOME              OFF //    OFF, HIGH或LOW启用并设置顺时针归零位置（从上方看） 选项
#define AXIS2_SENSE_LIMIT_MIN LIMIT_SENSE // ...NSE, HIGH或LOW状态限位开关停止运动                  选项
#define AXIS2_SENSE_LIMIT_MAX LIMIT_SENSE // ...NSE, HIGH或LOW状态限位开关停止运动                  选项

// WiFi Station 配置
#define STA1_SSID          "openwrt"        // WiFi 名称
#define STA1_PASSWORD      "daying923"      // WiFi 密码
#define STA1_DHCP_ENABLED  true             // 使用 DHCP 自动获取 IP

// MOUNT -------------------------------------------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Mount#MOUNT
#define MOUNT_TYPE                    GEM //    GEM, GEM         German Equatorial Mount, etc. that need meridian flips.     <-Req'd
                                          //         GEM_TA      GEM w/tangent arm Declination
                                          //         GEM_TAC     GEM w/tangent arm Declination and geometry correction
                                          //         FORK        Fork Mount
                                          //         FORK_TA     FORK w/tangent arm Declination
                                          //         FORK_TAC    FORK w/tangent arm Declination and geometry correction
                                          //         ALTAZM      Altitude/Azimuth Mount, Dobsonians, etc.
                                          //         ALTAZM_UNL  ALTAZM w/unlimited Azimuth motion

#define MOUNT_ALTERNATE_ORIENTATION   OFF //    OFF, ON Enables Meridian Flips for FORK mounts and passing through the        Option
                                          //         Zenith for ALTAZM mounts.  GEM mode ignores this setting.

#define MOUNT_STARTUP_MODE        SA_AUTO // ..AUTO, SA_STRICT, or SA_PERMISSIVE. Controls when startup trust is granted.     Option
                                          //         SA_AUTO keeps legacy immediate goto only when no absolute position source
                                          //         is present and coordinate memory is OFF.

#define MOUNT_COORDS          TOPOCENTRIC // ...RIC, Applies refraction to coordinates to/from OnStep, except exactly         Infreq
                                          //              at the poles. Use TOPO_STRICT to apply refraction even in that case.
                                          //              Use OBSERVED_PLACE for no refraction.

#define MOUNT_COORDS_MEMORY           OFF //    OFF, ON Remembers approximate mount coordinates across power cycles.          Option
                                          //         Requires FRAM NV memory and the mount must not move while powered down.

#define MOUNT_ENABLE_IN_STANDBY       OFF //    OFF, ON Enables mount motor drivers while in standby.                         Infreq

// TIME AND LOCATION ---------------------------------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Mount#TLS
#define TIME_LOCATION_SOURCE          GPS //    OFF, DS3231 (I2C,) SD3031 (I2C,) TEENSY (T3.2 etc,) GPS, or NTP source.       Option
                                          //         Provides Date/Time, and if available, PPS & Lat/Long also.
#define TIME_LOCATION_PPS_SENSE       OFF //    OFF, HIGH senses PPS (pulse per second,) signal rising edge, or use LOW for   Option
                                          //         falling edge, or use BOTH for rising and falling edges.

// STATUS ------------------------------------------------------ see https://onstep.groups.io/g/main/wiki/Configuration_Mount#STATUS
#define STATUS_MOUNT_LED              OFF //    OFF, ON Flashes proportional to rate of movement or solid on for slews.       Option
#define STATUS_BUZZER                 OFF //    OFF, ON, n. Where n=100..6000 (Hz freq.) for speaker. ON for piezo buzzer.    Option
#define STATUS_BUZZER_DEFAULT         OFF //    OFF, ON starts w/buzzer sound enabled.                                        Option
#define STATUS_BUZZER_MEMORY          OFF //    OFF, ON to remember buzzer sound setting across power cycles.                 Option

// ST4 INTERFACE -------------------------------------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Mount#ST4
// *** It is up to you to verify the interface meets the electrical specifications of any connected device, use at your own risk ***
#define ST4_INTERFACE                 OFF //    OFF, ON enables interface. <= 1X guides unless hand control mode.             Option
                                          //         During goto btn press: aborts slew or continue meridian flip pause home
#define ST4_HAND_CONTROL               ON //     ON, ON for hand controller special features and SHC support.                 Option
                                          //         Hold [E]+[W] btns >2s: Guide rate   [E]-  [W]+  [N] trk on/off [S] sync
                                          //         Hold [N]+[S] btns >2s: Usr cat item [E]-  [W]+  [N] goto [S] snd on/off
#define ST4_HAND_CONTROL_FOCUSER       ON //     ON, ON alternate to above: Focuser move [E]f1 [W]f2 [N]-     [S]+            Option

// GUIDING BEHAVIOUR ------------------------------------------ see https://onstep.groups.io/g/main/wiki/Configuration_Mount#GUIDING
#define GUIDE_TIME_LIMIT               10 //     10, n. Time limit n=0..120 seconds. Use 0 to disable.                        Adjust
#define GUIDE_DISABLE_BACKLASH        OFF //    OFF, Disable backlash takeup during guiding at <= 1X.                         Option

// LIMITS ------------------------------------------------------ see https://onstep.groups.io/g/main/wiki/Configuration_Mount#LIMITS
#define LIMIT_SENSE                   OFF //    OFF, HIGH or LOW state on limit sense switch stops movement.                  Option
#define LIMIT_STRICT                  OFF //    OFF, disables limits until unpark goto or sync. ON enables limits at startup. Option
                                          //         note that ON also disables all motion until date/time are set.

// PARKING ---------------------------------------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Mount#PARKING
#define PARK_SENSE                    OFF //    OFF, HIGH or LOW state indicates mount is in the park orientation.            Option
#define PARK_SIGNAL                   OFF //    OFF, HIGH or LOW state park input signal triggers parking.                    Option
#define PARK_STATUS                   OFF //    OFF, signals with a HIGH or LOW state when successfully parked.               Option

// PEC ------------------------------------------------------------ see https://onstep.groups.io/g/main/wiki/Configuration_Mount#PEC
#define PEC_STEPS_PER_WORM_ROTATION     0 //      0, n. Steps per worm rotation (0 disables else 720 sec buffer allocated.)  <-Req'd
                                          //         n = (AXIS1_STEPS_PER_DEGREE*360)/reduction_final_stage

#define PEC_SENSE                     OFF //    OFF, HIGH. Senses the PEC signal rising edge or use LOW for falling edge.     Option
                                          //         Ignored in ALTAZM mode.
#define PEC_BUFFER_SIZE_LIMIT         720 //    720, Seconds of PEC buffer allowed.                                           Infreq

// TRACKING BEHAVIOUR ---------------------------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Mount#TRACKING
#define TRACK_BACKLASH_RATE            20 //     20, n. Where n=2..50 (x sidereal rate) during backlash takeup.               Option
                                          //         Too fast motors stall/gears slam or too slow and sluggish in backlash.
#define TRACK_AUTOSTART               OFF //    OFF, ON Start with tracking enabled.                                          Option
#define TRACK_COMPENSATION_DEFAULT    OFF //    OFF, No compensation or REFRACTION, REFRACTION_DUAL, MODEL, MODEL_DUAL.       Option
#define TRACK_COMPENSATION_MEMORY     OFF //    OFF, ON Remembers refraction/pointing model compensated tracking settings.    Option

// SLEWING BEHAVIOUR ------------------------------------------ see https://onstep.groups.io/g/main/wiki/Configuration_Mount#SLEWING
#define SLEW_RATE_BASE_DESIRED        1 //    0.5, n. Desired slew rate in deg/sec. Adjustable at run-time from            <-Req'd
                                          //         1/2 to 2x this rate, and as performace considerations require.
#define SLEW_RATE_MEMORY              OFF //    OFF, ON Remembers rates set across power cycles.                              Option
#define SLEW_ACCELERATION_DIST        5.0 //    5.0, n, (degrees.) Approx. distance for acceleration (and deceleration.)      Adjust
#define SLEW_RAPID_STOP_DIST          2.0 //    2.0, n, (degrees.) Approx. distance required to stop when a slew              Adjust
                                          //         is aborted or a limit is exceeded.
#define GOTO_FEATURE                   ON //     ON, Use OFF to disable mount Goto features.                                  Infreq
#define GOTO_OFFSET                  0.25 //   0.25, Offset in deg's for goto target unidirectional approach, 0.0 disables    Adjust
#define GOTO_OFFSET_ALIGN             OFF //    OFF, ON skips final phase of goto for align stars so user tends to approach   Option
                                          //         from the correct direction when centering.

// PIER SIDE BEHAVIOUR --------------------------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Mount#PIERSIDE
#define MFLIP_SKIP_HOME               OFF //    OFF, ON Goto directly to the destination without visiting home position.      Option
#define MFLIP_AUTOMATIC_DEFAULT       OFF //    OFF, ON Start with automatic meridian flips enabled.                          Option
#define MFLIP_AUTOMATIC_MEMORY        OFF //    OFF, ON Remember automatic meridian flip setting across power cycles.         Option
#define MFLIP_PAUSE_HOME_DEFAULT      OFF //    OFF, ON Start with meridian flip pause at home enabed.                        Infreq
#define MFLIP_PAUSE_HOME_MEMORY       OFF //    OFF, ON Remember meridian flip pause at home setting across power cycles.     Infreq

#define PIER_SIDE_SYNC_CHANGE_SIDES   OFF //    OFF, ON Allows sync to change pier side, for GEM mounts.                      Option
#define PIER_SIDE_PREFERRED_DEFAULT  BEST //   BEST, BEST Stays on current side if possible. EAST or WEST switch if possible. Option
                                          //         AUTOMATIC prefers west nearer the under pole meridian or east otherwise. Option
#define PIER_SIDE_PREFERRED_MEMORY    OFF //    OFF, ON Remember preferred pier side setting across power cycles.             Option

// ALIGN -------------------------------------------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Mount#ALIGN
#define ALIGN_AUTO_HOME               OFF //    OFF, ON uses home switches to find home first when starting an align.         Option
#define ALIGN_MODEL_MEMORY            OFF //    OFF, ON Restores any pointing model saved in NV at startup.                   Option
#define ALIGN_MAX_STARS              AUTO //   AUTO, Uses HAL specified default (either 6 or 9 stars.)                        Infreq
                                          //         Or use n. Where n=1 (for Sync only) or 3 to 9 (for Goto Assist.)

// =================================================================================================================================
// 旋转器 (ROTATOR) =========================================================================================================================

// 电机驱动型号 (步进/方向 和 伺服) 许多驱动有特定要求，请参考以下链接了解详细信息
// 常用驱动: A4988, DRV8825, LV8729, S109, TMC2130S 等

// 轴3 - 旋转器 ---------------------------------------------------- 参见 https://onstep.groups.io/g/main/wiki/Configuration_Rotator
#define AXIS3_DRIVER_MODEL            OFF //    OFF, 填写电机驱动型号(如上)以激活旋转器                选项
#define AXIS3_SLEW_RATE_BASE_DESIRED  1.0 //    1.0, n. 期望的转动速率(度/秒)。运行时可在            <-必填
                                          //         1/2到2倍之间调整，并根据性能考虑进行调整

// 如果启用了运行时轴设置，以下部分的更改将被忽略（在SWS网页中禁用或清除NV/EEPROM）：
// \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/
#define AXIS3_STEPS_PER_DEGREE       64.0 //   64.0, n. 旋转器/去旋转器每度的步数                    调整
                                          //         经纬仪去旋转: n = (圆周像素数 * 2)/360, 最小值
#define AXIS3_REVERSE                 OFF //    OFF, ON 反转运动方向，或反转接线来纠正    选项
#define AXIS3_LIMIT_MIN                 0 //      0, n. n=-360..0 (度) 允许的最小旋转器角度             少用
#define AXIS3_LIMIT_MAX               360 //    360, n. n=0..360 (度) 允许的最大旋转器角度              少用

#define AXIS3_DRIVER_MICROSTEPS       OFF //    OFF, n. 默认微步模式                                               选项
#define AXIS3_DRIVER_MICROSTEPS_GOTO  OFF //    OFF, n. Goto微步模式覆盖。OFF使用上述_DRIVER_MICROSTEPS的值            选项

// 适用于 TMC2130, TMC5160, TMC2209, TMC2226 步进/方向驱动型号：
#define AXIS3_DRIVER_IHOLD            OFF //    OFF, n, (mA) 静止时的保持电流。OFF使用IRUN/2.0                    选项
#define AXIS3_DRIVER_IRUN             OFF //    OFF, n, (mA) 默认运行电流，根据电机/驱动等设置        选项
#define AXIS3_DRIVER_IGOTO            OFF //    OFF, n, (mA) 快速转动时的运行电流覆盖。OFF使用IRUN                  选项
// /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /

#define AXIS3_DRIVER_STATUS           OFF //    OFF, ON, HIGH或LOW。用于驱动状态信息/故障检测               选项

#define AXIS3_DRIVER_DECAY            OFF //    OFF, 跟踪衰减模式默认覆盖。TMC默认是STEALTHCHOP(静音模式)        少用
#define AXIS3_DRIVER_DECAY_GOTO       OFF //    OFF, Goto衰减模式默认覆盖。TMC默认是SPREADCYCLE(扩频模式)            少用

#define AXIS3_POWER_DOWN              OFF //    OFF, ON 运动停止后30秒关闭电源                           选项

#define AXIS3_SENSE_HOME              OFF //    OFF, HIGH或LOW启用并设置顺时针归零位置（从上方看） 选项
#define AXIS3_SENSE_LIMIT_MIN         OFF //    OFF, HIGH或LOW状态限位开关停止运动                  选项
#define AXIS3_SENSE_LIMIT_MAX         OFF //    OFF, HIGH或LOW状态限位开关停止运动                  选项

// =================================================================================================================================
// 调焦器 (FOCUSERS) ========================================================================================================================

// 电机驱动型号 (步进/方向 和 伺服) 许多驱动有特定要求，请参考以下链接了解详细信息
// 常用驱动: A4988, DRV8825, LV8729, S109, TMC2130S 等

// 轴4 - 调焦器1 -------------------------------------------------- 参见 https://onstep.groups.io/g/main/wiki/Configuration_Focuser
#define AXIS4_DRIVER_MODEL            OFF //    OFF, 填写电机驱动型号(如上)以激活调焦器                选项
#define AXIS4_SLEW_RATE_BASE_DESIRED  500 //    500, n. n=200..5000 (微米/秒)。运行时可调整        <-必填
                                          //         1/2到2倍之间，并根据性能考虑进行调整
#define AXIS4_SLEW_RATE_MINIMUM        20 //     20, n. n=5..200 (微米/秒) 最小微米/秒                        调整

// 如果启用了运行时轴设置，以下部分的更改将被忽略（在SWS网页中禁用或清除NV/EEPROM）：
// \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/
#define AXIS4_STEPS_PER_MICRON        0.5 //    0.5, n. 每微米步数。通过测试或其他方式确定      调整
#define AXIS4_REVERSE                 OFF //    OFF, ON 反转运动方向，或反转接线来纠正    选项
#define AXIS4_LIMIT_MIN                 0 //      0, n. n=0..500 (毫米) 允许的最小位置               调整
#define AXIS4_LIMIT_MAX                50 //     50, n. n=0..500 (毫米) 允许的最大位置               调整

#define AXIS4_DRIVER_MICROSTEPS       OFF //    OFF, n. 默认微步模式                                               选项
#define AXIS4_DRIVER_MICROSTEPS_GOTO  OFF //    OFF, n. Goto微步模式覆盖。OFF使用上述_DRIVER_MICROSTEPS的值            选项

// 适用于 TMC2130, TMC5160, TMC2209, TMC2226 步进/方向驱动型号：
#define AXIS4_DRIVER_IHOLD            OFF //    OFF, n, (mA) 静止时的保持电流。OFF使用IRUN/2.0                    选项
#define AXIS4_DRIVER_IRUN             OFF //    OFF, n, (mA) 默认运行电流，根据电机/驱动等设置        选项
#define AXIS4_DRIVER_IGOTO            OFF //    OFF, n, (mA) 快速转动时的运行电流覆盖。OFF使用IRUN                  选项
// /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /

#define AXIS4_DRIVER_STATUS           OFF //    OFF, ON, HIGH或LOW。用于驱动状态信息/故障检测               选项

#define AXIS4_DRIVER_DECAY            OFF //    OFF, 跟踪衰减模式默认覆盖。TMC默认是STEALTHCHOP(静音模式)        少用
#define AXIS4_DRIVER_DECAY_GOTO       OFF //    OFF, Goto衰减模式默认覆盖。TMC默认是SPREADCYCLE(扩频模式)            少用

#define AXIS4_POWER_DOWN              OFF //    OFF, ON 运动停止后30秒关闭电源                           选项

#define AXIS4_SENSE_HOME              OFF //    OFF, HIGH或LOW启用并设置顺时针归零位置（从上方看） 选项
#define AXIS4_SENSE_LIMIT_MIN         OFF //    OFF, HIGH或LOW状态限位开关停止运动                  选项
#define AXIS4_SENSE_LIMIT_MAX         OFF //    OFF, HIGH或LOW状态限位开关停止运动                  选项

// 轴5 - 调焦器2 -----------------------------------------------------------------------------------------------------------------
// 最多可存在6个调焦器 (AXIS4 到 AXIS9) 只需复制上述调焦器1的文本并将 AXIS5_ 重命名为调焦器2，依此类推

// 调焦器温度 ---------------------------------------------- 参见 https://onstep.groups.io/g/main/wiki/Configuration_Focuser
#define FOCUSER_TEMPERATURE           OFF //    OFF, THERMISTOR 或 n. n为ds18b20序列号用于调焦器温度            调整

// =================================================================================================================================
// AUXILIARY FEATURES ==============================================================================================================

// FEATURES ------------------------------------------------------------- see https://onstep.groups.io/g/main/wiki/Configuration_Aux
// Note: Temporarily set DEBUG mode to VERBOSE and use "FEATURE1_TEMP DS1820" to list the DS18B20 device serial numbers.

#define FEATURE1_PURPOSE            SWITCH //    OFF, SWITCH, MOMENTARY_SWITCH, ANALOG_OUT, DEW_HEATER, INTERVALOMETER.        Option
#define FEATURE1_NAME             "BRAKE1" // "FE..", Name of feature being controlled.                                        Adjust
#define FEATURE1_TEMP                 OFF //    OFF, THERMISTOR or n. Where n is the ds18b20 s/n. For DEW_HEATER temperature. Adjust
#define FEATURE1_PIN                   21 //    OFF, AUX for auxiliary pin, n. Where n is the pin#.                           Adjust
#define FEATURE1_VALUE_DEFAULT        ON  //    OFF, ON, n. Where n=0..255 for ANALOG_OUT purpose.                            Adjust
#define FEATURE1_VALUE_MEMORY         OFF //    OFF, ON remembers SWITCH, ANALOG_OUT, DEW_HEATER state across power cycles.   Adjust
#define FEATURE1_ON_STATE             LOW //   HIGH, LOW to invert so "ON" is 0V and "OFF" is Vcc (3.3V usually.)             Adjust

#define FEATURE2_PURPOSE              OFF //    OFF, SWITCH, MOMENTARY_SWITCH, ANALOG_OUT, DEW_HEATER, INTERVALOMETER.        Option
#define FEATURE2_NAME          "FEATURE2" // "FE..", Name of feature being controlled.                                        Adjust
#define FEATURE2_TEMP                 OFF //    OFF, THERMISTOR or n. Where n is the ds18b20 s/n. For DEW_HEATER temperature. Adjust
#define FEATURE2_PIN                  OFF //    OFF, AUX for auxiliary pin, n. Where n is the pin#.                           Adjust
#define FEATURE2_VALUE_DEFAULT        OFF //    OFF, ON, n. Where n=0..255 for ANALOG_OUT purpose.                            Adjust
#define FEATURE2_VALUE_MEMORY         OFF //    OFF, ON remembers SWITCH, ANALOG_OUT, DEW_HEATER state across power cycles.   Adjust
#define FEATURE2_ON_STATE            HIGH //   HIGH, LOW to invert so "ON" is 0V and "OFF" is Vcc (3.3V usually.)             Adjust

#define FEATURE3_PURPOSE              OFF //    OFF, SWITCH, MOMENTARY_SWITCH, ANALOG_OUT, DEW_HEATER, INTERVALOMETER.        Option
#define FEATURE3_NAME          "FEATURE3" // "FE..", Name of feature being controlled.                                        Adjust
#define FEATURE3_TEMP                 OFF //    OFF, THERMISTOR or n. Where n is the ds18b20 s/n. For DEW_HEATER temperature. Adjust
#define FEATURE3_PIN                  OFF //    OFF, AUX for auxiliary pin, n. Where n is the pin#.                           Adjust
#define FEATURE3_VALUE_DEFAULT        OFF //    OFF, ON, n. Where n=0..255 for ANALOG_OUT purpose.                            Adjust
#define FEATURE3_VALUE_MEMORY         OFF //    OFF, ON remembers SWITCH, ANALOG_OUT, DEW_HEATER state across power cycles.   Adjust
#define FEATURE3_ON_STATE            HIGH //   HIGH, LOW to invert so "ON" is 0V and "OFF" is Vcc (3.3V usually.)             Adjust

#define FEATURE4_PURPOSE              OFF //    OFF, SWITCH, MOMENTARY_SWITCH, ANALOG_OUT, DEW_HEATER, INTERVALOMETER.        Option
#define FEATURE4_NAME          "FEATURE4" // "FE..", Name of feature being controlled.                                        Adjust
#define FEATURE4_TEMP                 OFF //    OFF, THERMISTOR or n. Where n is the ds18b20 s/n. For DEW_HEATER temperature. Adjust
#define FEATURE4_PIN                  OFF //    OFF, AUX for auxiliary pin, n. Where n is the pin#.                           Adjust
#define FEATURE4_VALUE_DEFAULT        OFF //    OFF, ON, n. Where n=0..255 for ANALOG_OUT purpose.                            Adjust
#define FEATURE4_VALUE_MEMORY         OFF //    OFF, ON remembers SWITCH, ANALOG_OUT, DEW_HEATER state across power cycles.   Adjust
#define FEATURE4_ON_STATE            HIGH //   HIGH, LOW to invert so "ON" is 0V and "OFF" is Vcc (3.3V usually.)             Adjust

#define FEATURE5_PURPOSE              OFF //    OFF, SWITCH, MOMENTARY_SWITCH, ANALOG_OUT, DEW_HEATER, INTERVALOMETER.        Option
#define FEATURE5_NAME          "FEATURE5" // "FE..", Name of feature being controlled.                                        Adjust
#define FEATURE5_TEMP                 OFF //    OFF, THERMISTOR or n. Where n is the ds18b20 s/n. For DEW_HEATER temperature. Adjust
#define FEATURE5_PIN                  OFF //    OFF, AUX for auxiliary pin, n. Where n is the pin#.                           Adjust
#define FEATURE5_VALUE_DEFAULT        OFF //    OFF, ON, n. Where n=0..255 for ANALOG_OUT purpose.                            Adjust
#define FEATURE5_VALUE_MEMORY         OFF //    OFF, ON remembers SWITCH, ANALOG_OUT, DEW_HEATER state across power cycles.   Adjust
#define FEATURE5_ON_STATE            HIGH //   HIGH, LOW to invert so "ON" is 0V and "OFF" is Vcc (3.3V usually.)             Adjust

#define FEATURE6_PURPOSE              OFF //    OFF, SWITCH, MOMENTARY_SWITCH, ANALOG_OUT, DEW_HEATER, INTERVALOMETER.        Option
#define FEATURE6_NAME          "FEATURE6" // "FE..", Name of feature being controlled.                                        Adjust
#define FEATURE6_TEMP                 OFF //    OFF, THERMISTOR or n. Where n is the ds18b20 s/n. For DEW_HEATER temperature. Adjust
#define FEATURE6_PIN                  OFF //    OFF, AUX for auxiliary pin, n. Where n is the pin#.                           Adjust
#define FEATURE6_VALUE_DEFAULT        OFF //    OFF, ON, n. Where n=0..255 for ANALOG_OUT purpose.                            Adjust
#define FEATURE6_VALUE_MEMORY         OFF //    OFF, ON remembers SWITCH, ANALOG_OUT, DEW_HEATER state across power cycles.   Adjust
#define FEATURE6_ON_STATE            HIGH //   HIGH, LOW to invert so "ON" is 0V and "OFF" is Vcc (3.3V usually.)             Adjust

#define FEATURE7_PURPOSE              OFF //    OFF, SWITCH, MOMENTARY_SWITCH, ANALOG_OUT, DEW_HEATER, INTERVALOMETER.        Option
#define FEATURE7_NAME          "FEATURE7" // "FE..", Name of feature being controlled.                                        Adjust
#define FEATURE7_TEMP                 OFF //    OFF, THERMISTOR or n. Where n is the ds18b20 s/n. For DEW_HEATER temperature. Adjust
#define FEATURE7_PIN                  OFF //    OFF, AUX for auxiliary pin, n. Where n is the pin#.                           Adjust
#define FEATURE7_VALUE_DEFAULT        OFF //    OFF, ON, n. Where n=0..255 for ANALOG_OUT purpose.                            Adjust
#define FEATURE7_VALUE_MEMORY         OFF //    OFF, ON remembers SWITCH, ANALOG_OUT, DEW_HEATER state across power cycles.   Adjust
#define FEATURE7_ON_STATE            HIGH //   HIGH, LOW to invert so "ON" is 0V and "OFF" is Vcc (3.3V usually.)             Adjust

#define FEATURE8_PURPOSE              OFF //    OFF, SWITCH, MOMENTARY_SWITCH, ANALOG_OUT, DEW_HEATER, INTERVALOMETER.        Option
#define FEATURE8_NAME          "FEATURE8" // "FE..", Name of feature being controlled.                                        Adjust
#define FEATURE8_TEMP                 OFF //    OFF, THERMISTOR or n. Where n is the ds18b20 s/n. For DEW_HEATER temperature. Adjust
#define FEATURE8_PIN                  OFF //    OFF, AUX for auxiliary pin, n. Where n is the pin#.                           Adjust
#define FEATURE8_VALUE_DEFAULT        OFF //    OFF, ON, n. Where n=0..255 for ANALOG_OUT purpose.                            Adjust
#define FEATURE8_VALUE_MEMORY         OFF //    OFF, ON remembers SWITCH, ANALOG_OUT, DEW_HEATER state across power cycles.   Adjust
#define FEATURE8_ON_STATE            HIGH //   HIGH, LOW to invert so "ON" is 0V and "OFF" is Vcc (3.3V usually.)             Adjust

// ---------------------------------------------------------------------------------------------------------------------------------
#define FileVersionConfig 6
#include "Extended.config.h"
