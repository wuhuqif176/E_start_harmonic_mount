/* ---------------------------------------------------------------------------------------------------------------------------------
 * User plugins for OnStepX
 *
 * For each entery below one must specify the class instance name and #include the class header file.
 *
 * Each plugin should have a directory that contains all of its files, which gets dropped into to the /src/plugins directory.
 * The plugin main class instance name should match the directory name.
 * The plugin main class must have a "void init();" method for OnStepX to call when it starts up.
 * 
 * ---------------------------------------------------------------------------------------------------------------------------------
*/

// =================================================================================================================================

// *** 注释掉上面的 PLUGIN1，并取消注释以下两行以启用示例插件 ***
//#define PLUGIN1                    sample //    OFF, 指定要启用的类实例（与插件目录名称相同）.    Option
//#include "sample/Sample.h"                //        指定要包含类的头文件.

#define PLUGIN1                       website //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
#include "website/Website.h"            //         Specify the header file to include the class.
#define PLUGIN1_COMMAND_PROCESSING    OFF //    关闭，对于允许命令处理的插件，请设置为开启

#define PLUGIN2                       ch224k //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
#include "ch224k/CH224K.h"              //         Specify the header file to include the class.
#define PLUGIN2_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing

#define PLUGIN3                       OFF //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "plugin3/Name.h"               //         Specify the header file to include the class.
#define PLUGIN3_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing

#define PLUGIN4                       OFF //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "plugin4/Name.h"               //         Specify the header file to include the class.
#define PLUGIN4_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing

#define PLUGIN5                       OFF //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "plugin5/Name.h"               //         Specify the header file to include the class.
#define PLUGIN5_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing

#define PLUGIN6                       OFF //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "plugin6/Name.h"               //         Specify the header file to include the class.
#define PLUGIN6_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing

#define PLUGIN7                       OFF //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "plugin7/Name.h"               //         Specify the header file to include the class.
#define PLUGIN7_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing

#define PLUGIN8                       OFF //    OFF, Specify the class instance (same as plugin directory name) to enable.    Option
//#include "plugin8/Name.h"               //         Specify the header file to include the class.
#define PLUGIN8_COMMAND_PROCESSING    OFF //    OFF, Set to ON for plugins that allow command processing
