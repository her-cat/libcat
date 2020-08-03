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

#include "cat_process.h"

CAT_API cat_pid_t cat_process_get_id(void)
{
    cat_pid_t id;

    id = uv_os_getpid();

    if (unlikely(id < 0)) {
        cat_update_last_error_of_syscall("Process get id failed");
    }

    return id;
}

CAT_API cat_pid_t cat_process_get_parent_id(void)
{
    cat_pid_t parent_id;

    parent_id = uv_os_getppid();

    if (unlikely(parent_id < 0)) {
        cat_update_last_error_of_syscall("Process get parent id failed");
    }

    return parent_id;
}

static cat_bool_t cat_process_args_resgitered = cat_false;

CAT_API char **cat_process_setup_args(int argc, char** argv)
{
    if (cat_process_args_resgitered) {
        cat_core_error(PROCESS, "API misuse: process_setup_args() should be called only once");
    }
    cat_process_args_resgitered = cat_true;

    return uv_setup_args(argc, argv);
}

CAT_API char *cat_process_get_title(char* buffer, size_t size)
{
    int error;

    if (unlikely(!cat_process_args_resgitered)) {
        cat_update_last_error(CAT_EMISUSE, "Call process_setup_args() first");
        return NULL;
    }

    if (buffer == NULL) {
        if (size == 0) {
            size = CAT_PROCESS_TITLE_BUFFER_SIZE;
        }
        buffer = (char *) cat_malloc(size);
        if (unlikely(buffer == NULL)) {
            cat_update_last_error_of_syscall("Malloc for process title failed");
            return NULL;
        }
    }

    error = uv_get_process_title(buffer, size);

    if (unlikely(error != 0)) {
        cat_update_last_error_with_reason(error, "Process get title failed");
        return NULL;
    }

    return buffer;
}

CAT_API cat_bool_t cat_process_set_title(const char* title)
{
    int error;

    if (unlikely(!cat_process_args_resgitered)) {
        cat_update_last_error(CAT_EMISUSE, "Call process_setup_args() first");
        return cat_false;
    }

    error = uv_set_process_title(title);

    if (unlikely(error != 0)) {
        cat_update_last_error_with_reason(error, "Process set title failed");
        return cat_false;
    }

    return cat_true;
}
