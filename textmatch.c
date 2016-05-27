#include <stdio.h>
#include <string.h>

#define str_num 40000

int main(){
  FILE *fp1,*fp2;
  char* str1[str_num],str2[100],str_box[str_num];
  char *locat;
  int count,i,len_s,ch;

  count = 0;
  i = 0;

  

  //入力文字列と探索文字列をファイルから開く
  //ファイルが無かったらエラー出力
  fp1 = fopen("zundoko_cpy.txt","r");
  if( fp1 == NULL) {
    printf("no such Inputfile\n");
    return -1;
  }.
  fp2 = fopen("search.txt","r");
  if( fp2 == NULL){ 
    printf("no such Searchfile\n");
    return -1;
  }

  //動的メモリ確保

  //探索文字列をファイルから読み込む
  fgets(str2,16,fp2);

  //入力文字列の最後まで1文字ずつ読み込む
  while((ch = fgetc(fp1)) != EOF){  
    //str_boxに読み込んだ文字を1文字ずつ格納
    str_box[i] = ch;
    
    //探索文字列が見つかったらカウントしてiと配列を初期化
    if(strstr(str_box,str2) != NULL){
      count++;
      i = 0;
      len_s = strlen(str_box);
      memset(str_box,'0',len_s); 
    }
    i++;
    //printf("%s\n\n",str_box);
  }

  //検索結果を表示
  printf("Found %d kiyoshi\n",count);

  //ファイルを閉じる
  fclose(fp1);
  fclose(fp2);
  return 0;
}
