#include <stdio.h>
#include <map>
#include <vector>

int main()
{

 FILE *csv;
 csv = fopen("dados_venda_cluster_0.csv","r");
 
 std::vector<char *> client_codes;
 std::vector<char *> product_names;
 
 char client_buf[30];
 char product_buf[30];
 char buf1[59];
 char buf2[59];
 
 int i;
 
 for(i = 0; i < 10 ;i++)
 {
       
       if( i == 0 )
       {
         
         //fscanf(csv,"*30[^,],30[^,],30[^,],*49[^,]",client_buf,product_buf);
         
         
       } else
         {
             
             fscanf(csv,"%30[^,],%30[^,],%30[^,],%59[^\n]\n",buf1,client_buf,product_buf,buf2);
             printf("%s\n",product_buf);
             printf("%s\n",client_buf);
             setbuf(stdin,NULL);
             getchar();
             
         }
 }
 
 
 

 return 0;

}
