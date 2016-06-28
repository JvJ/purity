
#ifndef WS_TRIE_H
#define WS_TRIE_H

#include <wchar.h>

#define ASCII_CHARS 128 //TODO: There has to be a better way...

typedef struct _ws_trie{
  wchar_t ch;
  void *data;
  struct _ws_trie *nx[ASCII_CHARS];
} ws_trie;

ws_trie *ws_trie_new(wchar_t ch);

ws_trie *ws_trie_add_string(ws_trie *trie, wchar_t *str, void *data);

ws_trie *ws_trie_find(ws_trie *trie, wchar_t *str);

void ws_trie_free(ws_trie *trie);

#endif
