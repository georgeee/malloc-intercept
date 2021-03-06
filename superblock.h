#ifndef GHOARD_SUPERBLOCK
#define GHOARD_SUPERBLOCK

#include "constants.h"
#include <unistd.h>
#include <sys/mman.h>
#include <cstddef>


using namespace std;

namespace ghoard {
    const int SUPERBLOCK_MAGICK = 0xab45cd73;

    class heap;
    class superblock;

    struct large_block {
        size_t total_size;
        size_t indent;
        superblock * parent;
    };

    struct ordinary_block {
        size_t indent;
        superblock * parent;
    };

    struct empty_block {
        empty_block * next;
    };

    class superblock {
        friend class heap;
    private:
        heap * parent;
        int sz_group;
        size_t free_block_cnt;
        size_t initialized_cnt;
        superblock * fnext;
        superblock * fprev;
        superblock * szprev;
        superblock * sznext;
        empty_block * stack_head;
        int magick;
        size_t block_count;
        size_t block_with_meta_sz;
        void * next_uninitialized_block_start;
        void set_list_pointers_to_null();
        size_t get_block_count();
        void init();
        void * pop_free_block();
        void push_free_block(void * block);
        int get_fgroup_id();
        mutex_lock mutex;

    public:
        void check_magick();
        size_t get_block_with_meta_sz();
        bool has_free_blocks();
        bool is_empty();
        heap * get_parent();
        void lock();
        void unlock();
        int get_sz_group();
    };

    size_t get_size(void * ptr);
}
#endif
