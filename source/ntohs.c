#include <arpa/inet.h>
#include <stdint.h>
#include <fcntl.h>
#include <dlfcn.h>
#include "ws_types.h"

typedef void *HANDLE;
typedef HANDLE SOCKET;

uint16_t
ntohs (uint16_t netshort)
{
  void *Ws2_32 = dlopen ("ws2_32.dll", RTLD_LAZY);
  fn_ntohs_t _ntohs = (fn_ntohs_t) dlsym (Ws2_32, "ntohs");
  uint16_t result = _ntohs (netshort);
  dlclose (Ws2_32);
  return result;
}
