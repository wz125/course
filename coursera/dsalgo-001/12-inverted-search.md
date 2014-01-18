
##描述
现在已经对一些文档求出了倒排索引，对于一些词得出了这些词在哪些文档中出现。   
要求对于倒排索引实现一些简单的查询，即查询某些词同时出现，或者有些词出现有些词不出现的文档有哪些。

##输入
第一行包含一个数N，1 <= N <= 1000，表示倒排索引表的数目。  
接下来N行，每行第一个数ci，表示这个词出现在了多少个文档中。接下来跟着ci个数，表示出现在的文档编号，编号不一定有序。1 <= ci <= 1000，文档编号为32位整数。  
接下来一行包含一个数M，1 <= M <= 100，表示查询的数目。  
接下来M行每行N个数，每个数表示这个词要不要出现，1表示出现，-1表示不出现，0表示无所谓。数据保证每行至少出现一个1。
##输出
共M行，每行对应一个查询。输出查询到的文档编号，按照编号升序输出。  
如果查不到任何文档，输出"NOT FOUND"。  
###样例输入
>3
>3 1 2 3
>1 2
>1 3
>3
>1 1 1
>1 -1 0
>1 -1 -1

###样例输出
NOT FOUND
1 3
1