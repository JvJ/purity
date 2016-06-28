
#include <stdlib.h>

#include "ws_trie.h"

ws_trie *ws_trie_new(wchar_t ch){

  ws_trie *ret = calloc(1, sizeof(ws_trie));

  ret->ch = ch;
  
  return ret;
}

ws_trie *ws_trie_add_string(ws_trie *trie, wchar_t *str, void *data){

  ws_trie *next = NULL;
  wchar_t first = str[0];
  
  next = trie->nx[first];

  if (!next){
    next = ws_trie_new(first);
    trie->nx[first] = next;
  }

  if (first != L'\0'){
    return ws_trie_add_string(next, str+1, data);
  }
  else {
    trie->data = data;
    return trie;
  }
}

ws_trie *ws_trie_find(ws_trie *trie, wchar_t *str){

  wchar_t first = str[0];
  ws_trie *next = trie->nx[first];

  if (first == L'\0'){
    return trie;
  }
  else if (next){
    return ws_trie_find(next, str+1);
  }
  else{
    return NULL;
  }
}

void ws_trie_free(ws_trie *trie){

  for (int i = 0; i < ASCII_CHARS; i++){
    if (trie->nx[i]){
      ws_trie_free(trie->nx[i]);
      trie->nx[i] = NULL;
    }
  }

  free(trie);
}
