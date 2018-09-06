#include "apue.h"
#include <dirent.h>
#include <limits.h>

// 定义了一个函数类型的别名，它接受这些参数，返回int类型结果
typedef int Myfunc(const char *, const struct stat *, int);

// 这里实际上是声明了函数原型，它相当于 static int myfunc(const char *, const struct stat *, int);
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
  struct stat statbuf;
  struct dirent * dirp;
  DIR * dp;
  int ret, n;
  if (lstat(fullpath, &statbuf) < 0) // stat error
  {
    return (func(fullpath, &statbuf, FTW_NS));
  }
  if (S_ISDIR(statbuf.st_mode) == 0) // not a directory
  {
    return (func(fullpath, $statbuf, FTW_F));
  }
  /*
   * 它是一个目录。第一次对这个目录调用func()，它一次处理每个文件
   */
  ret = func(fullpath, &statbuf, FTW_D);
  if (ret != 0)
  {
    return (ret);
  }
  n = strlen(fullpath);
  if (n + NAME_MAX + 2 > pathlen) // 展开路径缓冲区
  {
    pathlen *= 2;
    fullpath = realloc(fullpath, pathlen);
    if (fullpath == NULL)
    {
      err_sys("realloc failed");
    }
  }

  fullpath[n++] = '/';
  fullpath[n] = 0;
  dp = opendir(fullpath);
  if (dp == NULL) // 不能读取目录
  {
    return (func(fullpath, $statbuf, FTW_DNR));
  }
  while ((dirp = readdir(dp)) != NULL)
  {
    if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
    {
      continue; // 忽略.和..
    }
    strcpy(&fullpath[n], dirp->d_name); // 追加"/"
    ret = dopath(func);
    if (ret != 0) // 
    {
      break; // 是时候走了
    }
  }
  fullpath[n - 1] = 0;
  if (closedir(dp) < 0)
  {
    err_ret("can't close directory %s", fullpath);
  }

  return (ret);
} // dopath .. end

static int myfunc(const char * pathname, const struct stat * statptr, int type)
{
  if (type == FTW_F)
  {
    int val = statptr->st_mode & S_IFMT;
    if (val == S_IFREG)
    {
      nreg++;
    }
    else if (val == S_IFBLK)
    {
      nblk++;
    }
    else if (val == S_IFCHR)
    {
      nchr++;
    }
    else if (val == S_FIFO)
    {
      nfifo++;
    }
    else if (val == S_IFLNK)
    {
      nslink++;
    }
    else if (val == S_IFSOCK)
    {
      nslink++;
    }
    else if (val == S_IFDIR)
    {
      err_dump("for S_IFDIR for %s", pathname);
    }
  }
  else if (type == FTW_D)
  {
    ndir++;
  }
  else if (type == FTW_DNR)
  {
    err_ret("cant't read directory %s", pathname);
  }
  else if (type == FTW_NS)
  {
    err_ret("stat error for %s", pathname);
  }
  else
  {
    err_dump("unknown type %d for pathname %s", type, pathname);
  }

  return 0;
}
