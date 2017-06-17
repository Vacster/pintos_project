/*
pintos-mkdisk myfile.dsk --filesys-size=5
pintos --qemu --disk=myfile.dsk -- -f -q
pintos --qemu --disk=myfile.dsk -p ../../examples/project -a project -- -q
pintos --qemu --disk=myfile.dsk -p ../../examples/child_sort -a child_sort -- -q
pintos --qemu --disk=myfile.dsk -p ../../examples/matmult -a matmult -- -q
pintos -r --qemu --disk=myfile.dsk -- -q run project
*/

#include <stdio.h>
#include <syscall.h>

#define t_amount 3

struct t_info
  {
    int times_running;
    int times_waiting;
    int priority;
  };

void print_info(struct t_info * info, pid_t id, int tmp);

int fin[t_amount];

int
main (void)
{
  int tmp;
  pid_t t[t_amount];
  struct t_info info;

  info.times_waiting = 0;
  info.times_running = 0;
  info.priority = 0;

  t[0] = exec("child_sort");
  t[1] = exec("matmult");
  t[2] = exec("mkdir pollo");
  printf("Created threads num: %d, %d, and %d\n", t[0], t[1], t[2]);

  for(tmp = 0; tmp < t_amount; tmp++)
  {
    fin[tmp] = 1;
    mine(&info, t[tmp]);
    print_info(&info, t[tmp], tmp);
  }

  while(fin[0] || fin[1] || fin[2])
  {
    for(tmp = 0; tmp < t_amount; tmp++)
    {
      info.times_waiting = 0;
      info.times_running = 0;
      info.priority = 0;
      mine(&info, t[tmp]);
      print_info(&info, t[tmp], tmp);
    }
  }

  printf("fin\n");

  return 0;
}

void
print_info(struct t_info * info, pid_t id, int tmp)
{
  if(info->times_running == 0 && info->times_waiting == 0 && info->priority == 0)
  {
    //printf("Thread: %d already died or doesn't exist.\n", id);
    fin[tmp] = 0;
  }
  else
  {
    printf("Thread: %d\tT_Run: %d\tT_Wait: %d\tPriority: %d\n", id, info->times_running, info->times_waiting, info->priority);
  }
}
