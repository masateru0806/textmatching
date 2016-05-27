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
  int sockfd ;
  int len ;
  struct sockaddr_in address ;
  int result ;
  int size;
  char ch[N];//={'\0'};
  char moziretu_re[20];
  char moziretu[40000];
  unsigned long int file_size;
  unsigned char file_size_buff[sizeof(file_size)];
  int i;
  
  /**/
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  /*アドレス構造体に代入*/
  address.sin_family = AF_INET ;
  address.sin_addr.s_addr = inet_addr("160.12.172.5");//IPアドレスを32ビットに変換
  address.sin_port = htons(9734) ;
  /*アドレス構造体の長さ*/
  len = sizeof(address);

  result = connect(sockfd , (struct sockaddr *)&address , len);

  if ( result == -1 ) {
    perror("oops: client3");
    return(1);
  }
  /*zundoko.txtのオープン*/
  fp= fopen("zundoko_sample.txt","rb");
  /*zundoko.txtから文字を読み込み*/   
  /*サーバーへ送信*/
  
  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
   memcpy(file_size_buff, &file_size, sizeof(file_size));
   write(sockfd ,file_size_buff, sizeof(file_size));

  for (i=0; i<file_size; i+=1000){
      if(file_size < i+1000){
	fread(ch,1,file_size-i,fp);
	write(sockfd, ch, file_size-i);
      }
      else{
	fread(ch,1,1000,fp);
	write(sockfd, ch, 1000);
      }
    }

  /*サーバーから結果を受信*/
  read(sockfd,moziretu_re,sizeof(moziretu_re));
  printf("%s",moziretu_re);
  fclose(fp);
  close(sockfd);
  return(0);
}
