#include <pwd.h>
#include <stddef.h>
#include <string.h>

// 获取密码

struct passwd * getpwnam(const char * name)
{
  struct passwd * ptr;

  setpwent();
  ptr = getpwent();
  while (ptr != NULL)
  {
    if (strcmp(name, ptr->pw_name) == 0)
    {
      break; // 找到匹配
    }

    ptr = getpwent();
  }
  endpwent();

  return (ptr);
}