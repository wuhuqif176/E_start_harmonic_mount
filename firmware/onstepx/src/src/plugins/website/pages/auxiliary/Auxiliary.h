// -----------------------------------------------------------------------------------
// Telescope auxiliary feature related functions 
#pragma once

#include "../htmlHeaders.h"
#include "../htmlMessages.h"
#include "../htmlScripts.h"

const char html_auxOnSwitch[] PROGMEM = 
"<button id='sw%d_on' class='btns_right' style='line-height: 1.2rem' onpointerdown=\"s('x%dv1','1')\" type='button'>" L_ON "</button>";
const char html_auxOffSwitch[] PROGMEM = 
"<button id='sw%d_off' class='btns_left' style='line-height: 1.2rem' onpointerdown=\"s('x%dv1','0')\" type='button'>" L_OFF "</button>\n";

const char html_auxStartStop1[] PROGMEM = "<button onpointerdown=\"s('";
const char html_auxStartStop2[] PROGMEM = "','1')\" type='button'>" L_START "</button><button onpointerdown=\"s('";
const char html_auxStartStop3[] PROGMEM = "','0')\" type='button'>" L_STOP "</button>\n";

const char html_auxAnalog[] PROGMEM ="<input style='width: 12em; background: #111' type='range' min='0' max='255' value='";
#if UNITS == METRIC
  const char html_auxHeater[] PROGMEM ="<input style='width: 12em; background: #111' type='range' min='-10' max='40' value='";
  #define DEW_HEATER_CONTROL_SCALE 2.0F
#else
  const char html_auxHeater[] PROGMEM ="<input style='width: 12em; background: #111' type='range' min='-9' max='36' value='";
  #define DEW_HEATER_CONTROL_SCALE 1.0F
#endif
const char html_auxExposure[] PROGMEM ="<input style='width: 12em; background: #111' type='range' min='0' max='255' value='";
const char html_auxDelay[] PROGMEM ="<input style='width: 12em; background: #111' type='range' min='10' max='255' value='";
const char html_auxCount[] PROGMEM ="<input style='width: 12em; background: #111' type='range' min='1' max='255' value='";
const char html_auxAuxE[] PROGMEM = "</div>\n";

const char html_auxEnd[] PROGMEM = "<br />\n";

#if CH224K_ENABLE == ON
// CH224K PD 诱骗电源 tile - 匹配项目 tile 风格，修复布局错位
const char html_ch224k_beg[] PROGMEM = 
"<div class='b1' style='width: 27em; min-height: 12em;'>"
"<div style='float: left;'>PD Power (CH224K):</div>"
"<div style='float: right; text-align: right;' class='c' id='ch224k_status'>等待</div>"
"<br /><hr />"
"<div style='float: left; text-align: right; width: 8em; height: 2em; line-height: 2em'>协议:</div>"
"<div style='float: left; width: 14em; height: 2em; line-height: 2em'><span id='ch224k_protocol'>-</span></div>"
"<div style='float: left; width: 4em; height: 2em; line-height: 2em'></div>"
"<br class='clear' />\n"
"<div style='float: left; text-align: right; width: 8em; height: 2em; line-height: 2em'>电压:</div>"
"<div style='float: left; width: 14em; height: 2em; line-height: 2em'>"
"<select id='ch224k_voltage' onchange='setCh224kVoltage(this.value)' style='width: 10.6em; margin: 3px; text-align-last: center;'>";

const char html_ch224k_end[] PROGMEM = 
"</select>"
"</div>"
"<div style='float: left; width: 4em; height: 2em; line-height: 2em'><span id='ch224k_voltage_val'>-</span></div>"
"<br class='clear' />\n"
"<div style='float: left; text-align: right; width: 8em; height: 2em; line-height: 2em'>PDO 电流:</div>"
"<div style='float: left; width: 14em; height: 2em; line-height: 2em'><span id='ch224k_pdo_current'>-</span>mA</div>"
"<div style='float: left; width: 4em; height: 2em; line-height: 2em'></div>"
"<br class='clear' />\n"
"<div style='float: left; text-align: right; width: 8em; height: 2em; line-height: 2em'>协商电流:</div>"
"<div style='float: left; width: 14em; height: 2em; line-height: 2em'><span id='ch224k_current'>-</span>mA</div>"
"<div style='float: left; width: 4em; height: 2em; line-height: 2em'></div>"
"<br class='clear' />\n"
"<div style='float: left; text-align: right; width: 8em; height: 2em; line-height: 2em'>PDO 数量:</div>"
"<div style='float: left; width: 14em; height: 2em; line-height: 2em'><span id='ch224k_pdo'>-</span></div>"
"<div style='float: left; width: 4em; height: 2em; line-height: 2em'></div>"
"<br class='clear' />\n"
"<div style='float: left; text-align: right; width: 8em; height: 2em; line-height: 2em'>操作:</div>"
"<div style='float: left; width: 14em; height: 2em; line-height: 2em'>"
"<button id='ch224k_reconnect_btn' onclick='reconnectCh224k()' type='button' style='background: #E02020; font-weight: bold; border-radius: 5px; margin: 2px; padding: 4px 8px;'>重新连接</button>"
"</div>"
"<div style='float: left; width: 4em; height: 2em; line-height: 2em'></div>"
"<br class='clear' />\n"
"</div>\n";

const char html_ch224k_script[] PROGMEM = 
"<script>\n"
"function setCh224kVoltage(v){"
"  var xhr=new XMLHttpRequest();"
"  xhr.open('GET','/ch224k-ajax-set.txt?v='+v,true);"
"  xhr.send();"
"}\n"
"function reconnectCh224k(){"
"  var btn=document.getElementById('ch224k_reconnect_btn');"
"  if(btn){btn.disabled=true;btn.innerHTML='重连中...';}"
"  var xhr=new XMLHttpRequest();"
"  xhr.open('GET','/ch224k-ajax-reconnect.txt',true);"
"  xhr.onload=function(){"
"    if(btn){btn.disabled=false;btn.innerHTML='重新连接';}"
"  };"
"  xhr.send();"
"}\n"
"</script>\n";

// AJAX 处理器声明
extern void ch224kAjaxSet();
extern void ch224kAjaxReconnect();
#endif