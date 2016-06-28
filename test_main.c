
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "purity.h"
#include "ws_trie.h"
#include "test.h"

/**
   Testing for cache performance.  Making arbitrary-sized linked-lists,
   allocated in blocks of block_size contiguous nodes.
   The operation is the sum of numbers 0..num_ints-1
 */
void time_test(int block_size, int num_ints){

  // Allocate these guys
  int num_blocks = num_ints / block_size + 1;
  unsigned long total = 0;
  clock_t start_time;
  clock_t end_time;
  
  test_node *list = NULL;
  test_node *cur_node = NULL;
  
  for (int i = 0; i < num_ints; i++){
    test_node *temp = NULL;

    if (i % block_size == 0){
      temp = malloc(sizeof(test_node) * block_size);
    }
    else {
      temp = cur_node + 1;
    }

    if (!list){
      list = temp;
    }
    
    if (cur_node){
      cur_node->next = temp;
    }

    temp->val = i;
    temp->next = NULL;
    
    cur_node = temp;
  }

  start_time = clock();
  
  for (test_node *itr = list; itr != NULL; itr = itr->next){
    total += itr->val;
  }

  end_time = clock();

  printf("Time for block_size:%d, num_ints:%d, num_blocks:%d, clicks:%ld\n",
         block_size, num_ints, num_blocks, (end_time - start_time));
  
}

void trie_test(wchar_t *key, wchar_t *val){

  ws_trie *root = ws_trie_new(L'\0');
  ws_trie *find_fail = ws_trie_find(root, key);
  ws_trie *new_ret = ws_trie_add_string(root, key, val);
  ws_trie *find_succeed = ws_trie_find(root, key);

  printf("Results:\n\tfind_fail:%S\n\tnew_ret:%S\n\tfind_succeed:%S\n",
         find_fail ? (wchar_t *)find_fail->data : NULL,
         new_ret ? (wchar_t *)new_ret->data : NULL,
         find_succeed ? (wchar_t *)find_succeed->data : NULL);

  printf("Starting free...");
  ws_trie_free(root);
  printf("Successful!\n");
}

int main (int argc, char **argv){

  if (argc <= 1){
    printf("Usage: At least one parameter required.\n");
    return 1;
  }

  if (_stricmp(argv[1], "time") == 0){
    int block_size = 0;
    int num_ints = 0;

    if (argc < 4){
      printf("Usage: test_main time block_size num_ints\n");
      return 1;
    }

    block_size = atoi(argv[2]);
    num_ints = atoi(argv[3]);

    if (block_size <= 0 || num_ints <= 0){
      printf("Params block_size and num_ints must be positive.");
      return 1;
    }

    time_test(block_size, num_ints);
  }
  else if (_stricmp(argv[1], "trie") == 0){
    wchar_t *key = NULL;
    wchar_t *val = NULL;
    int key_len = 0;
    int val_len = 0;

    if (argc < 4){
      printf("Usage: test_main trie key val\n");
      return 1;
    }

    key_len = strlen(argv[2]);
    val_len = strlen(argv[3]);

    key = malloc((key_len + 1) * sizeof(wchar_t));
    val = malloc((val_len + 1) * sizeof(wchar_t));

    swprintf(key, key_len+1, L"%S", argv[2]);
    swprintf(val, val_len+1, L"%S", argv[3]);

    printf("Starting trie test with key:%S, val:%S\n", key, val);

    trie_test(key,val);

    free(key);
    free(val);
  }

  return 0;
}
