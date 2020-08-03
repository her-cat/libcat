/*
  +--------------------------------------------------------------------------+
  | libcat                                                                   |
  +--------------------------------------------------------------------------+
  | Licensed under the Apache License, Version 2.0 (the "License");          |
  | you may not use this file except in compliance with the License.         |
  | You may obtain a copy of the License at                                  |
  | http://www.apache.org/licenses/LICENSE-2.0                               |
  | Unless required by applicable law or agreed to in writing, software      |
  | distributed under the License is distributed on an "AS IS" BASIS,        |
  | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. |
  | See the License for the specific language governing permissions and      |
  | limitations under the License. See accompanying LICENSE file.            |
  +--------------------------------------------------------------------------+
  | Author: Twosee <twose@qq.com>                                            |
  +--------------------------------------------------------------------------+
 */

#ifndef CAT_PROCESS_H
#define CAT_PROCESS_H
#ifdef __cplusplus
extern "C" {
#endif

#include "cat.h"

typedef uv_pid_t cat_pid_t;

CAT_API cat_pid_t cat_process_get_id(void);
CAT_API cat_pid_t cat_process_get_parent_id(void);

/* it may take ownership of the memory that argv points to */
CAT_API char **cat_process_setup_args(int argc, char** argv);

#define CAT_PROCESS_TITLE_BUFFER_SIZE 512
/* we must call process_setup_args() before using title releated APIs  */
CAT_API char *cat_process_get_title(char* buffer, size_t size); CAT_MAY_FREE
CAT_API cat_bool_t cat_process_set_title(const char* title);

#ifdef __cplusplus
}
#endif
#endif  /* CAT_PROCESS_H */
