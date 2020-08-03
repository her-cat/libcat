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

#include "test.h"

TEST(cat_process, get_id)
{
    ASSERT_GT(cat_process_get_id(), 0);
}

TEST(cat_process, get_parent_id)
{
    ASSERT_GT(cat_process_get_parent_id(), 0);
}

TEST(cat_process, title)
{
    const std::string custom_title = "cat_test";
    bool titled = cat_process_set_title(custom_title.c_str());
    char *process_title;

    process_title = cat_process_get_title(NULL, 0);
    ASSERT_NE(process_title, nullptr);
    DEFER(cat_free(process_title));

    if (titled) {
        ASSERT_EQ(custom_title, std::string(process_title));
    }
}

