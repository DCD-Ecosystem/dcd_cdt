#include <dcd/system.h>
#include <stddef.h>

void test_system( void ) {
   dcd_assert(0, NULL);
   dcd_assert_message(0, NULL, 0);
   dcd_assert_code(0, 0);
   dcd_exit(0);
   current_time();
   is_feature_activated(NULL);
   get_sender();
}
