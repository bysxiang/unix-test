#include "apue.h"
#include <dirent.h>
#include <limits.h>

// 定义了一个函数类型的别名，它接受这些参数，返回int类型结果
typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);
static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char * argv[])
{
  int ret;
  if (argc != 2)
  {
    err_quit("usage: ftw <strting-pathname>");
  }
  
  ret = myftw(argv[1], myfunc);
  ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
  if (ntot == 0)
  {
    ntot = 1; // 不能除以0，
  }
  printf("regular files = %7ld, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
  printf("directories = %7ld, %5.2f %%\n", ndir, ndir * 100.0 / ntot);
  printf("block special = %7ld, %5.2f %%\n", nblk, nblk * 100.0 / ntot);
  printf("char special = %7ld, %5.2f %%\n", nchar, nchar * 100.0 / ntot);
  printf("FIFOs = %7ld, %5.2f %%\n", nfifo, nfifo * 100.0 / ntot);
  printf("symbolic links = %7ld, %5.2f %%\n", nslink, nslink * 100.0 / ntot);
  printf("sockets = %7ld, %5.2f %%\n", nsock, nsock * 100.0 / ntot);

  exit(ret);
} // main .. end

// 通过层次结构下行，从pathname开始。为每个文件调用func()。

#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4

static char * fullpath; // 包括所有文件
static size_t pathlen;

// 我们返回func()返回的内容
static int myftw(char * pathname, Myfunc * func)
{
  fullpath = path_alloc(&pathlen);
  if (pathlen <= strlen(pathname))
  {
    pathlen = strlen(pathname) * 2;
    fullpath = realloc(fullpath, pathlen);
    if (fullpath == NULL)
    {
      err_sys("realloc failed");
    }
  }
  strcpy(fullpath, pathname);

  return (dopath(func));
}

// 通过层次结构，从fullpath开始。如果fullpath不是目录，我们lstat()它，调用func()，并返回目录
// ，我们递归自己为目录中每一个名称。
//
// 我们返回func()的返回值 
static int dopath(Myfunc * func)
{

}
