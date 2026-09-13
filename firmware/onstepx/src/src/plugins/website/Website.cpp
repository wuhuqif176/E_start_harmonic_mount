// Website plugin

#include "Website.h"
#include "Common.h"
#include "pages/Pages.h"
#include "pages/auxiliary/Auxiliary.h"

TaskHandle_t _webSvrTask;
void pollWebSvr(void * parameter) {
  for(;;) {
    www.handleClient();
    state.poll();
  }
}

void Website::init() {
  VLF("MSG: Website Plugin");

  VLF("MSG: Set webpage handlers");
  www.on("/index.htm", handleRoot);
  www.on("/index-ajax-get.txt", indexAjaxGet);
  www.on("/index.txt", indexAjax);

  www.on("/mount.htm", handleMount);
  www.on("/mount-ajax-get.txt", mountAjaxGet);
  www.on("/mount-ajax.txt", mountAjax);
  www.on("/libraryHelp.htm", handleLibraryHelp);

  www.on("/rotator.htm", handleRotator);
  www.on("/rotator-ajax-get.txt", rotatorAjaxGet);
  www.on("/rotator-ajax.txt", rotatorAjax);

  www.on("/focuser.htm", handleFocuser);
  www.on("/focuser-ajax-get.txt", focuserAjaxGet);
  www.on("/focuser-ajax.txt", focuserAjax);

  www.on("/auxiliary.htm", handleAux);
  www.on("/auxiliary-ajax-get.txt", auxAjaxGet);
  www.on("/auxiliary-ajax.txt", auxAjax);

#if CH224K_ENABLE == ON
  // CH224K PD 诱骗芯片 AJAX 接口（必须注册，否则前端设置电压/重连请求将 404）
  www.on("/ch224k-ajax-set.txt", ch224kAjaxSet);
  www.on("/ch224k-ajax-reconnect.txt", ch224kAjaxReconnect);
#endif

  www.on("/net.htm", handleNetwork);

  www.on("/", handleRoot);
  
  www.onNotFound(handleNotFound);

  VLF("MSG: Starting port 80 web server");
  www.begin();

  // allow time for the background servers to come up
  delay(2000);

  if (status.onStepFound) {
    status.update();
    delay(100);
  }

  state.init();

  VLF("MSG: Setup, starting web server FreeRTOS task (priority 1)");
  xTaskCreatePinnedToCore(pollWebSvr,"WebSvrTask", 10000, NULL, 1, &_webSvrTask, 0);

  VLF("MSG: Website Plugin ready");
}

Website website;
