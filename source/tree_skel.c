// Grupo21
// Carlota Filipe n51027
// Leonor Candeias n51057
// Mafalda Paço n53507

#include "sdmessage.pb-c.h"
//#include "tree_skel.h"
#include "message-private.h"
#include "entry.h"
#include "data.h"
#include "tree.h"
#include "serialization.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree_t *tree;

/* Inicia o skeleton da árvore.
 * O main() do servidor deve chamar esta função antes de poder usar a
 * função invoke(). 
 * Retorna 0 (OK) ou -1 (erro, por exemplo OUT OF MEMORY)
 */
int tree_skel_init(){
    tree=tree_create();
    if(tree == NULL)
        return -1;
    return 0;
}

/* Liberta toda a memória e recursos alocados pela função tree_skel_init.
 */
void tree_skel_destroy(){
    if(tree!=NULL)
        tree_destroy();

}

/* Executa uma operação na árvore (indicada pelo opcode contido em msg)
 * e utiliza a mesma estrutura message_t para devolver o resultado.
 * Retorna 0 (OK) ou -1 (erro, por exemplo, árvore nao incializada)
*/
int invoke(struct message_t *msg){
    if(table == NULL || msg == NULL)
        return -1;

    if(msg->opcode == 10){
        size_response_message(msg, tree_size(tree));
        return 0;
    }else if(msg->opcode== 20){
        if(tree_del(tree, msg->keys)==-1)
            msg->opcode = 99;
        else
            msg->opcode +=1;
        del_request_message(msg);
        return 0;
    }else if(msg->opcode == 30){
        struct data_t *data= tree_get(tree, msg->keys);
        free(msg->keys);
        //msg->keys= NULL;
        if(data == NULL){
            if(error_response_message(msg)==-1)
                return -1;
        }else{
            if(get_keys_response_message(msg, data)==-1)
                return -1;
        
            data_destroy(data);
        }
        return 0;
    }else if(msg->opcode == 40){
        struct entry_t *entry = buffer_to_entry(msg->data, msg->data_size);
        int put = tree_put(tree, entry->key, entry->value);
        if(put == -1){
            msg->opcode = 99;
        }else{
            msg->opcode += 1;
        }
        put_response_message(msg);
        entry_destroy(entry);
    }
}