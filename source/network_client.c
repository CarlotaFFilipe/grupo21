// Grupo21
// Carlota Filipe n51027
// Leonor Candeias n51057
// Mafalda Paço n53507

#include "client_stub.h"
#include "sdmessage.pb-c.h"
#include "network_client.h"
#include "client_stub-private.h"
#include "message-private.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

/* Esta função deve:
 * - Obter o endereço do servidor (struct sockaddr_in) a base da
 *   informação guardada na estrutura rtree;
 * - Estabelecer a ligação com o servidor;
 * - Guardar toda a informação necessária (e.g., descritor do socket)
 *   na estrutura rtree;
 * - Retornar 0 (OK) ou -1 (erro).
 */
int network_connect(struct rtree_t *rtree){
  struct sockaddr_in server;
  if ((rtree->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    free(rtree->hostname);
    //free(rtree->port); //porto eh int
    perror("Erro ao criar socket TCP");
    return -1;
  }
  //Preenche estrutura server para estabelecer conexão dando o endereco e o porto
  //rtree->server = malloc(sizeof ( struct sockaddr));
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(rtree->port));
  if (inet_pton(AF_INET, rtree->hostname, &server.sin_addr) < 1) {
    free(rtree->hostname);
    //free(rtree->port);
    printf("Erro ao converter IP\n");
    close(rtree->socket);
    return -1;
  }
  // Estabelece conexão com o servidor definido em server
  if (connect(rtree->socket,(struct sockaddr *)&server, sizeof(server)) < 0) {
    free(rtree->hostname);
    //free(rtree->port);
    perror("Erro ao conectar-se ao servidor");
    close(rtree->socket);
    return -1;
  }
  return 0;


}

/* Esta função deve:
 * - Obter o descritor da ligação (socket) da estrutura rtree_t;
 * - Serializar a mensagem contida em msg;
 * - Enviar a mensagem serializada para o servidor;
 * - Esperar a resposta do servidor;
 * - De-serializar a mensagem de resposta;
 * - Retornar a mensagem de-serializada ou NULL em caso de erro.
 */
struct message_t *network_send_receive(struct rtree_t * rtree,
                                       struct message_t *msg){

}

/* A função network_close() fecha a ligação estabelecida por
 * network_connect().
 */
int network_close(struct rtree_t * rtree){
  if(close(rtree->socket) == -1){
    free(rtree);
    return -1;
  }
  free(rtree);
  return 0;
}