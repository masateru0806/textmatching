#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define N 40000

int main(void)
{
  FILE *fp;
  FILE *fp2;
  int server_sockfd , client_sockfd ;
  int server_len , client_len ;
  struct sockaddr_in server_address ;
  struct sockaddr_in client_address ;
  unsigned long int file_size;
  unsigned char file_size_buff[sizeof(file_size)];
   const unsigned int file_size_const = sizeof(file_size);
   char moziretu[40000];
   char moziretu_re[20];

  char ch[1000];

  int size;
  fprintf(stderr, "server waiting\n");
  int i;

  server_sockfd = socket(AF_INET,SOCK_STREAM,0);
  server_address.sin_family = AF_INET ;
  server_address.sin_addr.s_addr = INADDR_ANY ;
  server_address.sin_port = htons(9734);
  server_len = sizeof(server_address);
  bind(server_sockfd , (struct sockaddr *)&server_address , server_len);
  listen(server_sockfd , 5);

  client_sockfd = accept(server_sockfd ,
			 (struct sockaddr *)&client_address , &client_len);
  read(client_sockfd ,file_size_buff, file_size_const);
  memcpy(&file_size, file_size_buff, file_size_const);
  fp= fopen("zundoko_cpy.txt","wb");
  /*test_result.txtに受信した文字を書き込み*/
  for (i=0; i<file_size; i+=1000){
    if(file_size < i+1000){
      read(client_sockfd, ch, file_size-i-1);
      memcpy(&moziretu[i], ch, file_size-i-1);
      break;
    }
    else{
      if (read(client_sockfd, ch, 1000)  <0 ){
	printf("受け取り失敗\n");
	break;
      };
      /* fwrite(moziretu,sizeof(char),file_size,fp); */
      /* memcpy(&moziretu[i], ch, file_size-i-1); */
      memcpy(&moziretu[i], ch, file_size-i);
      /* strcpy(&moziretu[i], ch); */
    }
  }
  fwrite(moziretu,sizeof(char),file_size,fp);
  /*テキストマッチング*/
   system("./a.out >> kiyoshi_num.txt");
  /*クライアントに返す*/
   fp2= fopen("kiyoshi_num.txt","rb");
   fread(moziretu_re,1,20,fp2);
   write(client_sockfd,moziretu_re,20); 
  fclose(fp);
  close(client_sockfd);   

  
}
